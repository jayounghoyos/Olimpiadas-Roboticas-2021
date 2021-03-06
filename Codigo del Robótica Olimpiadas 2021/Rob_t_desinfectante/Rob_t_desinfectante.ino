#include <SoftwareSerial.h>

SoftwareSerial BT(8, 9);

const int GiroM1 = 4;
const int ActivarM1 = 5;

const int GiroM2 = 7;
const int ActivarM2 = 6;

const int TriggerPin = 2;
const int EchoPin = 3;

const int GiroM3 = 11;
const int ActivarM3 = 12;

const int LED = 13;

int tiempo;
int distancia_cm;
bool isInitialized = false;

void setup() {

  BT.begin(9600);

  pinMode(GiroM1, OUTPUT);
  pinMode(ActivarM1, OUTPUT);

  pinMode(GiroM2, OUTPUT);
  pinMode(ActivarM2, OUTPUT);

  pinMode(LED, OUTPUT);

  pinMode(GiroM3, OUTPUT);
  pinMode(ActivarM3, OUTPUT);

  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);

  // Initial State
  detener();
  digitalWrite(LED, LOW);
}

void loop() {

  //codigo para que constantemente revise si hay un objeto en frente
  
  digitalWrite(TriggerPin, LOW);
  delayMicroseconds(4);

  digitalWrite(TriggerPin, HIGH);
  delayMicroseconds(10);

  tiempo = pulseIn(EchoPin, HIGH);
  distancia_cm = 0.01715 * tiempo;

  delay(100);

  if (BT.available()) {  //Revisando si si está activado
    switch (BT.read()) {
      case 'A':
        adelante();     //usando las funciones siempre que se presionen los botones de la app
        break;
      case 'a':
        derecha();
        break;
      case 'I':
        izquierda();
        break;
      case 'D':
        atras();
        break;
      case 'S':
        detener();
        break;
      default:
        detener();
        break;
    }
  }

  if (distancia_cm < 5) {
    if (!isInitialized) {
      isInitialized = true; //Pequeño lapso de espera
    } else {
      detener();  //Funciones para el movimiento del desinfectante
      digitalWrite(LED, HIGH);
      exprimir();
      delay(2000);
      detener();
      digitalWrite(LED, LOW);
    }
  }
}

void atras() {
  detener();
  digitalWrite(GiroM1, LOW);
  digitalWrite(ActivarM1, HIGH);
  digitalWrite(ActivarM2, HIGH);
  digitalWrite(GiroM2, HIGH);
}

void izquierda() {
  detener();
  digitalWrite(GiroM1, LOW);
  digitalWrite(ActivarM1, HIGH);
  digitalWrite(ActivarM2, HIGH);
  digitalWrite(GiroM2, LOW);
}

void derecha() {
  detener();
  digitalWrite(GiroM1, HIGH);
  digitalWrite(ActivarM1, HIGH);
  digitalWrite(ActivarM2, HIGH);
  digitalWrite(GiroM2, HIGH);
}

void adelante() {
  detener();
  digitalWrite(GiroM1, HIGH);
  digitalWrite(ActivarM1, HIGH);
  digitalWrite(ActivarM2, HIGH);
  digitalWrite(GiroM2, LOW);
}
void exprimir() {
  detener();
  digitalWrite(ActivarM3, LOW);
  digitalWrite(GiroM3, HIGH);
}

void detener() {
  digitalWrite(ActivarM1, LOW);
  digitalWrite(ActivarM2, LOW);
  digitalWrite(ActivarM3, LOW);
  digitalWrite(GiroM1, LOW);
  digitalWrite(GiroM2, LOW);
  digitalWrite(GiroM3, LOW);
}
