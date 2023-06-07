#include <SoftwareSerial.h>
#include <MsTimer2.h>
//#include "BlueTooth.cpp"
#define sensor A0
#define sensor1 A1
#define sensor2 A2
SoftwareSerial mySerial(2,3);//tx,rx
void SoundEvent();
void LEDRainbowEvent();
void bluetoothcheck(char);
const int AIA = 12;  //LEFT_ROLLER DIRECTION //11
const int AIB = 6;   //LEFT_ROLLER VELOCITY
const int BIA = 13;   //RIGHT_ROLLER DIRECTION //9 
const int BIB = 5;   //RIGHT_ROLLER VELOCITY
int Max_speed1 = 200; //forward speed
int Max_speed2 = 170; //turn speed


bool isDetected = false;
const int speaker = 7;
const int freq = 432;
const int RED =11;
const int GREEN = 10;
const int BLUE = 9;
const int RGB[12][3] = {
  {255, 0, 0},
  {255, 94, 0},
  {255, 187, 0},
  {255, 228, 0},
  {171, 242, 0},
  {29, 219, 22},
  {34, 116, 28},
  {0, 216, 255},
  {0, 83, 255},
  {5, 0, 153},
  {128, 65, 217},
  {42, 0, 102}
};
int Timer; // TimerCnt

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);
  MsTimer2::set(1,ISR_Timer);      //1ms, ISR_Timer
  MsTimer2::start();

  pinMode(AIA, OUTPUT);
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
  pinMode(sensor,INPUT);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

}

void loop() {
  char st;
  int adc = analogRead(sensor);
  int adc1 = analogRead(sensor1);
  int adc2 = analogRead(sensor2);
  bluetoothcheck(st);
  //last1=millis();
  
  if(adc>580||adc1>580||adc2>580)
  {
    DetectedCheck(adc);
    DetectedCheck(adc1);
    DetectedCheck(adc2); 
  }
  
  if(isDetected) 
  {
    brake();
    SoundEvent();
    LEDRainbowEvent();
    
  }
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
void ISR_Timer(){
  Timer++;
  if(Timer > 1000 && !isDetected){
    LEDBasicEvent();
    Timer = 0;
  }
}



float distArray[20];
void DetectedCheck(float distance){  
  int count = 0;
  int arraySize = sizeof(distArray) / sizeof(distArray[0]);
  for(int i = 0; i< arraySize; i++){
    if(distArray[i] != 0) count++;
    //Serial.print("distArray[i] : ");
    //Serial.println(distArray[i]);
  }
   Serial.print("count : ");
   Serial.println(count);
  if(distance > 500) {
    distArray[count] = distance;
    Serial.print("distance : ");
    Serial.println(distance);    
    Serial.print("distArray[count] : ");
    Serial.println(distArray[count]);
  }
  if(count == 20)
  {
    
    for(int i = 0; i< arraySize; i++)
    {
      distArray[i] = 0;
      Serial.print("Dog Detect! ");
      isDetected = true;
    }
  }
}

void LEDRainbowEvent(){
  Serial.print("Rainbow Detect! ");
  for(int i = 0; i<12; i++)
  {
    
    analogWrite(RED, RGB[i][0]); // RED ON
    analogWrite(GREEN, RGB[i][1]);
    analogWrite(BLUE, RGB[i][2]);
    delay(200);
  }  
}

void SoundEvent(){
  // dan dan dadadan dadadadan dadan
  int longDelay = 500;
  int shortDelay = 250;
  tone(speaker, freq, 300);
  delay(longDelay);
  tone(speaker, freq, 300);
  delay(longDelay);

  tone(speaker, freq, 300);
  delay(shortDelay);
  tone(speaker, freq, 300);
  delay(shortDelay);
  tone(speaker, freq, 300);
  delay(longDelay);

  tone(speaker, freq, 300);
  delay(shortDelay);
  tone(speaker, freq, 300);
  delay(shortDelay);
  tone(speaker, freq, 300);
  delay(shortDelay);
  tone(speaker, freq, 300);
  delay(longDelay);

  tone(speaker, freq, 300);
  delay(shortDelay);
  tone(speaker, freq, 300);
  delay(longDelay);
  
  isDetected = false;
}



void LEDBasicEvent(){
  for(int i = 0; i<12; i++)
  {
    analogWrite(RED, RGB[i][0]); // RED ON
    analogWrite(GREEN, RGB[i][1]);
    analogWrite(BLUE, RGB[i][2]);
    delay(1000);        
  }  
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
void Right()
{
  analogWrite(AIA, Max_speed1+20);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, Max_speed1);
}
void brake()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, 0);
}