#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>


Adafruit_BME280 bme;

unsigned long delayTime;
void bme280readings();
void setup() {
  Serial.begin(9600);
  if(! bme.begin(0x76, &Wire)){
    Serial.println("Could not find a valid BME280"); //check if you can find BME280
    while(1);
  }
  bme.setSampling(Adafruit_BME280::MODE_FORCED, Adafruit_BME280::SAMPLING_X1, Adafruit_BME280::SAMPLING_X1, Adafruit_BME280::SAMPLING_X1, Adafruit_BME280::FILTER_OFF);
  //weather station mode from datasheet
  delayTime = 10000; //recommended delay time from datasheet 60000
}

void loop() {
  bme.takeForcedMeasurement(); //using force mode
  bme280readings();
  delay(delayTime);
}


void bme280readings() {
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

