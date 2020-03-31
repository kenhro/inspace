/*
  Square Wave Generator

  Thumbwheel switches to control analog square wave output.

  See application note (AN043) "Methods for using thumbwheel switches as numeric input devices"
  By: Glenn Clark, Protean Logic Inc.

  modified 2020-03-11 by Ken Hrovat

*/

  
// square wave parameter arrays
int DUTY[] = {0, 5, 10, 20, 35, 50, 60, 75, 90, 100}; // array of duty cycle values (%)
float AMP[] = {4.1, 4.2, 4.3, 4.4, 4.5, 4.6, 4.7, 4.8, 4.9, 5.0}; // array of amplitude values (V)
float FREQ[] = {0.25, 0.5, 0.66, 1.0, 2.0, 2.66, 3.0, 5.0, 10.0, 20.0}; // array of frequency values (Hz)

// the setup function runs once when you press reset or power the board
void setup() {
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  // initialize serial rate
  Serial.begin(9600);
  Serial.println("setup done");
  
}

// the loop function runs over and over again forever
void loop() {

  for (int idx = 0; idx < 10; idx++) {
    
    // cycle through arrays
    Serial.print("Index = ");
    Serial.println(idx);
    Serial.println("----------------------------------------------------");
    
    Serial.print("Amplitude (V) = ");
    Serial.println(AMP[idx]);

    Serial.print("Duty Cycle (%) = ");
    Serial.println(DUTY[idx]);

    Serial.print("Frequency (Hz) = ");
    Serial.println(FREQ[idx]);
    
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(200);                       // wait for a second
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(150);                        // wait for a 150ms
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(200);                       // wait for a second  
  }

}
