//Interrupts using Arduino

volatile int output = LOW;                      
int i = 0;   

void setup() {

  // initialize the button pin as a input:
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  
  // initialize the LED as an output:
  //pinMode(13, OUTPUT);
  
  // initialize serial communication:
  Serial.begin(9600);
  
  delay(5000);                                                     
                                                                           
  attachInterrupt(digitalPinToInterrupt(3),buttonPressed3,RISING);  //  function for creating external interrupts at pin3 on Rising (LOW to HIGH)   
  attachInterrupt(digitalPinToInterrupt(4),buttonPressed4,RISING);  //  function for creating external interrupts at pin4 on Rising (LOW to HIGH)   

}

void loop()                                                      
{  
   Serial.print("COUNTER: ");                                           
   Serial.println(i);                                                  
   ++i;                                                            
   delay(1500);   
//   digitalWrite(13, output);     //Turns LED ON or OFF depending upon output value
   Serial.println("--------------------------------------------");                                                  

}

void buttonPressed3()           //ISR function excutes when push button at pin 3 is pressed                             
{                    
//   output = HIGH;               //Change Output value to HIGH
  i = i + 10;                                    
}


void buttonPressed4()           //ISR function excutes when push button at pin 4 is pressed                             
{                    
//   output = LOW;               //Change Output value to HIGH
  i = i + 100;                                    
}
