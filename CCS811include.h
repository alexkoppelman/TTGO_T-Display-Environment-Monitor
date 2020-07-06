#include <Wire.h>    // I2C library
#include "ccs811.h"  // CCS811 library
#include <Arduino.h>
  CCS811 ccs811; 

bool ccs811_init(void) {
  bool result = true;  
  //initialise Sensor

  ccs811.set_i2cdelay(50); // Needed for ESP8266 because it doesn't handle I2C clock stretch correctly
  
  bool ok= ccs811.begin();
  if( !ok ) {
    Serial.println("setup: CCS811 begin FAILED");
    result=false;
  }
  ok= ccs811.start(CCS811_MODE_1SEC);
  
  if( !ok ) {
    Serial.println("setup: CCS811 start FAILED");
    result=false;
  } else {
    result=true;
  }
   
    return result;
}

// take sensor values
 
bool ccs811_read(uint16_t eco2, uint16_t etvoc, uint16_t errstat, uint16_t raw) {
  bool result = true;
 
  if ((NULL == eco2) || (NULL == etvoc)) {
    result = false;
  }
 
  if (true == result) {
  result = false;
  if( errstat==CCS811_ERRSTAT_OK ) { 
      uint16_t eco2, etvoc, errstat, raw, eco2b, etvocb;
      ccs811.read(&eco2,&etvoc,&errstat,&raw); 
        eco2b = eco2;
        etvocb = etvoc;
         result = true;           
          
    } else if( errstat==CCS811_ERRSTAT_OK_NODATA ) {
    Serial.println("CCS811: waiting for (new) data");
    } else if( errstat & CCS811_ERRSTAT_I2CFAIL ) { 
    Serial.println("I2C error");
}
  }
 
  return result;
}
