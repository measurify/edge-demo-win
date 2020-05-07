#ifndef connection_windows_h
#define connection_windows_h


//SINGLETON wrapper
class connection_windows{
  private:
  //constructor
  connection_windows();
  
  //variables
  static connection_windows* instance;
  
  //methods
  
  public:
  //variables
//   bool TESTING;
  bool connected;

  //methods
  static connection_windows* getInstance(); 
  bool isConnected();
  void reconnect();
    
};

#endif