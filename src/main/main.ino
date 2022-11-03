#include <Servo.h>
#define pump 2
#define servoL 12
#define servoR 13
#define echoPin 20
#define triggerPin 21
#define entryServo 22
#define exitServo 36
#define pir 7
#define IR1 8
#define IR2 9
#define buzzer 19


void on();
void off();
bool AnimalInside();
long AnimalHeight();
void OpenEntry();
void OpenExit();
void CloseEntry();
void CloseExit();
void Spray();
bool DetectAnimal();
void buzz();

uint8_t inputs[] = { echoPin, pir };
uint8_t outputs[] = { pump, servoL, servoR, entryServo, exitServo };


void setup() {
  Serial.begin(9600);
  pinMode(pump, OUTPUT);
  for (int i = 0; i < 2; i++) {
    pinMode(inputs[i], INPUT);
  }
  for (int j = 0; j < 8; j++) {
    pinMode(outputs[j], OUTPUT);
  }
}
void loop() {
  long h = AnimalHeight();
  Serial.println(h);
  if (DetectAnimal()) {
    OpenEntry();
    delay(2000);
  }
  if (AnimalInside()) {
    CloseEntry();
    delay(2000);

    on();
    Spray();
    delay(10000);

    off();
    delay(1000);

    OpenExit();
    delay(20000);

    if (!AnimalInside()) {
      CloseExit();
    } else {
      delay(10000);
    }
  }
}
void OpenEntry() {
  analogWrite(entryServo, 180);
}
void CloseEntry() {
  analogWrite(entryServo, 0);
}
void OpenExit() {
  analogWrite(exitServo, 180);
}
void CloseExit() {
  analogWrite(exitServo, 0);
}
void Spray() {
  analogWrite(servoL, 180);
  analogWrite(servoR, 180);
  delay(1000);
  analogWrite(servoL, 180);
  analogWrite(servoR, 180);
}
bool DetectAnimal() {
  if (digitalRead(pir) == HIGH) {
    return true;
  } else {
    return false;
  }
}
bool AnimalInside() {
  if (digitalRead(IR1) == HIGH && digitalRead(IR2) == HIGH) {
    return true;
  } else {
    return false;
  }
}
void buzz() {
  digitalWrite(buzzer, HIGH);
  delay(2000);
  digitalWrite(buzzer, LOW);
}
long AnimalHeight() {
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(1);
  digitalWrite(triggerPin, LOW);
  unsigned long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;
  long height = 15 - distance;
  return height;
}
void on() {
  digitalWrite(pump, HIGH);
}
void off() {
  digitalWrite(pump, LOW);
}