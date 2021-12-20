#include <Wire.h>
//#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

// connect SCL to I2C SCL Clock
// connect SDA to I2C SDA Data
   
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

void setup_LuxSensor(void){  
  /*
  Serial.println("Light Sensor Test"); Serial.println("");
  if(!tsl.begin())
  {
    Serial.print("Ooops, no TSL2561 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  */
  tsl.enableAutoRange(true);
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);
}

uint32_t getLight(void){
  
  sensors_event_t event;
  tsl.getEvent(&event);
  
  uint32_t light = event.light;

  delay(250);
  return light;
}
