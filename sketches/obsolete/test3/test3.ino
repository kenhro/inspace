/*
  test3

  Set pin for thumbswitch #1's common to low and verify we can read 4 BCD lines to get values from 0 to 9
  and map those values to analog output voltages between 4.1V and 5.0V in 0.1V increments.

  modified 20 March 2020
  by Ken Hrovat
*/

int v1 = 0; // BCD line 1
int v2 = 0; // BCD line 2
int v4 = 0; // BCD line 4
int v8 = 0; // BCD line 8

int iSW = 0;  // index for first thumbswitch to be polled
int idx = 0;  // index for column of 2D array to yield either a FREQ, a DUTY, or an AMP aue (depending on THSW)

// FIXME this is not good practice to separate these labels from underlying values in fda, array, below
String labels[3] = { "Frequency", "Duty", "Amplitude" };
String units[3] = { "Hz", "ratio", "daclevel" };

// square wave parameters' 2d array for frequency, duty cycle and amplitude
float fda[3][10] = {
  { 0.25, 0.5, 0.66, 1.0, 2.0, 2.66, 3.0, 5.0, 10.0, 20.0 },  // FREQ values in Hz
//  { 0.0, 0.05, 0.1, 0.2, 0.35, 0.5, 0.6, 0.75, 0.9, 1.0},  // DUTY cycle values
  { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0},  // DUTY cycle values FIXME for testing we set all duty ratios to 1.0
  //{ 4.1, 4.2, 4.3, 4.4, 4.5, 4.6, 4.7, 4.8, 4.9, 5.0}                  // AMP  values in V << we need to look at this 0-1023 w/saturation starting at 185!
//  { 112.0, 120.0, 128.0, 136.0, 144.0, 152.0, 160.0, 168.0, 176.0, 184.0}  // AMP  values in DAC level (non-saturated region) this was for 8-bit DAC
  { 448.0, 480.0, 512.0, 544.0, 576.0, 608.0, 640.0, 672.0, 704.0, 736.0}  // AMP  values in DAC level (non-saturated region) this was for 8-bit DAC
  };

// initialize analog square wave parameters using first element from each array
// FIXME what should initial values be?
float params[3] = { fda[0][0], fda[1][0], fda[2][0] };

// initialize internal waveform variables
float T = 1 / params[0];  // period in seconds
float w = params[1] * T;  // width of pulse "ON" in seconds is duty cycle times period
float z = T - w;          // zero span "OFF" in seconds
float a = params[2];        // amplitude in DAC level (minding saturation, starting at ~1V?)
//int a = 180;  // output level 0-1023 maps to 0-2.275V
                // BUT output saturates at ~2.275V when a = 185 [only check with USB power]
       
// the setup function runs once when you press reset or power the board
void setup() {

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

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

// the loop function runs over and over again forever
void loop() {

  for (iSW = 0; iSW <= 2; iSW++) {
  
    // disable all thumbswitches
    digitalWrite(0, HIGH); // set common pin high to disable this THSW
    digitalWrite(1, HIGH); // set common pin high to disable this THSW
    digitalWrite(2, HIGH); // set common pin high to disable this THSW
  
    //enable thumbswitch of interest
    digitalWrite(iSW, LOW);  // set common pin low to enable this THSW
  
//    Serial.print("Polling thumbswitch #");
//    Serial.print(iSW + 1);
//    Serial.print(" for ");
//    Serial.print(labels[iSW]);
//    Serial.println(" (simulated)");
    
    // read BCD lines
    v1 = digitalRead(3);   // read pin for BCD 1 (R1)
    v2 = digitalRead(4);   // read pin for BCD 2 (R2)
    v4 = digitalRead(5);   // read pin for BCD 4 (R3)
    v8 = digitalRead(6);   // read pin for BCD 8 (R4)
  
    // convert BCD to index aue into 2D array of square wave parameters
    idx = bcd2index(v1, v2, v4, v8);

    // update this parameter in 3-element float array
    params[iSW] = fda[iSW][idx];
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
    Serial.print(params[iSW]);
    Serial.print(" ");
    Serial.println(units[iSW]);
    
  //  digitalWrite(LED_BUILTIN, HIGH);   // turn the built-in LED on (HIGH)
    analogWrite(15,(int)a);
    delay(1000*w);  // wait

  //  digitalWrite(LED_BUILTIN, LOW);    // turn the built-in LED off (LOW)
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
