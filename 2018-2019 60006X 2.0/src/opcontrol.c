
#include "main.h"

 /*
 Joystick Axis
 1 = Right Stick Horizontal
 2 = Right Stick Vertical
 3 = Left Stick Vertical
 4 = Left Stick Horizontal
*/
void driveControl();

int lDCurrent = 0, rDCurrent = 0;
float power,turn;
int deadzone = 25;
float multiplier = (5.0/5.0);
const int driveStyle = 0;
int lD,rD;
//0 = tank
//1 = arcade
bool auton = false;
void operatorControl() {
	while (1) {
		driveControl();
		puncherControl();
		anglerControl();
		intakeControl();
		delay(20);
	}
}

void driveControl(){
	if(driveStyle == 0){
		if(abs(joystick(3)) > deadzone){
			lD = joystick(3) * multiplier;
		}
		else{
			lD = 0;
		}

		if(abs(joystick(2)) > deadzone){
			rD = joystick(2) * multiplier;
		}
		else{
			rD = 0;
		}
		//lDriveGoal = lD;
		//rDriveGoal = rD;

		setDrive(lD,rD);

	}
	if(driveStyle == 1){
		if(abs(joystick(3)) > deadzone){
			power = joystick(3) * multiplier;
		}
		else{
			power = 0;
		}

		if(abs(joystick(4)) > deadzone){
			turn = joystick(4) * multiplier;
		}
		else{
			turn = 0;
		}
		setDrive(power + turn, power - turn);
	//lDriveGoal = power + turn;
//	rDriveGoal = power - turn;

	}
}
void puncherControl(){
	printf("Puncher Value: %d",encoderGet(puncher));
	if(button(8,'U')){
		setPuncher(127);
	}
	else{
		setPuncher(0);
	}
}
void intakeControl(){
	if(button(5,'U')){
		setIntake(127);
	}
	else if(button(5,'D')){
		setIntake(-127);
	}
	else{
		setIntake(0);
	}
}
void anglerControl(){
	printf("Angler Pos: %d",analogRead(anglerE));
	int expected = 0;
	if(button(6,'U')){
		setAngler(65);
	}
	else if(button(6,'D')){
		setAngler(-65);
	}
	else{
		setAngler(0);
	}
}
