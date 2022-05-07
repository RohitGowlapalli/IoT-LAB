#define POWER_PIN  16 // ESP32 pin GIOP17 connected to sensor's VCC pin
#define SIGNAL_PIN 36 // ESP32 pin GIOP36 (ADC0) connected to sensor's signal pin
#define touch_pin_numer T0
const int BUZZER_PIN       = 17;
const int VALUE_THRESHOLD = 30;
int TOUCH_SENSOR_VALUE;
int T = 9999999;

void setup() {
  Serial.begin(9600);
  pinMode(POWER_PIN, OUTPUT);   // configure pin as an OUTPUT
  digitalWrite(POWER_PIN, LOW); // turn the sensor OFF
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN,1);
}


void loop() {
  int value;
  TOUCH_SENSOR_VALUE = touchRead(touch_pin_numer);
   Serial.print("The touch value is");
  Serial.println(TOUCH_SENSOR_VALUE);
  digitalWrite(POWER_PIN, HIGH);  // turn the sensor ON
  if (TOUCH_SENSOR_VALUE < VALUE_THRESHOLD)
  {
    Serial.println("The sensor is being touched");

    T = analogRead(SIGNAL_PIN); // read the analog value from sensor
    Serial.print("The threshold value of water level is");
    Serial.println(T);
  }
  //After touch, record threshold water level and store in T.
  //Check in each loop if water level higher than T.
  value = analogRead(SIGNAL_PIN);
   Serial.print("The height of water level is");
  Serial.println((value/2182.0)*40);
  digitalWrite(POWER_PIN, LOW);// turn the sensor OFF
  if (value > T)
  {
    Serial.println("The water level is higher than the threshold");
    digitalWrite(BUZZER_PIN, 0);
  }
  delay(1000);
  digitalWrite(BUZZER_PIN, 1);

}
