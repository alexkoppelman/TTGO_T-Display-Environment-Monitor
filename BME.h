#include "Seeed_BME280.h"
#include <Wire.h>

BME280 bme280;

bool bme280_init(void) {
  return bme280.init();
}
 

bool bme280_read(float *temp, float *hum, float *pres) {
  bool result = true;
 
  if ((NULL == temp) || (NULL == hum) || (NULL == pres)) {
    result = false;
  }
 
  if (true == result) {
    *temp = bme280.getTemperature();
    *hum = bme280.getHumidity();
    *pres = bme280.getPressure()/1000;
 
    if (isnan(*hum) || isnan(*temp)) {
      result = false;
    }
  }
 
  return result;
}
