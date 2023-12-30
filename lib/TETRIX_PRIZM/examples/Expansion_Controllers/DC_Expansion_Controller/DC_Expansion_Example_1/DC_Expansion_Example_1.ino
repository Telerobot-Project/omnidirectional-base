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

}

void loop() {

  exc.setMotorPower(1,1,50);        // Set the power of motor 1 connnted to DC expansion controller with ID 1 to 50%
                                    // When using the expansion controllers, the first number (1) in the function parameter is the controller's ID#/I2C address.

  delay(2000);                      // wait here 2 seconds while motor spins
  exc.setMotorPower(1,1,0);         // Set Motor 1 power to 0. (0 = coast stop; 125 = brake stop)
  delay(1000);                      // wait here 1 second

  exc.setMotorPower(1,2,-50);       // Set the power of motor 2 connected to DC expansion controller with ID 1 to -50%.
  delay(2000);                      // wait here 2 seconds while motor spins
  exc.setMotorPower(1,2,0);         // Set Motor 2 power to 0. (0 = coast stop; 125 = brake stop)
  delay(1000);                      // wait here 1 second.

  exc.setMotorPowers(1,50,-50);     // Set the power of motor 1 to 50% and motor 2 to -50%. First number "1" is controller ID#.
  delay(2000);                      // wait here 2 seconds while motors spin
  exc.setMotorPowers(1,125,125);    // Stop motors(0 = coast stop; 125 = brake stop)
  delay(1000);                      // wait here 1 second, then repeat

}




