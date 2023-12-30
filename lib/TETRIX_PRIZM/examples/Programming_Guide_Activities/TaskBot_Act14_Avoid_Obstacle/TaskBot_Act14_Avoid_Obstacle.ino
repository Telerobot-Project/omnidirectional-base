/*   PRIZM Controller example program
 *   This program uses the ultrasonic sensor connected to sensor port D4 to detect objects in its 
 *   driving path. When detected, the robot will stop, backup, make a right turn and continue on.
 *   author PWU 08/05/2016
 */

  #include <PRIZM.h>     // include PRIZM library
  PRIZM prizm;           // instantiate a PRIZM object “prizm” so we can use its functions

void setup() {

  prizm.PrizmBegin(); //initialize PRIZM

  prizm.setMotorInvert(1,1);      // invert the direction of DC Motor 1
                                  // to harmonize the direction of
                                  // opposite facing drive motors
}

void loop() {

  if(prizm.readSonicSensorCM(4) > 25)     // obstacle sense range set at 25 centimeters
  {
    prizm.setMotorPowers(35,35);          // forward while no obstacle detected 
    prizm.setRedLED(LOW);                 // turn off the red LED
    prizm.setGreenLED(HIGH);              // turn on green LED
  }
  else
  {
   prizm.setGreenLED(LOW);                // turn off green LED
   prizm.setRedLED(HIGH);                    // detected obstacle, turn red LED 
   prizm.setMotorPowers(125,125);         // stop, obstacle detected
   delay(500);
   prizm.setMotorPowers(-35,-35);         // back up
   delay(1000);
   prizm.setMotorPowers(125,125);         // stop
   delay(500);
   prizm.setMotorPowers(35,-35);          // make a right turn
   delay(500);
   
  }   
}









