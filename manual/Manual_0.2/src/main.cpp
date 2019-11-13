/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\s1                                               */
/*    Created:      Mon Nov 11 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// ArmMotor             motor         4               
// VisionSensor         vision        3               
// Drivetrain           drivetrain    1, 2            
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <iostream>
using namespace std;

using namespace vex;



int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  while(true){

    if (Controller1.ButtonX.pressing()){
      Brain.Screen.drawCircle(15,15,15);
      Drivetrain.driveFor(10, mm);
    }
    //Testing if i could get the robot to move if a pressed a button.

    VisionSensor.takeSnapshot(VisionSensor__ORANGE_CUBE);

    if()
  
    //Working on getting this to make the robot to move when it identifies an orange cube but does no work yet.


  }
  
}
