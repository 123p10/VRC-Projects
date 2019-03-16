#pragma config(Motor,  port1,           mogoL,         tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           driveLB,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           driveLM,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           driveLF,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           driveRF,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           driveRM,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           driveRB,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          mogoR,         tmotorVex393_HBridge, openLoop, reversed)

#pragma platform(VEX2)

#pragma competitionControl(Competition)

#include "Vex_Competition_Includes.c"

void setLDrive(int speed);
void setRDrive(int speed);
void setMogo(int speed);
void pre_auton()
{
  bStopTasksBetweenModes = true;
}

task autonomous()
{
}
task usercontrol()
{
  while (true)
  {

  	if(abs(vexRT[Ch3]) > 15){
  		setLDrive(vexRT[Ch3]);
  	}
  	else{
  		setLDrive(0);
  	}

  	 if(abs(vexRT[Ch2]) > 15){
  		setRDrive(vexRT[Ch2]);
  	}
  	else{
  		setRDrive(0);
  	}
  	if(vexRT[Btn6U]){
  		setMogo(127);
  	}
  	else if(vexRT[Btn6D]){
  		setMogo(-127);
  	}
  	else{
  		setMogo(0);
  	}
  }
}


void setMogo(int speed){
	motor[mogoL] = speed;
	motor[mogoR] = speed;
}
void setLDrive(int speed){
	motor[driveLB] = speed;
	motor[driveLM] = speed;

	motor[driveLF] = speed;
}

void setRDrive(int speed){
	motor[driveRB] = speed;
	motor[driveRM] = speed;

	motor[driveRF] = speed;
}
