#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "Adafruit_VEML7700.h"

Adafruit_BME280 bme;
Adafruit_VEML7700 veml = Adafruit_VEML7700();

unsigned long delayTime;
void bme280readings();
void veml7700readings();

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.setClock(50000);
  if(! bme.begin(0x76, &Wire)){
    Serial.println("Could not find a valid BME280"); //check if you can find BME280
    while(1);
  }
  if(!veml.begin()){
    Serial.println("Could not find a valid VEML7700"); //check if you can find VEML7700
    while(1);
  }
  bme.setSampling(Adafruit_BME280::MODE_FORCED, Adafruit_BME280::SAMPLING_X1, Adafruit_BME280::SAMPLING_X1, Adafruit_BME280::SAMPLING_X1, Adafruit_BME280::FILTER_OFF);
  //weather station mode from datasheet
  delayTime = 10000; //recommended delay time from datasheet for bme 60000
}

void loop() {
  bme.takeForcedMeasurement(); //using force mode
  bme280readings();
  veml7700readings();
  delay(delayTime);
}

void veml7700readings() {
  Serial.println("---------------------");
  Serial.print("Lux = ");
  Serial.print(veml.readLux(VEML_LUX_AUTO)); //lux readings
  Serial.println(" lux");
  //future i can gain and integration time (if nessesery)
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

