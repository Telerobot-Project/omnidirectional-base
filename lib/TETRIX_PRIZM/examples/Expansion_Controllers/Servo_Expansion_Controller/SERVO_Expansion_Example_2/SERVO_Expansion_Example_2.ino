/* This example program demonstates the use of the TETRIX Expansion Controllers. Their are two types.
 * A DC motor expansion controller and a Servo motor expansion controller. Each controller enables
 * additional DC and Servo motor channels to be added to the PRIZM controller for programming and control.
 * The Expansion Controllers connect to the PRIZM controller via the expansion port using the
 * data port data cable included with each expansion controller.
 * Power is daisy chained to the expansion controller using the RED/Black motor power extension cable
 * included with each expansion controller.
 * Multiple expansion controllers can share the same data port in a daisy chain hook up. Being an I2C device, each controller
 * on the daisy chain must have a unique I2C address/ID to function. By default, the TETRIX DC expansion
 * controller is set to ID 1. The TETRIX Servo expansion controller is set to ID 2. Additional controllers may
 * be added, however their ID's must be changed using software commands supported by the PRIZM library. 
 * Each controller in the chain must have a different ID. Valid ID's compatible with the PRIZM library are 1,2,3 and 4. 
 * Up to four controllers can be daisy chained together. ID's can be set or read using the library functions supported in the PRIZM library. 
 * All DC motor functions supported by PRIZM are also supported by the expansion controller. 
 * For additional details,please download the specififcation documents for the expansion controllers at www.TETRIXRobotics.com.
 */

#include <PRIZM.h>      // Include the PRIZM library in sketch

PRIZM prizm;            // Instantiate an object in the PRIZM class named "prizm".

EXPANSION exc;          // Instantiate an object in the EXPANSION class named "exc". Shortend name for expansion controller.
                        // "exc" can be changed to whatever you wish.

void setup() {
  
  prizm.PrizmBegin();   // Initiates the PRIZM controller. Must be called at the beginning

  exc.setServoSpeeds(2,25,25,25,25,25,25);    // set the speed of all six servos attached to Servo Expansion Controller with ID# 2 to 25%. Range is 0 - 100%
                                              // The first number (#2) in the parameter paraenthesis is the ID# of the controller.
}

void loop() {

  exc.setServoPositions(2,180,180,180,180,180,180);        // Move ALL servos to 180 degree position. First number (#2) is ID of expansion controller. Range is 0 - 180 degees.
  delay(3000);                                             // wait here for 3 seconds while servo moves to position
  exc.setServoPositions(2,0,0,0,0,0,0);                    // Move ALL servos to 0 degree position. First number (#2) is ID of expansion controller.
  delay(3000);                                             // wait here for 3 seconds while servo moves to position, then repeat
  
}




