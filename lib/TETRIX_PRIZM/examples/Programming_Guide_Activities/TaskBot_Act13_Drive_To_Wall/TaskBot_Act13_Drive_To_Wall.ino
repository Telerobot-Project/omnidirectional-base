/*   PRIZM Controller example program.
 *   This program uses the ultrasonic sensor connected to 
 *   sensor port D4 to detect an obstacle in it's driving path
 *   within 25cm. When detected, the robot will stop and wait 
 *   for the object blocking it's path to be cleared.
 *   author PWU 08/05/2016
 */

  #include <PRIZM.h>      // include PRIZM library
  PRIZM prizm;            // instantiate a PRIZM object “prizm” so we can use its functions

void setup() {

  prizm.PrizmBegin();   //initialize PRIZM

  prizm.setMotorInvert(1,1);      // invert the direction of DC Motor 1
                                  // to harmonize the direction of
                                  // opposite facing drive motors
}

void loop() {

  if(prizm.readSonicSensorCM(4) > 25) 
  {
    prizm.setMotorPowers(50,50);    // if distance greater than 25cm, do this
  }
  else
  {
   prizm.setMotorPowers(125,125);   // if distance less than 25cm, do this
  }   
}







