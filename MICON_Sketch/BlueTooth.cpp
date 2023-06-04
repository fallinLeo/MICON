

class Motor
{
  public:
  int AIA,AIB;
  int vel;
  void forward(vel);
  void back(vel);
  void stop();
  Motor(int aia,int aib)
  {
    AIA=aia;
    AIB=aib;
    vel=150;
    pinMode(AIA,OUTPUT);
    pinMode(AIB,OUTPUT);

  }

};

void Motor::forward(vel)
{
  analogWrite(AIA, 0);
	analogWrite(AIB, vel);
}
void Motor::back(vel)
{
  analogWrite(AIA,0);
  analogWrite(AIB,0);
}
void Motor::back(vel);