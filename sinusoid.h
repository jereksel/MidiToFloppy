#define MIN 40
#define MAX 60

class Sinusoid : public Song
{
  private:
    int a;
    boolean up;
    void reset();
  public:
    Sinusoid();
    char* getName();
    void getMusic(int i, int number, unsigned int *song);
    unsigned int getDevicesNumber();
};

Sinusoid::Sinusoid()
{
  reset();
}

void Sinusoid::reset()
{
  up = true;
  a = MIN;
}

void Sinusoid::getMusic(int i, int number, unsigned int *song)
{

  song[0] = a % 12;
  song[1] = a / 12;
  song[2] = 100;
  song[3] = 0;

  if (up)
  {
    a++;
    if (a > MAX)
    {
      up = false;
    }
  }
  else
  {
    a--;
    if (a < MIN)
    {
      up = true;
    }
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
