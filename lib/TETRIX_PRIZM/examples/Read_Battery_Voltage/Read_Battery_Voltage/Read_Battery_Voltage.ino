/* This example demonstrates how to read the PRIZM controller's battery voltage and print it to the Serial Moniitor.
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

  
  int x = prizm.readBatteryVoltage();      // Place the battery voltage returned by the function into
                                           // integer variable x. 
                                           // For example, a value of 1268 = 12.68 volts.

  Serial.println(x);
  delay(250);       // print to serial monitor ever 250 milliseconds (1/4 second).                                           
                                                 

  

  
}





