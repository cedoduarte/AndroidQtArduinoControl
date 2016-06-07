#define LED_PIN 2

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  if (Serial.available()) {
    const int selectedOption = Serial.parseInt();
    switch (selectedOption) {
    case 0: {
      digitalWrite(LED_PIN, LOW);
      break;
    }
    case 1: {
      digitalWrite(LED_PIN, HIGH);
      break;
    }
    }
  }
}
