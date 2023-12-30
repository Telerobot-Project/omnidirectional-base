/*  PRIZM Controller example program
 *  This program sets the speed of servo 1 to 25%.
 *  Servo 1 is then rotated back and forth between 0 and 180 degree range.
 *  author PWU on 08/05/2016
*/

#include <PRIZM.h>    // include the PRIZM library in the sketch
PRIZM prizm;          // instantiate a PRIZM object “prizm” so we can use its functions

void setup() {

  prizm.PrizmBegin();         // initialize the PRIZM controller
  prizm.setServoSpeed(1,25);  // set servo 1 speed to 25%

}

void loop() {     // repeat in a loop

  prizm.setServoPosition(1,180);  // rotate servo1 to 180 degrees
  delay(3000);                    // wait for 3 seconds to give servo1 time
                                  // to get to position 180
  prizm.setServoPosition(1,0);    // rotate servo1 to 0 degrees
  delay(3000);                    // wait for 3 seconds to give servo1 time
                                  // to get to position 0
 
}





