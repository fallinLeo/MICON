


#define TRIG 9
#define ECHO 8
//=======motor pin set
const int AIA = 11;
const int AIB = 6;
const int BIA = 3;
const int BIB = 5;
//=======motor pin set end
int Speed = 150;

long first1=millis();//timer1
long last1;//timer1


void forward();
void setup() {
  //AIA,AIB ==> right direction, velocity
  //BIA,BIB ==> left direction,velocity
  pinMode(AIA, OUTPUT); //motor setting(output)
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
}

void loop() {
  last1 = millis();
  //left();
  if(first1-last1<=5000)
  {
    forward();
  }
}


void left()
{
  analogWrite(AIA,0);
  analogWrite(AIB,Speed);
  analogWrite(BIA,0);
  analogWrite(BIB,Speed);
}
void right()
{
  analogWrite(AIA,0);
  analogWrite(AIB,Speed);
  analogWrite(BIA,Speed);
  analogWrite(BIB,0);
}
void forward() {
	analogWrite(AIA, 0);
	analogWrite(AIB, Speed);
	analogWrite(BIA, 0);
	analogWrite(BIB, Speed);
}

void brake(float t)
{
  analogWrite(AIA,0);
  analogWrite(AIB,0);
  analogWrite(BIA,0);
  analogWrite(BIB,0);
}


/*float Super_Sonic()
{
  long duration, distance;
  digitalWrite(TRIG,LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG,LOW);
  duration = pulseIn(ECHO.HIGH);
  distance = duration*17/1000;
  return distance;
}*/
