#include <Arduino.h>

#include "BluetoothSerial.h"


BluetoothSerial SerialBT;

const char *pin = "2408"; 

String device_name = "FrangoAssado";

#define ENA 12 // GPIO12
#define IN1 13 // GPIO13
#define IN2 14 // GPIO14
#define IN3 27 // GPIO27
#define IN4 26 // GPIO26
#define ENB 25 // GPIO25
#define ledPin 35 // LED

bool forward = false;
bool backward = false;
bool left = false;
bool right = false;
bool ledOn = false;
int Speed = 0;



void setup() {
  Serial.begin(115200);
  SerialBT.begin(device_name);
  SerialBT.setPin(pin); 

  Serial.println("Aguardando conexão Bluetooth...");

  
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (SerialBT.available() > 0) {
    char command = SerialBT.read(); // Lê um caractere enviado pelo dispositivo Bluetooth
    Serial.print("Mensagem recebida via Bluetooth: ");
     // Imprime o comando recebido no Serial Monitor
    Serial.println("Comando Recebido: ");
    Serial.println(command);

    switch (command) {
      case 'F':
        forward = true;
        backward = false;
        left = false;
        right = false;
        break;

      case 'B':
        forward = false;
        backward = true;
        left = false;
        right = false;
        break;

      case 'L':
        forward = false;
        backward = false;
        left = true;
        right = false;
        break;

      case 'R':
        forward = false;
        backward = false;
        left = false;
        right = true;
        break;

      case 'S':
        forward = false;
        backward = false;
        left = false;
        right = false;
        break;

     case 'O': // Liga o LED
        digitalWrite(ledPin, HIGH);
        break;

      case 'D': // Desliga o LED
        digitalWrite(ledPin, LOW);
        break;
        

      default:
        break;
    }

    smartcar(); 
  }
}

void smartcar() {
  if (forward) {
    carforward();
    Serial.println("carforward");
  } else if (backward) {
    carbackward();
    Serial.println("carbackward");
  } else if (left) {
    carturnleft();
    Serial.println("carleft");
  } else if (right) {
    carturnright();
    Serial.println("carright");
  } else {
    carStop();
    Serial.println("carstop");
  }
} 

void carforward() {
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void carbackward() {
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void carturnleft() {
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void carturnright() {
 
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void carStop() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
   digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

