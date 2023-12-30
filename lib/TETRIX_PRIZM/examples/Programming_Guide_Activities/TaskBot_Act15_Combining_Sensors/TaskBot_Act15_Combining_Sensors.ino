/*  PRIZM Controller example program.  
 *  This program uses the Line Finder and the Ultrasonic sensor at the same time. 
 *  The robot will follow the edge of a black line (stripe) on a white surface and scan for an object
 *  in its path. Once detected, it will wait for the obstacle to be cleared, then continue on. 
 *  The line sensor is   connected to digital port D3. The sonic sensor is connected to
 *  digital port D4. The red LED shows the line sensor status. The green LED shows the 
 *  sonic sensor   status.
 *  author PWU 08/05/2016
 */

  #include <PRIZM.h>      // include PRIZM library
  PRIZM prizm;            // instantiate a PRIZM object “prizm” so we can use its functions

void setup() {

  prizm.PrizmBegin();           // initialize PRIZM
  prizm.setMotorInvert(1,1);    // invert the direction of DC Motor 1
                                // to harmonize the direction of
                                // opposite facing drive motors
  prizm.setServoSpeed(1,50);    // set servo 1 speed to 50;                              
}

void loop() {
    if(prizm.readLineSensor(3) == 1){
        prizm.setMotorPowers(30,125);     // line detected
        prizm.setRedLED(HIGH);
      }
      else
      {
        prizm.setMotorPowers(125,30);     // no line detected
        prizm.setRedLED(LOW);
      }  
  
    while(prizm.readSonicSensorCM(4) < 25){   // object is in path, loop here until cleared
          prizm.setGreenLED(HIGH);            // turn on
          prizm.setMotorPowers(125,125);      // stop, obstacle detected
          prizm.setServoPosition(1,0);        // raise detection flag!
      }

  prizm.setGreenLED(LOW);                 // turn off green LED
  prizm.setServoPosition(1,90);           // lowered flag position 
}





