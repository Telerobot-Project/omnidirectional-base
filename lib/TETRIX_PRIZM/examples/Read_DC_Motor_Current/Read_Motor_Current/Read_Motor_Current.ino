/* This example demonstrates how to read the load current of a DC motor channel and print it to the Serial Moniitor.
 * For more detailed information on using the PRIZM library functions,
 * Please see the Arduino Library functions grid in the TETRIX PRIZM Programmer's guide 
 * which can be viewed and downloaded at www.TETRIXRobotics.com
 */


#include <PRIZM.h>    // Include PRIZM Library

PRIZM prizm;          // Instantiate an object named prizm




void setup() {

  Serial.begin(9600);   // Setup the serial monitor at 9600 baud. You must open the serial monitor to view data
  prizm.PrizmBegin();   // Initiates the PRIZM controller - must be called in the setup of each PRIZM sketch
  

}

void loop() {

  prizm.setMotorPower(1,50);               // Spin DC motor 1 at 50% power

  int x = prizm.readMotorCurrent(1);       // Place the  current value of motor channel 1 returned by the function into
                                           // integer variable x. Value returned is motor current in  milliamps.
                                           // For example, 1500 = 1.5 amps

  Serial.println(x);
  delay(250);       // print to serial monitor ever 250 milliseconds (1/4 second).                                           
                                                 

  

  
}





