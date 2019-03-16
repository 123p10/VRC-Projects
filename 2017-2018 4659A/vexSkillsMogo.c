#pragma config(Sensor, dgtl3,  Mogo,           sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  DriveL,         sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  DriveR,         sensorQuadEncoder)
#pragma config(Motor,  port2,           DriveR1,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           DriveR2,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           DriveR3,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           MogoR,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           MogoL,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           DriveL3,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           DriveL2,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           DriveL1,       tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX2)
#pragma competitionControl(Competition)
#include "Vex_Competition_Includes.c"

int leftDrivePIDError = 0;
int leftDrivePIDLastError = 0;
int leftDrivePIDDerivative = 0;
int rightDrivePIDError = 0;
int rightDrivePIDLastError = 0;
int rightDrivePIDDerivative = 0;
bool driveStatus = false;
int moveCount = 0;
int PIDtimer = 0;
void setLDrive(int speed);
void setRDrive(int speed);
void setMogo(int speed);
void drivePID(int dist,int m);
bool turnDriveAsync(int rotation);
void mMogo(int ud);
void turn(int x, int s);
void pre_auton()
{
	SensorValue[DriveL] = 0;
	SensorValue[DriveR] = 0;
	SensorValue[Mogo] = 0;
  bStopTasksBetweenModes = true;
}
task autonomous()
{
	SensorValue[DriveL] = 0;
	SensorValue[DriveR] = 0;
	SensorValue[Mogo] = 0;
		drivePID(900,1);
		wait1Msec(750);
		drivePID(400,1);
		mMogo(1);
		wait1Msec(500);
		drivePID(-800,2);
		//while(!turnDriveAsync(200));
		turn(350,1);
		wait1Msec(500);
		drivePID(405,0);
		mMogo(0);
		wait1Msec(750);
		drivePID(-250,0);
		mMogo(1);
		//drivePid
	 //wait1Msec()
		turn(125,0);
		wait1Msec(500);
		drivePID(-100,0);
		mMogo(0);
		drivePID(450,0);
		wait1Msec(200);
		drivePID(-300,2);
		//turn(160, 1);

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
  		wait1Msec(25);
  }
}
void turn(int x, int s){
	SensorValue[DriveL] = 0;
	SensorValue[DriveR] = 0;
	int speed = 80;
	int kP = 1;
	while(true){
		if(s == 0){
			int eL = x - SensorValue[DriveL];
			int eR = x + SensorValue[DriveR];
			if(el > 10){
				setLDrive(speed);
			}
			else{
				setLDrive(0);
			}
			if(eR > 10){
				setRDrive(-speed);
			}
			else{
				setRDrive(0);
			}
			if(eL < 10 && eR < 10){

				break;

			}
		}
		if(s == 1){

			int eR = x - SensorValue[DriveR];
			int eL = x + SensorValue[DriveL];
			if(eL > 10){
				setLDrive(-speed);
			}
			else{
				setLDrive(0);
			}
			if(eR > 10){
				setRDrive(speed);
			}
			else{
				setRDrive(0);
			}
			if(eR < 10 && eL < 10){
				break;
			}
		}
		wait1Msec(75);
	}
	setLDrive(0);
	setRDrive(0);
}

void drivePID(int dist,int m){

	SensorValue[DriveL] = 0;
	SensorValue[DriveR] = 0;
	int eL = dist - SensorValue[DriveL];
	int eR = dist - SensorValue[DriveR];
	float kP = -0.15;
	if(dist < 0){
		kP = kP * -1;
	}
	int defS = 80;
	int e = eL - eR;
	int mB = 95;
	int mH = 20;
	while(true){
		if(dist > 0){
			eL = dist - SensorValue[DriveL];
			eR = dist - SensorValue[DriveR];
			e = eL - eR;
			setLDrive(defS + e * kP);
			setRDrive(defS - e * kP);
			if(eL < 10){
				break;
			}
		}
		else{
			//dist = abs(dist);
			eL = dist - SensorValue[DriveL];
			eR = dist - SensorValue[DriveR];
			e = eL - eR;
			setLDrive(-(defS + e * kP));
			setRDrive(-(defS - e * kP));
			if(eL > 10){
				break;
			}

		}
		//m == 1 == Drop
		//m == 2 == Lift
		if(m == 1){
			if(SensorValue[Mogo] < mB){
				setMogo(127);
			}
			else{
				setMogo(0);
			}
		}
		if(m == 2){
			if(SensorValue[Mogo] > mH){
				setMogo(-127);
			}
			else{
				setMogo(0);
			}
		}
		wait1Msec(25);
	}

	setLDrive(0);
	setRDrive(0);
	SensorValue[DriveL] = 0;
	SensorValue[DriveR] = 0;
}
bool turnDriveAsync(int rotation) {
		SensorValue[DriveL] = 0;
		SensorValue[DriveR] = 0;
	if (moveCount == 0) {
		leftDrivePIDLastError = rightDrivePIDError = leftDrivePIDDerivative = rightDrivePIDDerivative = 0;
		moveCount = 1;
		PIDtimer = 0;
	}
	driveStatus = false;

	leftDrivePIDError = rotation - SensorValue[DriveL];
	rightDrivePIDError = -1*rotation - SensorValue[DriveR];

	leftDrivePIDDerivative = leftDrivePIDError - leftDrivePIDLastError;
	rightDrivePIDDerivative = rightDrivePIDError - rightDrivePIDLastError;

	motor[DriveL1] = motor[DriveL2] = motor[DriveL3] = 2*leftDrivePIDError + 2*leftDrivePIDDerivative;
	motor[DriveR1] = motor[DriveR2] = motor[DriveR3] = 2*rightDrivePIDError + 2*rightDrivePIDDerivative;

	leftDrivePIDLastError = leftDrivePIDError;
	rightDrivePIDLastError = rightDrivePIDError;

	if (abs(rotation - SensorValue[DriveL]) < 5 || abs(-1*rotation - SensorValue[DriveR]) < 5) {
		PIDtimer++;
	}

	if (PIDtimer >= 1500) {
		moveCount = 0;
		driveStatus = true;
		motor[DriveL1] = motor[DriveL2] = motor[DriveL3] = 0;
		motor[DriveR1] = motor[DriveR2] = motor[DriveR3] = 0;
	}

	return driveStatus;
}
void mMogo(int ud){
	while(true){
		//ud == 0 == down
		//ud == 1 == up

		if(ud == 0){
			if(SensorValue[Mogo] < 90){
				setMogo(127);
			}
			else{
				setMogo(0);
				break;
			}
		}
		if(ud == 1){
			if(SensorValue[Mogo] > 15){
				setMogo(-127);
			}
			else{
				setMogo(0);
				break;
			}
		}
	}
	setMogo(0);
}
void setLDrive(int speed){
	motor[DriveL1] = speed;
	motor[DriveL2] = speed;
	motor[DriveL3] = speed;
}

void setRDrive(int speed){
	motor[DriveR1] = speed;
	motor[DriveR2] = speed;
	motor[DriveR3] = speed;
}
void setMogo(int speed){
	motor[mogoL] = speed;
	motor[mogoR] = speed;
}
