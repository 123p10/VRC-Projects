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

 //Constants for driving
 //0.75 is a good kP for both drive methods
 //turnEncoder(40) does approximately a 180

/*
New Auton Runs

1 red back tile left high flag, descore cap, platform attempt middle flag
2 blue back tile right high flag descore cap platform attempt middle flag
3 blue back tile right high flag descore cap platform attempt
4 red front tile left high flag, descore cap middle flag platform attempt
5 blue front tile right high flag, descore cap middle flag platform attempt

6 skills

7 red back middle both flags platform cap
9 red front top flag middle flag
*/

#define AUTON 15

void autonomous() {
  initSensors();
  TaskHandle anglerTask = taskRunLoop(anglerAuton, 25);
  TaskHandle puncherTask = taskRunLoop(puncherAuton, 25);
  initSensors();
  if(AUTON == 0){
  }
  if(AUTON == 1){
    autonShoot(250);
    setAnglerAutonHeight(2250);
    wait_for(800);
    autonShoot(360+80);
    wait_for(700);
    turnGyro(-86,1,5000);
    wait_for(300);
    setIntake(127);
    setAnglerAutonHeight(315);
    driveForward(cmToTicks(105),0.75,0,0);
    autonShoot(360+250);
    wait_for(1500);
    driveBackward(cmToTicks(17), 0.8, 4000);
    wait_for(400);
    setIntake(0);
    turnGyro(90,1,3000);
    wait_for(300);
    driveForward(cmToTicks(55),0.75,0,0);
    wait_for(500);
    setAnglerAutonHeight(1500);
    turnGyro(-8,1,1250);
    setIntake(127);
    wait_for(450);
    setIntake(0);
    autonShoot(360*2+200);
    wait_for(1200);
  }
  if(AUTON == 2){
    setAnglerAutonHeight(2600);
    autonShoot(200);
    wait_for(700);
    autonShoot(360+80);
    wait_for(700);
    turnGyro(80,1,5000);
    wait_for(300);
    setIntake(127);
    setAnglerAutonHeight(315);
    autonShoot(360+250);
    driveForward(cmToTicks(90),0.75,0,0);
    wait_for(1500);
    setIntake(0);
    driveBackward(cmToTicks(7), 0.8, 4000);
    wait_for(400);
    turnGyro(-90,1,3000);
    wait_for(300);
    driveForward(cmToTicks(63),0.75,0,0);
    wait_for(500);
    setAnglerAutonHeight(1450);
    turnGyro(10,1,3000);
    wait_for(300);
    setIntake(127);
    wait_for(750);
    setIntake(0);
    wait_for(500);
    autonShoot(360*2+80);
    wait_for(1000);
  }
  if(AUTON == 3){
    setAnglerAutonHeight(2300);
    wait_for(700);
    autonShoot(360+80);
    wait_for(700);
    turnGyro(-90,1,5000);
    wait_for(300);
    setIntake(127);
    setAnglerAutonHeight(315);
    driveForward(cmToTicks(105),0.75,0,0);
    wait_for(1500);
    setIntake(0);
    driveBackward(cmToTicks(15), 0.8, 4000);
    wait_for(400);
    turnGyro(90,1,3000);
    wait_for(300);
    driveForward(cmToTicks(60),0.75,0,0);
    wait_for(500);
    turnGyro(-90,1,4000);
    wait_for(750);
    driveForward(cmToTicks(50),0.75,0,0);
  }
  if(AUTON == 4){
    setAnglerAutonHeight(2850);
    autonShoot(250);
    wait_for(300);
    autonShoot(360+200);
    wait_for(650);
    setIntake(127);
    setAnglerAutonHeight(315);
    turnGyro(-90,1,3500);
    wait_for(250);
    driveForward(cmToTicks(105), 0.75, 0, 0);
    wait_for(1100);
    setIntake(0);
    driveBackward(cmToTicks(93), 0.75, 5000);
    wait_for(300);
    turnGyro(76,1,4500);
    wait_for(300);
    setAnglerAutonHeight(1700);
    wait_for(350);
    autonShoot(360*2+200);
    wait_for(700);
    turnGyro(5,1,800);
    driveBackward(cmToTicks(40), 0.75, 2500);
    wait_for(200);
    turnGyro(-90,1,3500);
    wait_for(200);
    driveForward(cmToTicks(80), 0.75, 0, 0);
  }
  if(AUTON == 5){
    setAnglerAutonHeight(2850);
    autonShoot(250);
    wait_for(300);
    autonShoot(360+200);
    wait_for(650);
    setIntake(127);
    setAnglerAutonHeight(315);
    turnGyro(75,1,3500);
    wait_for(250);
    driveForward(cmToTicks(93), 0.75, 0, 0);
    wait_for(1100);
    driveBackward(cmToTicks(83), 0.75, 5000);
    wait_for(300);
    turnGyro(-92,1,4500);
    setIntake(0);
    wait_for(300);
    setAnglerAutonHeight(1700);
    wait_for(350);
    autonShoot(360*2+200);
    wait_for(700);
    driveBackward(cmToTicks(30), 0.75, 2500);
    wait_for(200);
    turnGyro(90,1,3500);
    wait_for(200);
    driveForward(cmToTicks(65), 0.75, 0, 0);
  }
  if(AUTON == 6){
    setAnglerAutonHeight(3100);
    autonShoot(250);
    wait_for(300);
    autonShoot(360+200);
    wait_for(650);
    setIntake(127);
    setAnglerAutonHeight(315);
    turnGyro(-90,1,3500);
    wait_for(250);
    driveForward(cmToTicks(105), 0.75, 0, 0);
    wait_for(1500);
    driveBackward(cmToTicks(45), 0.75, 5000);
    wait_for(250);
    turnGyro(78,1,2500);
    wait_for(250);
    setIntake(-100);
    driveForward(cmToTicks(45),0.75,0,0);
    wait_for(500);
    setIntake(0);
    driveBackward(cmToTicks(20), 0.8, 3000);
    wait_for(400);
    turnGyro(20,1,3500);
    wait_for(200);
    setAnglerAutonHeight(2300);
    wait_for(600);
    //Shoot left middle
    autonShoot(360*2+200);
    wait_for(700);
    turnGyro(-90,0,2500);
    setAnglerAutonHeight(315);
    wait_for(250);
    driveForward(cmToTicks(55),0.8,0,0);
    wait_for(200);
    turnGyro(79,1,2500);
    wait_for(200);
    //Hit bottom middle
    driveForward(cmToTicks(58),0.8,0,0);
    wait_for(200);
    driveBackward(cmToTicks(33), 0.8, 2500);
    wait_for(200);
    turnGyro(-95,1,2500);
    setIntake(-127);
    wait_for(200);
    driveForward(cmToTicks(115),0.8,0,0);
    wait_for(200);
    setIntake(0);
    //driveBackward(cmToTicks(2), 0.8, 1000);
    wait_for(200);
    turnGyro(82,1,2000);
    wait_for(200);
    driveForward(cmToTicks(50),0.75,0,0);
    wait_for(200);
    driveBackward(cmToTicks(100),0.8,2500);
    wait_for(200);
    setIntake(127);
    turnGyro(80,1,2500);
    wait_for(200);
    driveForward(cmToTicks(35),0.8,0,0);
    wait_for(1200);
    driveBackward(cmToTicks(45),0.8,2500);
    wait_for(200);
    turnGyro(-100,1,2500);
    wait_for(200);
    setAnglerAutonHeight(3200);
    wait_for(500);
    setIntake(0);
    //shoot right middle
    autonShoot(360*3+200);
    wait_for(800);
    driveBackward(cmToTicks(60),0.8,2500);
    wait_for(200);
    turnGyro(80,1,2500);
    setIntake(127);
    wait_for(200);
    driveForward(cmToTicks(105),0.8,0,0);
    wait_for(1200);
    driveBackward(cmToTicks(115), 0.8, 3500);
    wait_for(200);
    turnGyro(-80,1,2500);
    setAnglerAutonHeight(2200);
    wait_for(600);
    autonShoot(360*4+200);
    wait_for(800);
    driveForward(cmToTicks(40),0.8,0,0);
    wait_for(200);
    turnGyro(80,1,2500);
    wait_for(250);
    driveForward(cmToTicks(130),0.8,0,0);
  }
  if(AUTON == 7){
    autonShoot(250);
    setAnglerAutonHeight(2500);

    turnGyro(-26,1,2500);
    wait_for(1100);
    autonShoot(360+80);
    wait_for(800);
//    setRDrive(-50);
    turnGyro(-61,1,5000);
    wait_for(800);
  //  setDrive(0,0);
    setIntake(127);
    setAnglerAutonHeight(315);
    driveForward(cmToTicks(102),0.75,0,0);
    autonShoot(360+250);
    wait_for(1500);
    driveBackward(cmToTicks(12), 0.8, 4000);
    wait_for(400);
    turnGyro(83,1,3000);
    wait_for(300);
    setIntake(0);
    driveForward(cmToTicks(55),0.75,0,0);
    wait_for(500);
    setAnglerAutonHeight(1400);
    turnGyro(-11,1,800);
    setIntake(127);
    wait_for(450);
    setIntake(0);
    autonShoot(360*2+200);
    wait_for(1200);
  }
  if(AUTON == 8){
    setAnglerAutonHeight(1780);
    wait_for(5000);
    setAnglerAutonHeight(2400);
    wait_for(4000);
    setAnglerAutonHeight(350);
    wait_for(4000);
  }
  if(AUTON == 9){
    setAnglerAutonHeight(2850);
    autonShoot(250);
    wait_for(650);
    autonShoot(360+200);
    wait_for(650);
    setIntake(127);
    setAnglerAutonHeight(315);
    turnGyro(-90,1,3500);
    wait_for(250);
    driveForward(cmToTicks(94), 0.75, 0, 0);
    wait_for(1100);
    driveBackward(cmToTicks(60), 0.75, 5000);
    wait_for(200);
    setIntake(0);
    setAnglerAutonHeight(1700);
    turnGyro(90,1,3500);
    wait_for(200);
    autonShoot(360*2+200);
    wait_for(600);
    turnGyro(-30,1,2500);
    wait_for(200);
    setIntake(-127);
    driveForward(cmToTicks(62),0.8,0,0);
    wait_for(300);
    driveBackward(cmToTicks(22),0.8,3500);
    wait_for(250);
    turnGyro(55,1,3500);
    wait_for(200);
    driveForward(cmToTicks(40),0.8,0,0);
    wait_for(200);
    turnGyro(-40,1,3500);
    wait_for(200);
    setIntake(0);
    driveForward(cmToTicks(33),0.8,0,0);
    wait_for(200);
    driveBackward(cmToTicks(15),0.8,2500);
  }
  if(AUTON == 10){
    setAnglerAutonHeight(1780);
    wait_for(5000);
    setAnglerAutonHeight(2400);
    wait_for(4000);
    setAnglerAutonHeight(350);
    wait_for(4000);
  }
  if(AUTON == 11){
    setAnglerAutonHeight(2850);
    autonShoot(250);
    wait_for(650);
    autonShoot(360+200);
    wait_for(650);
    setIntake(127);
    setAnglerAutonHeight(315);
    turnGyro(-90,1,3500);
    wait_for(250);
    driveForward(cmToTicks(105), 0.75, 0, 0);
    wait_for(1100);
    driveBackward(cmToTicks(71), 0.75, 5000);
    wait_for(200);
    setIntake(0);
    setAnglerAutonHeight(1700);
    turnGyro(90,1,3500);
    wait_for(200);
    autonShoot(360*2+200);
    wait_for(600);
    turnGyro(-32,1,2500);
    wait_for(200);
    setIntake(-127);
    driveForward(cmToTicks(62),0.8,0,0);
    wait_for(300);
    driveBackward(cmToTicks(62),0.8,3500);
    wait_for(250);
    turnGyro(29,1,2500);
    wait_for(200);
    driveBackward(cmToTicks(112),0.8,4500);
    wait_for(250);
    turnGyro(-97,1,2500);
    setAnglerAutonHeight(360);
    setIntake(127);
    wait_for(250);
    driveForward(cmToTicks(105),0.8,0,0);
    wait_for(250);
    driveBackward(cmToTicks(115),0.8,4500);
    wait_for(250);
    driveForward(cmToTicks(10),0.8,0,0);
    wait_for(250);
    setAnglerAutonHeight(2000);
    turnGyro(56,1,3500);
    wait_for(450);
    autonShoot(360*3+200);
    wait_for(800);
    turnGyro(30,1,2500);
    wait_for(250);
    driveForward(cmToTicks(30),0.8,0,0);
    wait_for(250);
    turnGyro(-95,1,4500);
     wait_for(250);
    driveForward(cmToTicks(142),0.8,0,0);



  }
  if(AUTON == 12){
    setAnglerAutonHeight(2850);
    autonShoot(250);
    wait_for(650);
    autonShoot(360+200);
    wait_for(650);
    setIntake(127);
    setAnglerAutonHeight(315);
    turnGyro(-90,1,3500);
    wait_for(250);
    driveForward(cmToTicks(105), 0.75, 0, 0);
    wait_for(1100);
    driveBackward(cmToTicks(71), 0.75, 5000);
    wait_for(200);
    setIntake(0);
    setAnglerAutonHeight(1700);
    turnGyro(90,1,3500);
    wait_for(200);
    autonShoot(360*2+200);
    wait_for(600);
    turnGyro(-32,1,2500);
    wait_for(200);
    setIntake(-127);
    driveForward(cmToTicks(62),0.8,0,0);
    wait_for(300);
    driveBackward(cmToTicks(20),0.8,3500);
    wait_for(200);
    turnGyro(-30,1,2500);
    wait_for(200);
    driveForward(cmToTicks(60),0.8,0,0);

  }
  if(AUTON == 13){
    setAnglerAutonHeight(2850);
    autonShoot(250);
    wait_for(300);
    autonShoot(360+200);
    wait_for(650);
    setIntake(127);
    setAnglerAutonHeight(315);
    turnGyro(75,1,3500);
    wait_for(250);
    driveForward(cmToTicks(93), 0.75, 0, 0);
    wait_for(1100);
    driveBackward(cmToTicks(83), 0.75, 5000);
    wait_for(300);
    turnGyro(-92,1,4500);
    setIntake(0);
    wait_for(300);
    setAnglerAutonHeight(1700);
    wait_for(350);
    autonShoot(360*2+200);
    wait_for(700);
    driveForward(cmToTicks(60),0.8,0,0);
  }
  if(AUTON == 14){
    setAnglerAutonHeight(2850);
    autonShoot(250);
    wait_for(850);
    autonShoot(360+200);
    wait_for(650);
    setIntake(127);
    setAnglerAutonHeight(315);
    turnGyro(78,1,3500);
    wait_for(250);
    driveForward(cmToTicks(91), 0.75, 0, 0);
    wait_for(1100);
    driveBackward(cmToTicks(67), 0.75, 5000);
    wait_for(200);
    setIntake(0);
    setAnglerAutonHeight(1700);
    turnGyro(-90,1,3500);
    wait_for(200);
    autonShoot(360*2+200);
    wait_for(600);
    turnGyro(20,1,2500);
    wait_for(200);
    setIntake(-127);
    driveForward(cmToTicks(92),0.8,0,0);
    wait_for(300);
  }
  if(AUTON == 15){
    autonShoot(250);
    setAnglerAutonHeight(2500);
    turnGyro(21,1,2500);
    wait_for(700);
    autonShoot(360+250);
    wait_for(700);
    turnGyro(80,0,5000);
    wait_for(300);
    setIntake(127);
    setAnglerAutonHeight(315);
    autonShoot(360+250);
    driveForward(cmToTicks(90),0.75,0,0);
    wait_for(1500);
    setIntake(0);
    driveBackward(cmToTicks(7), 0.8, 4000);
    wait_for(400);
    turnGyro(-90,1,3000);
    wait_for(300);
    driveForward(cmToTicks(63),0.75,0,0);
    wait_for(500);
    setAnglerAutonHeight(1400);
    turnGyro(9,1,800);
    wait_for(300);
    setIntake(127);
    wait_for(750);
    setIntake(0);
    wait_for(500);
    autonShoot(360*2+80);
    wait_for(1000);

  }

  taskDelete(anglerTask);
  taskDelete(puncherTask);
}

void initSensors(){
  encoderReset(driveL);
  encoderReset(driveR);
  encoderReset(puncher);
//  gyroReset(gyro);
}




//Do not use this I left this here to help me think
