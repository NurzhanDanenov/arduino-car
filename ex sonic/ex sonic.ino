#include<NewPing.h>           
#include<Servo.h>             
#include<AFMotor.h>           

#define TRIGGER_PIN 12       
#define ECHO_PIN 13          
#define MAX_DISTANCE 200      

unsigned int distance = 0;    
 int d=10;  

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

int E1 = 5;
int M1 = 4;
int E2 = 9;
int M2 = 2;

 Servo myservo; 
 int pos=0;     

void setup() { 
  pinMode(12, INPUT);
  pinMode(13, INPUT);
   Serial.begin(9600); 
   myservo.attach(10); 
}

void loop() {                             
  
delay(50);                                        
distance = sonar.ping_cm();                       
Serial.print("distance");                   
Serial.println(distance);                         

{
for(pos = 90; pos <= 180; pos += 1){    
  myservo.write(pos);
  if((distance > 5) && (distance < d)){            
  digitalWrite(M1,LOW);
  digitalWrite(M2, HIGH);
  analogWrite(E1, 255);
  analogWrite(E2, 255);
  
}else if(distance > d) {                          
  
stop();
}                   
  delay(15);                            
  } 
for(pos = 180; pos >= 0; pos-= 1) {     
  myservo.write(pos);
  if((distance > 5) && (distance < d)){            
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  analogWrite(E1, 255);
  analogWrite(E2, 255);
  
}else if(distance > d) {                          
stop();
}                   
  delay(15);                            
  }
for(pos = 0; pos<=90; pos += 1) {       
  myservo.write(pos);
  if((distance > 5) && (distance < d)){            
  digitalWrite(M1, HIGH);
  digitalWrite(M2, LOW);
  analogWrite(E1, 255);
  analogWrite(E2, 255);
  
}else if(distance > d) {                          
stop();
}                   
  delay(15);                            
  }
}

}

void stop(){
    //Stop
  digitalWrite(M1, LOW);
  digitalWrite(M2, HIGH);
  analogWrite(E1, 0);
  analogWrite(E2, 0);
}