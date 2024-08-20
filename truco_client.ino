#include <SoftwareSerial.h>

// Módulo Bluetooth para a comunicação com o computador
SoftwareSerial HM10(2, 3);

// Função que enviará o array de dados para o computador
void sendData(const int* arr, int size) {
  HM10.println();
  for (int j = 0; j < size; ++j) {
    HM10.print(arr[j]);
    HM10.print(" ");
  }
  HM10.println();
}

// Inicializando configurações iniciais para rodar o 
int* numbers = nullptr;
int currentIndex = 0;
int currentSize = 0;

unsigned long prevTimeGetDataForArray = millis();

void setup() {
  // Inicializa o serial
  HM10.begin(9600);

  // Sensor de leitura das cartas
  pinMode(A2, INPUT);
}

void loop() {
  unsigned long currentTimeGetDataForArray = millis();
  if (currentTimeGetDataForArray - prevTimeGetDataForArray > 25) {
    if (analogRead(A2) < 600) {
      currentSize++;
      numbers = (int*)realloc(numbers, currentSize * sizeof(int));

      if (numbers != nullptr) {
        numbers[currentIndex] = analogRead(A2);
        currentIndex++;
      }
    } else {
      if (currentIndex > 0) {
        sendData(numbers, currentSize);
      }

      currentSize = 0;
      currentIndex = 0;

      numbers = (int*)realloc(numbers, currentSize * sizeof(int));
    }

    prevTimeGetDataForArray = currentTimeGetDataForArray;
  }
}
