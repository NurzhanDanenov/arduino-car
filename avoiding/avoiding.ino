#include <AFMotor.h>      
#include <Servo.h>                    
#include <NewPing.h>      

#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define MAX_DISTANCE 300 
#define MAX_SPEED 160 
#define MAX_SPEED_OFFSET 40 
#define COLL_DIST 30 
#define TURN_DIST COLL_DIST+20 
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

int E1 = 5;
int M1 = 4;
int E2 = 9;
int M2 = 2;
Servo myservo;  

int leftDistance, rightDistance; 
int curDist = 0;
String motorSet = "";
int speedSet = 0;

void setup() {
  myservo.attach(10);  
  myservo.write(90); 
  delay(1000); 
 }

void loop() {
  myservo.write(90);  
  delay(90);
  curDist = readPing();   
  if (curDist < COLL_DIST) {changePath();}  
  moveForward(); 
  delay(500);
 }
 
void changePath() {
  moveStop(); 
  myservo.write(36);
    delay(500);
    rightDistance = readPing();
    delay(500);
    myservo.write(144);
    delay(700);
    leftDistance = readPing();
    delay(500);
    myservo.write(90);
    delay(100);
    compareDistance();
  }

  
void compareDistance() 
{
  if (leftDistance>rightDistance)  
  {
    turnLeft();
  }
  else if (rightDistance>leftDistance) 
  {
    turnRight();
  }
   else 
  {
    turnAround();
  }
}

int readPing() {
  delay(70);   
  unsigned int uS = sonar.ping();
  int cm = uS/US_ROUNDTRIP_CM;
  return cm;
}

void moveStop() {
  digitalWrite(M1, RELEASE);
  digitalWrite(M2, RELEASE);
}  // stop the motors.

void moveForward() {
    motorSet = "FORWARD";
    digitalWrite(M1, HIGH);
    digitalWrite(M2, HIGH);
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) 
  {
    analogWrite(E1, speedSet);
    analogWrite(E2, speedSet);
    delay(5);
  }
}

void moveBackward() {
    motorSet = "BACKWARD";
    digitalWrite(M1, LOW);
    digitalWrite(M2, LOW);
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) 
  {
    analogWrite(E1, speedSet);
    analogWrite(E2, speedSet); 
    delay(5);
  }
}  

void turnRight() {
  motorSet = "RIGHT";
  digitalWrite(M1, HIGH);
  digitalWrite(M2, LOW);
  analogWrite(E2, speedSet+MAX_SPEED_OFFSET);      
  delay(1500); 
  motorSet = "FORWARD";
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);      
}  

void turnLeft() {
  motorSet = "LEFT";
  digitalWrite(M1, LOW);
  analogWrite(E1, speedSet+MAX_SPEED_OFFSET);    
  digitalWrite(M2, HIGH); 
  delay(1500);   
  motorSet = "FORWARD";
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);  
}  

void turnAround() {
  motorSet = "RIGHT";
  digitalWrite(M1, HIGH);
  digitalWrite(M2, LOW);
  analogWrite(E2, speedSet+MAX_SPEED_OFFSET);      
  delay(1700);
  motorSet = "FORWARD";
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);        
}  