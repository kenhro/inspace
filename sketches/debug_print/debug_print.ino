// Comment out next line with 2 leading slash // marks to suppress debug print statements
#define DEBUG

#include "debug_print.h"
#include "parameters.h"

void setup() {

  #ifdef DEBUG
    // initialize serial output
    Serial.begin(9600); // baud rate must match what you use in Serial Monitor utility
    while (!Serial);
  #endif
  DEBUG_PRINTLN("Begin setup...");
  DEBUG_PRINTLN(labels[0]);
  DEBUG_PRINTLN(params[0][5]);
  DEBUG_PRINTLN("===SETUP DONE =================================================================");
  delay(2000);

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
}
