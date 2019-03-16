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

void autonomous() {
  initSensors();
}

void initSensors(){
  gyroReset(gyro);
  encoderReset(driveL);
  encoderReset(driveR);
  encoderReset(mogo);
}

void drive(int d,int speed){
  //Adjustables
  /*
  TBH Fuck Integral
  Just tune kP till its p good
  Then tune kD
  */
  float kP = 1;
  float kI = 0;
  float kD = 0;
  d = inchesToTicks(d);
  //Constant
  int previous_error = 0;
  int calc = 0;
  int integral = 0;
  int derivative = 0;
  int errorL = d - encoderGet(driveL);
  int errorR = d - encoderGet(driveR);
  int eD = (errorL + errorR)/2;
  int error = errorL - errorR;
  int left,right;


  if(d > 0){
    while(eD > 10){
      eD = (errorL + errorR)/2;
      error = errorL - errorR;

      integral += error;
      derivative = error - previous_error;
      previous_error = error;
      calc = error * kP + kI * integral + kD * derivative;

      left = speed + calc;
      right = speed - calc;
      setDrive(left,right);
      delay(50);
    }
  }
  else{
  }
}
