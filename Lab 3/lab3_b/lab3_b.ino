#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#define I2C_SDA 33
#define I2C_SCL 32

#define SEALEVELPRESSURE_HPA (1013.25)

TwoWire I2CBMP = TwoWire(0);
Adafruit_BMP280 bmp(&I2CBMP);

unsigned long delayTime;

void setup() {
  Serial.begin(9600);
  Serial.println(F("BMP280 test"));
  I2CBMP.begin(I2C_SDA, I2C_SCL, 100000);

  bool status;

  // default settings
  // (you can also pass in a Wire library object like &Wire2)

  status = bmp.begin(0x76);  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  Serial.println("-- Default Test --");
  delayTime = 1000;

  Serial.println();
}

void loop() { 
  printValues();
  delay(delayTime);
}

void printValues() {
  Serial.print("Temperature = ");
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");
  
  // Convert temperature to Fahrenheit
  Serial.print("Temperature = ");
  Serial.print(1.8 * bmp.readTemperature() + 32);
  Serial.println(" F");
  
  Serial.print("Pressure = ");
  Serial.print(bmp.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bmp.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");
/*
  Serial.print("Humidity = ");
  Serial.print(bmp.readHumidity());
  Serial.println(" %");
  */

  Serial.println();
}
