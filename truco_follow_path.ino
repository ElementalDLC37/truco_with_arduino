#include "KeepPath.cpp"

KeepPath keepPath;

void setup() {
  // Inicializa o serial
  Serial.begin(9600);

  // Sensores de movimento
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  // Motores
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  // Gate de movimento
  pinMode(2, INPUT);
}

void loop() {
  Serial.println(digitalRead(2));

  keepPath.updateSensor(analogRead(A0), analogRead(A1));
  analogWrite(5, keepPath.leftForward);
  analogWrite(6, keepPath.leftBack);
  analogWrite(9, keepPath.rightForward);
  analogWrite(10, keepPath.rightBack);

  // Caso tenha corrente, habilita.
  /*
  if (digitalRead(2) == 0) {

  } else {
    analogWrite(5, 0);
    analogWrite(6, 0);
    analogWrite(9, 0);
    analogWrite(10, 0);
  }*/
}
