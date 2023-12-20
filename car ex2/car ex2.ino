int ir_pin = A0;
int pin_in1 = 4; 
int pin_in2 = 5;
int pin_in3 = 13;
int pin_in4 = 12;

int pin_ena = 3;
int pin_enb = 11;

int signal = 0;
float speed = 0;

void stop(){
  digitalWrite(pin_in1, LOW);
  digitalWrite(pin_in2, LOW);
  digitalWrite(pin_in3, LOW);
  digitalWrite(pin_in4, LOW);
}

void forward(){
  digitalWrite(pin_in1, HIGH);
  digitalWrite(pin_in2, LOW);
  digitalWrite(pin_in3, HIGH);
  digitalWrite(pin_in4, LOW);
}

void backward(){
  digitalWrite(pin_in1, LOW);
  digitalWrite(pin_in2, HIGH);
  digitalWrite(pin_in3, LOW);
  digitalWrite(pin_in4, HIGH);
}

void turnleft(){
  digitalWrite(pin_in1, LOW);
  digitalWrite(pin_in2, HIGH);
  digitalWrite(pin_in3, HIGH);
  digitalWrite(pin_in4, LOW);
}

void turnright(){
  digitalWrite(pin_in1, HIGH);
  digitalWrite(pin_in2, LOW);
  digitalWrite(pin_in3, LOW);
  digitalWrite(pin_in4, HIGH);
}

void speedup(float val){
  if(val + 25.5 <= 255){
    val += 25.5;
  }
  else{
    val = 255;
  }
  analogWrite(pin_ena, val);
  analogWrite(pin_enb, val);
  speed = val;
}

void speeddown(float val){
  if(val - 25.5 >= 0){
    val -= 25.5;
  }
  else{
    val = 0;
  }
  analogWrite(pin_ena, val);
  analogWrite(pin_enb, val);
  speed = val;
}

void setmanualspeed(float val){
  analogWrite(pin_ena, val);
  analogWrite(pin_enb, val);
  speed = val;
}


void setup() {
  Serial.begin(9600);
  Serial.setTimeout(500);
  pinMode(pin_in1, OUTPUT);
  pinMode(pin_in2, OUTPUT);
  pinMode(pin_in3, OUTPUT);
  pinMode(pin_in4, OUTPUT);
  pinMode(pin_ena, OUTPUT);
  pinMode(pin_enb, OUTPUT);
  setmanualspeed(speed);
  stop();
}

void loop() {
  signal = 0;
  if(Serial.available()){
    signal = Serial.parseInt();
    Serial.println(signal);
    if(signal == 1){
      forward();
    }
    else if(signal == 2){
      backward();
    }
    else if(signal == 3){
      turnleft();
    }
    else if(signal == 4){
      turnright();
    }
    else if(signal == 5){
      stop();
    }
    else if(signal == 6){
      speedup(speed);
      Serial.print("Current speed: ");
      Serial.print((int)((speed/255)*100));
      Serial.println("%");
    }
    else if(signal == 7){
      speeddown(speed);
      Serial.print("Current speed: ");
      Serial.print((int)((speed/255)*100));
      Serial.println("%");
    }
    else if(signal >= 100 && signal <= 200){
      setmanualspeed(map(signal, 100, 200, 0, 255));
      Serial.print("Current speed: ");
      Serial.print((int)((speed/255)*100));
      Serial.println("%");
    }
    else{
      Serial.println("Unknown command value.");
    }
  }
}