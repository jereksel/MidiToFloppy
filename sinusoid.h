class Sinusoid : public Song
{
  private:
    int a;
    void reset();
  public:
    Sinusoid();
    char* getName();
    void getMusic(int i, int number, unsigned int *song);
    unsigned int getDevicesNumber();
};

Sinusoid::Sinusoid()
{
  a = 20;
}

void Sinusoid::reset()
{
  a = 20;
}

void Sinusoid::getMusic(int i, int number, unsigned int *song)
{

  song[0] = a%12;
  song[1] = a/12;
  song[2] = 100;
  song[3] = 0;
  a++;
  
  Serial.println(a);
  
  if (a>35)
  {
    i = 20;
  }

}

unsigned int Sinusoid::getDevicesNumber()
{
  return devices_number;
}

char* Sinusoid::getName()
{
  reset();
  return "Sinusoid";
}
