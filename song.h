class Song
{
  public:
    virtual unsigned int getDevicesNumber() = 0;
    virtual void getMusic(int i, int number, unsigned int *song) = 0;
    virtual char* getName() = 0;
};
