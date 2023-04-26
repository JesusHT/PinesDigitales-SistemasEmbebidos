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
  {'G', '0', '#', 'D'}
};

byte pinesFilas[filas] = {A5, A4, A3, A2};
byte pinesColumnas[columnas] = {8, 9, 10, 11};
Keypad teclado = Keypad(makeKeymap(teclas), pinesFilas, pinesColumnas, filas, columnas);
LiquidCrystal lcd(2,3,4,5,6,7); // Configuramos el LCD

// Definimos algunas constantes y variables
const byte tamanoPassword = 4;
const byte direccionEEPROM = 0;
const byte direccionAdmin = 10;
char password[tamanoPassword + 1];
bool passwordGuardada = false;
const byte ledVerde = 12;
const byte ledRojo = 13;
bool status = false;
String claveAdmin = "1234";
int menu = 0;
bool accessAdmin = false;
bool visibilidad = EEPROM.read(65);

void setup() {
  lcd.begin(16, 2);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  Serial.begin(9600);



  if (checkPassword()) {    
    printLCD("Ingrese clave:");
    lcd.setCursor(0,2);
  } else {
    passwordGuardada = true;
    printLCD("Ingrese clave:");
    lcd.setCursor(0,2);
  }
}

void onLed(int led){digitalWrite(led, HIGH);}

void offLed(int led){digitalWrite(led, LOW);}

void printLCD(String massage){
  lcd.clear();
  lcd.print(massage);
}

void setNewPass(int direccion, String newpass) {
  for (int i = 0; i < tamanoPassword; i++) {
    EEPROM.write(direccion + i, newpass[i]);
  }
}

bool validatePass(int direccion, String pass) {
  char passwordLeida[tamanoPassword + 1];
  for (byte i = 0; i < tamanoPassword; i++) {
    passwordLeida[i] = EEPROM.read(direccion + i);
  }
  passwordLeida[tamanoPassword] = '\0'; // Agregar un carácter nulo al final de la cadena

  return strcmp(pass.c_str(), passwordLeida) == 0;
}

bool validatePassGenral(int direccion, String pass) {
 char passwordLeida[tamanoPassword + 1];
  for (byte i = 0; i < tamanoPassword; i++) {
    passwordLeida[i] = claveAdmin[i];
  }
  passwordLeida[tamanoPassword] = '\0'; // Agregar un carácter nulo al final de la cadena

  return strcmp(pass.c_str(), passwordLeida) == 0;
}

void showResult(bool claveCorrecta){
  if (claveCorrecta) {
    printLCD("BIENVENIDO");
    onLed(ledVerde);
    delay(200);
  } else {
    printLCD("Clave incorrecta");
    offLed(ledVerde);
    onLed(ledRojo);
    delay(200);
  }
}

void reset(){
  delay(1000);
  lcd.clear();
  printLCD("Ingrese clave:");
  lcd.setCursor(0,2);
  offLed(ledVerde);
  offLed(ledRojo);
}

void clearEEPROM() {
  for (int i = 0; i < 8; i++) {
    EEPROM.write(i, 0xFF);
  }
}

bool checkPassword() {
  char passwordLeida;
  
  passwordLeida = EEPROM.read(0);
  int valorInt = atoi(&passwordLeida);

  if(valorInt * 1 == 0){
    return true;
  }

  return false;
}

void MENU(int x){
  switch(x) {
    case 0:
      printLCD("Bienvenido");
        break;
    case 1:
      printLCD("Nueva clave");
        break;
    case 2:
      printLCD("Eliminar clave");
        break;
    case 3:
      printLCD("Visibilidad");
      break;
    case 4:
      printLCD("Salir");
        break;
  } 
}

void printAsteriscos(int n) {
  for (int i = 0; i < n; i++) {
    lcd.print("*");
  }
}

void loop() {
  char tecla = teclado.getKey();
  static byte pos = 0;

  if (tecla != NO_KEY) {
    if (pos < tamanoPassword && visibilidad) {
      lcd.print(tecla);
      password[pos++] = tecla;
    }else if (pos < tamanoPassword && !visibilidad){
      lcd.print("*");
      password[pos++] = tecla;
    }
  }

  if (tecla == 'C') {
    lcd.clear();
    offLed(ledVerde);
    offLed(ledRojo);
    pos = 0;

    if (checkPassword() && !accessAdmin) {
      printLCD("Ingrese clave:");
      lcd.setCursor(0, 2);
    } else if (!accessAdmin){
      passwordGuardada = true;
      printLCD("Ingrese clave:");
      lcd.setCursor(0, 2);
    }
  }

  if (tecla == 'A' && pos == tamanoPassword || accessAdmin){
    password[pos] = '\0';
    lcd.clear();

    if (!passwordGuardada || accessAdmin) {
      if (validatePassGenral(direccionAdmin, password) || accessAdmin) {
        onLed(ledVerde);

        while (true) {
          tecla = teclado.getKey();

          if (tecla == 'B') {
            lcd.clear();
            pos = 0;
            menu++;
            if (menu > 4) {
              menu = 0;
            }
            MENU(menu);
            delay(200);
          } else {
            lcd.clear();
            pos = 0;
            MENU(menu);
            delay(200);
          }

          if (menu == 1 && tecla == 'A') {
            lcd.clear();
            printLCD("Ingresa Nueva: ");
            lcd.setCursor(0,2);
            delay(200);
            
            while (true) {
              tecla = teclado.getKey();
              
              if (tecla != NO_KEY) {

                if (pos < tamanoPassword ){
                
                  lcd.print(tecla);
                    password[pos++] = tecla;
                }

                if (tecla == 'C') {
                    lcd.clear();
                    pos = 0;
                    printLCD("Ingrese Nueva:");
                    lcd.setCursor(0, 2);
                } 

                if(tecla == 'B'){
                  break;
                  MENU(menu);
                }
                
                if (tecla == 'A') {
                  lcd.clear();
                  printLCD("Guardando...");
                  delay(1000);
                  setNewPass(direccionEEPROM, password);
                  printLCD("Clave guardada");
                  delay(1000);
                  lcd.clear();
                  pos = 0;
                  break;
                }
              }
            }
          }

          if (menu == 2 && tecla == 'A') {
            lcd.clear();
            lcd.setCursor(0,1); // Establece el cursor en la primera línea, columna 0
            printLCD("Eliminar clave?");
            lcd.setCursor(0,2); // Establece el cursor en la segunda línea, columna 0
            lcd.print("Si(A) No(B)");

            
            while (true) {
              tecla = teclado.getKey();
              
              if (tecla != NO_KEY) {

                if(tecla == 'B'){
                  break;
                  MENU(menu);
                }
                
                if (tecla == 'A') {
                  lcd.clear();
                  printLCD("Borrando...");
                  delay(1000);
                  clearEEPROM();
                  printLCD("Borrado exitoso!");
                  delay(1000);
                  lcd.clear();
                  pos = 0;
                  break;
                }
              }
            }
          }

          if (menu == 3 && tecla == 'A') {
            lcd.clear();
            
              lcd.setCursor(0,1);
            if (visibilidad){
              printLCD("Visibilidad ON");
              lcd.setCursor(0,2); 
              lcd.print("Desactivar (A)");
            }else {
              printLCD("Visibilidad OFF");
              lcd.setCursor(0,2); 
              lcd.print("Activar (A)");
            }

            
            while (true) {
              tecla = teclado.getKey();
              
              if (tecla != NO_KEY) {

                if(tecla == 'B'){
                  break;
                  MENU(menu);
                }
                
                if (tecla == 'A') {
                  lcd.clear();

                  if (visibilidad){
                    printLCD("Desactivado");
                    visibilidad = false;
                    EEPROM.write(65, 0);
                  } else {
                    printLCD("Activado");
                    EEPROM.write(65, 1);
                    visibilidad = true;
                  }
                  
                  delay(1000);
                  lcd.clear();
                  pos = 0;
                  break;
                }
              }
            }
          }

          if (menu == 4 && tecla == 'A') {
            lcd.clear();
            lcd.setCursor(0,1);
            printLCD("Salir?");
            lcd.setCursor(0,2); 
            lcd.print("Si(A) No(B)");

            
            while (true) {
              tecla = teclado.getKey();
              
              if (tecla != NO_KEY) {

                if(tecla == 'B'){
                  break;
                  MENU(menu);
                }
                
                if (tecla == 'A') {
                  lcd.clear();
                  accessAdmin = false;
                  printLCD("Hasta pronto!");
                  delay(1000);
                  offLed(ledVerde);
                  void (*resetFunc) (void) = 0; 
                  resetFunc();
                  lcd.clear();
                  pos = 0;
                  break;
                }
              }
            }
          }
        }
      }else {
        printLCD("Clave incorrecta!");
        offLed(ledVerde);
        onLed(ledRojo);
        delay(200);
      }
    } else {
      if(validatePass(direccionEEPROM, password)){
        printLCD("Bienvenido");
        
        while(true){
          onLed(ledVerde);
          tecla = teclado.getKey();
              
          if (tecla != NO_KEY) {
            if(tecla == 'B'){
              lcd.clear();
              printLCD("Hasta pronto!");
              delay(1000);
              offLed(ledVerde);
              void (*resetFunc) (void) = 0; 
              resetFunc();
              lcd.clear();
              pos = 0;
              break;
            }
          }          
        }
      } else {
        if(validatePassGenral(direccionAdmin, password)){
          accessAdmin = true;
        } else {
          printLCD("Clave incorrecta");
          offLed(ledVerde);
          onLed(ledRojo);
        }
      }
    }

    reset();
    pos = 0;
  }
}