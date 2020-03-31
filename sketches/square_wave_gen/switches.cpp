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

// update duty ratio value
void update_duty() {
  read_bcd(1);
//  DEBUG_PRINTLN("update_duty");
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
