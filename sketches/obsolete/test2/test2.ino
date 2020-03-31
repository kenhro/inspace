/*
  test1

  Set pin for thumbswitch #1's common to low and verify we can read 4 BCD lines to get values from 0 to 9
  and map those values to analog output voltages between 4.1V and 5.0V in 0.1V increments.

  modified 20 March 2020
  by Ken Hrovat
*/

int v1 = 0; // BCD line 1
int v2 = 0; // BCD line 2
int v4 = 0; // BCD line 4
int v8 = 0; // BCD line 8
int val = 180;  // output level 0-255 maps to 0-2.275V
                // BUT output saturates at ~2.275V when val = 185 [only check with USB power]

// the setup function runs once when you press reset or power the board
void setup() {

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  // initialize analog output pin
  pinMode(15, OUTPUT);  // analog output
  
  // initialize thumbswitch common pins as outputs
  pinMode(0, OUTPUT); // THSW-1 FREQ
  pinMode(1, OUTPUT); // THSW-2 DUTY
  pinMode(2, OUTPUT); // THSW-3 AMP

  // initialize 4 BCD pins as inputs
  pinMode(3, INPUT_PULLUP); // BCD bit 1
  pinMode(4, INPUT_PULLUP); // BCD bit 2
  pinMode(5, INPUT_PULLUP); // BCD bit 4
  pinMode(6, INPUT_PULLUP); // BCD bit 8

  // initialize serial output rate
  Serial.begin(9600);
  Serial.println("setup done");
  delay(3000);
  
}

// the loop function runs over and over again forever
void loop() {
  
  // enable just first thumbswitch
  digitalWrite(0, LOW);  // set common pin low to enable this THSW
  digitalWrite(1, HIGH); // set common pin high to disable this THSW
  digitalWrite(2, HIGH); // set common pin high to disable this THSW

  // read BCD lines
  v1 = digitalRead(3);   // read pin for BCD 1 (R1)
  v2 = digitalRead(4);   // read pin for BCD 2 (R2)
  v4 = digitalRead(5);   // read pin for BCD 4 (R3)
  v8 = digitalRead(6);   // read pin for BCD 8 (R4)

  Serial.print(v1);
  Serial.print(v2);
  Serial.print(v4);
  Serial.println(v8);

  digitalWrite(LED_BUILTIN, HIGH);   // turn the built-in LED on (HIGH)
//  if (v1 == 0 && v2 == 0) {
//    val = 255;
//  }
//  else { // otherwise
//    val = 128;
//  }
  val = val + 1;
  if (val > 190) { val = 180; }
  analogWrite(15, val);
  Serial.println(val);
  delay(2000);                       // wait
  
  digitalWrite(LED_BUILTIN, LOW);    // turn the built-in LED off (LOW)
  analogWrite(15, 0);
  delay(2000);                       // wait

  Serial.println("----------");

}
