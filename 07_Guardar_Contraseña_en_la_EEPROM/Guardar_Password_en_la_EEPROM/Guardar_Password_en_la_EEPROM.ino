#include <Keypad.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>

// Definimos el teclado matricial y el LCD
const byte filas = 4;
const byte columnas = 4;
char teclas[filas][columnas] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte pinesFilas[filas] = {7, A3, 5, 4};
byte pinesColumnas[columnas] = {3, 2, A5, A4};
Keypad teclado = Keypad(makeKeymap(teclas), pinesFilas, pinesColumnas, filas, columnas);
LiquidCrystal lcd(13,8,9,10,11,12); // Configuramos el LCD

// Definimos algunas constantes y variables
const byte tamanoPassword = 5;
const byte direccionEEPROM = 0;
char password[tamanoPassword + 1];
bool passwordGuardada = false;
const byte ledVerde = A2;
const byte ledRojo = A1;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Nueva clave:");
  lcd.setCursor(0,2);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRojo, OUTPUT);
}

void loop() {
  char tecla = teclado.getKey();
  if (tecla != NO_KEY) {
    lcd.print(tecla);
    static byte pos = 0; // Posición actual en la contraseña
    if (pos < tamanoPassword) {
      password[pos++] = tecla;
    }
    if (pos == tamanoPassword) {
      password[pos] = '\0';
      lcd.clear();
      if (!passwordGuardada) {
        for (byte i = 0; i <= tamanoPassword; i++) {
          EEPROM.write(direccionEEPROM + i, password[i]);
        }
        passwordGuardada = true;
        lcd.print("Clave guardada");
      } else {
        char passwordLeida[tamanoPassword + 1];
        for (byte i = 0; i <= tamanoPassword; i++) {
          passwordLeida[i] = EEPROM.read(direccionEEPROM + i);
        }
        if (strcmp(password, passwordLeida) == 0) {
          lcd.print("Clave correcta");
          digitalWrite(ledVerde, HIGH); // Encender LED verde
          digitalWrite(ledRojo, LOW); // Apagar LED rojo
        } else {
          lcd.print("Clave incorrecta");
          digitalWrite(ledVerde, LOW); // Apagar LED verde
          digitalWrite(ledRojo, HIGH); // Encender LED rojo
        }
      }
      delay(1000);
      lcd.clear();
      lcd.print("Ingrese clave:");
      lcd.setCursor(0,2);
      pos = 0;
      digitalWrite(ledVerde, LOW); // Apagar LED verde
      digitalWrite(ledRojo, LOW); // Apagar LED rojo
    }
  }
}