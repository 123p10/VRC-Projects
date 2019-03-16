/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost, the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */

 //This File will be used for auton functions
 //Create a new file for each route
//driveForward 0.001


  //Negative is left
  //Positive is right

/*
New Auton Runs
  0 = red back auton, descore, flip cap, mount platform
  4 = blue back auton
  5 = red front auton
*/
void autonomous() {
//  TaskHandle flywheeltask = taskRunLoop(flyWheelSpeedManager,100);
  const int auton = 6;
  //flyWheelTargetSpeed = 0;
  initSensors();
  if(auton == 0){
  }

}

void initSensors(){
  encoderReset(driveL);
  encoderReset(driveR);
  encoderReset(puncher);
}




//Do not use this I left this here to help me think
