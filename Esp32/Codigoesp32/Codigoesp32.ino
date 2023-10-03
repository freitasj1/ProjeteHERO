#include <Arduino.h>

#include "BluetoothSerial.h"


BluetoothSerial SerialBT;

const char *pin = "2408"; 


const int botaoPin = 18;  // Pino do botão
const int relePin = 19;   // Pino conectado ao módulo de relé
int ledEstado = LOW;     // Inicialmente, o LED está desligado
int botaoEstado;         // Estado atual do botão
int ultimoEstadoBotao = LOW;   // Estado anterior do botão
unsigned long ultimoTempoPressionado = 0;  // Último tempo em que o botão foi pressionado
unsigned long intervaloDebounce = 50;  // Tempo de debounce em milissegundos

String device_name = "Patolino";

#define ENA 12 // GPIO12
#define IN1 33 // GPIO13
#define IN2 14 // GPIO14
#define IN3 27 // GPIO27
#define IN4 26 // GPIO26
#define ENB 25 // GPIO25
#define ledPin 32 // LED

bool forward = false;
bool backward = false;
bool left = false;
bool right = false;
bool ledOn = false;
int Speed = 0;



void setup() {
  
  Serial.begin(115200);
  SerialBT.setPin(pin); 
  SerialBT.begin(device_name);
  

  Serial.println("Aguardando conexão Bluetooth...");

  
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(ledPin, OUTPUT);

  pinMode(botaoPin, INPUT_PULLUP);   // Configura o pino do botão como entrada com pull-up interno
  pinMode(relePin, OUTPUT);         // Configura o pino do relé como saída
  digitalWrite(relePin, LOW);      // Desliga o relé inicialmente (LOW = desligado)
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

     case 'A': // Liga o LED
        digitalWrite(ledPin, HIGH);
        break;

      case 'C': // Desliga o LED
        digitalWrite(ledPin, LOW);
        break;
        

      default:
        break;
    }

    int leituraBotao = digitalRead(botaoPin);
  
  if (leituraBotao != ultimoEstadoBotao) {
    ultimoTempoPressionado = millis();
  }
  
  if ((millis() - ultimoTempoPressionado) > intervaloDebounce) {
    if (leituraBotao != botaoEstado) {
      botaoEstado = leituraBotao;
      if (botaoEstado == LOW) {
        if (ledEstado == LOW) {
          ledEstado = HIGH;
          digitalWrite(relePin, HIGH);   // Liga o relé (HIGH = ligado)
        } else {
          ledEstado = LOW;
          digitalWrite(relePin, LOW);    // Desliga o relé (LOW = desligado)
        }
      }
    }
  }
  
  ultimoEstadoBotao = leituraBotao;

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