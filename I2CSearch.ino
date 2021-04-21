// ---------------------------------------------------------------- /
// Arduino I2C Scanner
// Re-writed by Arbi Abdul Jabbaar
// Using Arduino IDE 1.8.7
// Using GY-87 module for the target
// Tested on 10 September 2019
// This sketch tests the standard 7-bit addresses
// Devices with higher bit address might not be seen properly.
// ---------------------------------------------------------------- /

#include <Wire.h> //include Wire.h library
//uncomment which i2c line youd like to search on (Be sure to change the mux address as well)
//TwoWire myWire(&sercom0,17,16);
//TwoWire myWire(&sercom1,20,19);
TwoWire myWire(&sercom2, 23, 22);
//TwoWire myWire(&sercom3,26,25);
//TwoWire myWire(&sercom4,29,28);
//TwoWire myWire(&sercom5,32,31);
void setup()
{
  delay(20);

  pinMode(38, OUTPUT);
  digitalWrite(38, HIGH); // Set OLEDReset High
  //delay(20);
  myWire.begin(); // Wire communication begin

  myWire.beginTransmission(0x72); // ------Make sure this matches the correct mux
  myWire.write(1);//-----------------------Set to 1 for the first channel of I2c Mux set to 2 for Second Channel
  myWire.endTransmission();
  //delay(20);
  Serial.begin(9600); // The baudrate of Serial monitor is set in 9600
  while (!Serial); // Waiting for Serial Monitor

}

void loop()
{

  byte error, address; //variable for error and I2C address
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    myWire.beginTransmission(address);
    error = myWire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");
      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000); // wait 5 seconds for the next I2C scan
}
