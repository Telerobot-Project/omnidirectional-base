/*  PRIZM Controller example program
 *  This program implements line following with the TaskBot. Using the line finder sensor   
 *  on sensor port D3, the robot will follow the edge of a black stripe on a white surface. 
 *  The DC drive motors will power one motor at a time resulting in back and forth forward motion to
 *  keep the robot traversing the line edge.
 *  author PWU 08/05/2016
 */

  #include <PRIZM.h>     // include PRIZM library
  PRIZM prizm;           // instantiate a PRIZM object “prizm” so we can use its functions

void setup() {

  prizm.PrizmBegin();   // initialize PRIZM

  prizm.setMotorInvert(1,1);      // invert the direction of DC Motor 1
                                  // to harmonize the direction of
                                  // opposite facing drive motors
}

void loop() {

  // beam reflected, no line detected
  if(prizm.readLineSensor(3) == 0){prizm.setMotorPowers(125,30); prizm.setRedLED(LOW);}  

  // no relected beam, line detected
  if(prizm.readLineSensor(3) == 1){prizm.setMotorPowers(30,125); prizm.setRedLED(HIGH);} 
   
}







