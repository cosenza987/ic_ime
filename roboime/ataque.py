#!/usr/bin/env python3

from ev3dev2.motor import MediumMotor, LargeMotor, OUTPUT_A, OUTPUT_B, OUTPUT_C, OUTPUT_D, MoveTank, SpeedDPS, SpeedRPS, SpeedRPM, MoveSteering
from ev3dev2.led import Leds
from ev3dev2.button import Button 
from ev3dev2.sensor.lego import TouchSensor, UltrasonicSensor, ColorSensor, InfraredSensor
from ev3dev2.sensor import INPUT_1, INPUT_2, INPUT_3, INPUT_4
from time import sleep

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
        tank_pair.on(left_speed = -10, right_speed = 45)
        while color_right.color == 1:
            continue
        tank_pair.off(brake = True)
        tank_pair.on_for_rotations(left_speed = -70, right_speed = -70, rotations = 2, brake = True, block = True)
        tank_pair.on_for_rotations(left_speed = 50, right_speed = -50, rotations = 1, brake = False, block = True)
    if(color_right.color == 6):
        tank_pair.on(left_speed = 45, right_speed = -10)
        while color_left.color == 1:
            continue
        tank_pair.off(brake = True)
        tank_pair.on_for_rotations(left_speed = -70, right_speed = -70, rotations = 2, brake = True, block = True)
        tank_pair.on_for_rotations(left_speed = 50, right_speed = -50, rotations = 1, brake = False, block = True)


def ataque():
    claw.on_to_position(speed = 100, position = 0, brake = True, block = False) #tem que testar para encontrar posicao direito
    while True:
        tank_pair.on(left_speed = 70, right_speed = 70)
        if color_left.color == 6 or color_right.color == 6:
            tank_pair.off(brake = True)
            break
        if dist_left.proximity > 20 and dist_right.proximity > 20:
            tank_pair.off()
            return #definimos dps na main
        elif dist_left.proximity > 20:
            tank_pair.off()
            tank_pair.on(left_speed = 70, right_speed = 50)
            while dist_left.proximity > 20:
                continue
        elif dist_right.proximity > 20:
            tank_pair.off()
            tank_pair.on(left_speed = 50, right_speed = 70)
            while dist_right.proximity > 20:
                continue
        elif dist_left.proximity < 15 and dist_right.proximity < 15:
            claw.on_to_position(speed = 70, position = 180, brake = True, block = True)
        claw.on_to_posiiton(speed = 70, position = 0, brake = True, block = False)
    claw.on_to_position(speed = 100, position = 0, brake = True, block = False)
    saida()