int Sensor= A0;
double sensorValue;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = 5.0*(analogRead(Sensor)/1024.0);
  Serial.println(sensorValue);
}
