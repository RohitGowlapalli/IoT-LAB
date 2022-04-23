#include "Servo.h"
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
Servo servo1;
float angle=0;

float Min=31;
float Max=32;

static const int servoPin = 16;
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  servo1.attach(servoPin);
  dht.begin();
}
float temp1=0;
float temp2=0;
float hum;
float hif;

void loop()
{
  temp1=dht.readTemperature();
   hum=dht.readHumidity();
  if(temp1==temp2)
  {
    servo1.write(angle+10);
    delay(500);
    servo1.write(angle-10);
    delay(500);
    return;
  }
 // hif = dht.computeHeatIndex(temp1,hum,false);
  /*
   if (isnan(hum) || isnan(temp1)) {
    //Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  */
 // Serial.println(hif);
 
 
  Serial.print(F("Humidity: "));
  Serial.print(hum);
  Serial.print(F("%  Temperature: "));
  Serial.print(temp1);
  
  
  
  
  if(temp1>Min&&temp1<Max)
  {
    angle = 180.0*(temp1-31);
    servo1.write(angle);
  }
  Serial.print(" Angle: ");
  Serial.print(angle);
  Serial.print("\n");
  delay(1000);
  
  temp2=temp1;
  
}
