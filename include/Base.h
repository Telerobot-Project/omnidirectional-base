#include <Arduino.h>
#include <PRIZM.h>
#include <HC_SR04.h>



class Base
{
public:
  void init();
  void runDirection(float, float, float);
  void avoidObjects();
private:
  PRIZM *prizm = new PRIZM;
  EXPANSION *exp = new EXPANSION;
  HC_SR04 *sensor = new HC_SR04(0, 0, 0, 0);
};

void Base::init()
{
  this->prizm->PrizmBegin();
}

void Base::runDirection(float direction, float speed, float correction)
{
  direction *= -1;
  float l_x = 32; // width of the robot
  float l_y = 33.5; // length of the robot
  float r = 5; // radius of wheels
  float max_v = 60; // max speed in cm/s 
  speed = (speed > max_v ? max_v : speed);
  speed = (speed < -max_v ? -max_v : speed);
  direction = direction / 180.0 * M_PI;
  correction = correction / 180.0 * M_PI;
  float v_x = sin(direction) * speed;
  float v_y = cos(direction) * speed;
  float v_fl = (v_x - v_y - (l_x + l_y) * correction) / r / M_PI * 180.0;
  float v_fr = (v_x + v_y + (l_x + l_y) * correction) / r / M_PI * 180.0;
  float v_bl = (v_x + v_y - (l_x + l_y) * correction) / r / M_PI * 180.0;
  float v_br = (v_x - v_y + (l_x + l_y) * correction) / r / M_PI * 180.0;
  this->exp->setMotorSpeeds(3, v_fr, v_fl);
  this->exp->setMotorSpeeds(1, -v_bl, -v_br);
}

void Base::avoidObjects()
{

}