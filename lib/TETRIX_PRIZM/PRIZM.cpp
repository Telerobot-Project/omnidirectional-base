/*  TETRIX PRIZM robotics controller cpp File for PRIZM Arduino Library
    Written by: Paul W. Uttley
  01/03/2018
  Version 3.0
  =============== Added support for DC and Servo Motor EXPANSIONansion Controllers
  Default address for DC box is 1. Default for Servo box is 2.
  Additional boxes can be added in a daisy chain, and if so the addresses will need to be set different
  Valid address range for PRIZM to support is address 1 - 4.
  =============== Version 3 - fixed minor servo jitter related to PRIZM version 1 firmware ===============
  A workaround to fix is to change each servo channel position update to always update all servo channels with one I2C transaction.

*/

#include <Arduino.h>
// PICO
// #include <avr/wdt.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <Wire.h>
#include "PRIZM.h"

// PICO
// #include <hardware/watchdog.h>
// #include "utility/WSWire.h"


// Wire was changed to Wire1 
#define WIRE1_SDA       2  // Use GP2 as I2C1 SDA
#define WIRE1_SCL       3  // Use GP3 as I2C1 SCL
arduino::MbedI2C Wire1(WIRE1_SDA, WIRE1_SCL);


void EXPANSION::controllerEnable(int address)
{
  Wire1.beginTransmission(address); // Send an "Enable" Byte to EXPANSION controller at address/ID
  Wire1.write(0x25);
  Wire1.endTransmission();
  delay(25);
}

void EXPANSION::controllerReset(int address)
{

  Wire1.beginTransmission(address); // Send an "reset" Byte to EXPANSION controller at address/ID
  Wire1.write(0x27);
  Wire1.endTransmission();
  delay(25);
}

void EXPANSION::WDT_STOP(int address)
{ //===== This forces a watch dog timer HARD STOP on the expansion controller at address #

  Wire1.beginTransmission(address);
  Wire1.write(0x23);
  Wire1.endTransmission();
  delay(50);
}

void EXPANSION::setExpID(int newID)
{            // === command to change ID/ I2C address of a TETRIX Expansion DC or Servo Controller.
             // There can only be one expansion box connected to PRIZM when changing ID's.
  int oldID = 1; // No other I2C devices can be connected to sensor ports when executing this command.

  for (int i = 1; i < 120; i++)
  { // Spin up I2C addresses from 1 - 120

    Wire1.beginTransmission(i);

    if ((Wire1.endTransmission() == 0) && ((i < 5) || (i > 6))) // Capture response from expansion controller (ignore 5 and 6 - they are used by PRIZM)
    {
      oldID = i;
      delay(10);
    }
  }

  Wire1.beginTransmission(oldID); // Send new ID/address to the found Expansion Controller
  Wire1.write(0x24);
  Wire1.write(newID);
  Wire1.endTransmission();
  delay(10);

  pinMode(6, OUTPUT);    //===== RED LED is on pin 6
  digitalWrite(6, HIGH); // Flash PRIZM Red LED when finished
  delay(250);
  digitalWrite(6, LOW);
  delay(250);
  digitalWrite(6, HIGH);
  delay(250);
  digitalWrite(6, LOW);
}

int EXPANSION::readExpID()
{         // === command to get the I2C address / ID from a TETRIX DC or Servo Expansion Controller
          // There can only be one expansion box connected to PRIZM when using this function
  int ID = 1; // All other I2C devices must also be disconnected from sensor ports when using this function

  for (int i = 1; i < 120; i++)
  { // Spin up I2C addresses from 1 - 120

    Wire1.beginTransmission(i);

    if ((Wire1.endTransmission() == 0) && ((i < 5) || (i > 6))) // Capture response from expansion controller (ignore 5 and 6 - they are used by PRIZM)
    {
      ID = i;
      delay(10);
    }
  }

  return ID;
}

void PRIZM::setMotorSpeedPID(int P, int I, int D)
{ //=== Change the speed PID parameters for DC Chip

  int lobyteP;
  int hibyteP;
  int lobyteI;
  int hibyteI;
  int lobyteD;
  int hibyteD;

  lobyteP = lowByte(P);
  hibyteP = highByte(P);
  lobyteI = lowByte(I);
  hibyteI = highByte(I);
  lobyteD = lowByte(D);
  hibyteD = highByte(D);

  Wire1.beginTransmission(5);
  Wire1.write(0X56);
  Wire1.write(hibyteP);
  Wire1.write(lobyteP);
  Wire1.write(hibyteI);
  Wire1.write(lobyteI);
  Wire1.write(hibyteD);
  Wire1.write(lobyteD);
  Wire1.endTransmission();
  delay(10);
}

void EXPANSION::setMotorSpeedPID(int address, int P, int I, int D)
{ //=== Change the speed PID parameters for DC EXPANSIONANSION

  int lobyteP;
  int hibyteP;
  int lobyteI;
  int hibyteI;
  int lobyteD;
  int hibyteD;

  lobyteP = lowByte(P);
  hibyteP = highByte(P);
  lobyteI = lowByte(I);
  hibyteI = highByte(I);
  lobyteD = lowByte(D);
  hibyteD = highByte(D);

  Wire1.beginTransmission(address);
  Wire1.write(0X56);
  Wire1.write(hibyteP);
  Wire1.write(lobyteP);
  Wire1.write(hibyteI);
  Wire1.write(lobyteI);
  Wire1.write(hibyteD);
  Wire1.write(lobyteD);
  Wire1.endTransmission();
  delay(10);
}

void PRIZM::setMotorTargetPID(int P, int I, int D)
{ //=== Change the target PID parameters for DC chip

  int lobyteP;
  int hibyteP;
  int lobyteI;
  int hibyteI;
  int lobyteD;
  int hibyteD;

  lobyteP = lowByte(P);
  hibyteP = highByte(P);
  lobyteI = lowByte(I);
  hibyteI = highByte(I);
  lobyteD = lowByte(D);
  hibyteD = highByte(D);

  Wire1.beginTransmission(5); // transmit to DC address
  Wire1.write(0X57);
  Wire1.write(hibyteP);
  Wire1.write(lobyteP);
  Wire1.write(hibyteI);
  Wire1.write(lobyteI);
  Wire1.write(hibyteD);
  Wire1.write(lobyteD);
  Wire1.endTransmission();
  delay(10);
}

void EXPANSION::setMotorTargetPID(int address, int P, int I, int D)
{ //=== Change the target PID parameters for DC EXPANSIONANSION

  int lobyteP;
  int hibyteP;
  int lobyteI;
  int hibyteI;
  int lobyteD;
  int hibyteD;

  lobyteP = lowByte(P);
  hibyteP = highByte(P);
  lobyteI = lowByte(I);
  hibyteI = highByte(I);
  lobyteD = lowByte(D);
  hibyteD = highByte(D);

  Wire1.beginTransmission(address);
  Wire1.write(0X57);
  Wire1.write(hibyteP);
  Wire1.write(lobyteP);
  Wire1.write(hibyteI);
  Wire1.write(lobyteI);
  Wire1.write(hibyteD);
  Wire1.write(lobyteD);
  Wire1.endTransmission();
  delay(10);
}

int PRIZM::readDCFirmware()
{ //==== Request firmware version of DC motor chip

  int byte1;
  int DCversion;

  Wire1.beginTransmission(5);
  Wire1.write(0x26);
  Wire1.endTransmission();
  delay(10);
  Wire1.requestFrom(5, 1);
  byte1 = Wire1.read();
  DCversion = byte1;
  delay(10);
  return DCversion;
}

int EXPANSION::readDCFirmware(int address)
{ //==== Request firmware version of DC EXPANSIONANSION

  int byte1;
  int DCversion;

  Wire1.beginTransmission(address);
  Wire1.write(0x26);
  Wire1.endTransmission();
  delay(10);
  Wire1.requestFrom(address, 1);
  byte1 = Wire1.read();
  DCversion = byte1;
  delay(10);
  return DCversion;
}

int PRIZM::readSVOFirmware()
{ //==== Request firmware version of Servo motor chip

  int byte1;
  int SVOversion;

  Wire1.beginTransmission(6);
  Wire1.write(0x26);
  Wire1.endTransmission();
  delay(10);
  Wire1.requestFrom(6, 1);
  byte1 = Wire1.read();
  SVOversion = byte1;
  delay(10);
  return SVOversion;
}

int EXPANSION::readSVOFirmware(int address)
{ //==== Request firmware version of Servo EXPANSIONANSION

  int byte1;
  int SVOversion;

  Wire1.beginTransmission(address);
  Wire1.write(0x26);
  Wire1.endTransmission();
  delay(10);
  Wire1.requestFrom(address, 1);
  byte1 = Wire1.read();
  SVOversion = byte1;
  delay(10);

  return SVOversion;
}

void PRIZM::PrizmBegin()
{ //======= Send a SW reset to all EXPANSIONansion port I2C
  Wire1.begin();
  // Wire1.setSDA();

  delay(500);                // Give EXPANSION controllers time to reset
                             // SW reset on Expansion and DC + Servo chips at addresses 5 and 6 (7 is not used)
  Wire1.beginTransmission(5); // Supported I2C addresses for EXPANSIONansion controllers is 1 - 4 (4 boxes total)
  Wire1.write(0x27);          // If additional boxes above that are added at different addresses, 0x27 writes for each need to be added as well.
  Wire1.endTransmission();    // No guarantee that more than 4 boxes will work on single I2C bus because of cable capacitance
  delay(10);
  Wire1.beginTransmission(6);
  Wire1.write(0x27);
  Wire1.endTransmission();
  delay(10);
  Wire1.beginTransmission(1);
  Wire1.write(0x27);
  Wire1.endTransmission();
  delay(10);
  Wire1.beginTransmission(2);
  Wire1.write(0x27);
  Wire1.endTransmission();
  delay(10);
  Wire1.beginTransmission(3);
  Wire1.write(0x27);
  Wire1.endTransmission();
  delay(10);
  Wire1.beginTransmission(4);
  Wire1.write(0x27);
  Wire1.endTransmission();
  delay(10);

  Wire1.beginTransmission(5); // Supported I2C addresses for EXPANSIONansion controllers is 1 - 4 (4 boxes total)
  Wire1.write(0x27);          // Do a reset on Expansions and PRIZM Motor chips after green button start
  Wire1.endTransmission();    // If additional boxes above that are added at different addresses, 0x27 writes for each need to be added as well.
  delay(10);                 // No guarantee that more than 4 boxes will work on single I2C bus because of cable capacitance
  Wire1.beginTransmission(6);
  Wire1.write(0x27);
  Wire1.endTransmission();
  delay(10);
  Wire1.beginTransmission(1);
  Wire1.write(0x27);
  Wire1.endTransmission();
  delay(10);
  Wire1.beginTransmission(2);
  Wire1.write(0x27);
  Wire1.endTransmission();
  delay(10);
  Wire1.beginTransmission(3);
  Wire1.write(0x27);
  Wire1.endTransmission();
  delay(10);
  Wire1.beginTransmission(4);
  Wire1.write(0x27);
  Wire1.endTransmission();
  delay(10);

  Wire1.beginTransmission(5); // Send an "Enable" Byte to DC and Servo controller chips and EXPANSIONansion controllers
  Wire1.write(0x25);          // enable command so that the robots won't move without a PrizmBegin statement
  Wire1.endTransmission();
  delay(10);
  Wire1.beginTransmission(6);
  Wire1.write(0x25);
  Wire1.endTransmission();
  delay(10);
  Wire1.beginTransmission(1);
  Wire1.write(0x25);
  Wire1.endTransmission();
  delay(10);
  Wire1.beginTransmission(2);
  Wire1.write(0x25);
  Wire1.endTransmission();
  delay(10);
  Wire1.beginTransmission(3);
  Wire1.write(0x25);
  Wire1.endTransmission();
  delay(10);
  Wire1.beginTransmission(4);
  Wire1.write(0x25);
  Wire1.endTransmission();
  delay(10);
}

void PRIZM::PrizmEnd()
{ //======= Send a SW reset to all I2C devices(resets everything) This is done mainly to stop all motors

  Wire1.beginTransmission(5); // Supported I2C addresses for EXPANSIONansion controllers is 1 - 4
  Wire1.write(0x27);          // 5 and 6 is PRIZM DC and Servo chips
  Wire1.endTransmission();
  delay(10);
  Wire1.beginTransmission(6);
  Wire1.write(0x27);
  Wire1.endTransmission();
  delay(10);
  Wire1.beginTransmission(1);
  Wire1.write(0x27);
  Wire1.endTransmission();
  delay(10);
  Wire1.beginTransmission(2);
  Wire1.write(0x27);
  Wire1.endTransmission();
  delay(10);
  Wire1.beginTransmission(3);
  Wire1.write(0x27);
  Wire1.endTransmission();
  delay(10);
  Wire1.beginTransmission(4);
  Wire1.write(0x27);
  Wire1.endTransmission();
  delay(10);

  // PICO
  // wdt_enable(WDTO_15MS); // set the wdt to timeout after 15ms automatically resets
  // watchdog_enable(15, false);
  // for (;;)
  // {
  // }
}

int PRIZM::readBatteryVoltage()
{

  int Bvoltage = analogRead(0) * 2;
  return Bvoltage;
}

int EXPANSION::readBatteryVoltage(int address)
{

  int Bvoltage;

  byte byte1;
  byte byte2;

  Wire1.beginTransmission(address);
  Wire1.write(0x53);
  Wire1.endTransmission();
  delay(10);

  Wire1.requestFrom(address, 2);
  byte1 = Wire1.read();
  byte2 = Wire1.read();
  Bvoltage = byte1;
  Bvoltage = (Bvoltage * 256) + byte2;
  delay(10);

  return Bvoltage;
}

int PRIZM::readLineSensor(int pin)
{              // Can sense black or white (follow the edge of a black line on a white surface)
  int BWstate; // black or white
  pinMode(pin, INPUT);
  if (HIGH == digitalRead(pin))
  {
    BWstate = 1;
  }
  else
  {
    BWstate = 0;
  }
  return BWstate;
}

int PRIZM::readSonicSensorCM(int pin)
{ // Returns distance of object from sensor in Centimeters

  delayMicroseconds(1000); // added in version 2 to help with reading accuracy, can't read sonic sensors very fast
  int duration;
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delayMicroseconds(2);
  digitalWrite(pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pin, LOW);
  pinMode(pin, INPUT);
  duration = pulseIn(pin, HIGH);
  return duration / 29 / 2; // convert time of echo to centimeters distance
}

int PRIZM::readSonicSensorIN(int pin)
{ // Returns distance of object from sensor in Inches

  delayMicroseconds(1000); // added in version 2 to help with reading accuracy, can't read sonic sensors very fast
  int duration;
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delayMicroseconds(2);
  digitalWrite(pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pin, LOW);
  pinMode(pin, INPUT);
  duration = pulseIn(pin, HIGH);
  return duration / 74 / 2; // convert time of echo to centimeters distance
}

void PRIZM::setMotorPower(int channel, int power) // set Motor Channel power on PRIZM
{

  if (channel == 1)
  {
    channel = 0x40;
  } // DC channel 1
  if (channel == 2)
  {
    channel = 0x41;
  } // DC channel 2

  Wire1.beginTransmission(5);
  Wire1.write(channel);
  Wire1.write(power);
  Wire1.endTransmission();
  delay(10);
}

void EXPANSION::setMotorPower(int address, int channel, int power) // set Motor Channel power on DC EXPANSIONANSION
{

  if (channel == 1)
  {
    channel = 0x40;
  } // DC channel 1
  if (channel == 2)
  {
    channel = 0x41;
  } // DC channel 2

  Wire1.beginTransmission(address);
  Wire1.write(channel);
  Wire1.write(power);
  Wire1.endTransmission();
  delay(10);
}

void PRIZM::setMotorPowers(int power1, int power2)
{ // power only Block Command for PRIZM Motor 1 and 2 (both in one transmission)

  Wire1.beginTransmission(5);
  Wire1.write(0x42);
  Wire1.write(power1);
  Wire1.write(power2);
  Wire1.endTransmission();
  delay(10);
}

void EXPANSION::setMotorPowers(int address, int power1, int power2)
{ // power only Block Command for EXPANSIONANSION Motor 1 and 2 (both in one transmission)

  Wire1.beginTransmission(address);
  Wire1.write(0x42);
  Wire1.write(power1);
  Wire1.write(power2);
  Wire1.endTransmission();
  delay(10);
}

void PRIZM::setMotorSpeed(int channel, long Mspeed)
{ // === set speed of each PRIZM DC motor == requires a 1440 CPR installed encoder to do the PID

  int lobyte;
  int hibyte;

  lobyte = lowByte(Mspeed);
  hibyte = highByte(Mspeed);

  if (channel == 1)
  {
    channel = 0x43;
  } // DC channel 1
  if (channel == 2)
  {
    channel = 0x44;
  } // DC channel 2

  Wire1.beginTransmission(5);
  Wire1.write(channel);
  Wire1.write(hibyte);
  Wire1.write(lobyte);
  Wire1.endTransmission();
  delay(10);
}

void EXPANSION::setMotorSpeed(int address, int channel, long Mspeed)
{ // === set speed of each EXPANSIONANSION DC motor == requires a 1440 CPR installed encoder to do the PID

  int lobyte;
  int hibyte;

  lobyte = lowByte(Mspeed);
  hibyte = highByte(Mspeed);

  if (channel == 1)
  {
    channel = 0x43;
  } // DC channel 1
  if (channel == 2)
  {
    channel = 0x44;
  } // DC channel 2

  Wire1.beginTransmission(address);
  Wire1.write(channel);
  Wire1.write(hibyte);
  Wire1.write(lobyte);
  Wire1.endTransmission();
  delay(10);
}

void PRIZM::setMotorSpeeds(long Mspeed1, long Mspeed2)
{ // === BLOCK write to set speeds of both PRIZM motors at once == 1440 CPR encoder must be installed to do PID

  int lobyte1;
  int hibyte1;

  int lobyte2;
  int hibyte2;

  lobyte1 = lowByte(Mspeed1);
  hibyte1 = highByte(Mspeed1);

  lobyte2 = lowByte(Mspeed2);
  hibyte2 = highByte(Mspeed2);

  Wire1.beginTransmission(5);
  Wire1.write(0x45);
  Wire1.write(hibyte1);
  Wire1.write(lobyte1);
  Wire1.write(hibyte2);
  Wire1.write(lobyte2);
  Wire1.endTransmission();
  delay(10);
}

void EXPANSION::setMotorSpeeds(int address, long Mspeed1, long Mspeed2)
{ // === BLOCK write to set speeds of both EXPANSIONANSION motors at once == 1440 CPR encoder must be installed to do PID

  int lobyte1;
  int hibyte1;

  int lobyte2;
  int hibyte2;

  lobyte1 = lowByte(Mspeed1);
  hibyte1 = highByte(Mspeed1);

  lobyte2 = lowByte(Mspeed2);
  hibyte2 = highByte(Mspeed2);

  Wire1.beginTransmission(address);
  Wire1.write(0x45);
  Wire1.write(hibyte1);
  Wire1.write(lobyte1);
  Wire1.write(hibyte2);
  Wire1.write(lobyte2);
  Wire1.endTransmission();
  delay(10);
}

void PRIZM::setMotorTarget(int channel, long Mspeed, long Mtarget)
{ // === set speed and encoder target of each PRIZM DC motor == requires a 1440 CPR encoder to do the PID

  int lobyte;
  int hibyte;

  lobyte = lowByte(Mspeed);
  hibyte = highByte(Mspeed);

  byte four = (Mtarget);
  byte three = (Mtarget >> 8);
  byte two = (Mtarget >> 16);
  byte one = (Mtarget >> 24);

  if (channel == 1)
  {
    channel = 0x46;
  } // DC channel 1
  if (channel == 2)
  {
    channel = 0x47;
  } // DC channel 2

  Wire1.beginTransmission(5);
  Wire1.write(channel);
  Wire1.write(hibyte);
  Wire1.write(lobyte);
  Wire1.write(one);
  Wire1.write(two);
  Wire1.write(three);
  Wire1.write(four);
  Wire1.endTransmission();
  delay(10);
}

void EXPANSION::setMotorTarget(int address, int channel, long Mspeed, long Mtarget)
{ // === set speed and encoder target of each EXPANSIONANSION DC motor == requires a 1440 CPR encoder to do the PID

  int lobyte;
  int hibyte;

  lobyte = lowByte(Mspeed);
  hibyte = highByte(Mspeed);

  byte four = (Mtarget);
  byte three = (Mtarget >> 8);
  byte two = (Mtarget >> 16);
  byte one = (Mtarget >> 24);

  if (channel == 1)
  {
    channel = 0x46;
  } // DC channel 1
  if (channel == 2)
  {
    channel = 0x47;
  } // DC channel 2

  Wire1.beginTransmission(address);
  Wire1.write(channel);
  Wire1.write(hibyte);
  Wire1.write(lobyte);
  Wire1.write(one);
  Wire1.write(two);
  Wire1.write(three);
  Wire1.write(four);
  Wire1.endTransmission();
  delay(10);
}

void PRIZM::setMotorTargets(long Mspeed1, long Mtarget1, long Mspeed2, long Mtarget2)
{ // === BLOCK WRITE set speed and encoder target of both PRIZM DC motors == requires a 1440 CPR encoder to do the PID

  int lobyte1;
  int hibyte1;

  int lobyte2;
  int hibyte2;

  lobyte1 = lowByte(Mspeed1);
  hibyte1 = highByte(Mspeed1);

  lobyte2 = lowByte(Mspeed2);
  hibyte2 = highByte(Mspeed2);

  byte four1 = (Mtarget1);
  byte three1 = (Mtarget1 >> 8);
  byte two1 = (Mtarget1 >> 16);
  byte one1 = (Mtarget1 >> 24);

  byte four2 = (Mtarget2);
  byte three2 = (Mtarget2 >> 8);
  byte two2 = (Mtarget2 >> 16);
  byte one2 = (Mtarget2 >> 24);

  Wire1.beginTransmission(5);
  Wire1.write(0x48);
  Wire1.write(hibyte1);
  Wire1.write(lobyte1);
  Wire1.write(one1);
  Wire1.write(two1);
  Wire1.write(three1);
  Wire1.write(four1);
  Wire1.write(hibyte2);
  Wire1.write(lobyte2);
  Wire1.write(one2);
  Wire1.write(two2);
  Wire1.write(three2);
  Wire1.write(four2);
  Wire1.endTransmission();
  delay(10);
}

void EXPANSION::setMotorTargets(int address, long Mspeed1, long Mtarget1, long Mspeed2, long Mtarget2)
{ // === BLOCK WRITE set speed and encoder target of both EXPANSIONANSION DC motors == requires a 1440 CPR encoder to do the PID

  int lobyte1;
  int hibyte1;

  int lobyte2;
  int hibyte2;

  lobyte1 = lowByte(Mspeed1);
  hibyte1 = highByte(Mspeed1);

  lobyte2 = lowByte(Mspeed2);
  hibyte2 = highByte(Mspeed2);

  byte four1 = (Mtarget1);
  byte three1 = (Mtarget1 >> 8);
  byte two1 = (Mtarget1 >> 16);
  byte one1 = (Mtarget1 >> 24);

  byte four2 = (Mtarget2);
  byte three2 = (Mtarget2 >> 8);
  byte two2 = (Mtarget2 >> 16);
  byte one2 = (Mtarget2 >> 24);

  Wire1.beginTransmission(address);
  Wire1.write(0x48);
  Wire1.write(hibyte1);
  Wire1.write(lobyte1);
  Wire1.write(one1);
  Wire1.write(two1);
  Wire1.write(three1);
  Wire1.write(four1);
  Wire1.write(hibyte2);
  Wire1.write(lobyte2);
  Wire1.write(one2);
  Wire1.write(two2);
  Wire1.write(three2);
  Wire1.write(four2);
  Wire1.endTransmission();
  delay(10);
}

void PRIZM::setMotorDegree(int channel, long Mspeed, long Mdegrees)
{ // === set speed and encoder target of each PRIZM DC motor in DEGREES  == requires a 1440 CPR encoder to do the PID

  int lobyte;
  int hibyte;

  lobyte = lowByte(Mspeed);
  hibyte = highByte(Mspeed);

  byte four = (Mdegrees);
  byte three = (Mdegrees >> 8);
  byte two = (Mdegrees >> 16);
  byte one = (Mdegrees >> 24);

  if (channel == 1)
  {
    channel = 0x58;
  }
  if (channel == 2)
  {
    channel = 0x59;
  }

  Wire1.beginTransmission(5);
  Wire1.write(channel);
  Wire1.write(hibyte);
  Wire1.write(lobyte);
  Wire1.write(one);
  Wire1.write(two);
  Wire1.write(three);
  Wire1.write(four);
  Wire1.endTransmission();
  delay(10);
}

void EXPANSION::setMotorDegree(int address, int channel, long Mspeed, long Mdegrees)
{ // === set speed and encoder target of each EXPANSIONANSION DC motor in DEGREES  == requires a 1440 CPR encoder to do the PID

  int lobyte;
  int hibyte;

  lobyte = lowByte(Mspeed);
  hibyte = highByte(Mspeed);

  byte four = (Mdegrees);
  byte three = (Mdegrees >> 8);
  byte two = (Mdegrees >> 16);
  byte one = (Mdegrees >> 24);

  if (channel == 1)
  {
    channel = 0x58;
  }
  if (channel == 2)
  {
    channel = 0x59;
  }

  Wire1.beginTransmission(address);
  Wire1.write(channel);
  Wire1.write(hibyte);
  Wire1.write(lobyte);
  Wire1.write(one);
  Wire1.write(two);
  Wire1.write(three);
  Wire1.write(four);
  Wire1.endTransmission();
  delay(10);
}

void PRIZM::setMotorDegrees(long Mspeed1, long Mdegrees1, long Mspeed2, long Mdegrees2)
{ // === BLOCK WRITE set speed and encoder target in DEGREES of both PRIZM DC motors == requires a 1440 CPR encoder to do the PID

  int lobyte1;
  int hibyte1;

  int lobyte2;
  int hibyte2;

  lobyte1 = lowByte(Mspeed1);
  hibyte1 = highByte(Mspeed1);

  lobyte2 = lowByte(Mspeed2);
  hibyte2 = highByte(Mspeed2);

  byte four1 = (Mdegrees1);
  byte three1 = (Mdegrees1 >> 8);
  byte two1 = (Mdegrees1 >> 16);
  byte one1 = (Mdegrees1 >> 24);

  byte four2 = (Mdegrees2);
  byte three2 = (Mdegrees2 >> 8);
  byte two2 = (Mdegrees2 >> 16);
  byte one2 = (Mdegrees2 >> 24);

  Wire1.beginTransmission(5);
  Wire1.write(0x5A);
  Wire1.write(hibyte1);
  Wire1.write(lobyte1);
  Wire1.write(one1);
  Wire1.write(two1);
  Wire1.write(three1);
  Wire1.write(four1);
  Wire1.write(hibyte2);
  Wire1.write(lobyte2);
  Wire1.write(one2);
  Wire1.write(two2);
  Wire1.write(three2);
  Wire1.write(four2);
  Wire1.endTransmission();
  delay(10);
}

void EXPANSION::setMotorDegrees(int address, long Mspeed1, long Mdegrees1, long Mspeed2, long Mdegrees2)
{ // === BLOCK WRITE set speed and encoder target in DEGREES of both EXPANSIONANSION DC motors == requires a 1440 CPR encoder to do the PID

  int lobyte1;
  int hibyte1;

  int lobyte2;
  int hibyte2;

  lobyte1 = lowByte(Mspeed1);
  hibyte1 = highByte(Mspeed1);

  lobyte2 = lowByte(Mspeed2);
  hibyte2 = highByte(Mspeed2);

  byte four1 = (Mdegrees1);
  byte three1 = (Mdegrees1 >> 8);
  byte two1 = (Mdegrees1 >> 16);
  byte one1 = (Mdegrees1 >> 24);

  byte four2 = (Mdegrees2);
  byte three2 = (Mdegrees2 >> 8);
  byte two2 = (Mdegrees2 >> 16);
  byte one2 = (Mdegrees2 >> 24);

  Wire1.beginTransmission(address);
  Wire1.write(0x5A);
  Wire1.write(hibyte1);
  Wire1.write(lobyte1);
  Wire1.write(one1);
  Wire1.write(two1);
  Wire1.write(three1);
  Wire1.write(four1);
  Wire1.write(hibyte2);
  Wire1.write(lobyte2);
  Wire1.write(one2);
  Wire1.write(two2);
  Wire1.write(three2);
  Wire1.write(four2);
  Wire1.endTransmission();
  delay(10);
}

long PRIZM::readEncoderCount(int channel)
{ // ============================= READ PRIZM ENCODER DATA COUNTS ====================================

  unsigned long eCount; // return value variable. We have to pass this an unsigned into Arduino.

  byte byte1;
  byte byte2;
  byte byte3;
  byte byte4;

  if (channel == 1)
  {
    channel = 0x49;
  } // channel 1 encoder FOR count value
  if (channel == 2)
  {
    channel = 0x4A;
  } // channel 2 encoder FOR count value

  Wire1.beginTransmission(5);
  Wire1.write(channel);
  Wire1.endTransmission();
  delay(10);

  Wire1.requestFrom(5, 4);
  byte1 = Wire1.read();
  byte2 = Wire1.read();
  byte3 = Wire1.read();
  byte4 = Wire1.read();

  eCount = byte1;
  eCount = (eCount * 256) + byte2;
  eCount = (eCount * 256) + byte3;
  eCount = (eCount * 256) + byte4;
  delay(10);
  return eCount;
}

long EXPANSION::readEncoderCount(int address, int channel)
{ // ============================= READ EXPANSIONANSION ENCODER DATA COUNTS ====================================

  unsigned long eCount; // return value variable. We have to pass this an unsigned into Arduino.

  byte byte1;
  byte byte2;
  byte byte3;
  byte byte4;

  if (channel == 1)
  {
    channel = 0x49;
  } // channel 1 encoder FOR count value
  if (channel == 2)
  {
    channel = 0x4A;
  } // channel 2 encoder FOR count value

  Wire1.beginTransmission(address);
  Wire1.write(channel);
  Wire1.endTransmission();
  delay(10);

  Wire1.requestFrom(address, 4);
  byte1 = Wire1.read();
  byte2 = Wire1.read();
  byte3 = Wire1.read();
  byte4 = Wire1.read();

  eCount = byte1;
  eCount = (eCount * 256) + byte2;
  eCount = (eCount * 256) + byte3;
  eCount = (eCount * 256) + byte4;
  delay(10);
  return eCount;
}

long PRIZM::readEncoderDegrees(int channel)
{ // ============================= READ PRIZM ENCODER DATA DEGREES ====================================

  unsigned long eCount; // return value variable. We have to pass this an unsigned into Arduino.

  byte byte1;
  byte byte2;
  byte byte3;
  byte byte4;

  if (channel == 1)
  {
    channel = 0x5B;
  } // channel 1 encoder FOR degrees
  if (channel == 2)
  {
    channel = 0x5C;
  } // channel 2 encoder FOR degrees

  Wire1.beginTransmission(5);
  Wire1.write(channel);
  Wire1.endTransmission();
  delay(10);

  Wire1.requestFrom(5, 4);
  byte1 = Wire1.read();
  byte2 = Wire1.read();
  byte3 = Wire1.read();
  byte4 = Wire1.read();

  eCount = byte1;
  eCount = (eCount * 256) + byte2;
  eCount = (eCount * 256) + byte3;
  eCount = (eCount * 256) + byte4;
  delay(10);
  return eCount;
}

long EXPANSION::readEncoderDegrees(int address, int channel)
{ // ============================= READ EXPANSIONANSION ENCODER DATA DEGREES ====================================

  unsigned long eCount; // return value variable. We have to pass this an unsigned into Arduino.

  byte byte1;
  byte byte2;
  byte byte3;
  byte byte4;

  if (channel == 1)
  {
    channel = 0x5B;
  } // channel 1 encoder FOR degrees
  if (channel == 2)
  {
    channel = 0x5C;
  } // channel 2 encoder FOR degrees

  Wire1.beginTransmission(address);
  Wire1.write(channel);
  Wire1.endTransmission();
  delay(10);

  Wire1.requestFrom(address, 4);
  byte1 = Wire1.read();
  byte2 = Wire1.read();
  byte3 = Wire1.read();
  byte4 = Wire1.read();

  eCount = byte1;
  eCount = (eCount * 256) + byte2;
  eCount = (eCount * 256) + byte3;
  eCount = (eCount * 256) + byte4;
  delay(10);
  return eCount;
}

void PRIZM::resetEncoder(int channel)
{ // =================== RESET PRIZM ENCODERS 1 or 2 =============================

  if (channel == 1)
  {
    channel = 0x4C;
  } // channel 1 encoder reset command
  if (channel == 2)
  {
    channel = 0x4D;
  } // channel 2 encoder reset command

  Wire1.beginTransmission(5);
  Wire1.write(channel);
  Wire1.endTransmission();
  delay(10);
}

void EXPANSION::resetEncoder(int address, int channel)
{ // =================== RESET EXPANSIONANSION ENCODERS 1 or 2 =============================

  if (channel == 1)
  {
    channel = 0x4C;
  } // channel 1 encoder reset command
  if (channel == 2)
  {
    channel = 0x4D;
  } // channel 2 encoder reset command

  Wire1.beginTransmission(address);
  Wire1.write(channel);
  Wire1.endTransmission();
  delay(10);
}

void PRIZM::resetEncoders()
{ // ================== Reset BOTH PRIZM Encoders at once =========================

  Wire1.beginTransmission(5);
  Wire1.write(0x4E);
  Wire1.endTransmission();
  delay(10);
}

void EXPANSION::resetEncoders(int address)
{ // ================== Reset BOTH EXPANSIONANSION Encoders at once =========================

  Wire1.beginTransmission(address);
  Wire1.write(0x4E);
  Wire1.endTransmission();
  delay(10);
}

int PRIZM::readMotorBusy(int channel)
{ // ================== Read Busy Status of PRIZM DC motor channel =======================

  int byte1;
  int MotorStatus;

  if (channel == 1)
  {
    channel = 0x4F;
  } // channel 1 busy flag
  if (channel == 2)
  {
    channel = 0x50;
  } // channel 2 busy flag

  Wire1.beginTransmission(5);
  Wire1.write(channel);
  Wire1.endTransmission();
  delay(10);

  Wire1.requestFrom(5, 1);
  byte1 = Wire1.read();
  MotorStatus = byte1;
  delay(10);

  return MotorStatus;
}

int EXPANSION::readMotorBusy(int address, int channel)
{ // ================== Read Busy Status of EXPANSIONANSION DC motor channel =======================

  int byte1;
  int MotorStatus;

  if (channel == 1)
  {
    channel = 0x4F;
  } // channel 1 busy flag
  if (channel == 2)
  {
    channel = 0x50;
  } // channel 2 busy flag

  Wire1.beginTransmission(address);
  Wire1.write(channel);
  Wire1.endTransmission();
  delay(10);

  Wire1.requestFrom(address, 1);
  byte1 = Wire1.read();
  MotorStatus = byte1;
  delay(10);

  return MotorStatus;
}

int PRIZM::readMotorCurrent(int channel)
{ // ================ Read DC motor current of PRIZM DC channels ======================

  int Mcurrent;

  byte byte1;
  byte byte2;

  if (channel == 1)
  {
    channel = 0x54;
  } // read DC motor 1 current
  if (channel == 2)
  {
    channel = 0x55;
  } // read DC motor 2 current

  Wire1.beginTransmission(5);
  Wire1.write(channel);
  Wire1.endTransmission();
  delay(10);

  Wire1.requestFrom(5, 2);
  byte1 = Wire1.read();
  byte2 = Wire1.read();
  Mcurrent = byte1;
  Mcurrent = (Mcurrent * 256) + byte2;
  delay(10);

  return (Mcurrent); // return Mcurrent in milliamps
}

int EXPANSION::readMotorCurrent(int address, int channel)
{ // ================ Read DC motor current of EXPANSIONANSION DC channels ======================

  int Mcurrent;

  byte byte1;
  byte byte2;

  if (channel == 1)
  {
    channel = 0x54;
  } // read DC motor 1 current
  if (channel == 2)
  {
    channel = 0x55;
  } // read DC motor 2 current

  Wire1.beginTransmission(address);
  Wire1.write(channel);
  Wire1.endTransmission();
  delay(10);

  Wire1.requestFrom(address, 2);
  byte1 = Wire1.read();
  byte2 = Wire1.read();
  Mcurrent = byte1;
  Mcurrent = (Mcurrent * 256) + byte2;
  delay(10);

  return (Mcurrent); // return Mcurrent in milliamps
}

void PRIZM::setMotorInvert(int channel, int invert)
{ // ======================== Set the PRIZM DC Motor Direction invert status ====================

  if (channel == 1)
  {
    channel = 0x51;
  } // channel 1
  if (channel == 2)
  {
    channel = 0x52;
  } // channel 2

  Wire1.beginTransmission(5);
  Wire1.write(channel);
  Wire1.write(invert);
  Wire1.endTransmission();
  delay(10);
}

void EXPANSION::setMotorInvert(int address, int channel, int invert)
{ // ======================== Set the EXPANSIONANSION DC Motor Direction invert status ====================

  if (channel == 1)
  {
    channel = 0x51;
  } // channel 1
  if (channel == 2)
  {
    channel = 0x52;
  } // channel 2

  Wire1.beginTransmission(address);
  Wire1.write(channel);
  Wire1.write(invert);
  Wire1.endTransmission();
  delay(10);
}

//=========THE END ===========================================================================================================================================================
