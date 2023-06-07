#include <SoftwareSerial.h>
#include "BlueTooth.cpp"
#define sensor A0
#define sensor1 A1
#define sensor2 A2
SoftwareSerial mySerial(2,3);//tx,rx

const int AIA = 11;  //LEFT_ROLLER DIRECTION
const int AIB = 6;   //LEFT_ROLLER VELOCITY
const int BIA = 9;   //RIGHT_ROLLER DIRECTION
const int BIB = 5;   //RIGHT_ROLLER VELOCITY
int Max_speed1 = 200; //forward speed
int Max_speed2 = 170; //turn speed
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);
  
  pinMode(AIA, OUTPUT);
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
  pinMode(sensor,INPUT);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
}
float distArray[20];

void loop() {
  char st;
  int adc=analogRead(sensor);
  int adc1 = analogRead(sensor1);
  int adc2 = analogRead(sensor2);
  bluetoothcheck(st);
  DetectedCheck(adc);
  DetectedCheck(adc1);
  DetectedCheck(adc2);
}

void bluetoothcheck(char st)
{
  
  if(mySerial.available()>0)
  {
    st = mySerial.read();
    //forward();
    if(st=='S')
    {
      brake();
      Serial.println(st);
    }
    else if(st=='F')
    {
      forward();
      Serial.println(st);
    }
    else if(st=='B')
    {
      back();
      Serial.println(st);
    }
    else if(st=='L')
    {
      left();
      Serial.println(st);
    }
    else if(st=='R')
    {
      right(); 
      Serial.println(st);
    }
    else if(st=='I')
    {
      FRward();
      Serial.println(st);
    }
    else if(st=='J')
    {
      RBward();
      Serial.println(st);
    }
    else if(st=='H')
    {
      LBward();
      Serial.println(st);
    }
    else if(st=='G')
    {
      FLward();
      Serial.println(st);
    }
  }
}



void DetectedCheck(float distance){  
  int count = 0;
  int arraySize = sizeof(distArray) / sizeof(distArray[0]) ;
  for(int i = 0; i< arraySize; i++){
    if(distArray[i] != 0) count++;
    //Serial.print("distArray[i] : ");
    //Serial.println(distArray[i]);
  }
   //Serial.print("count : ");
  //Serial.println(count);
  if(distance > 500) {
    Serial.print("distance : ");
    Serial.println(distance);
    distArray[count] = distance;
    Serial.print("distArray[count] : ");
    Serial.println(distArray[count]);
  }
  if(count == 20) DetectedEvent();
}
void DetectedEvent(){
  // distArray 배열 초기화
  int arraySize = sizeof(distArray) / sizeof(distArray[0]) ;
  for(int i = 0; i< arraySize; i++){
    distArray[i] = 0;    
  }
  Serial.print("Dog Detect! ");
}











//=======motor run function start=====
void forward() {
  analogWrite(AIA, Max_speed1+20);
  analogWrite(AIB, 0);
  analogWrite(BIA, Max_speed1);
  analogWrite(BIB, 0);
}
void back() {
  analogWrite(AIA, 0);
  analogWrite(AIB, Max_speed1+20);
  analogWrite(BIA, 0);
  analogWrite(BIB, Max_speed1);

}
void FRward()
{
  analogWrite(AIA,250);
  analogWrite(AIB,0);
  analogWrite(BIA,Max_speed2);
  analogWrite(BIB,0);
}
void RBward()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, Max_speed1+20);
  analogWrite(BIA, 0);
  analogWrite(BIB, Max_speed2);
}
void LBward()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, Max_speed2);
  analogWrite(BIA, 0);
  analogWrite(BIB, Max_speed1+20);

}
void FLward()
{
  analogWrite(AIA, Max_speed2);
  analogWrite(AIB, 0);
  analogWrite(BIA, Max_speed1);
  analogWrite(BIB, 0);
}
void left() {
  analogWrite(AIA, 0);
  analogWrite(AIB, 0);
  analogWrite(BIA, Max_speed1+20);
  analogWrite(BIB, 0);
  

}
void right()
{
  analogWrite(AIA, Max_speed1+20);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, 0);
}

void brake()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, 0);
}