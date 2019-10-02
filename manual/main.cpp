import vex

#region config
brain   = vex.Brain()
motor_1 = vex.Motor(vex.Ports.PORT1, vex.GearSetting.RATIO18_1, False)
motor_2 = vex.Motor(vex.Ports.PORT2, vex.GearSetting.RATIO18_1, False)
con     = vex.Controller(vex.ControllerType.PRIMARY)
#endregion config

con.set_deadband(5)


#region actions
while True:
	motor_2_power = 0
	motor_1_power = 0
	
	# axis2: Linear Control
	power = con.axis2.position() * 1.5
	if power != 0:
		motor_2_power = -(power/2)
	
	# axis2: Linear Control
	power = con.axis3.position() * 1.5
	if power != 0:
		motor_1_power = -(power/2)
		
	# buttonUp: Forward
	if con.buttonUp.pressing():
		motor_1_power = -60
		motor_2_power = -60
	
	# buttonDown: Forward
	if con.buttonDown.pressing():
		motor_1_power = 60
		motor_2_power = 60
	
	motor_2.spin(vex.DirectionType.FWD, motor_2_power)
	motor_1.spin(vex.DirectionType.REV, motor_1_power)
	
#endregion actions
