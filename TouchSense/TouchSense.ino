#include "Adafruit_FreeTouch.h"

Adafruit_FreeTouch qt_0 = Adafruit_FreeTouch(8, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_1 = Adafruit_FreeTouch(9, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_2 = Adafruit_FreeTouch(10, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_3 = Adafruit_FreeTouch(11, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_4 = Adafruit_FreeTouch(12, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_5 = Adafruit_FreeTouch(13, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_6 = Adafruit_FreeTouch(14, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_7 = Adafruit_FreeTouch(15, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);

void setup() {
  Serial.begin(115200);
  
  while (!Serial);
  Serial.println("FreeTouch test");
  // initialize digital pin LED_BUILTIN as an output.
//  pinMode(LED_BUILTIN, OUTPUT);

  if (! qt_0.begin())  
    Serial.println("Failed to begin qt on pin A02");
  if (! qt_1.begin())  
    Serial.println("Failed to begin qt on pin A03");
  if (! qt_2.begin())  
    Serial.println("Failed to begin qt on pin A04");
  if (! qt_3.begin())  
    Serial.println("Failed to begin qt on pin A05");
    if (! qt_4.begin())  
    Serial.println("Failed to begin qt on pin A06");
    if (! qt_5.begin())  
    Serial.println("Failed to begin qt on pin A07");
    if (! qt_6.begin())  
    Serial.println("Failed to begin qt on pin B00");
    if (! qt_7.begin())  
    Serial.println("Failed to begin qt on pin B01");
    

}



void loop() {
  int counter, result = 0;
  
  // DIY
  Serial.println("\n*************************************");

  counter = millis();
  result = qt_0.measure(); 
  Serial.print("PTC 0: "); Serial.print(result);
  Serial.print(" (");  Serial.print(millis() - counter); Serial.println(" ms)");

  counter = millis();
  result = qt_1.measure(); 
  Serial.print("PTC 1: "); Serial.print(result);
  Serial.print(" (");  Serial.print(millis() - counter); Serial.println(" ms)");

  counter = millis();
  result = qt_2.measure(); 
  Serial.print("PTC 2: "); Serial.print(result);
  Serial.print(" (");  Serial.print(millis() - counter); Serial.println(" ms)");
  
  counter = millis();
  result = qt_3.measure(); 
  Serial.print("PTC 3: "); Serial.print(result);
  Serial.print(" (");  Serial.print(millis() - counter); Serial.println(" ms)");

  counter = millis();
  result = qt_4.measure(); 
  Serial.print("PTC 4: "); Serial.print(result);
  Serial.print(" (");  Serial.print(millis() - counter); Serial.println(" ms)");

  counter = millis();
  result = qt_5.measure(); 
  Serial.print("PTC 5: "); Serial.print(result);
  Serial.print(" (");  Serial.print(millis() - counter); Serial.println(" ms)");

  counter = millis();
  result = qt_6.measure(); 
  Serial.print("PTC 6: "); Serial.print(result);
  Serial.print(" (");  Serial.print(millis() - counter); Serial.println(" ms)");

  counter = millis();
  result = qt_7.measure(); 
  Serial.print("PTC 7: "); Serial.print(result);
  Serial.print(" (");  Serial.print(millis() - counter); Serial.println(" ms)");
  delay(200);
}
