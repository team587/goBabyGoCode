//pin definitions
#include <Math.h>

#define xJoystick A0
#define yJoystick A1

//DeadArea value
#define joystickDeadValue 520

//Motor pin definitions
int motor1PinR = 5;
int motor1PinL = 6;
int motor2PinR = 9;
int motor2PinL = 10;

int led1Red = 3;
int led1Green = 2; 
int led1Blue = 4;

int led2Red = 8;
int led2Green = 7;
int led2Blue = 21;


//ezButton butonn(s);

//Adjusts pins to either output or input respectively.
void setup() {
  //begins the serial monitor.
  Serial.begin(9600);
  pinMode(motor1PinR, OUTPUT);
  pinMode(motor1PinL, OUTPUT);
  pinMode(motor2PinR, OUTPUT);
  pinMode(motor2PinL, OUTPUT);
 
  pinMode(led1Red, OUTPUT);
  pinMode(led1Green, OUTPUT);
  pinMode(led1Blue, OUTPUT);

  pinMode(led2Red, OUTPUT);
  pinMode(led2Green, OUTPUT);
  pinMode(led2Blue, OUTPUT);

  
  //possible button
  //butonn.setDebounceTime(100);

}

void loop() {
  //Set X and Y to the joystick's axis.
  int x = analogRead(xJoystick);
  int y = analogRead(yJoystick);

  //Makes sure x and y don't get off the dead area by small changes.
  y = deadArea(y);
  x = deadArea(x);

  
  //Moves in the direction in which tbe joystick relies on.
  movement(x, y);
}

//Creates a dead area where values around a specific range will alyaws set x and y to joystickDeadValue, else it will return the actual axis value.
int deadArea(float valueN) {
  if (valueN >= 440 && valueN <= 600) {
    return joystickDeadValue;
  }
  return valueN;
}

//Movement function which controls wheelchair's movement if a condition is met.
int movement(float xValue, float yValue) {
  //pwm values for motor controllers are about 0 - 255
  float xSpeed = (xValue - joystickDeadValue) / 2.0;
  float ySpeed = (yValue - joystickDeadValue) / 2.0;
  //prevents pwm values from exceding 251
   xSpeed = abs(xSpeed);
   ySpeed = abs(ySpeed);
   if (xSpeed > 251){
    xSpeed = 251.0;
   }
   if (ySpeed > 251) {
    ySpeed = 251.0;
   }
   
   /*Serial.print("xSpeed = ");
   Serial.print(xSpeed);
   Serial.print(", ySpeed = ");
   Serial.println(ySpeed);*/
   
   Serial.print("xValue = ");
   Serial.print(xValue);
   Serial.print(", yValue = ");
   Serial.print(yValue);
   
  if ((xValue > joystickDeadValue && yValue == joystickDeadValue)) { //rotate left
    analogWrite(motor1PinR, 0);
    analogWrite(motor1PinL, xSpeed);
    analogWrite(motor2PinR, 0);
    analogWrite(motor2PinL, xSpeed);
    //Serial.println(xValue);
    Serial.println(xSpeed); 
    digitalWrite(led1Green, HIGH);
    digitalWrite(led2Green, HIGH);
    digitalWrite(led1Blue, LOW);
    digitalWrite(led2Blue, LOW);
    digitalWrite(led1Red, LOW);
    digitalWrite(led2Red, LOW);
  } else if (xValue < joystickDeadValue && yValue == joystickDeadValue) { //rotate right
    analogWrite(motor1PinR, /*leftValue*/ ySpeed);
    analogWrite(motor1PinL, 0);
    analogWrite(motor2PinR, ySpeed);
    analogWrite(motor2PinL, /*leftValue*/ 0);
    digitalWrite(led1Green, LOW);
    digitalWrite(led2Green, LOW);
    digitalWrite(led1Blue, LOW);
    digitalWrite(led2Blue, LOW);
    digitalWrite(led1Red, HIGH);
    digitalWrite(led2Red, HIGH);
  } else if (xValue == joystickDeadValue && yValue < joystickDeadValue) { //backwards
    analogWrite(motor1PinR, xSpeed);
    analogWrite(motor1PinL, 0);
    analogWrite(motor2PinR, 0);
    analogWrite(motor2PinL, xSpeed);
    //Serial.println(leftValue);
    Serial.println(-1 * ySpeed);
    digitalWrite(led1Green, LOW);
    digitalWrite(led2Green, LOW);
    digitalWrite(led1Blue, HIGH);
    digitalWrite(led2Blue, HIGH);
    digitalWrite(led1Red, LOW);
    digitalWrite(led2Red, LOW);
  } else if (xValue == joystickDeadValue && yValue > joystickDeadValue) { //forward
    analogWrite(motor1PinR, 0);
    analogWrite(motor1PinL, /*rightValue*/ ySpeed);
    analogWrite(motor2PinR, /*rightValue*/ ySpeed);
    analogWrite(motor2PinL, 0);
    //Serial.println(rightValue);
    Serial.println(ySpeed);
    digitalWrite(led1Green, LOW);
    digitalWrite(led2Green, LOW);
    digitalWrite(led1Blue, HIGH);
    digitalWrite(led2Blue, HIGH);
    digitalWrite(led1Red, LOW);
    digitalWrite(led2Red, LOW);
  } else if (xValue < joystickDeadValue && yValue < joystickDeadValue) { //inferior right diagonal x
    /*if (yValue >= 520 && yValue < 771) {
      ySpeed = abs(cos((yValue - 520)/251) * 245);
    } else if (yValue >= 771 && yValue <= 1023) {
      ySpeed = abs(sin((yValue - 628)/251) * 245);
    }
    if (xValue >= 520 && xValue < 771) {
      xSpeed = abs(cos((xValue - 520)/251) * 245);
    } else if (xValue >= 771 && xValue <= 1023) {
      xSpeed = abs(sin((xValue - 628)/251) * 245);
    }*/    
    analogWrite(motor1PinR, ySpeed * 0.3);
    analogWrite(motor1PinL, 0);
    analogWrite(motor2PinR, 0);
    analogWrite(motor2PinL, ySpeed);
    digitalWrite(led1Green, LOW);
    digitalWrite(led2Green, LOW);
    digitalWrite(led1Blue, LOW);
    digitalWrite(led2Blue, LOW);
    digitalWrite(led1Red, HIGH);
    digitalWrite(led2Red, HIGH);

    
  } else if (xValue > joystickDeadValue && yValue < joystickDeadValue) { //inferior left diagonal x
    /*if (yValue <= 520 && yValue > 260) {
      ySpeed = abs(cos((yValue - 514) / 251) * 245);
    } else if (yValue >= 0 && yValue <= 260) {
      ySpeed = abs(sin((yValue - 401) / 251) * 245);
    }
    if (xValue >= 520 && xValue < 771) {
      xSpeed = abs(cos((xValue - 520)/251) * 245);
    } else if (xValue >= 771 && xValue <= 1023) {
      xSpeed = abs(sin((xValue - 628)/251) * 245);
    }*/
    
    analogWrite(motor1PinR, xSpeed);
    analogWrite(motor1PinL, 0);
    analogWrite(motor2PinR, 0);
    analogWrite(motor2PinL, xSpeed * 0.3);
    digitalWrite(led1Green, LOW);
    digitalWrite(led2Green, LOW);
    digitalWrite(led1Blue, LOW);
    digitalWrite(led2Blue, LOW);
    digitalWrite(led1Red, HIGH);
    digitalWrite(led2Red, HIGH);

    } else if (xValue < joystickDeadValue && yValue > joystickDeadValue) { //superior right diagonal x
    /*//motor1PinR pwm has to be the higher speed when this logic is executed
    if (yValue <= 520 && yValue > 260) {
      ySpeed = abs(cos((yValue - 514) / 251) * 245);
    } else if (yValue >= 0 && yValue <= 260) {
      ySpeed = abs(sin((yValue - 401) / 251) * 245);
    }
    if (xValue >= 520 && xValue < 771) {
      xSpeed = abs(cos((xValue - 520)/251) * 245);
    } else if (xValue >= 771 && xValue <= 1023) {
      xSpeed = abs(sin((xValue - 628)/251) * 245);
    }*/
    analogWrite(motor1PinR, 0);
    analogWrite(motor1PinL, ySpeed * 0.5);
    analogWrite(motor2PinR, ySpeed);
    analogWrite(motor2PinL, 0);
    
    digitalWrite(led1Green, HIGH);
    digitalWrite(led2Green, HIGH);
    digitalWrite(led1Blue, LOW);
    digitalWrite(led2Blue, LOW);
    digitalWrite(led1Red, LOW);
    digitalWrite(led2Red, LOW);

    
  } else if (xValue > joystickDeadValue && yValue > joystickDeadValue){ //superior left diagonal 
    /*//analogWrite(motor1PinR, ySpeed * 0.8);
    if (xValue >= 520 && xValue < 771) {
      xSpeed = abs(cos((xValue - 520)/251) * 246);
    } else if (xValue >= 771 && xValue <= 1023) {
      xSpeed = abs(sin((xValue - 628)/251) * 246);
    }
    if (yValue >= 520 && yValue < 771) {
      ySpeed = abs(cos((yValue - 520)/251) * 247);
    } else if (yValue >= 771 && yValue <= 1023) {
      ySpeed = abs(sin((yValue - 628)/251) * 247);
    }*/
    analogWrite(motor1PinR, 0);
    analogWrite(motor1PinL, ySpeed);
    analogWrite(motor2PinR, ySpeed * 0.5);
    //analogWrite(motor2PinR, ySpeed * 0.8);
    analogWrite(motor2PinL, 0);
    
    digitalWrite(led1Green, HIGH);
    digitalWrite(led2Green, HIGH);
    digitalWrite(led1Blue, LOW);
    digitalWrite(led2Blue, LOW);
    digitalWrite(led1Red, LOW);
    digitalWrite(led2Red, LOW);

    
  } else { //no movement x
    analogWrite(motor1PinR, 0);
    analogWrite(motor1PinL, 0);
    analogWrite(motor2PinR, 0);
    analogWrite(motor2PinL, 0);
    digitalWrite(led1Green, LOW);
    digitalWrite(led2Green, LOW);
    digitalWrite(led1Blue, LOW);
    digitalWrite(led2Blue, LOW);
    digitalWrite(led1Red, LOW);
    digitalWrite(led2Red, LOW);
  }
  Serial.print(", xSpeed = ");
   Serial.print(xSpeed);
   Serial.print(", ySpeed = ");
   Serial.println(ySpeed);
}
