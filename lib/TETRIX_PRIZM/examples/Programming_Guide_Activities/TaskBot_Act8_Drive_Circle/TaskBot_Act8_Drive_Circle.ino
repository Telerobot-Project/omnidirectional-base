/*  PRIZM Controller example program
 *  This program will cause the PRIZM TaskBot to drive in a continuous circle. 
 *  Press the red reset button to stop the program.
 *  author PWU 08/05/2016
 */

  #include <PRIZM.h>      // include PRIZM library
  PRIZM prizm;            // instantiate a PRIZM object “prizm” so we can use its functions

void setup() {

  prizm.PrizmBegin();           // initialize PRIZM
  prizm.setMotorInvert(1,1);    // invert the direction of DC Motor 1 to harmonize direction
                              
}

void loop() {

  prizm.setMotorPowers(50,25);    // spin motor 1 a 50% power and motor 2 at 25% power
                                  // resulting in the robot driving in a clockwise circle.
}












