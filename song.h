class Song
{
  public:
    Song() {}
    virtual ~Song() {}
    virtual void getMusic(int i, int number, int *song) = 0;  // "=0" part makes this method pure virtual, and
    virtual int test() = 0;
};
