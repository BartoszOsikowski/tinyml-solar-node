#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "Adafruit_VEML7700.h"
#include "INA226.h"

Adafruit_BME280 bme;
Adafruit_VEML7700 veml;
INA226 INA0(0x40);
INA226 INA1(0x41);

unsigned long delayTime;
bool okBME = false, okVEML = false, okINA0 = false, okINA1 = false;
void bme280readings();
void veml7700readings();
void ina226readings();

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.setClock(50000); 
  

  okBME  = bme.begin(0x76, &Wire);
  okVEML = veml.begin();

  okINA0 = INA0.begin();
  okINA1 = INA1.begin();

  if (!okBME){
    Serial.println("Could not find a valid BME280");
  }  
  if (!okVEML){
    Serial.println("Could not find a valid VEML7700");
  } 
  if (!okINA0){
    Serial.println("Could not find a valid first INA226");
  } 
  if (!okINA1){
    Serial.println("Could not find a valid second INA226");
  }
  
  
  bme.setSampling(Adafruit_BME280::MODE_FORCED, Adafruit_BME280::SAMPLING_X1, Adafruit_BME280::SAMPLING_X1, Adafruit_BME280::SAMPLING_X1, Adafruit_BME280::FILTER_OFF);
  //weather station mode from datasheet
  INA0.setMaxCurrentShunt(1, 0.002);
  INA1.setMaxCurrentShunt(1, 0.002);
  
  delayTime = 3000; //recommended delay time from datasheet for bme 60000
  
}

void loop() {
  bme.takeForcedMeasurement(); //using force mode
  bme280readings();
  veml7700readings();
  ina226readings();
  delay(delayTime);
}

void ina226readings() {
  Serial.println("---------------------");
  Serial.print("Voltage1 = ");
  Serial.print(INA0.getBusVoltage_mV(), 3);
  Serial.println(" mV");
  Serial.print("Current1 = ");
  Serial.print(INA0.getCurrent_mA(), 3);
  Serial.println(" mA");
  Serial.print("Power1 = ");
  Serial.print(INA0.getPower_mW(), 3);
  Serial.println(" mW");
  Serial.println("---------------------");
  Serial.print("Voltage2 = ");
  Serial.print(INA1.getBusVoltage_mV(), 3);
  Serial.println(" mV");
  Serial.print("Current2 = ");
  Serial.print(INA1.getCurrent_mA(), 3);
  Serial.println(" mA");
  Serial.print("Power2 = ");
  Serial.print(INA1.getPower_mW(), 3);
  Serial.println(" mW");
}

void veml7700readings() {
  Serial.println("---------------------");
  Serial.print("Lux = ");
  Serial.print(veml.readLux(VEML_LUX_AUTO)); //lux readings
  Serial.println(" lux");
  //future i can get gain and integration time (if nessesery)
}

void bme280readings() {
  Serial.println("---------------------");
  Serial.print("Temp = ");
  Serial.print(bme.readTemperature());
  Serial.println(" C"); //temp reading

  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println( "hPa"); //pressure reading

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %"); //humidity reading
}

