 #include "BluetoothSerial.h"
BluetoothSerial SerialBT;
const int buzzer=17;
const int trigger=5;
const int echo =18;
#define speed 0.034
#define conv 0.01
float  TIME;
float distance1;
float distance2;
//float digit;
String DATA;
float threshold = 20;
void setup(){
  Serial.begin(115200);
   pinMode(echo,INPUT);
  pinMode(trigger,OUTPUT);
  pinMode(buzzer,OUTPUT);
 digitalWrite(buzzer,1);
  SerialBT.begin("Table-18");
  //Serial.println("Bluetooth Started! Ready to pair...");

}
void loop()
{
  digitalWrite(trigger,LOW);
  delayMicroseconds(100);
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  TIME=pulseIn(echo,HIGH);
  distance1=(speed*TIME)/2;
  distance2=(distance1)/100;
 /* Serial.print("Distance in cm");
  Serial.println(distance1);
  Serial.println("Distance in m");
  Serial.println(distance2);
  */
  delay(1000);
//  digit= 0;
  if (SerialBT.available()) threshold = 0;
  while (SerialBT.available())
  {
   /* threshold *= (float) 10;
    digit= (float) SerialBT.read() - '0';
    
    threshold += digit;
   */
    delay(10);
    DATA=SerialBT.readString();
    threshold = (float) DATA.toInt();

    SerialBT.print("the threshold is ");
  SerialBT.println(threshold);
  }
  SerialBT.print("Distance in CM: ");
  SerialBT.println(distance1);
  if(distance1>threshold)
  {
    digitalWrite(buzzer,1);
    //SerialBT.println("Distance >Threshold");
  }
  else{
    digitalWrite(buzzer,0);
    SerialBT.println("Object in vicinity.");
  }
 // 
 
}




 
