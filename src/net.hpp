#ifndef net_hpp
#define net_hpp

class net {
  private:
    int fd;
    void tracker();
  public:
    net();
    void starttracker();
};

#endif