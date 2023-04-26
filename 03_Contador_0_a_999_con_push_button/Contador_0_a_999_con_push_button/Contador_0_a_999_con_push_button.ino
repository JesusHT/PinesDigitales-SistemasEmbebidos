#include <SevSeg.h>
SevSeg sevseg;  //Instanciamos el objeto SevSeg

const byte botonPin = 12;          // Pin del botón
bool pausa = false;                // Inicialmente el contador no está en pausa
unsigned long tiempoUltimoEvento;  // Tiempo del último evento antes de la pausa

void setup() {
  // put your setup code here, to run once:
  byte Numdigits = 3;
  byte Comunes[] = { 9, 8, 2 };
  byte Segmentos[] = { 11, 7, 5, 4, 3, 10, 6 };
  byte Tipo = COMMON_ANODE;
  sevseg.begin(Tipo, Numdigits, Comunes, Segmentos);
  pinMode(botonPin, INPUT_PULLUP);  // Configura el pin del botón como entrada con resistencia pull-up
}

void loop() {
  bool isPushed = LOW;
  if (digitalRead(botonPin) == LOW) {  // Si el botón está presionado
    // pausa();                           // Cambia el estado de pausa
    isPushed = HIGH;                       // Espera un momento para evitar leer varias veces el mismo evento
  }

  if (!pausa) {                                 // Si el contador no está en pausa
    if (millis() - tiempoUltimoEvento >= 10) {  // Si ha pasado suficiente tiempo desde el último evento
      tiempoUltimoEvento += 10; 
      if (!isPushed)                // Proximo evento
        sevseg.setNumber(millis() / 10, 1);       // Muestra el contador (en lugar de contador, usa millis() si quieres contar el tiempo transcurrido)
    }
  }
  sevseg.refreshDisplay();
}