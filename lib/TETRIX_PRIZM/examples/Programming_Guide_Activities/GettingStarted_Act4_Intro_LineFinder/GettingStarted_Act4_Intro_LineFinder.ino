/*  This program will read the digital signal of the
 *  Line Finder sensor attached to digital port D3.
 *  If the sensor is facing a reflective surface and 
 *  receiving a reflected IR beam, the PRIZM red LED
 *  will switch on. If the sensor is facing a dark 
 *  surface, or too far away from a reflective surface
 *  the red LED will be off. 
 */
  
  #include <PRIZM.h>    //include the PRIZM Library
  PRIZM prizm;          //create an object name of "prizm"

void setup() {          //this code runs once

  prizm.PrizmBegin();   //initialize PRIZM
  
}

void loop() {           //this code repeats in a loop

  if(prizm.readLineSensor(3) == HIGH) {prizm.setRedLED(LOW);}  // LED off

  if(prizm.readLineSensor(3) == LOW)  {prizm.setRedLED(HIGH);} // LED on
  
  delay(50);  //slow the loop down

}







