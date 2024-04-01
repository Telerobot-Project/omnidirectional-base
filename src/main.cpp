#include <Arduino.h>
#include <Wire.h>
#include "Base.h"

Base base;
bool state = 1;
String command = "";

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  for (int i = 0; i < 20; i++)
  {
    digitalWrite(LED_BUILTIN, i % 2);
    delay(50);
  }
  Serial.begin(9600);
  while(!Serial.available())
  {
    Serial.println("Wait for start init");
    digitalWrite(LED_BUILTIN, state);
    state = !state;
    delay(1000);
  }
  Serial.println("Start init base");
  base.init();
  Serial.println("Finish init base");
  base.move(0, 10, 0);
  delay(1000);
  base.move(0, 0, 0);
}

void loop()
{
  if (Serial.available() > 0)
  {
    command = Serial.readString();
    Serial.print("SERIAL -> ");
    Serial.println(command);
    if (command.startsWith("MOVE"))
    {
      base.speed = command.substring(5, 7).toInt();
      base.direction = command.substring(8, 11).toInt();

      Serial.print("SET Speed to ");
      Serial.println(base.speed);
      Serial.print("SET Angle to ");
      Serial.println(base.direction);

      base.move(base.direction, base.speed, 0);
      delay(1000);
      base.move(0, 0, 0);

      Serial.println("STOP");
    }
    if (command.startsWith("STOP"))
    {
      base.speed = 0;
      base.direction = 0;
      Serial.println("STOP");
    }
  }
  Serial.println('1');
  digitalWrite(LED_BUILTIN, state);
  state = !state;
  delay(1000);
}