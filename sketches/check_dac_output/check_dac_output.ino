/*
  check_dac_output

  Over a 30s span, ramp up DAC analog output level from 0 to 1023 so we can measure output levels.

  modified 23 March 2020
  by Ken Hrovat
*/

// constants won't change
const long interval =  9000;  // milliseconds between amplitude steps
const int dacStart = 0;       // atart DAC level output at this amount // 0, 725, 0
const int dacStep = 1;       // step DAC level output by this amount with each iteration of main loop // 64, 1, 1
const int dacEnd = 10;      // ending DAC level output at this amount // 1024, 740, 10

// variables will change
int dacLevel = 0;

void setup() {
  
  // initialize output pin
  pinMode(15, OUTPUT);  // analog square wave output
  
  // change the analog write resolution to 10-bit
  analogWriteResolution(10);  // default is 8-bit

  // initialize serial output
  Serial.begin(9600); // baud rate must match what you use in Serial Monitor utility
  while (!Serial);  // FIXME this blocks further execution until Serial Monitor is open/available
  Serial.println("setup done");
  Serial.println("========================================================================");
  delay(2000);
}

void loop() {

  for (int i = dacStart; i <= dacEnd; i+=dacStep) {

    // get usable DAC level
    dacLevel = min(i, 1023);
    
    // print DAC level
    Serial.println(dacLevel);

    // set output level
    analogWrite(15, dacLevel);

    delay(interval);
    
  }
  
}
