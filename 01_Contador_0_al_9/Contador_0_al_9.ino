//7 Declaramos los segmentos del display
const byte a = 2;
const byte b = 3;
const byte c = 4;
const byte d = 5;
const byte e = 6;
const byte f = 7;
const byte g = 8;

// Declaramos los pines de los display en caso de ser de 4 digitos
const byte Display[] = {9};

// Variables para los números del 0 al 9 en un display 7 segmentos de cátodo común
const byte NUMEROS[] = {
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110  // 9
};

void setup(){
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);

  pinMode(Display[0], OUTPUT);
}

void loop(){
  for(int i = 0; i <= 9; i++){
    digitalWrite(Display[0], LOW);
    mostrarNumero(i);
    digitalWrite(Display[0], HIGH);
    delay(4);
  }
}

void mostrarNumero(int numero) {  
  if (numero < 0 || numero > 9) { return; }
  
  byte valorBinario = NUMEROS[numero];  
  
  digitalWrite(a, bitRead(valorBinario, 0));
  digitalWrite(b, bitRead(valorBinario, 1));
  digitalWrite(c, bitRead(valorBinario, 2));
  digitalWrite(d, bitRead(valorBinario, 3));
  digitalWrite(e, bitRead(valorBinario, 4));
  digitalWrite(f, bitRead(valorBinario, 5));
  digitalWrite(g, bitRead(valorBinario, 6));
}
