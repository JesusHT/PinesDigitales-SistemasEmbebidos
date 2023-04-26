#include <DHT.h>

#define DHT11_PIN A0   // what pin we're connected to
#define DHTTYPE DHT11  // DHT 11
DHT dht(DHT11_PIN, DHTTYPE);

int a = 7;
int b = 8;
int c = 9;
int d = 10;
int e = 11;
int f = 12;
int g = 13;
int GND1 = 3;
int GND2 = 4;
int GND3 = 5;
int GND4 = 6;
int dig1 = 0;
int dig2 = 0;
int dig3 = 0;
int dig4 = 0;
int Temp;
int Humi;
int i;
int j;

bool estadoAnterior = false;
unsigned long tiempoAnterior = 0;
const unsigned long intervalo = 20;  // tiempo en milisegundos entre cambios de estado de salida
int salida = 0;

void setup() {
  dht.begin();

  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(GND1, OUTPUT);
  pinMode(GND2, OUTPUT);
  pinMode(GND3, OUTPUT);
  pinMode(GND4, OUTPUT);
  pinMode(2, INPUT);
  pinMode(A1, OUTPUT);
}

void DisplayNumber(int x) {
  switch (x) {
    case 0: zero(); break;
    case 1: one(); break;
    case 2: two(); break;
    case 3: three(); break;
    case 4: four(); break;
    case 5: five(); break;
    case 6: six(); break;
    case 7: seven(); break;
    case 8: eight(); break;
    case 9: nine(); break;
    case 10: o(); break;
    case 11: C(); break;
    case 12: hr(); break;
    case 13: hr1(); break;
  }
}

void zero() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
}

void one() {
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void two() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}

void three() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}

void four() {
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void five() {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void six() {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void seven() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void eight() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void nine() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void o() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void C() {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
}

void hr() {
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void hr1() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}

void loop() {

  bool estado = digitalRead(2);
  unsigned long tiempoActual = millis();

  if (estado && !estadoAnterior && (tiempoActual - tiempoAnterior) > intervalo) {
    salida = 1 - salida;
    tiempoAnterior = tiempoActual;
  }

  estadoAnterior = estado;

  if (salida == 1) {
    digitalWrite(A1, HIGH);
    Temp = 5;
    dig1 = (int)Temp / 10;
    dig2 = Temp - (dig1 * 10);
    dig3 = 10;
    dig4 = 11;    
  } else {
    digitalWrite(A1, LOW);
    Humi = 3;
    dig1 = (int)Humi / 10;
    dig2 = (int)Humi - (dig1 * 10);
    dig3 = 12;
    dig4 = 13; 
   
  }
  
  digitalWrite(GND4, LOW);  //digit 4
  DisplayNumber(dig4);
  delay(4);
  digitalWrite(GND4, HIGH);

  digitalWrite(GND3, LOW);  //digit 3
  DisplayNumber(dig3);
  delay(4);
  digitalWrite(GND3, HIGH);

  digitalWrite(GND2, LOW);  //digit 2
  DisplayNumber(dig2);
  delay(4);
  digitalWrite(GND2, HIGH);

  digitalWrite(GND1, LOW);  //digit 1
  DisplayNumber(dig1);
  delay(4);
  digitalWrite(GND1, HIGH);
}