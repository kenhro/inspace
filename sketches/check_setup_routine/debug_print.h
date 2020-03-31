#ifdef DEBUG
  #define DEBUG_PRINT(x)     Serial.print(x)
  #define DEBUG_PRINTLN(x)   Serial.println(x)
  #define SERIAL_INIT()      Serial.begin(9600); while(!Serial)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTLN(x)
  #define SERIAL_INIT()
#endif

// FIXME this is not good practice to separate these labels from underlying values in another array
String labels[3] = { "Frequency", "Duty",  "Amplitude" };
String units[3] =  { "Hz",        "ratio", "daclevel" };
