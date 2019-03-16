
#include "main.h"

 /*
 Joystick Axis
 1 = Right Stick Horizontal
 2 = Right Stick Vertical
 3 = Left Stick Vertical
 4 = Left Stick Horizontal
*/
void driveControl();
int puncherCrossed = 0;
int lastShot = 0;
int eightUPressed = 0;
int fiveUHeld = 0;
int fiveDHeld = 0;
int puncherAngle = 315;
int angleError = 0;
int angleChoice = 2;
int angler_integral = 0;
int lDCurrent = 0, rDCurrent = 0;
float power,turn;
int deadzone = 30;
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
		delay(25);
	}
}
/*const int driveMap[128] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		10,11,12,11,12,14,15,17,18,19,
		20,23,26,27,29,30,35,36,37,39,
		40,40,41,41,42,42,43,43,44,44,
		45,45,46,46,47,47,48,48,49,49,
		50,50,51,51,52,52,53,53,54,54,
		55,55,56,56,57,57,58,58,59,59,
		60,60,61,62,63,64,65,66,67,68,
		69,70,71,72,73,74,75,76,77,78,
		79,80,81,82,83,84,85,86,87,88,
		89,90,91,92,94,96,127,127};*/
const int driveMap[128] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
10,11,12,11,12,14,15,17,18,19,
20,22,23,24,25,26,27,28,30,31,
32,33,34,35,36,37,38,39,40,42,
43,44,45,46,47,48,49,48,49,49,
50,50,51,51,52,52,53,53,54,54,
55,55,56,56,57,57,58,58,59,59,
60,60,61,62,63,64,65,66,67,68,
69,70,71,72,73,74,75,76,77,78,
79,80,81,82,83,84,85,86,87,88,
89,90,91,92,94,96,127,127};

void driveControl(){
//	printf("Gyro Angle: %d\n\n",gyroGet(gyro));
//printf("Puncher: %d\n\n",encoderGet(puncher));
	//printf("Left Drive: %d Right Drive: %d \n\n",encoderGet(driveL),encoderGet(driveR));
	if(driveStyle == 0){
		if(abs(joystick(3)) > deadzone){
			lD = driveMap[abs(joystick(3))] * sgn(joystick(3));
		}
		else{
			lD = 0;
		}

		if(abs(joystick(2)) > deadzone){
			rD = driveMap[abs(joystick(2))] * sgn(joystick(2));
		}
		else{
			rD = 0;
		}
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
	}
}
void puncherControl(){
//	printf("Puncher Value: %d \n",encoderGet(puncher));
/*	if(button(8,'U')){
		setPuncher(127);
	}
	else{
		setPuncher(0);
	}*/
	if(button(8,'U')){
		setPuncher(127);
		puncherCrossed = 0;
		lastShot = millis();
	}
	else{
		if(encoderGet(puncher) % 360 < 300){
			if(millis() - lastShot > 700){
				if(puncherCrossed == 0){
					setPuncher(127);
				}
			}
			else{
				setPuncher(0);
			}
		}
		else{
			puncherCrossed = 1;
			setPuncher(0);
		}
	}
}
void intakeControl(){
	if(button(6,'U')){
		setIntake(127);
	}
	else if(button(6,'D')){
		setIntake(-127);
	}
	else{
		setIntake(0);
	}
}
int last_angler_error = 0;
double kI = 0.005;

void anglerControl(){
	//Bottom Value 215
	//Back Middle flag 1700

	//Max Pos 3200
	printf("Angler Pos: %d \n\n",analogRead(anglerE));
	if(button(5,'U') && fiveUHeld == 0){
		angleChoice++;
		if(angleChoice > 2){angleChoice = 2;}
		angler_integral = 0;
		last_angler_error = 0;
		fiveUHeld = 1;
	}
	else if(!button(5,'U')){
		fiveUHeld = 0;
	}
	if(button(5,'D') && fiveDHeld == 0){
		angleChoice--;
		fiveDHeld = 1;
		angler_integral = 0;
		last_angler_error = 0;

		if(angleChoice < 1){angleChoice = 1;}
	}
	else if(!button(5,'D')){
		fiveDHeld = 0;
	}
	if(button(7,'U')){
		angleChoice = 3;
	}
	if(button(7,'D')){
		angleChoice = 0;
	}
	/*if(button(5,'D')){
		angleChoice = 0;
		angler_integral = 0;
	}
	if(button(7,'L')){
		angleChoice = 1;
		angler_integral = 0;

	}
	if(button(7,'U')){
		angleChoice = 2;
		angler_integral = 0;

	}
	if(button(7,'R')){
		angleChoice = 3;
		angler_integral = 0;

	}*/
	if(angleChoice == 0){puncherAngle = 230; kI = 0; angler_integral = 0;}
	else{kI = 0.000;}
	if(angleChoice == 1){puncherAngle = 1780;}
	if(angleChoice == 2){puncherAngle = 2850;}
	if(angleChoice == 3){puncherAngle = 2600;}
	printf("Angler: %d",analogRead(anglerE));
	angleError = analogRead(anglerE) - puncherAngle;
//	if(abs(angleError) > 20){
	if(abs(angleError) > 40){
		setAngler(angleError * 0.09 + angler_integral * 0.001 + (angleError - last_angler_error) * 0.05);
	}
	else{
		setAngler(0);
	}
	//}
//	else{
//		setAngler(0);
	//}
	//	setAngler(0);
	last_angler_error = angleError;


}
