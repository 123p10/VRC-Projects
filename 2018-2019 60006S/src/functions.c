#include "main.h"

/*
 OK for all declarations of motors USE THESE FUNCTIONS
 This is because motors cannot be reversed using pros so we must set them to negative in these functions
*/

void setLDrive(int speed){
  motorSet(LDF, speed);
  motorSet(LDB, speed);
  motorSet(LDM, speed);
}
void setRDrive(int speed){
  motorSet(RDF, -speed);
  motorSet(RDB, -speed);
  motorSet(RDM, -speed);
}
void setPuncher(int speed){
  motorSet(puncherM, -speed);
}
void setDrive(int left,int right){
  setLDrive(left);
  setRDrive(right);
}
void setIntake(int speed){
  motorSet(intake,-speed);
}
void setAngler(int speed){
  motorSet(angler,-speed);
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

//Auton functions
int inchesToTicks(int inches){
  return (360 / (4 * 3.14159)) * inches;
}
int cmToTicks(int cm){
  return (360/(10.16*3.14159)) * cm;
}
int lError = 0;
//my PID
void driveForward(int distance, double kP,double kI, double kD){
  int acceleration = 30;
  int integral = 0;
//  int start = millis();
  encoderReset(driveL);
  encoderReset(driveR);
  int dL = distance - encoderGet(driveL);
  int dR = distance - encoderGet(driveR);
  int output = dL - dR;
  setLDrive(acceleration);
  setRDrive(acceleration-5);
  while(dL >= 0){
    dL = distance - encoderGet(driveL);
    dR = distance - encoderGet(driveR);
    int error = encoderGet(driveL) - encoderGet(driveR);
    integral = error + integral;
    output = (error * kP + kD * (error - lError) + kI * integral);
    setLDrive(acceleration);
    setRDrive(acceleration + output);
    lError = encoderGet(driveL) - encoderGet(driveR);
    delay(50);
    if(acceleration - 5 <= 70){
      acceleration += 5;
    }
    if(dL <= 200){
      if(acceleration + 5 >= 30){
        acceleration -= 5;
      }
    }
    //printf("Error: %d Output: %d\n\n",error,output);
  }
  setDrive(-10, -10);
  delay(200);
  setDrive(0, 0);
}
void driveBackward(int distance,double kP,int breakout){
  int acceleration = 30;
  float kD = 0.0;
  float kI = 0.00;
  int integral = 0;
  encoderReset(driveL);
  encoderReset(driveR);
  int dL = distance + encoderGet(driveL);
  int dR = distance + encoderGet(driveR);
  int output = dL - dR;
  int start = millis();
  setLDrive(-acceleration);
  setRDrive(-acceleration+5);
  while(dL >= 0){
    dL = distance + encoderGet(driveL);
    dR = distance + encoderGet(driveR);
    int error = encoderGet(driveL) - encoderGet(driveR);
    integral = error + integral;
    output = (error * kP + kD * (error - lError) + kI * integral);
    setLDrive(-acceleration);
    setRDrive(-acceleration + output);
    lError = encoderGet(driveL) - encoderGet(driveR);
    delay(70);
    if(acceleration - 5 <= 65){
      acceleration += 5;
    }
    if(dL <= 200){
      if(acceleration - 10 <= -30){
        acceleration += 5;
      }
    }
    if(millis() - start > breakout){
      break;
    }
    //printf("Error: %d Output: %d\n\n",error,output);
  }
  setDrive(10, 10);
  delay(200);
  setDrive(0, 0);
}
//17 cmToTicks is like 90 degrees
//20 cmToTicks is like 135 degrees
void turnEncoder(int dist){
  encoderReset(driveL);
  encoderReset(driveR);
  int turningSpeed = 50;
  setLDrive(turningSpeed * sgn(dist));
  setRDrive(turningSpeed * sgn(dist) * -1);
  int error = dist - encoderGet(driveL);
  while(error * sgn(dist) > 0){
      if(abs(error) < 300){
        turningSpeed = 20;
      }
      setLDrive(turningSpeed * sgn(dist));
      setRDrive(turningSpeed * sgn(dist) * -1);
      error = dist - encoderGet(driveL);
      delay(50);
  }
  setDrive(-10 * sgn(dist), 10 * sgn(dist));
  delay(150);
  setDrive(0, 0);
}
int sgn(int in){
  if(in > 0){
    return 1;
  }
  else if(in < 0){
    return -1;
  }
  else{
    return 0;
  }
}
int increment = 10;
int lE = 0;
int lR = 0;

void driveSlewRate(){
  lE = lDriveGoal + motorGet(LDF);
  lR = rDriveGoal - motorGet(RDB);
  if(abs(lE) > 5){
    setLDrive(motorGet(LDF) + lE * 0.25);
  }
  if(abs(lR) > 5){
    setRDrive(motorGet(RDB) + lR * 0.25);
  }
}

void turnGyro(int x,int reset,int breakout){
    int start = millis();
    int dir = 1;
    int lerr = 0;
    if(reset == 1){gyroReset(gyro);}
    int err = x - gyroGet(gyro);
    int power = 25;

    if(err < 0){dir = -1;}
    while(err * dir > 0){
      //printf("Angle: %d",gyroGet(gyro));
      err = x - gyroGet(gyro);
    //  if(abs(err) > 15){power = 10;}
  //    if(err > 0){dir = 1;}
    //  else{dir = -1;}
      if(abs(err) < 10){power = 20;}
      if(abs(err) > 30){power = 25;}
      if(abs(err) > 45){power = 25;}
      if(abs(err) > 60){power = 35;}
      if(abs(err) > 90){power = 35;}
      setDrive(-dir*power,dir*power);
      delay(25);
      if(millis()-start > breakout){
        break;
      }
    }
    setDrive(dir * 5,-dir * 5);
    delay(50);
  //  setDrive(0,0);
    err = x - gyroGet(gyro);
    if(err > 0){dir = 1;}
    if(err < 0){dir = -1;}
    float k_i = 0.05;
    float k_p = 0.75;
    int turn_integral = 0;
    int l_error = err;
  /*  while(abs(err) > 0 && abs(err - l_error) > 1){
      //  err = x - gyroGet(gyro);
        if(err > 0){dir = 1;}
        if(err < 0){dir = -1;}

        if(abs(err) > 0){power = 15;}
        if(abs(err) > 10){power = 20;}
        if(abs(err) > 30){power = 30;}
        turn_integral += abs(err);
        //power = 15 + abs(err) * k_p + (turn_integral * k_i);
        setDrive(-dir*power,dir*power);
        l_error = err;
        delay(25);
        if(millis()-start > breakout){
          break;
        }
        err = x - gyroGet(gyro);

      }*/
  //  setDrive(5*dir,-5*dir);
    //delay(75);
    setDrive(0,0);

}




int auton_goal = 300;
int auton_angler_integral = 0;
int auton_angler = 350;
int puncher_crossed = 0;
int last_puncher_error_auton = 0;
void anglerAuton(){
  int angleError = analogRead(anglerE) - auton_angler;
//  printf("Puncher Angler: %d",angleError);
  if(abs(angleError) > 40){
		setAngler(angleError * 0.09 + auton_angler_integral * 0.001 + (angleError - last_puncher_error_auton) * 0.05);
	}
	else{
		setAngler(0);
	}
  last_puncher_error_auton = angleError;
}
void setAnglerAutonHeight(int h){
  //last_puncher_error_auton = analogRead(anglerE) - h;
  auton_angler = h;
  auton_angler_integral = 0;
}
void puncherAuton(){
  //printf("Puncher: %d\n\n",encoderGet(puncher));
  if(auton_goal - encoderGet(puncher) >= 0){
    if(puncher_crossed == 0){
      setPuncher(127);
    }
  }
  else{
    puncher_crossed = 1;
    setPuncher(0);
  }
}
void autonShoot(int g){
  auton_goal = g;
  puncher_crossed = 0;
}
void wait_for(int n){
  int init = millis();
  while(millis() - init <= n){delay(25);}
  return;
}

void driveOneWheelBack(int dist,char side){
  encoderReset(driveL);
  encoderReset(driveR);
  if(side == 'L'){
    int err = dist + encoderGet(driveL);
    while(err > 0){
      err = dist + encoderGet(driveL);
      setLDrive(-25);
      delay(50);
    }
    setDrive(0,0);
  }
  else{
    int err = side + encoderGet(driveR);
    while(err > 0){
      err = side + encoderGet(driveR);
      setRDrive(-25);
      delay(50);
    }
    setDrive(0,0);
  }
}
