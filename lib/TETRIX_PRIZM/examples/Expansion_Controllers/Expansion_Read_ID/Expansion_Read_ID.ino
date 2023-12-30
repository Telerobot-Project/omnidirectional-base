/* This example program demonstates how to read the ID# of a TETRIX Expansion Controller connected to the PRIZM controllers expansion port.
 * The ID# is read into a variable X and printed to the Arduino Serial Monitor.
 * Important: When reading the ID# of a controller, only one (1) controller can be connected to the expansion port.
 * Each controller's ID must be read separately - one at a time.
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

  Serial.print("Expansion Controller ID# = ");        // Print the ID# to the Serial Monitor. You must open the serial monitor to view.
  Serial.print(x);
  Serial.println(" ");
  
  prizm.PrizmEnd();         // Terminate program
                              
}




