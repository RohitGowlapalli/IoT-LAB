#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

const char* ssid = "Rohit's Galaxy A20"; 
const char* password = "jxos6973";

//const char *host = "maker.ifttt.com";
//const char privateKey = "gkb_HtIpE-FeOWMH20obLTvUR7_fPipDyj****";

WebServer server(80); 
void send_event(const char *event);

//int led_pin = 14;  
int sensor_pin = 26; 
String Message;

const char MAIN_page[] PROGMEM = R"=====(
<!doctype html>
<html>
<head>
<title>IoT Motion detector</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <h1 style="text-align:center; color:red;font-size: 2.5rem;">IoT Motion Detector</h1>
  <style>
  canvas{
    -moz-user-select: none;
    -webkit-user-select: none;
    -ms-user-select: none;
  }
  #data_table {
    font-family: New Times Roman;
    border-collapse: collapse;
    width: 100%;
    text-align: center;
    font-size: 0.8rem;
  }
  #data_table td, #data_table th {
    border: 3px solid #ddd;
    padding: 15px;
  }
  #data_table tr:nth-child(even){background-color: #f7dada;}
  #data_table tr:hover {background-color: #f7dada;}
  #data_table th {
    padding-top: 20px;
    padding-bottom: 20px;
    text-align: center;
    background-color: #e00909;
    color: white;
  }
  </style>
</head>
<body>   
<div>
  <table id="data_table">
    <tr><th>Time</th><th>Activity</th></tr>
  </table>
</div>
<br>
<br>  
<script>

var Avalues = [];
var dateStamp = [];

setInterval(function() {
  getData();
}, 3000); 
function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
  var date = new Date();
  var txt = this.responseText;
  var obj = JSON.parse(txt); 
      Avalues.push(obj.Activity);
      dateStamp.push(date);

    var table = document.getElementById("data_table");
    var row = table.insertRow(1); 
    var cell1 = row.insertCell(0);
    var cell2 = row.insertCell(1);
    cell1.innerHTML = date;
    cell2.innerHTML = obj.Activity;
    }
  };
  xhttp.open("GET", "read_data", true); 
  xhttp.send();
}    
</script>
</body>
</html>

)====="; 

void handleRoot() {
 String s = MAIN_page; 
 server.send(200, "text/html", s); 
}


void read_data() {
  int state = digitalRead(sensor_pin); 
  delay(500);                        
  Serial.print(state);
    if(state == HIGH){ 
      
    digitalWrite (led_pin, HIGH);    
    delay(1000);
    digitalWrite (led_pin, LOW);
    
    Message = "Motion Detected";
    String data = "{\"Activity\":\""+ String(Message) +"\"}";
    server.send(200, "text/plane", data); 
   // send_event("Motion_Detection");               
    Serial.println("Motion detected!");
    }
}


void setup() {
 Serial.begin(9600);
  WiFi.mode(WIFI_STA);
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print("Connecting...");
 }
 Serial.println("");
 Serial.println("Successfully connected to WiFi.");
 Serial.println("IP address is : ");
 Serial.println(WiFi.localIP());
 
server.on("/", handleRoot);     
server.on("/read_data", read_data);
server.begin();               
 
 pinMode(sensor_pin, INPUT); 
// pinMode(led_pin, OUTPUT); 
 //digitalWrite (led_pin, LOW);
}
void loop(){
  server.handleClient();         
}
/*
void send_event(const char *event)
{
  Serial.print("Connecting to "); 
 // Serial.println(host); 

  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed");
    return;
  } 

  String url = "/trigger/";
  url += event;
  url += "/with/key/";
  url += privateKey; 
  Serial.print("Requesting URL: ");
  Serial.println(url);  
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  while(client.connected())
  {
    if(client.available())
    {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    } else {
      delay(50);
    };
  }  
  Serial.println();
  Serial.println("Closing Connection");
  client.stop();
}
*/
