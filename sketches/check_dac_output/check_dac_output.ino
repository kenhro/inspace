/*
  check_dac_output

  Test calibration values; slowly step up DAC analog output level up to about 2V for 2.8 scale factor
  that gets us to desired coil voltage.

  modified 25 March 2020
  by Ken Hrovat
*/

// define output pins
#define out 15

// constants won't change
const long interval =  9000;  // milliseconds between amplitude steps
const int dacStart = 435;     // atart DAC level output at this amount // 435
const int dacStep = 25;       // step DAC level output by this amount with each iteration of main loop // 25
const int dacEnd = 660;       // ending DAC level output at this amount // 660

// Note: roughly-speaking, each change in DAC level output, gives about 3mV change in analog output voltage

// variables will change
int dacLevel = dacStart;

void setup() {
  
  // initialize output pin
  pinMode(out, OUTPUT);  // analog square wave output
  
  // change the analog write resolution to 10-bit (1024 levels)
  analogWriteResolution(10);  // default is 8-bit (256 levels)

  // initialize serial output
  Serial.begin(9600); // baud rate must match what we use in Serial Monitor utility
  while (!Serial);  // FIXME this blocks further execution until Serial Monitor is open/available
  Serial.println("setup done");
  Serial.println("========================================================================");
  delay(2000);
}

void loop() {

  for (int dacLevel = dacStart; dacLevel <= dacEnd; dacLevel += dacStep) {
    
    // print DAC level
    Serial.println(dacLevel);

    // set output level
    analogWrite(out, dacLevel);

    delay(interval); // time to jot down output value in Excel and be ready for change to next
    
  }
  
}
