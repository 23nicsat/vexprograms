# VEX V5 Python Project
import sys
import vex
from vex import *

#region config
brain   = vex.Brain()
motor_1 = vex.Motor(vex.Ports.PORT1, vex.GearSetting.RATIO18_1, False)
motor_2 = vex.Motor(vex.Ports.PORT2, vex.GearSetting.RATIO18_1, False)
con     = vex.Controller(vex.ControllerType.PRIMARY)
#endregion config
motorspeed = -100

def forward():
    motor_1_power = motorspeed
    motor_2_power = motorspeed

#region actions
while True:
    motor_1_power = 0
    motor_2_power = 0

    if con.buttonUp.pressing():
	    motor_1_power = motorspeed
	    motor_2_power = motorspeed

    motor_2.spin(vex.DirectionType.FWD, motor_2_power)
    motor_1.spin(vex.DirectionType.REV, motor_1_power)
	

