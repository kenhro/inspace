/* square_wave_gen

  Square wave generator.  This sketch continuously polls each of 3 thumbwheel
  switch inputs in order to update the analog square wave output.  These
  switches control waveform parameters with one switch for each of frequency,
  duty ratio and amplitude.
  
  To read a thumbwheel switch, we set its common pin low and then read the 4 BCD
  lines to get values from 0 to 9, and then we map those values to desired
  frequency, duty ratio and amplitude.

  modified 26 March 2020 by Ken Hrovat

*/

// Comment out the next line with 2 leading slashes // to suppress debug prints
#define DEBUG

#include "debug_print.h"
#include "parameters.h"

// declare variables to save BCD values
int v1 = 0; // store BCD line 1 value
int v2 = 0; // store BCD line 2 value
int v4 = 0; // store BCD line 4 value
int v8 = 0; // store BCD line 8 value

// declare index values for switch (one of 3 switches) & array element (ten choices)
int isw = 0;  // index of thumbswitch to be polled
int idx = 0;  // index of 2D array element gives FREQ, DUTY, or AMP value

// initialize analog square wave params using first element from each array
float params[3] = { parameters[0][0], parameters[1][0], parameters[2][0] };

// initialize actual waveform variables derived from freq, duty ratio & amplitude params
float T = 1 / params[0];  // total period in seconds
float w = params[1] * T;  // width of "ON" pulse in seconds; duty ratio times period
float z = T - w;          // width of "OFF" (zero) in seconds
float a = params[2];      // amplitude in terms of DAC level
       
// the setup function runs once when you press reset or first power the board
void setup() {

  // initialize analog output pin
  pinMode(15, OUTPUT);  // analog square wave output
  
  // initialize thumbswitch common pins as outputs
  pinMode(0, OUTPUT); // THSW-1 FREQ
  pinMode(1, OUTPUT); // THSW-2 DUTY
  pinMode(2, OUTPUT); // THSW-3 AMP

  // initialize 4 BCD pins as inputs
  pinMode(3, INPUT); // BCD bit 1
  pinMode(4, INPUT); // BCD bit 2
  pinMode(5, INPUT); // BCD bit 4
  pinMode(6, INPUT); // BCD bit 8

  // change the analog write resolution to 10-bit
  analogWriteResolution(10);  // default is 8-bit

  // initialize serial output
  Serial.begin(9600); // baud rate must match what you use in Serial Monitor utility
  while (!Serial);  // FIXME this blocks further execution until Serial Monitor is open/available
  Serial.println("initial parameters are:");
  for (int i = 0; i <= 2; i++) {
    Serial.print(labels[i]);
    Serial.print(" = ");
    Serial.print(params[i]);
    Serial.print(" ");
    Serial.println(units[i]);
  }
  Serial.println("setup done");
  Serial.println("========================================================================");
  delay(2000);
  
}

// the loop function runs forever
void loop() {

  for (isw = 0; isw <= 2; isw++) {
  
    // disable all thumbswitches
    digitalWrite(0, HIGH); // set common pin high to disable this THSW
    digitalWrite(1, HIGH); // set common pin high to disable this THSW
    digitalWrite(2, HIGH); // set common pin high to disable this THSW
  
    //enable thumbswitch of interest
    digitalWrite(isw, LOW);  // set common pin low to enable this THSW
  
    Serial.print("Polling thumbswitch #");
    Serial.print(isw + 1);
    Serial.print(" for ");
    Serial.print(labels[isw]);
    Serial.println(" (simulated)");
    
    // read BCD lines
    v1 = digitalRead(3);   // read pin for BCD 1 (R1)
    v2 = digitalRead(4);   // read pin for BCD 2 (R2)
    v4 = digitalRead(5);   // read pin for BCD 4 (R3)
    v8 = digitalRead(6);   // read pin for BCD 8 (R4)
  
    // convert BCD to index aue into 2D array of square wave parameters
    idx = bcd2index(v1, v2, v4, v8);

    // update this parameter in 3-element float array
    params[isw] = parameters[isw][idx];
    T = 1 / params[0];  // period in seconds
    w = params[1] * T;  // width of pulse "ON" in seconds is duty cycle times period
    z = T - w;          // zero span "OFF" in seconds
    a = params[2];      // amplitude in DAC level

    Serial.print("INPUTS: ");
    Serial.print(v8);
    Serial.print(v4);
    Serial.print(v2);
    Serial.print(v1);
    Serial.print(" --> ");
    Serial.print(" idx = ");
    Serial.print(idx);
    Serial.print(" ==> ");
    Serial.print(params[isw]);
    Serial.print(" ");
    Serial.println(units[isw]);

    // write the "ON" pulse of square wave output
    analogWrite(15,(int)a);
    delay(1000*w);  // wait
    
    // write the "OFF" zeros part of square wave output
    analogWrite(15, 0);
    delay(1000*z);  // wait

    Serial.print("OUTPUT: [DAC output level (0-1023)]: ");
    Serial.print("T = ");
    Serial.print(T);
    Serial.print(" sec, w = ");
    Serial.print(w);
    Serial.print(" sec, z = ");
    Serial.print(z);
    Serial.print(" sec, a = ");
    Serial.println(a);
    
    Serial.println("-----------------------------------------------------");
    
  }
}

// convert binary input (inverse logic) values to index
int bcd2index(int v1, int v2, int v4, int v8){
  int result;
  result = 1 * (1 - v1) + 2 * (1 - v2) + 4 * (1 - v4) + 8 * (1 - v8);
  // FIXME what should we set index value to when internal state is out of bounds?
  if (result > 9) {result = 0;}
  return result;
}
