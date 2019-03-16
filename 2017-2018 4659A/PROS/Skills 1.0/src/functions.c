#include "main.h"

/*
 OK for all declarations of motors USE THESE FUNCTIONS
 This is because motors cannot be reversed using pros so we must set them to negative in these functions
*/

void setLDrive(int speed){
  motorSet(LDF, speed);
  motorSet(LDM, -speed);
  motorSet(LDB, speed);
}
void setRDrive(int speed){
  motorSet(RDF, -speed);
  motorSet(RDM, speed);
  motorSet(RDB, -speed);
}
void setMogo(int speed){
  motorSet(ML, speed);
  motorSet(MR, -speed);
}
void setDrive(int left,int right){
  setLDrive(left);
  setRDrive(right);
}

/*
Joystick Axis
1 = Right Stick Horizontal
2 = Right Stick Vertical
3 = Left Stick Vertical
4 = Left Stick Horizontal
*/
int joystick(int axis){
  return joystickGetAnalog (1,axis);
}



int button(int btnGroup, char dir){
  if(dir == 'L') dir = JOY_LEFT;
  if(dir == 'R') dir = JOY_RIGHT;
  if(dir == 'U') dir = JOY_UP;
  if(dir == 'D') dir = JOY_DOWN;
  //IF YOU PUT LEFT OR RIGHT FOR 5 or 6
  //Will return undefined
  return joystickGetDigital(1, btnGroup, dir);
}

int inchesToTicks(int inches){
  return (360 / (4 * 3.14159)) * inches;
}
int cmToTicks(int cm){
  return (360/(10.16*3.14159)) * cm;
}
