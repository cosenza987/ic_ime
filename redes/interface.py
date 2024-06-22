import random, pygame, sys, socket, asyncio, json
from pygame.locals import *
pygame.init()

white = (255, 255, 255)
yellow = (255, 255, 102)
grey = (211, 211, 211)
black = (0, 0, 0)
red = (255, 0, 0)
green = (0, 255, 0)
lightGreen = (153, 255, 204)

HOST = "172.15.5.172"
PORT = 8000
SPACING = 100

font = pygame.font.SysFont("Helvetica neue", 40)
bigFont = pygame.font.SysFont("Helvetica neue", 80)

youWin = bigFont.render("You Win!", True, green)
youLose = bigFont.render("You Lose!", True, red)
playAgain = bigFont.render("Play Again?", True, lightGreen)
Answer = bigFont.render("The answer is:", True, white)

class Message:

    def __init__(self):
        self.json_size = None
        self.header = None
        self.content_size = None
        self.content = None
        self.encoded_content = None
        self.type = None

    def read(self, server):
        self.json_size = int.from_bytes(server.recv(2), "big")
        self.header = json.loads((server.recv(self.json_size)).decode("utf-8"))
        self.content_size = self.header['content_size']
        self.type = self.header['response_type']
        if self.content_size != 0:
            self.encoded_content = server.recv(self.content_size)
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

    def send(self, server):
        server.send(self.json_size.to_bytes(2, "big"))
        server.send(self.header)
        server.send(self.encoded_content)

def draw(mask, guess, turns, window):
    renderList = ["", "", "", "", ""]
    spacing = 0
    guessColorCode = [grey, grey, grey, grey, grey]
    for x in range(0, 5):
        if mask[x] == '1':
            guessColorCode[x] = green
        if mask[x] == '2':
            guessColorCode[x] = yellow
    
    list(guess)

    for x in range(0, 5):
        renderList[x] = font.render(guess[x], True, black)
        pygame.draw.rect(window, guessColorCode[x], pygame.Rect(60 + spacing, 50 + (turns * SPACING), 50, 50))
        window.blit(renderList[x], (75 + spacing, 65 + (turns * SPACING)))
        spacing += SPACING
    
    if guessColorCode == [green, green, green, green, green]:
        return True
    else:
        return False

def wait():
    while True:
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            if event.type == KEYDOWN and event.key == K_RETURN:
                return

def main():
    st = Message()
    st.write('start', "")
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((HOST, PORT))
    st.send(client)
    rec = Message()
    rec.read(client)
    if rec.type != 'conn_acc':
        print("unable to establish connection")
        return
    height = 900
    width = 570
    FPS = 30
    clock = pygame.time.Clock()
    window = pygame.display.set_mode((width, height))
    window.fill(black)
    for x in range(0,5):
        for y in range(0,6):
            pygame.draw.rect(window, grey, pygame.Rect(60 + (x * SPACING), 50 + (y * SPACING), 50, 50), 2)
    pygame.display.set_caption("Wordle - Redes")
    turns = 0
    win = False
    guess = ""
    while True:
        for event in pygame.event.get():
            if event.type == QUIT:
                ending = Message()
                ending.write('end', "")
                ending.send(client)
                sys.exit()
            if event.type == pygame.KEYDOWN:
                guess += event.unicode.upper()
                if event.key == K_RETURN and win == True:
                    main()
                    break
                if event.key == K_RETURN and turns == 6:
                    main()
                    break
                if event.key == pygame.K_BACKSPACE:
                    guess = guess[:-1]
                if len(guess) > 5 or not event.unicode.isalpha():
                    guess = guess[:-1]
                if event.key == K_RETURN and len(guess) > 4:
                    toSend = Message()
                    toSend.write('guess', guess)
                    print('guess ' + guess)
                    toSend.send(client)
                    msg = Message()
                    msg.read(client)
                    print('msg type: ' + msg.type)
                    print('msg content: ' + msg.content)
                    if msg.type == 'invalid_guess':
                        guess = ""
                        window.fill(black, (0, 650, 500, 200))
                        continue
                    turns = int(msg.content[-1])
                    msg.content = msg.content[:-1]
                    win = draw(msg.content, guess, turns - 1, window)
                    print(turns)
                    guess = ""
                    window.fill(black, (0, 650, 500, 200))
        window.fill(black, (0, 650, 500, 200))
        renderGuess = font.render(guess, True, grey)
        window.blit(renderGuess, (240, 680))

        if win == True:
            #pygame.draw.rect(window, white, pygame.Rect(60, 50, 450, 450))
            window.blit(youWin, (150, 200))
            window.blit(playAgain, (120, 300))

        if turns == 6 and win != True:
            #pygame.draw.rect(window, white, pygame.Rect(60, 50, 450, 450))
            getAns = Message()
            getAns.write('lost', "")
            getAns.send(client)
            Ans = Message()
            Ans.read(client)
            window.blit(youLose, (150, 200))
            window.blit(playAgain, (120, 300))
            window.blit(Answer, (70, 650))
            window.blit(bigFont.render(Ans.content, True, white), (200, 720))
            pygame.display.update()
            wait()
            main()
            break

        pygame.display.update()
        clock.tick(FPS)



if __name__ == "__main__":
    main()