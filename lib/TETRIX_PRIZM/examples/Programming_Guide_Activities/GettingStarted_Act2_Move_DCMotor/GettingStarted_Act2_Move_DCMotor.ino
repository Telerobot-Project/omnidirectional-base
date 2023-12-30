/*  PRIZM Controller example program
 *  Spin DC motor channel 1 for 5 seconds, then coast to a stop.
 *  After stopping, wait for 2 seconds, spin in opposite direction.
 *  Continue to repeat until RED reset button is pressed.
 *  author PWU on 08/05/2016
*/

  #include <PRIZM.h>    // include the PRIZM library in the sketch
  PRIZM prizm;          // instantiate a PRIZM object “prizm” so we can use its functions

void setup() {        

  prizm.PrizmBegin();   // Initialize the PRIZM controller
}

void loop() {     // repeat in a loop

  prizm.setMotorPower(1,25);    // spin Motor 1 CW at 25% power
  delay(5000);                  // wait while the motor runs for 5 seconds
  prizm.setMotorPower(1,0);     // stop motor (coast to stop)
  delay(2000);                  // After stopping, wait here for 2 seconds
  prizm.setMotorPower(1,-25);   // spin Motor 1 CCW at 25% power
  delay(5000);                  // wait while the motor runs for 5 seconds
  prizm.setMotorPower(1,0);     // stop motor (coast to stop);
  delay(2000);                  // After stopping, wait here for 2 seconds, then repeat
  
}






