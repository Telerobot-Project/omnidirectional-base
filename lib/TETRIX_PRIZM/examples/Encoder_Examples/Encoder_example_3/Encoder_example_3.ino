/* Implement PID control of TETRIX motors equipped with encoders using the PRIZM controller.
 * The recommended DC motor is the TETRIX TorqueNADO - part number 44260.
 * This example demonstrates how to use position targetting functions to accurately
 * position a DC motor + encoder to an encoder count position and hold the position
 * in a servo like mode. For more detailed information on using the PRIZM library functions,
 * Please see the Arduino Library functions grid in the TETRIX PRIZM Programmer's guide 
 * which can be viewed and downloaded at www.TETRIXRobotics.com
 */


#include <PRIZM.h>    // Include PRIZM Library

PRIZM prizm;          // Instantiate an object named prizm




void setup() {

  prizm.PrizmBegin(); // Initiates the PRIZM controller - must be called in the setup of each PRIZM sketch
  

}

void loop() {

  prizm.setMotorTargets(360,1440,360,-1440);   // Spin DC motors 1 and 2 at a constant 360 degrees per second and stop when encoder count reaches 1440 and -1440 respectively.
                                               // For TETRIX TorqueNADO encoders, 1440 = 1 motor shaft revolution. (1440 / 4 = 360)

  delay(2000);    // wait here for 2 seconds while motors get to their destination

  prizm.setMotorTargets(360,0,360,0);         // Spin DC motors 1 and 2 at 360 degrees per second back to encoder position "0".   

  delay(2000);    // wait here for 2 seconds, and repeat                                     
}
