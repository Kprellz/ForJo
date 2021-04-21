
#include <Wire.h>
#include <Arduino.h>

class IOExpander {
  private:
    int mAddress;
    TwoWire &myWire;
  public:
    IOExpander(int _Address, TwoWire &_myWire) : mAddress(_Address), myWire(_myWire) {
     
    }
    void StartWire() {
      myWire.begin();
    }

    void IOExpanderSetup(int _Port0, int _Port1, int _Inv) {
      //configure IO expander
      myWire.beginTransmission(mAddress);
      myWire.write(0x6);
      myWire.write(_Port0);
      myWire.write(_Port1);
      myWire.endTransmission();
      //Set port Invert polarity
      myWire.beginTransmission(mAddress);
      myWire.write(0x4);
      myWire.write(0x00);
      myWire.write(_Inv);
      myWire.endTransmission();
    }

    void WriteIOExpander(int _Port0, int _Port1) {
      //set IO Expander Output HIGH/LOW
      myWire.beginTransmission(mAddress);
      myWire.write(0x2);
      myWire.write(_Port0);
      myWire.write(_Port1);
      myWire.endTransmission();
    }

    byte ReadIOExpander() {
      byte low, high;
      //prepare i2c bus to read
      myWire.beginTransmission(mAddress);
      myWire.write(0);
      myWire.endTransmission();
      //read i2c bus
      myWire.beginTransmission(mAddress);
      myWire.requestFrom(mAddress, 2u);

      //while (!myWire[mI2C].available()) {};
      low = myWire.read();
      //while (!myWire[mI2C].available()) {};
      high = myWire.read();

      myWire.endTransmission();
      //return 16 bit value
      return high;
    }

};
