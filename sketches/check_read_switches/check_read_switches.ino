/* square_wave_gen

  Square wave generator.  This sketch continuously polls each of 3 thumbwheel
  switch inputs in order to update the analog square wave output.  These
  switches control waveform parameters with one switch for each of frequency,
  duty ratio and amplitude.
  
  To read a thumbwheel switch, we set its common pin low and then read the 4 BCD
  lines to get values from 0 to 9, and then we map those values to desired
  frequency, duty ratio and amplitude.

  modified 30 March 2020 by Ken Hrovat

*/

// Change last word in next line to: DEBUG for print statements, or FLIGHT to suppress those
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
  SERIAL_INIT();
  DEBUG_PRINTLN("initial parameters are:");
  for (int i = 0; i <= 2; i++) {
    DEBUG_PRINT(labels[i]);
    DEBUG_PRINT(" = ");
    DEBUG_PRINT(params[i]);
    DEBUG_PRINT(" ");
    DEBUG_PRINTLN(units[i]);
  }
  DEBUG_PRINTLN("setup done");
  DEBUG_PRINTLN("========================================================================");
  delay(2000);
}

// the loop function runs forever
void loop() {

  for (isw = 0; isw <= 2; isw++) {
  	for (int i = 0; i <= 9; i++) {
  		read_bcd(isw);
  		DEBUG_PRINT("change switch #");
  		DEBUG_PRINTLN(isw + 1);
  		debug_print_inputs();
        debug_print_outputs();
        DEBUG_PRINTLN("-----------------------------------------------------");
        delay(9000);   
  	}
  }
}

// disable all switches
void disable_all_switches() {
  // disable all thumbswitches
  digitalWrite(0, HIGH); // set common pin high to disable this THSW
  digitalWrite(1, HIGH); // set common pin high to disable this THSW
  digitalWrite(2, HIGH); // set common pin high to disable this THSW
}

// enable specificed thumbswitch
void enable_switch(int ix) {
  
  // disable all thumbswitches
  disable_all_switches();
  
  //enable thumbswitch of interest
  digitalWrite(ix, LOW);  // set common pin low to enable this THSW 
}

// check if duty ratio is zero
boolean is_duty_zero() {
  enable_switch(1); // enable duty ratio thumbswitch (pin 1 for duty)
  return digitalRead(3) == HIGH && digitalRead(4) == HIGH && digitalRead(5) == HIGH && digitalRead(6) == HIGH;
}

// convert binary input (inverse logic) values to index
int bcd2index(int v1, int v2, int v4, int v8){
  int result;
  result = 1 * (1 - v1) + 2 * (1 - v2) + 4 * (1 - v4) + 8 * (1 - v8);
  // FIXME what should we set index value to when internal state is out of bounds?
  if (result > 9) {result = 0;}
  return result;
}

// read BCD lines
void read_bcd(int k) { // read BCD lines for switch at index = k
  // enable kth switch
  enable_switch(k);
  
  // read BCD lines
  v1 = digitalRead(3);   // read pin for BCD 1 (R1)
  v2 = digitalRead(4);   // read pin for BCD 2 (R2)
  v4 = digitalRead(5);   // read pin for BCD 4 (R3)
  v8 = digitalRead(6);   // read pin for BCD 8 (R4)

  // disable all switches
  disable_all_switches();
  
  // convert BCD to index value into 2D array of square wave parameters
  idx = bcd2index(v1, v2, v4, v8);

  // update kth parameter in 3-element float array
  params[k] = parameters[k][idx];
  T = 1 / params[0];  // period in seconds
  w = params[1] * T;  // width of pulse "ON" in seconds is duty cycle times period
  z = T - w;          // zero span "OFF" in seconds
  a = params[2];      // amplitude in DAC level
}

// update duty ratio value
void update_duty() {
  read_bcd(1);
//  DEBUG_PRINTLN("update_duty");
}

// debug print inputs
void debug_print_inputs() {
  DEBUG_PRINT("INPUTS: ");
  DEBUG_PRINT(v8);
  DEBUG_PRINT(v4);
  DEBUG_PRINT(v2);
  DEBUG_PRINT(v1);
  DEBUG_PRINT(" --> ");
  DEBUG_PRINT(" idx = ");
  DEBUG_PRINT(idx);
  DEBUG_PRINT(" ==> F = ");
  DEBUG_PRINT(params[0]);
  DEBUG_PRINT(" ");
  DEBUG_PRINT(units[0]);
  DEBUG_PRINT(", D = ");
  DEBUG_PRINT(params[1]);
  DEBUG_PRINT(" ");
  DEBUG_PRINT(units[1]);
  DEBUG_PRINT(", A = ");
  DEBUG_PRINT(params[2]);
  DEBUG_PRINT(" ");
  DEBUG_PRINTLN(units[2]);
}

// debug print outputs
void debug_print_outputs() {
  DEBUG_PRINT("OUTPUT: [DAC output level (0-1023)]: ");
  DEBUG_PRINT("T = ");
  DEBUG_PRINT(T);
  DEBUG_PRINT(" sec, w = ");
  DEBUG_PRINT(w);
  DEBUG_PRINT(" sec, z = ");
  DEBUG_PRINT(z);
  DEBUG_PRINT(" sec, a = ");
  DEBUG_PRINTLN(a);
}
