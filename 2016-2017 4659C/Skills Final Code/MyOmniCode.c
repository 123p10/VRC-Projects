#pragma config(Sensor, in7,    ClawRight,      sensorPotentiometer)
#pragma config(Sensor, in8,    ClawLeft,       sensorPotentiometer)
#pragma config(Sensor, dgtl1,  LDrive,         sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  RDrive,         sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  Lift,           sensorQuadEncoder)
#pragma config(Motor,  port1,           ClawL,         tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           LD,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           LD2,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           LiftR2,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           LiftR,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           LiftL,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           LiftL2,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           RD2,           tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           RD,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          ClawR,         tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*			MOTORS			*/
//ClawL Left Claw
//FL Front Left Drive
//BL Back Left Drive
//LiftR2 Right Side of Lift with 2 Motors through a Y-Splitter. They should be the two that are oriented the same.
//LiftR Right Side of Lift with 1 Motor
//LiftL Left Side of Lift with 1 Motor
//LiftL2 Left Side of Lift with 2 Motors through a Y-Splitter.They should be the two that are oriented the same.
//FR Front Right Drive
//BR Back Right Drive
//ClawR Right Claw


/**/
/*Kush test the turning code. Make it better and make sure the values work*/
/**/

int auton = 2;

/*
0 = grab cube and throw over middle(Timed)
1 = autonomous that descores preload(Timed)
2 = skillsAuton(PID)
3 = Left Side Auton for Competition(PID)
4 = Right Side Auton for Competition(PID)
*/


#pragma platform(VEX2)]
#pragma competitionControl(Competition)
#include "Vex_Competition_Includes.c"


//Turns on and off debugstreams
bool isDebug = true;
//Deadzone for controller
int deadzone = 15;
//Speed of lift should ussually be 127 though because less speed = less torque
int liftSens = 127;

//Good Functions
void skillsAuton();
void competitionAuton();
void goodCompetitionAutonL();
void goodCompetitionAutonR();
void score(int liftH,int clawsL,int clawsR,int openClawH,int dist,int speed,int liftDist);
void turn(int distL,int distR);
void debugStreamSensors();
void moveClaws(int speed,int distL,int distR);
void moveLiftPID(short speed,short dist);
void drivePID(int speed,int dist);

//Bad Functions(But do not delete)
void rDriveMove(int speed);
void lDriveMove(int speed);
void crapAuton();
void moveLift(int speed);
void moveForward(int speedL,int speedR);
void moveClaw(int speed);

void pre_auton()
{

	bStopTasksBetweenModes = true;
	SensorValue[Lift] = 0;
	SensorValue[LDrive] = 0;
	SensorValue[RDrive] = 0;

}

task autonomous()
{
	if(auton == 0){
		competitionAuton();
	}
	else if(auton == 1){
		crapAuton();
	}
	else if(auton == 2){
		skillsAuton();
	}
	else if(auton == 3){
		goodCompetitionAutonL();
	}
	else if(auton == 4){
		goodCompetitionAutonR();
	}




}

void goodCompetitionAutonL(){
	moveClaws(127,1040,2000);
	drivePID(100,100);
	turn(100,-100);
	drivePID(100,150);
	moveClaws(-127,300,800);
	turn(100,-100);
	score(700,1140,1680,500,-100,-100,0);
	moveLiftPID(-127,0);
	drivePID(100,150);
	moveClaws(-127,300,800);
	score(700,1140,1680,600,-200,-100,-100);
}
void goodCompetitionAutonR(){
	moveClaws(127,1040,2000);
	drivePID(100,100);
	turn(-100,100);
	drivePID(100,150);
	moveClaws(-127,300,800);
	turn(-100,100);
	score(700,1140,1680,500,-100,-100,0);
	moveLiftPID(-127,0);
	drivePID(100,150);
	moveClaws(-127,300,800)
	score(700,1140,1680,600,-200,-100,-100);

}
void skillsAuton(){


	//First Preload
	drivePID(-100,-180);
	moveClaws(127,1040,2000);
	drivePID(100,20);
	wait1Msec(750);
	moveClaws(-127,300,800);
	moveClaw(-50);
	score(700,1140,1680,600,-300,-100,-200);

	//Second Preload
	moveLiftPID(-127,0);
	drivePID(100,350);
	wait1Msec(950);
	moveClaws(-127,150,550);
	moveClaw(-15);
	score(700,1140,1680,500,-300,-100,-200);
	moveLiftPID(-127,0);
	/*Working Leave Here*/
	/*Working Leave Here*/

	/*Testing Code work with Values*/
	/*Testing Code work with Values*/

	//Move to middle Cube
	drivePID(100,100);
	turn(100,-100);
	drivePID(100,100);
	moveClaws(-127,150,550);
	drivePID(100,100);
	turn(-100,100);
	score(700,1140,1680,500,-100,-100,0);

	//Cube in front of far fence
	moveLiftPID(-127,0);
	drivePID(100,350);
	moveClaws(-127,150,550);
	score(700,1140,1680,500,-300,-100,-200);

}
void score(int liftH,int clawsL,int clawsR,int openClawH,int dist,int speed,int liftDist){
	//Variables

	//Lift H is maximum height of the lift should be ~700
	//ClawsL is the maximum distance the clawL should open
	//ClawsR is the maximum distance the clawR should open
	//openClawH is when the lift reaches this point open claw
	//dist is how far the drive should move
	//speed is how fast the drive moves
	//liftDist is the point at which the lift starts to lift



	int goal = (28.7 * dist) / 10;
	SensorValue[LDrive] = 0;
	SensorValue[RDrive] = 0;
	int kp = 5;
	int error;
	int output;
	int it = 100;
	int ml = 3;
	int mr = 3;
	while(liftH > SensorValue[Lift]){
	if(speed > 0 && dist > 0){
		motor[LD] = speed;
		motor[LD2] = speed;
		motor[RD] = speed ;
		motor[RD2] = speed;
		for(int i = 0; i < 10;i++){
			motor[RD]  += 1;
			motor[RD2] += 1;
			wait1Msec(25);
		}
		if(SensorValue[LDrive] < goal){
			error = SensorValue[LDrive] - SensorValue[RDrive];
			output = error * kp;
			motor[LD] = speed + ml * error;
			motor[LD2] = speed + ml * error;
			motor[RD] = output + mr * error;
			motor[RD2] = output + mr * error;

			wait1Msec(it);

		}
	}
		else{
		ml = 1;
		mr = 1;
			motor[LD] = speed;
		motor[LD2] = speed;
		motor[RD] = speed ;
		motor[RD2] = speed;
		for(int i = 0; i < 20;i++){
	//		motor[RD]  += 1;
	//		motor[RD2] += 1;
			wait1Msec(10);
		}
		if(SensorValue[LDrive] > goal){
			error = SensorValue[LDrive] - SensorValue[RDrive];
			output = error * kp;
			motor[LD] = speed + ml * error;
			motor[LD2] = speed + ml * error;
			motor[RD] = output + mr * error;
			motor[RD2] = output + mr * error;

			wait1Msec(it);

		}
		}
		if(SensorValue[Lift] >= openClawH){
			if(SensorValue[ClawLeft] < clawsL){
				motor[ClawL] = 127;
			}
			else{
				motor[ClawL] = 0;
			}
			if(SensorValue[ClawLeft] < clawsR){
				motor[ClawR] = 127;
			}
			else{
				motor[ClawR] = 0;
			}

		}
		else{
			motor[ClawL] = 0;
			motor[ClawR] = 0;
		}

		if((SensorValue[Lift] * 28.7) / 10 >= liftDist){
			moveLift(127);
		}
	}
	if(SensorValue[Lift] > 650){
		moveLift(-15)
	}
	else{
		moveLift(15);
	}
	motor[ClawL] = 0;
	motor[ClawR] = 0;
}

void competitionAuton(){
	moveClaw(127);
	wait1Msec(1500);
	moveClaw(0);
	moveForward(127,127);
	wait1Msec(1500);
	moveForward(0,0);
	moveClaw(-127);
	wait1Msec(1000);
	moveClaw(-15);
	moveForward(-127,127);
	wait1Msec(1300);
	moveForward(0,0);
	moveForward(-127,-127);
	wait1Msec(1500);
	moveForward(0,0);
	moveLift(127);
	wait1Msec(1950);
	if(SensorValue[Lift] < 650){
		moveLift(15);
	}
	else{
		moveLift(-15);
	}
	wait1Msec(200);
	moveClaw(127);
	wait1Msec(500);
	moveClaw(0);

}
void crapAuton(){
	moveForward(127,127);
	wait1Msec(2000);
	moveForward(0,0);
}




void moveClaw(int speed){
	motor[ClawL] = speed;
	motor[ClawR] = speed;
}

void moveClaws(int speed,int distL,int distR){
	int oldDistR[11];
	int oldDistL[11];
	oldDistR[10] = 50;
	oldDistL[10] = 50;
	motor[ClawL] = speed;
	motor[ClawR] = speed;
	wait1Msec(200);
	if(distL < SensorValue[ClawLeft] && distR < SensorValue[ClawRight]){
		while(distL < SensorValue[ClawLeft] || distR < SensorValue[ClawRight]){
			motor[ClawL] = speed;
			motor[ClawR] = speed;
			if(abs(distL - oldDistL[10]) < 10){
				break;
			}

			oldDistL[10] = oldDistL[9];
			oldDistR[10] = oldDistR[9];
			oldDistL[9] = oldDistL[8];
			oldDistR[9] = oldDistR[8];
			oldDistL[8] = oldDistL[7];
			oldDistR[8] = oldDistR[7];
			oldDistL[7] = oldDistL[6];
			oldDistR[7] = oldDistR[6];
			oldDistL[6] = oldDistL[5];
			oldDistR[6] = oldDistR[5];
			oldDistL[5] = oldDistL[4];
			oldDistR[5] = oldDistR[4];
			oldDistL[4] = oldDistL[3];
			oldDistR[4] = oldDistR[3];
			oldDistL[3] = oldDistL[2];
			oldDistR[3] = oldDistR[2];
			oldDistL[2] = oldDistL[1];
			oldDistR[2] = oldDistR[1];
			oldDistL[1] = oldDistL[0];
			oldDistR[1] = oldDistR[0];
			oldDistL[0] = distL;
			oldDistR[0] = distR;
		}
	}
	else{
		while(distL > SensorValue[ClawLeft] || distR > SensorValue[ClawRight]){
			motor[ClawL] = speed;
			motor[ClawR] = speed;

			if(abs(distL - oldDistL[10]) < 10){
				break;
			}

			oldDistL[10] = oldDistL[9];
			oldDistR[10] = oldDistR[9];
			oldDistL[9] = oldDistL[8];
			oldDistR[9] = oldDistR[8];
			oldDistL[8] = oldDistL[7];
			oldDistR[8] = oldDistR[7];
			oldDistL[7] = oldDistL[6];
			oldDistR[7] = oldDistR[6];
			oldDistL[6] = oldDistL[5];
			oldDistR[6] = oldDistR[5];
			oldDistL[5] = oldDistL[4];
			oldDistR[5] = oldDistR[4];
			oldDistL[4] = oldDistL[3];
			oldDistR[4] = oldDistR[3];
			oldDistL[3] = oldDistL[2];
			oldDistR[3] = oldDistR[2];
			oldDistL[2] = oldDistL[1];
			oldDistR[2] = oldDistR[1];
			oldDistL[1] = oldDistL[0];
			oldDistR[1] = oldDistR[0];
			oldDistL[0] = distL;
			oldDistR[0] = distR;

		}
	}
 motor[ClawL] = 0;
 motor[ClawR] = 0;

}



void debugStreamSensors(){
	wait1Msec(1000);
	writeDebugStreamLine("Battery Level is: %d", nImmediateBatteryLevel);
}
task usercontrol()
{

	while (true)
	{
		if(isDebug){
			debugStreamSensors();
		}




		//Drive Code
		if(abs(vexRT[Ch3]) > deadzone){
			motor[LD] = vexRT[Ch3];
			motor[LD2] = vexRT[Ch3];
		}
		else{
			motor[LD] = 0;
			motor[LD2] = 0;
		}
		if(abs(vexRT[Ch2]) > deadzone){
			motor[RD] = vexRT[Ch2];
			motor[RD2] = vexRT[Ch2];
		}
		else{
			motor[RD] = 0;
			motor[RD2] = 0;
		}


		//Claw Code
		if(vexRT[Btn6D]){

			if(SensorValue[ClawLeft] < 1550){
				motor[ClawL] = 127;
			}
			else{
				motor[ClawL] = 0;
			}
			if(SensorValue[ClawRight] < 2000){
				motor[ClawR] = 127;
			}
			else{
				motor[ClawR] = 0;
			}
		}
		if(vexRT[Btn6U]){
			if(SensorValue[ClawLeft] > 350){
				motor[ClawL] = -127;
			}
			else{
				motor[ClawL] = 0;
			}

		if(SensorValue[ClawRight] > 800){
				motor[ClawR] = -127;
		}
		else{
			motor[ClawR] = 0;
		}

		}
		if(!vexRT[Btn6U] && !vexRT[Btn6D]){
			motor[ClawL] = 0;
			motor[ClawR] = 0;
		}
		if(vexRT[Btn8L]){
			drivePID(80,430);
		}
		if(vexRT[Btn8U]){
			moveClaws(127,1550,2270);
		}

		//Lift Code
		if(vexRT[Btn5U]){
			motor[LiftL] = liftSens;
			motor[LiftL2] = liftSens;
			motor[LiftR] = liftSens;
			motor[LiftR2] = liftSens;
		}
		else if(vexRT[Btn5D]){
			motor[LiftL] = -liftSens;
			motor[LiftL2] = -liftSens;
			motor[LiftR] = -liftSens;
			motor[LiftR2] = -liftSens;
		}

		else{
			if(SensorValue[Lift] < 650){
				motor[LiftL] = 15;
				motor[LiftL2] = 15;
				motor[LiftR] = 15;
				motor[LiftR2] = 15;
			}
			else{
				motor[LiftL] = -15;
				motor[LiftL2] = -15;
				motor[LiftR] = -15;
				motor[LiftR2] = -15;
			}
		}
	}
}

void moveLift(int speed){
	motor[LiftL] = speed;
	motor[LiftL2] = speed;
	motor[LiftR] = speed;
	motor[LiftR2] = speed;
}
void lDriveMove(int speed){
	motor[LD] = speed;
	motor[LD2] = speed;
}
void rDriveMove(int speed){
	motor[RD] = speed;
	motor[RD2] = speed;
}

void moveClaw(int speed){
	motor[ClawL] = speed;
	motor[ClawR] = speed;
}

void moveForward(int speedL,int speedR){
	lDriveMove(speedL);
	rDriveMove(speedR);
}



void moveLiftPID(short speed,short dist){
	if(SensorValue[Lift] < dist){
		while(SensorValue[Lift] < dist){
			moveLift(speed);
		}
	}
	else{
		while(SensorValue[Lift] > dist){
			moveLift(speed);
		}
	}


	if(SensorValue[Lift] > 650){
		moveLift(-15);
	}
	else{
		moveLift(15);
	}
}
void drivePID(int speed,int dist){
	//PI * diameter of wheel which is 4*3.14
	// 360 / by the solution(12.56)
	int goal = (28.7 * dist) / 10;

	SensorValue[LDrive] = 0;
	SensorValue[RDrive] = 0;
	int kp = 5;
	int error;
	int output;
	int it = 100;

	int ml = 1;
	int mr = 6;
	//LDrive is master
	if(speed > 0 && dist > 0){
		motor[LD] = speed;
		motor[LD2] = speed;
		motor[RD] = speed ;
		motor[RD2] = speed;
		for(int i = 0; i < 10;i++){
			motor[RD]  += 7;
			motor[RD2] += 7;
			wait1Msec(25);
		}
		while(SensorValue[LDrive] < goal){
			error = SensorValue[LDrive] - SensorValue[RDrive];
			output = error * kp;
			motor[LD] = speed + ml * error;
			motor[LD2] = speed + ml * error;
			motor[RD] = output + mr * error;
			motor[RD2] = output + mr * error;

			wait1Msec(it);

		}
	}
	else{
		ml = 1;
		mr = 3;
			motor[LD] = speed;
		motor[LD2] = speed;
		motor[RD] = speed ;
		motor[RD2] = speed;
		for(int i = 0; i < 20;i++){
			motor[RD]  += 1;
			motor[RD2] += 1;
			wait1Msec(10);
		}
		while(SensorValue[LDrive] > goal){
			error = SensorValue[LDrive] - SensorValue[RDrive];
			output = error * kp;
			motor[LD] = speed + ml * error;
			motor[LD2] = speed + ml * error;
			motor[RD] = output + mr * error;
			motor[RD2] = output + mr * error;

			wait1Msec(it);

		}
	}
	//RDrive is slave

	motor[LD] = 0;
	motor[LD2] = 0;
	motor[RD] = 0;
	motor[RD2] = 0;
}

void turn(int distL,int distR){
	SensorValue[LDrive] = 0;
	SensorValue[RDrive] = 0;
	while(abs(SensorValue[LDrive]) < abs(distL)){
		if(distL < 0){
			motor[LD] = -127;
			motor[LD2] = -127
		}
		else{
			motor[LD] = 127;
			motor[LD2] = 127;
		}
		if(distR < 0){
			motor[RD] = -127;
			motor[RD2] = -127;
		}
		else{
			motor[RD] = 127;
			motor[RD2] = 127;
 		}
	}
	motor[LD] = 0;
	motor[LD2] = 0;
	motor[RD] = 0;
	motor[RD2] = 0;
}
