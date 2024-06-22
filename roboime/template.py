#!/usr/bin/env python3

from ev3dev2.motor import MediumMotor, LargeMotor, OUTPUT_A, OUTPUT_B, OUTPUT_C, MoveTank, SpeedDPS, SpeedRPS, SpeedRPM, MoveSteering
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