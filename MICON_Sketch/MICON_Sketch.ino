
const int AIA = 11;
const int AIB = 6;
const int BIA = 3;
const int BIB = 5;
int Speed = 200;
long first1=millis();
long last1;


void setup() {
  // put your setup code here, to run once:
  pinMode(AIA, OUTPUT);
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
}

void loop() {
  last1 = millis();
  if(first1<=5000)
  {
    forward();
  }
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