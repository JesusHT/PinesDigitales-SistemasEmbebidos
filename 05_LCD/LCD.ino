#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); 
byte caracter[8] = {
  B00010,
  B00100,
  B01110,
  B11111,
  B10101,
  B11111,
  B01010,
  B00000
};

void setup() {
  lcd.createChar(1, caracter);

  lcd.begin(16, 2); 
  lcd.print("Jesus Hernandez "); 
  lcd.write(byte(1));
  lcd.print(" Fatima Marin");
}

void loop() {
  lcd.scrollDisplayLeft();
  delay(500); 
}
