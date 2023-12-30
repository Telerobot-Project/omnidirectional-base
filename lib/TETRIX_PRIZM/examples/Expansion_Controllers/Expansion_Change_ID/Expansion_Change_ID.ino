/* This example program demonstates how to change the ID# of a TETRIX Expansion Controller connected to the PRIZM controllers expansion port.
 * Up to four DC/Servo controllers may be connected to a PRIZM expansion port in a daisy chain. Be default, DC controllers are set to ID# 1 and  
 * Servo controllers to ID# 2. If additional controllers are added, they must be changed to a different ID#.
 * Important: When reading/changing the ID# of a controller, only one (1) controller can be connected to the expansion port.
 * Each controller's ID must be read/written separately - only one controller connected to PRIZM.
 * For additional details,please download the specififcation documents for the expansion controllers at www.TETRIXRobotics.com.
 */

#include <PRIZM.h>      // Include the PRIZM library in sketch

PRIZM prizm;            // Instantiate an object in the PRIZM class named "prizm".
EXPANSION exc;          // Instantiate an object in the EXPANSION class named "exc". Shortend name for expansion controller.
                        // "exc" can be changed to whatever you wish.

void setup() {

  Serial.begin(9600);   // Setup the Serial Monitor at 9600 baud.
  prizm.PrizmBegin();   // Initiates the PRIZM controller. Must be called at the beginning of the sketch

}

void loop() {

  int x = exc.readExpID();  // read the ID# of the expansion controller connected to the PRIZM expansion port.
                            // Important: Only one controller can be connected when using this function.

  Serial.print("Expansion Controller ID# found = ");        // Print the ID# of current ID# to the Serial Monitor. You must open the serial monitor to view.
  Serial.print(x);
  Serial.println(" ");      // blank line

  exc.setExpID(3);          // Change the ID# of the controller to "3". Valid ID's supported by PRIZM are 1,2,3 and 4.

  Serial.println("Expansion Controller ID# changed.");      // Print changed message.
                                                            // The new ID# will be activated upon a power off/on cycle of the controller
  
  prizm.PrizmEnd();         // Terminate program
                              
}




