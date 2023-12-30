/* 	Header file for TETRIX PRIZM robotics controller Arduino Library
   	Written by: Paul W. Uttley
	01/03/2018
	Version 3.0
	=============== Added support for DC and Servo Motor Expansion Controllers =============================
	Default address for DC box is 1. Default for Servo box is 2.
	Additional boxes can be added in a daisy chain, and if so the addresses will need to be set different
	Valid address range for PRIZM to support is address 1 - 4.
	=============== Version 3 - fixed minor servo jitter related to PRIZM version 1 firmware ===============
	A workaround to fix is to change each servo channel position update to always update all servo channels with one I2C transaction.
*/

#include <Arduino.h>


#ifndef PRIZM_H
#define PRIZM_H

//#include <avr/wdt.h>
//#include <inttypes.h>
//#include <stdio.h>
//#include <string.h>
//#include "PRIZM.h"

//#include "utility/WSWire.h" // Not the standard Arduino library, but a variant that is supposed to perform better and not lock up



class PRIZM
{
	public:
	
		int lastPosition_1 = 90;		// these hold the current 'last' positions of each servo channel
		int lastPosition_2 = 90;
		int lastPosition_3 = 90;
		int lastPosition_4 = 90;
		int lastPosition_5 = 90;
		int lastPosition_6 = 90;
		
		void setMotorPower(int channel, int power);
		void setMotorPowers(int power1,int power2);

		void setMotorSpeed (int channel, long Mspeed);
		void setMotorSpeeds (long Mspeed1, long Mspeed2);
		void setMotorTarget (int channel, long Mspeed, long Mtarget);
		void setMotorTargets (long Mspeed1, long Mtarget1, long Mspeed2, long Mtarget2);
		void setMotorDegree (int channel, long Mspeed, long Mdegrees);
		void setMotorDegrees (long Mspeed1, long Mdegrees1, long Mspeed2, long Mdegrees2);		
		void setMotorInvert (int channel, int invert);
		int readMotorBusy (int channel);
		int readMotorCurrent (int channel);

		long readEncoderCount (int channel);
		long readEncoderDegrees (int channel);
		void resetEncoder (int channel);
		void resetEncoders (void);

		void setMotorSpeedPID  (int P, int I, int D);
		void setMotorTargetPID (int P, int I, int D);

		int readLineSensor(int pin);
		int readSonicSensorCM(int pin);
		int readSonicSensorIN(int pin);

		int readBatteryVoltage(void);
		
		void PrizmBegin(void);
		void PrizmEnd(void);
		int readDCFirmware(void);
		int readSVOFirmware(void);

		void setGreenLED(int state);
		void setRedLED(int state);

		int  readStartButton(void);

		void setServoSpeed(int channel, int servospeed);
		void setServoSpeeds(int servospeed1, int servospeed2, int servospeed3, int servospeed4, int servospeed5, int servospeed6);
		void setServoPosition (int channel, int servoposition);
		void setServoPositions (int servoposition1,int servoposition2,int servoposition3,int servoposition4,int servoposition5,int servoposition6);
		void setCRServoState (int channel, int servospeed);
		int readServoPosition (int channel);
		
	private:
};


class EXPANSION
{
	public:
	
		void WDT_STOP (int address);
		void controllerEnable(int address);
		void controllerReset(int address);
		
		void setExpID(int newID);
		int readExpID(void);
		
		void setMotorPower(int address, int channel, int power);
		void setMotorPowers(int address, int power1,int power2);

		void setMotorSpeed (int address, int channel, long Mspeed);
		void setMotorSpeeds (int address, long Mspeed1, long Mspeed2);
		void setMotorTarget (int address, int channel, long Mspeed, long Mtarget);
		void setMotorTargets (int address, long Mspeed1, long Mtarget1, long Mspeed2, long Mtarget2);
		void setMotorDegree (int address, int channel, long Mspeed, long Mdegrees);
		void setMotorDegrees (int address, long Mspeed1, long Mdegrees1, long Mspeed2, long Mdegrees2);		
		void setMotorInvert (int address, int channel, int invert);
		int readMotorBusy (int address, int channel);
		int readMotorCurrent (int address, int channel);
		
		int readBatteryVoltage(int address);

		long readEncoderCount (int address, int channel);
		long readEncoderDegrees (int address, int channel);
		void resetEncoder (int address, int channel);
		void resetEncoders (int address);

		void setMotorSpeedPID  (int address, int P, int I, int D);
		void setMotorTargetPID (int address, int P, int I, int D);
		
		int readDCFirmware(int address);
		int readSVOFirmware(int address);

		void setServoSpeed(int address, int channel, int servospeed);
		void setServoSpeeds(int address, int servospeed1, int servospeed2, int servospeed3, int servospeed4, int servospeed5, int servospeed6);
		void setServoPosition (int address, int channel, int servoposition);
		void setServoPositions (int address, int servoposition1,int servoposition2,int servoposition3,int servoposition4,int servoposition5,int servoposition6);
		void setCRServoState (int address, int channel, int servospeed);
		int readServoPosition (int address, int channel);
		
	private:
		
};

#endif







