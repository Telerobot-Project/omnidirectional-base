/* Implement PID control of TETRIX motors equipped with encoders using the PRIZM controller.
 * The recommended DC motor is the TETRIX TorqueNADO - part number 44260.
 * This example demonstrates how to use the degree targetting functions to accurately
 * position a DC motor + encoder to a position in units of degrees at a constant speed rate in degrees per second. 
 * For more detailed information on using the PRIZM library functions,
 * Please see the Arduino Library functions grid in the TETRIX PRIZM Programmer's guide 
 * which can be viewed and downloaded at www.TETRIXRobotics.com
 */


#include <PRIZM.h>    // Include PRIZM Library

PRIZM prizm;          // Instantiate an object named prizm




void setup() {

  prizm.PrizmBegin(); // Initiates the PRIZM controller - must be called in the setup of each PRIZM sketch
  

}

void loop() {

  prizm.setMotorDegree(1,200,360);       // Spin DC motor 1 at a constant 200 degrees per second rate 360 degrees and stop. 
                                         // The +/- sign of position parameter determines direction.
                                         // For TETRIX TorqueNADO encoders, max speed rate is approximately 600 degrees per second.

  delay(4000);          // wait here for 4 seconds

  prizm.resetEncoder(1);                 // Reset encoder count to zero

  prizm.setMotorDegree(1,200,360);       // Spin another 360 degrees
  
  delay(4000);          // wait here for 4 seconds

  prizm.resetEncoder(1);                 // Reset encoder count to zero and repeat loop

  
}





