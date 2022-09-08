#include <VL6180X.h>

#include <Arduino.h>
#include "TCA9548A.h"

#define n_sensors 2

TCA9548A I2CMux;  // Address can be passed into the constructor
VL6180X  sensors[n_sensors];


void setup() {
  Serial.begin(9600);
  //  Wire.setPins(21, 22);       // ESP32 users, use setPins(sda, scl) if customised, *before* passing Wire to the library (the line below).  
  I2CMux.begin(Wire);             // Wire instance is passed to the library
  I2CMux.closeAll();
  for(int i = 0; i < n_sensors; i++)
  {
    Serial.print("sensor ");
    Serial.print(i);
    Serial.print(",");
    I2CMux.openChannel(i);
    sensors[i].init();
    sensors[i].configureDefault();
    sensors[i].writeReg(VL6180X::SYSRANGE__MAX_CONVERGENCE_TIME, 30);
    sensors[i].writeReg16Bit(VL6180X::SYSALS__INTEGRATION_PERIOD, 50);
    sensors[i].setTimeout(500);
    sensors[i].stopContinuous();
    delay(300);
    sensors[i].startInterleavedContinuous(100);
    I2CMux.closeChannel(i);
    
  }
  Serial.println();
  I2CMux.closeAll();              // Set a base state which we know (also the default state on power on)
}

void loop() 
{
  I2CMux.closeAll();
  for(int i = 0; i < n_sensors; i++)
  {
    I2CMux.openChannel(i);
    int val = sensors[i].readRangeContinuous();
    if(!sensors[i].timeoutOccurred())
    {
      Serial.print(val);
        
    }else{
      Serial.print("TIMEOUT");
    }
    Serial.print(",");
    I2CMux.closeChannel(i);
    
  }
  Serial.println();

  
}
