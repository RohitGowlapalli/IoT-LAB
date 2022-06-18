#include <Arduino.h>
#include "WiFi.h"
#include "HTTPClient.h"
#include "time.h"
#include <ArduinoJson.h>
char *wifi_ssid = "Galaxy M31A913";
char *wifi_pwd = "rhyr5785";
String cse_ip = "192.168.125.123"; // YOUR IP from ipconfig/ifconfig
String cse_port = "8080";
String server = "http://" + cse_ip + ":" + cse_port + "/~/in-cse/in-name/";
String ae = "HC-Sr04";
String cnt = "node1";

WiFiClient client;

const int trigger = 5;
const int echo = 18;
#define speed 0.034
#define conv 0.01
float TIME;
float distance1;

void createCI(const String &val)
{
  // add the lines in step 3-6 inside this function
  HTTPClient http;
  http.begin(server + ae + "/" + cnt + "/");

  http.addHeader("X-M2M-Origin", "admin:admin");
  http.addHeader("Content-Type", "application/json;ty=4");

  int code = http.POST("{\"m2m:cin\": {\"cnf\":\"application/json\",\"con\": " + String(val) + "}}");
  // Check if the request has been sent and close the connection
  Serial.println(code);
  if (code == -1)
  {
    Serial.println("UNABLE TO CONNECT TO THE SERVER");
  }
  http.end();
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(echo, INPUT);
  pinMode(trigger, OUTPUT);
  //WiFi.mode(WIFI_STA);
  WiFi.begin(wifi_ssid, wifi_pwd);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print("Connecting...");
  }
  Serial.println("");
  Serial.println("Successfully connected to WiFi.");
  Serial.println("IP address is : ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  // put your main code here, to run repeatedly:
  digitalWrite(trigger, LOW);
  delayMicroseconds(100);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  TIME = pulseIn(echo, HIGH);
  distance1 = (speed * TIME) / 2;
  Serial.println("Distance in cm: ");
  Serial.println(distance1);

  createCI(String(distance1));

  delay(10000);
}