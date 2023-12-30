/*  PRIZM Controller example program
 *  Blink the PRIZM red LED at a 1 second flash rate
 *  author PWU on 08/05/2016
*/
  
  #include <PRIZM.h>      // include the PRIZM library

  PRIZM prizm;            // instantiate a PRIZM object "prizm" so we can use its functions

void setup() {

   prizm.PrizmBegin();   // initialize the PRIZM controller

}

void loop() {     // repeat this code in a loop

  prizm.setRedLED(HIGH);    // turn the RED LED on
  delay(1000);              // wait here for 1000ms (1 second)
  prizm.setRedLED(LOW);     // turn the RED LED off
  delay(1000);              // wait here for 1000ms (1 second)
 

}












