/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
 int button(int btnGroup, char dir){
   if(dir == 'L') dir = JOY_LEFT;
   if(dir == 'R') dir = JOY_RIGHT;
   if(dir == 'U') dir = JOY_UP;
   if(dir == 'D') dir = JOY_DOWN;
   //IF YOU PUT LEFT OR RIGHT FOR 5 or 6
   //Will return undefined
   return joystickGetDigital(1, btnGroup, dir);
 }

 int joystick(int axis){
   return joystickGetAnalog (1,axis);
 }
void setDrive(int l, int r){
	motorSet(2,l);
	motorSet(3,-l);
	motorSet(4,l);
  motorSet(5,-l);

	motorSet(6,r);
	motorSet(7,-r);
	motorSet(8,r);
	motorSet(9,-r);

}

void operatorControl() {
	int lD = 0;
	int rD = 0;
	while (1) {
		if(abs(joystick(3)) > 15){
			lD = joystick(3);
		}
		else{
			lD = 0;
		}

		if(abs(joystick(2)) > 15){
			rD = joystick(2);
		}
		else{
			rD = 0;
		}
    if(button(6,'U')){
      motorSet(10,127);
    }
    else if(button(6,'D')){
      motorSet(10,-127);
    }
    else{
      motorSet(10,0);
    }
		setDrive(-lD,-rD);
	}
}
