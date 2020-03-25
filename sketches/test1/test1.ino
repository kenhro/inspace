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
int val = 0;

// the setup function runs once when you press reset or power the board
void setup() {

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  // initialize analog output pin
  pinMode(15, OUTPUT);  // analog output
  
  // initialize thumbswitch common pins as inputs (with pull-up resistor)
  pinMode(0, INPUT_PULLUP); // THSW-1
  pinMode(1, INPUT_PULLUP); // THSW-2
  pinMode(2, INPUT_PULLUP); // THSW-3

  // initialize 4 BCD pins as output
  pinMode(3, OUTPUT); // BCD 1
  pinMode(4, OUTPUT); // BCD 2
  pinMode(5, OUTPUT); // BCD 4
  pinMode(6, OUTPUT); // BCD 8

  // initialize serial output rate
  Serial.begin(9600);
  Serial.println("setup done");
  
}

// the loop function runs over and over again forever
void loop() {
  
  // enable thumbswitch
  digitalWrite(0, LOW);  // set common pin low to enable this THSW

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
  if (v1 == 0 && v2 == 0) {
    val = 255;
  }
  else { // otherwise
    val = 128;
  }
  analogWrite(15, val);
  delay(2000);                       // wait
  
  digitalWrite(LED_BUILTIN, LOW);    // turn the built-in LED off (LOW)
  analogWrite(15, 0);
  delay(2000);                       // wait

}
