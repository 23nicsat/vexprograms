#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor ArmMotor = motor(PORT4, ratio18_1, false);
/*vex-vision-config:begin*/
signature VisionSensor__SIG_1 = signature (1, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature VisionSensor__SIG_2 = signature (2, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature VisionSensor__SIG_3 = signature (3, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature VisionSensor__SIG_4 = signature (4, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature VisionSensor__SIG_5 = signature (5, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature VisionSensor__SIG_6 = signature (6, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature VisionSensor__SIG_7 = signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vision VisionSensor = vision (PORT3, 50, VisionSensor__SIG_1, VisionSensor__SIG_2, VisionSensor__SIG_3, VisionSensor__SIG_4, VisionSensor__SIG_5, VisionSensor__SIG_6, VisionSensor__SIG_7);
/*vex-vision-config:end*/
motor LeftDriveSmart = motor(PORT1, ratio18_1, false);
motor RightDriveSmart = motor(PORT2, ratio18_1, true);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 219.44, 1900, 130, mm, 1);

// VEXcode generated functions
// define variables used for controlling motors based on controller inputs
bool Controller1RightShoulderControlMotorsStopped = true;
bool DrivetrainNeedsToBeStopped_Controller1 = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_callback_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    // calculate the drivetrain motor velocities from the controller joystick axies
    // left = Axis3 + Axis4
    // right = Axis3 - Axis4
    int drivetrainLeftSideSpeed = Controller1.Axis3.position() + Controller1.Axis4.position();
    int drivetrainRightSideSpeed = Controller1.Axis3.position() - Controller1.Axis4.position();
    // check if the values are inside of the deadband range
    if (abs(drivetrainLeftSideSpeed) < 5 && abs(drivetrainRightSideSpeed) < 5) {
      // check if the motors have already been stopped
      if (DrivetrainNeedsToBeStopped_Controller1) {
        // stop the drive motors
        LeftDriveSmart.stop();
        RightDriveSmart.stop();
        // tell the code that the motors have been stopped
        DrivetrainNeedsToBeStopped_Controller1 = false;
      }
    } else {
      // reset the toggle so that the deadband code knows to stop the motors next time the input is in the deadband range
      DrivetrainNeedsToBeStopped_Controller1 = true;
    }
    // only tell the left drive motor to spin if the values are not in the deadband range
    if (DrivetrainNeedsToBeStopped_Controller1) {
      LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
      LeftDriveSmart.spin(forward);
    }
    // only tell the right drive motor to spin if the values are not in the deadband range
    if (DrivetrainNeedsToBeStopped_Controller1) {
      RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
      RightDriveSmart.spin(forward);
    }
    // check the ButtonR1/ButtonR2 status to control ArmMotor
    if (Controller1.ButtonR1.pressing()) {
      ArmMotor.spin(forward);
      Controller1RightShoulderControlMotorsStopped = false;
    } else if (Controller1.ButtonR2.pressing()) {
      ArmMotor.spin(reverse);
      Controller1RightShoulderControlMotorsStopped = false;
    } else if (!Controller1RightShoulderControlMotorsStopped) {
      ArmMotor.stop();
      // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
      Controller1RightShoulderControlMotorsStopped = true;
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_callback_Controller1);
}