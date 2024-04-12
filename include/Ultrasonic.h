#include <Arduino.h>
#include <HC_SR04.h>



class Ultrasonic
{
private:
  int trig = 6;
  int echo[6] = {7, 8, 9, 10, 11, 12};
  HC_SR04 *us;

  bool finished = true;
  unsigned long long finish_time = 0;
  int max_time = 23; // roughly 8 meters 

public:
  void init();
  void read();
  unsigned int dist[6] = {200, 200, 200, 200, 200, 200};
  Ultrasonic();
};

Ultrasonic::Ultrasonic()
{
  for (int i = 0; i < 6; i++)
    us[i] = HC_SR04(this->trig, this->echo[i]);
}

void Ultrasonic::init()
{
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  for (int i = 0; i < 6; i++)
    us[i].begin();
}

void Ultrasonic::read()
{
  if (!this->finished)
  {
    this->finished = true;
    for (int i = 0; i < 6; i++)
      this->finished &= us[i].isFinished();
    this->finished |= millis() > this->max_time;
  }
  if (this->finished)
  {
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    for (int i = 0; i < 6; i++)
      us[i].start();
    this->finished = false;
    this->finish_time = millis() + this->max_time;
  }
}