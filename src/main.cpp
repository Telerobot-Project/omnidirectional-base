#include <Arduino.h>
#include <MPU6050_6Axis_MotionApps_V6_12.h>
#include <Wire.h>
#include <PRIZM.h>

MPU6050 mpu(0x68);
uint8_t fifoBuffer[64];
Quaternion q;
VectorFloat gravity;
float ypr[3];
double angle = 0;
int counter = 0;
bool led_state = false;

PRIZM prizm;
EXPANSION exc;

void set_direction(float direction = 0, float speed = 0, float correction = 0)
{
  direction *= -1;
  float l_x = 32;
  float l_y = 33.5;
  float r = 5;
  float max_v = 60; // cm/s
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
  exc.setMotorSpeeds(3, v_fr, v_fl);
  exc.setMotorSpeeds(1, -v_bl, -v_br);
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Wire.begin();

  delay(3000);

  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Start gyro init");
  mpu.initialize();
  mpu.dmpInitialize();
  mpu.CalibrateGyro(6);
  mpu.setDMPEnabled(true);
  delay(5000);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Finish gyro init");
}

void loop()
{
  if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer))
  {
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
    angle = ypr[0] * 180 / M_PI;
  }

  counter++;
  if (counter >= 100) 
  {
    digitalWrite(LED_BUILTIN, led_state);
    Serial.println(angle);
    counter = 0;
    led_state = not led_state;
  } 

  set_direction(0, 30);

  delay(10);
}