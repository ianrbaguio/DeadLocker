   

class LED
{

  private:
    int port;
  public:
    LED(int _port)
    {
      port = _port;
      pinMode(port, OUTPUT);
    }

    void ON()
    {

      digitalWrite(port, HIGH);
    }
    void OFF()
    {
      digitalWrite(port, LOW);
    }
    void BLINK( int freq, int del)
    {
    
      for (int i = 0; i < freq; i++)
      {
        digitalWrite(port, HIGH);
        delay(del);
        digitalWrite(port, LOW);
        delay(del);
      }
    }
};
