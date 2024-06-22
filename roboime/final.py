#!/usr/bin/env python3

from ev3dev2.motor import MediumMotor, LargeMotor, OUTPUT_A, OUTPUT_B, OUTPUT_C, OUTPUT_D, MoveTank, SpeedDPS, SpeedRPS, SpeedRPM, MoveSteering
from ev3dev2.led import Leds
from ev3dev2.button import Button
from ev3dev2.sensor.lego import TouchSensor, UltrasonicSensor, ColorSensor, InfraredSensor
from ev3dev2.sensor import INPUT_1, INPUT_2, INPUT_3, INPUT_4
from time import sleep
import random

#definindo as variáveis

btn = Button()
dist_left = InfraredSensor(INPUT_2)
dist_right = InfraredSensor(INPUT_3)
#para o sensor infravermelho, use assim: dist_left.proximity
#ele te da a porcentagem da distancia entre o proprio e um objeto na frente
# 100% ~ 70 centimetros
color_left = ColorSensor(INPUT_1)
color_right = ColorSensor(INPUT_4)
#use assim: color_left.color
#os valores sao os seguintes: 0 -> sem cor, 1 -> preto, 6 -> branco
claw = MediumMotor(OUTPUT_A)
#on_for_rotations(speed, rotations, brake=True, block=True)
#on_for_degrees(speed, degrees, brake=True, block=True)
#on_to_position(speed, position, brake=True, block=True)
#on_for_seconds(speed, seconds, brake=True, block=True)
#on(speed, brake=True, block=False)
#off
wheel_pair = MoveTank(OUTPUT_B, OUTPUT_C)
#on_for_degrees(left_speed, right_speed, degrees, brake=True, block=True)
#on_for_rotations(left_speed, right_speed, rotations, brake=True, block=True)
#on_for_seconds(left_speed, right_speed, seconds, brake=True, block=True)
#on(left_speed, right_speed)
#off
steer_pair = MoveSteering(OUTPUT_B, OUTPUT_C)
#talvez este nao seja necessario


def saida():
    if color_left.color == 6:
        wheel_pair.on(left_speed=-10, right_speed=45)
        while color_right.color == 1:
            continue
        wheel_pair.off(brake=True)
        wheel_pair.on_for_rotations(left_speed=-70, right_speed=-70, rotations=2, brake=True, block=True)
        wheel_pair.on_for_rotations(left_speed=50, right_speed=-50, rotations=1, brake=False, block=True)
    if(color_right.color == 6):
        wheel_pair.on(left_speed=45, right_speed=-10)
        while color_left.color == 1:
            continue
        wheel_pair.off(brake=True)
        wheel_pair.on_for_rotations(left_speed=-70, right_speed=-70, rotations=2, brake=True, block=True)
        wheel_pair.on_for_rotations(left_speed=50, right_speed=-50, rotations=1, brake=False, block=True)


def ataque():
    # tem que testar para encontrar posicao direito
    claw.on_to_position(speed=100, position=0, brake=True, block=False)
    count = 0
    while True:
        wheel_pair.on(left_speed=70, right_speed=70)
        if color_left.color == 6 or color_right.color == 6:
            wheel_pair.off(brake=True)
            break
        if dist_left.proximity > 20 and dist_right.proximity > 20:
            wheel_pair.off()
            return  # definimos dps na main
        elif dist_left.proximity > 20:
            wheel_pair.off()
            wheel_pair.on(left_speed=70, right_speed=50)
            while dist_left.proximity > 20:
                continue
        elif dist_right.proximity > 20:
            wheel_pair.off()
            wheel_pair.on(left_speed=50, right_speed=70)
            while dist_right.proximity > 20:
                continue
        elif dist_left.proximity < 15 and dist_right.proximity < 15:
            claw.on_to_position(speed=70, position=180, brake=True, block=True)
            count = count + 1
        claw.on_to_posiiton(speed=70, position=0, brake=True, block=False)
    claw.on_to_position(speed=100, position=0, brake=True, block=False)
    if(count > 100000):
        return False
    saida()
    return True

def busca1():
    claw.on_to_position(speed=100, position=0, brake=True, block=False)
    if dist_right.proximity < 50 or dist_left.proximity < 50:
        wheel_pair.on_for_seconds(left_speed = 50, right_speed = 50, seconds = 0.3, brake = False, block = True)
        if dist_right.proximity < 15 or dist_left.proximity < 15:
            return False
        else:
            return True
    while dist_right.proximity and dist_left.proximity > 50:
        lado = random.randint(0, 1)
        if lado == 0:
            claw.on_for_degrees(speed=50, degrees=70)
            wheel_pair.on_for_seconds(left_speed=50, right_speed=70, seconds = 0.5, brake = False, block = True)
            busca2()
        elif lado == 1:
            claw.on_for_degrees(speed=50, degrees=-70)
            wheel_pair.on_for_seconds(left_speed=70, right_speed=50, seconds = 0.5, brake = False, block = True)
            busca2()

def busca2():
    wheel_pair.on(left_speed = 50, right_speed= -50)
    if dist_right.proximity < 15 or dist_left.proximity < 15:
        return False
    else:
        return True

def defesa():
    while True:
        t11 = dist_left.proximity
        t21 = dist_right.proximity
        sleep(1)
        t12 = dist_left.proximity
        t22 = dist_right.proximity
        if abs(t11 - t12) < 1 and abs(t21 - t22) < 1:
            wheel_pair.on_for_seconds(left_speed = -70, right_speed = -50, brake=True, block=True)
            if busca2():
                wheel_pair.on(left_speed=70, right_speed=70)
                break
        else:
            continue

#inicio
while color_left.color != 6 and color_right.color != 6:
    wheel_pair.on(left_speed = 50, right_speed = 50)

wheel_pair.off(brake = True)
wheel_pair.on_for_degrees(left_speed = -50, right_speed = -50, degrees = 90, brake = True, block = True)

#girar
wheel_pair.on_for_rotations(left_speed = 50, right_speed = -50, rotations = 1, brake = False, block = True)



while not btn.any():
    while busca1():
        if not ataque():
            defesa()