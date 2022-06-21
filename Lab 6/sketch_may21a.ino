const int trigger=5;
const int echo =18;
#define speed 0.034
#define conv 0.01
float  TIME;
float distance1;
float distance2;
void setup(){
  Serial.begin(9600);
   pinMode(echo,INPUT);
  pinMode(trigger,OUTPUT);
 
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
  Serial.print("Distance in cm");
  Serial.println(distance1);
  Serial.println("Distance in m");
  Serial.println(distance2);
  delay(1000);
}
