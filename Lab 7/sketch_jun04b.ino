#include<ThingSpeak.h>
#include<WiFi.h>
#include<WebServer.h>
unsigned long channel_num=1758347;
const char* ssid="Galaxy M31A913";
const char* password="rhyr5785";
int led;
unsigned int value;
WiFiClient client;   // make the client of the WiFi which connect to the ThingSpeak webServer
WebServer server(80);
void setup()
{
 pinMode(4,OUTPUT);
 digitalWrite(4,1);
 Serial.begin(115200);
 WiFi.begin(ssid,password);    // connect to the wifi STA connection
 while(WiFi.status()!=WL_CONNECTED)
 {
   delay(500);
   Serial.print(".");
 }
 Serial.println(WiFi.localIP());    // print the wifi local ip
 server.on("/",handleonconnect);    // in urt type the "/" then call the handle on connect function
 ThingSpeak.begin(client);      // connect the client to the thingSpeak server
 server.begin();   // start the server
}
void loop()
{
 server.handleClient();    // it realy handle the Client
 led=ThingSpeak.readFloatField(channel_num,1);    // read the last data of the field 1
 Serial.println(led);
 if(led==1)
 {
   digitalWrite(4,HIGH);
 }
 else if(led==0)
 {
   digitalWrite(4,LOW);
 }
}
String SendHTML(void){
 String ptr = "<!DOCTYPE html> <html>\n";
 ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
 ptr +="<title>LED Control</title>\n";
 ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
 ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
 ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
 ptr +=".button-on {background-color: #1abc9c;}\n";
 ptr +=".button-on:active {background-color: #16a085;}\n";
 ptr +=".button-off {background-color: #34495e;}\n";
 ptr +=".button-off:active {background-color: #2c3e50;}\n";
 ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
 ptr +="</style>\n";
 ptr +="</head>\n";
 ptr +="<body>\n";
 ptr +="<h1>ESP8266 with ThingSpeak Server</h1>\n";
 ptr +="<h3>Using Station(STA) Mode</h3>\n";
 ptr +="<h4>Control status For D1</h4>\n";
 ptr +="<a class=\"button button-on\" href=\"https://api.thingspeak.com/update?api_key=RQ0J0C2XBJHNPUF3&field1=1\">ON</a>\n";
 ptr +="<a class=\"button button-off\" href=\"https://api.thingspeak.com/update?api_key=RQ0J0C2XBJHNPUF3&field1=0\">OFF</a>\n";
 ptr +="</body>\n";
 ptr +="</html>\n";
 return ptr;
}
void handleonconnect()
{
 server.send(200,"text/html",SendHTML());
}