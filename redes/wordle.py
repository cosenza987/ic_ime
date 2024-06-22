import socket
import asyncio
import random
import json
import sys

class Message:

    def __init__(self):
        self.json_size = None
        self.header = None
        self.content_size = None
        self.content = None
        self.encoded_content = None
        self.type = None

    async def read(self, client, loop):
        self.json_size = int.from_bytes(await loop.sock_recv(client, 2), "big")
        self.header = json.loads((await loop.sock_recv(client, self.json_size)).decode("utf-8"))
        self.content_size = self.header['content_size']
        self.type = self.header['response_type']
        if self.content_size != 0:
            self.encoded_content = await loop.sock_recv(client, self.content_size)
            self.content = self.encoded_content.decode("utf-8")
        else:
            self.content = ""
            self.encoded_content = self.content.encode("utf-8")

    def write(self, type, content):
        self.type = type
        self.content = content
        self.encoded_content = self.content.encode("utf-8")
        self.content_size = len(self.encoded_content)
        self.header = json.dumps({'content_size': self.content_size, 'response_type': type}, ensure_ascii=False).encode("utf-8")
        self.json_size = len(self.header)

    async def send(self, client, loop):
        await loop.sock_sendall(client, self.json_size.to_bytes(2, "big"))
        await loop.sock_sendall(client, self.header)
        await loop.sock_sendall(client, self.content)


async def handle_guess(addr, guess):
    ans = answer[addr]
    msg = Message()
    guess = guess.lower()
    if (len(ans) != 5) or not (guess.isalpha()):
        msg.write("invalid_guess", "")
        return msg
    mask = "0" * 5
    cnt_ans, cnt_guess = dict(), dict()
    for i in range(5):
        cnt_ans[i] = cnt_ans.get(i, 0) + 1
    for i in range(5):
        if ans[i] == guess[i]:
            mask[i] = "1"
            cnt_guess[i] = cnt_guess.get(i,0) + 1
    for i in range(5):
        if cnt_guess.get(cnt_guess[i], 0) < cnt_ans.get(cnt_guess[i], 0):
            mask[i] = "2"
            cnt_guess[i] = cnt_guess.get(i, 0) + 1
    msg.write("valid_guess", mask)
    return msg


async def start_game(addr):
    answer[addr] = random.choice(answers)
    msg = Message()
    msg.write("conn_acc", "")
    return msg

async def end_game(addr):
    ans = answer.pop(addr)
    msg = Message()
    msg.write("game_ended", ans)
    return msg

async def run_server():

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    HOST = "172.15.5.172"
    PORT = 8000

    server.bind((HOST, PORT))

    loop = asyncio.get_event_loop()

    while True:

        server.listen(0)
        client, addr = await loop.sock_accept(server)
        loop.create_task(handle_client(client, addr))

async def handle_client(client, addr):

    loop = asyncio.get_event_loop()

    while True:

        msg = Message()
        await msg.read(client, loop)

        if msg.type == 'start': response = await start_game(addr)
        elif msg.type == 'guess': response = await handle_guess(addr, msg.content)
        elif msg.type == 'end': response = await end_game(addr)
        else:
            print("Error!")
            sys.exit(1)

        await response.send(client, loop)
        if msg.type == 'end': break

    client.close()

answer = dict()

word_file = open("wordlist.txt")
words = word_file.read().splitlines()

answer_file = open("answerlist.txt")
answers = answer_file.read().splitlines()

print(answers)

asyncio.run(run_server())