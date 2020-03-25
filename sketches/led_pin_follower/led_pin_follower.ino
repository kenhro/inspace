int ledPin = 13;  // built-in LED connected to digital pin 13
int outPin = 22;  // thumbwheel #1 common connected to this digital pin
int inPin = 16;   // thumbwheel #1 THSW1-1 connected to this digital pin
int val = 0;      // variable to store the read value

void setup() {
  pinMode(ledPin, OUTPUT);  // sets this digital pin as output
  pinMode(outPin, OUTPUT);  // sets this digital pin as output
  pinMode(inPin, INPUT);    // sets this digital pin as input
}

void loop() {
  digitalWrite(outPin, LOW);  // enable this thumbwheel switch by setting common low
  val = digitalRead(inPin);   // read the input pin
  digitalWrite(ledPin, val);  // sets the LED to the thumbwheel's value
}
