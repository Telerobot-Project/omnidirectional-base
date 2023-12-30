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

  prizm.setMotorDegree(1,200,360);               // Spin DC motor 1 at a constant 200 degrees per second rate 360 degrees and stop. 
                                                 // The +/- sign of position parameter determines direction.
                                                 // For TETRIX TorqueNADO encoders, max speed rate is approximately 600 degrees per second.

  while (prizm.readMotorBusy(1) == 1){}          // Instead of using a delay, we'll poll the motor busy parameter. 
                                                 // While the motor is busy doing an encoder task, this function will return "1".
                                                 // When the task is complete, it will return "0". So, we sit poll the function and do nothing
                                                 // until the busy flag returns a zero.

  prizm.setMotorDegree(1,200,0);                 // Spin back to zero degrees encoder position starting point.
  
  while (prizm.readMotorBusy(1) == 1){}          // Wait for motor to complete it's task, then repeat

  
}





