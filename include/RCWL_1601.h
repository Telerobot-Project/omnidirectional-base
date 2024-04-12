#include <Arduino.h>


template <int n> void callback()
{

}

class RCWL_1601
{
private:
  int echo, num;
public:
  bool finished = true;
  RCWL_1601(int e, int n): echo(e), num(n) {};
  void init();
};

void RCWL_1601::init()
{
  pinMode(echo, INPUT);
  attachInterrupt(digitalPinToInterrupt(echo), callback<0>, FALLING);
  attachInterrupt(digitalPinToInterrupt(echo), callback<1>, FALLING);
  attachInterrupt(digitalPinToInterrupt(echo), callback<2>, FALLING);
  attachInterrupt(digitalPinToInterrupt(echo), callback<3>, FALLING);
  attachInterrupt(digitalPinToInterrupt(echo), callback<4>, FALLING);
  attachInterrupt(digitalPinToInterrupt(echo), callback<5>, FALLING);
}

