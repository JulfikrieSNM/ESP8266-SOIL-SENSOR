int sensorPin = A0;  // Soil sensor AO connected to A0
int sensorValue = 0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  Serial.print("Soil Moisture Value: ");
  Serial.println(sensorValue);

  if(sensorValue < 400) {
    Serial.println("Tanah lembab");
  } else if(sensorValue >= 400 && sensorValue < 800) {
    Serial.println("Tanah sederhana lembah");
  } else {
    Serial.println("TANAH KERING! Sila siram tanaman anda.");
  }

  delay(2000);
}
