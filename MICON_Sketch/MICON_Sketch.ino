#include <SoftwareSerial.h>

SoftwareSerial mySerial(2,3);//tx,rx

const int AIA = 11;  //LEFT_ROLLER DIRECTION
const int AIB = 6;   //LEFT_ROLLER VELOCITY
const int BIA = 9;   //RIGHT_ROLLER DIRECTION
const int BIB = 5;   //RIGHT_ROLLER VELOCITY
int Max_speed1 = 200; //forward speed
int Max_speed2 = 180; //turn speed
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);
  
  pinMode(AIA, OUTPUT);
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(mySerial.available())
  {
    //forward();
    if(mySerial.read()=='S')
    {
      brake();
      Serial.println(mySerial.read());
    }
    else if(mySerial.read()=='F')
    {
      forward();
      Serial.println(mySerial.read());
    }
    else if(mySerial.read()=='B')
    {
      back();
      Serial.println(mySerial.read());
    }
    else if(mySerial.read()=='L')
    {
      left();
      Serial.println(mySerial.read());
    }
    else if(mySerial.read()=='R')
    {
      right(); 
      Serial.println(mySerial.read());
    }
  }

  
}
/*

  */
//=======motor run function start=====
void forward() {
  analogWrite(AIA, 0);
  analogWrite(AIB, Max_speed1+20);
  analogWrite(BIA, 0);
  analogWrite(BIB, Max_speed1);

}
void back() {
  analogWrite(AIA, Max_speed1+20);
  analogWrite(AIB, 0);
  analogWrite(BIA, Max_speed1);
  analogWrite(BIB, 0);

}

void right() {
  analogWrite(AIA, 0);
  analogWrite(AIB, Max_speed2);
  analogWrite(BIA, Max_speed2);
  analogWrite(BIB, 0);
  

}

void left(float t) {
  analogWrite(AIA, Max_speed2);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, Max_speed2);
  delay(t);

}

void Brake(float t) {
  analogWrite(AIA, 0);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, 0);
  delay(t);
}
void Right() {
  analogWrite(AIA, 0);
  analogWrite(AIB, 0);
  analogWrite(BIA, Max_speed2);
  analogWrite(BIB, 0);
  

}

void left() {
  analogWrite(AIA, Max_speed2-20);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, 0);
  

}

void brake() {
  analogWrite(AIA, 0);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, 0);
}