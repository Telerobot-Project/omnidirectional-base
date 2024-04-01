#include <Arduino.h>

class UltrasonicArray
{
private:
  int trig;
  int echo;
  int num;
  // Ultrasonic *us = new Ultrasonic[this->num];
public:
  void init();
  void start();
  UltrasonicArray(int t, int e, int n): trig(t), echo(e), num(n);
};

class Ultrasonic
{
private:
  int trig;
  int echo;
  bool state = false;
  static void callback();
public:
  Ultrasonic(int, int);
  void init();
};

// UltrasonicArray::UltrasonicArray(int trig, int echo, int num)
// {
//   this->trig = trig;
//   this->echo = echo;
//   this->num = num;

// }

Ultrasonic::Ultrasonic(int trig, int echo)
{
  this->trig = trig;
  this->echo = echo;
}

void Ultrasonic::callback()
{

}


void Ultrasonic::init()
{
  pinMode(this->trig, OUTPUT);
  pinMode(this->echo, INPUT);
  attachInterrupt(digitalPinToInterrupt(this->echo), this->callback, CHANGE);
}

