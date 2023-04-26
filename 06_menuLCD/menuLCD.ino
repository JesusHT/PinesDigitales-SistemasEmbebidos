#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 9, 10, 11, 12); 

bool estadoAnterior = false;
bool estadoAnterior2 = false;
  
unsigned long tiempoAnterior = 0;
unsigned long tiempoAnterior2 = 0;
const unsigned long intervalo = 20;  // tiempo en milisegundos entre cambios de estado de salida
int salida = 0;

int estadoActualLED   = 1;
int estadoAnteriorLED = 0;

int LED1 = A0;  
int LED2 = A1;
int LED3 = A2;

void setup() {
  // put your setup code here, to run once:
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void encendido(int x){
  switch (x) {
    case 1: digitalWrite(LED1,HIGH); break;
    case 2: digitalWrite(LED2,HIGH); break;
    case 3: digitalWrite(LED3,HIGH); break;
  }
}

void apagado(int x){
  switch (x) {
    case 1: digitalWrite(LED1,LOW); break;
    case 2: digitalWrite(LED2,LOW); break;
    case 3: digitalWrite(LED3,LOW); break;
  }
}

void imprimir(int x){
  lcd.clear();
  lcd.begin(16, 2);
  lcd.print("Menu");
  lcd.setCursor(0,1);
  switch (x) {
    case 1: lcd.print("1) Inicializar"); break;
    case 2: lcd.print("2) Calibrar"); break;
    case 3: lcd.print("3) Medir"); break;
  }
}

void getFuctions(int x){
  lcd.clear();
  lcd.begin(16, 2);
  switch (x) {
    case 1: lcd.print("Inicializando..."); break;
    case 2: lcd.print("Calibrando..."); break;
    case 3: lcd.print("Midiendo..."); break;
  }  
}

int validarMenu(int estado2){
  unsigned long tiempoActual2 = millis();

 

  return salida;
}

void loop() {
  // put your main code here, to run repeatedly:
  bool estado  = digitalRead(4);
  bool estado2 = digitalRead(5);
  unsigned long tiempoActual = millis();
  unsigned long tiempoActual2 = millis();

  if(estado2 && !estadoAnterior2 && (tiempoActual2 - tiempoAnterior2) > intervalo){
    salida = 1 - salida;
    tiempoAnterior2 = tiempoActual2;
  }

  estadoAnterior2 = estado2;

  if (estado && !estadoAnterior && (tiempoActual - tiempoAnterior) > intervalo && salida != 1) {
    estadoActualLED++;

    if (estadoAnteriorLED > 2){
      estadoActualLED = 1;
    }

    estadoAnteriorLED = estadoActualLED;
    tiempoAnterior = tiempoActual;

    imprimir(estadoActualLED);
    delay(200);

  } else if(salida != 1) {
    imprimir(estadoActualLED);
    delay(200);    
  }

  estadoAnterior = estado;

  if (salida == 1){
    lcd.clear();
    getFuctions(estadoActualLED);
    encendido(estadoActualLED);
    delay(200);
  } else {
    apagado(1);
    apagado(estadoAnteriorLED);
  }
    
}
