/*  PRIZM Controller example program
 *  This program will move the TaskBot in a square driving pattern using a forward and right turn function.
 *  author PWU 08/05/2016  
*/
  #include <PRIZM.h>      // include PRIZM library
  PRIZM prizm;            // instantiate a PRIZM object “prizm” so we can use its functions

void setup() {

  prizm.PrizmBegin();         // initialize PRIZM
  prizm.setMotorInvert(1,1);  // invert the direction of DC Motor 1 to harmonize direction
                              
}

void loop() {

for(int x=0; x<=3; x++){    // Do this four times, increment x by + 1
  forward();
  rightTurn();
 }
  prizm.PrizmEnd();
}

void forward(){                       // function to go forward
  prizm.setMotorPowers(50,50);        // go forward at 50% power
  delay(3000);                        // wait here for 3 seconds while motors spin
  prizm.setMotorPowers(125,125);      // stop both motors with in brake mode
  delay(1000);                        // wait here for 1 second

  }

void rightTurn(){                     // function for a right turn
  prizm.setMotorPowers(50,-50);       // make a right turn
  delay(600);                         // wait here for .6 seconds while motors spin
  prizm.setMotorPowers(125,125);      // stop both motors with in brake mode
  delay(1000);                        // wait here for 1 second

  }


  


  


  





