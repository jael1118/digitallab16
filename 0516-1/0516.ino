int sensorValue = 0;
int sensorPin = A0;

int ledPin=13;

void setup() {
  
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
 
  int ledB=map(sensorValue,0,1023,0,255);  // read the input pin
  analogWrite(ledPin, ledB);
  delay(1);
}

