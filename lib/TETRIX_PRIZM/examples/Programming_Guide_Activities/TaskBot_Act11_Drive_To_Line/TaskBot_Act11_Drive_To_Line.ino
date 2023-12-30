/*  PRIZM Controller example program
 *  This program will move the PRIZM TaskBot forward on a white surface until it detects a black
 *  line. When the line is detected, the robot will stop.
 *  Connect the line finder sensor to digital port D3.
 *  author PWU 08/05/2016
*/

  #include <PRIZM.h>      // include PRIZM library
  PRIZM prizm;            // instantiate a PRIZM object “prizm” so we can use its functions

void setup() {

  prizm.PrizmBegin();     // initialize PRIZM

  prizm.setMotorInvert(1,1);    // invert the direction of DC Motor 1
                                // to harmonize the direction of
                                // opposite facing drive motors
}

void loop() {

  if(prizm.readLineSensor(3) == 0) {     // when sensor is receiving reflected light beam
    prizm.setMotorPowers(35,35);         // turn Motors 1 and 2 on at 35% power if line
    
  }                                                                    

  if(prizm.readLineSensor(3) == 1) {    // when sensor detects black stripe
    prizm.setMotorPowers(125,125);      // stop motors in brake mode if black line is detected

    while(1){                    // infinite loop - stays locked in this loop until reset is pressed
    prizm.setRedLED(HIGH);       // flash Prizm red LED on and off until reset
    delay(500);
    prizm.setRedLED(LOW);
    delay(500);
    }
  }
}















