/* @file CustomKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates changing the keypad size and key values.
|| #
*/
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

const byte ROWS = 4;  //four rows
const byte COLS = 4;  //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  { '1', '2', '3', '/' },
  { '4', '5', '6', '*' },
  { '7', '8', '9', '-' },
  { 'C', '0', '#', '+' }
};
byte rowPins[ROWS] = { 9, 8, 7, 6 };  //connect to the row pinouts of the keypad
byte colPins[COLS] = { 5, 4, 3, 2 };  //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
String Num1 = "";
String Num2 = "";
char action = 'j';
String result = "";
boolean gotNum1 = false;
String numeric = "1234567890";

void setup() {
  Serial.begin(9600);

  lcd.init();

  lcd.backlight();
  lcd.setCursor(0, 0);
}

void loop() {
  char key = customKeypad.getKey();
  if (key != NO_KEY) {
    if (key == '+') {
      continueAction();
      if (Num1 != "" && action == 'j') {
        action = '+';
        lcd.print(action);
        gotNum1 = true;
      }

      return;
    } else if (key == '-') {
      continueAction();
      if (Num1 != "" && action == 'j') {
        action = '-';
        lcd.print(action);

        gotNum1 = true;
      }

      return;
    } else if (key == '*') {
      continueAction();
      if (Num1 != "" && action == 'j') {
        action = '*';
        lcd.print(action);

        gotNum1 = true;
      }
      return;
    } else if (key == '/') {
      continueAction();
      if (Num1 != "" && action == 'j') {
        action = '/';
        lcd.print(action);
        gotNum1 = true;
      }
      return;
    }

    if (key == '#') {
      if (Num1 != "" && Num2 != "") {
        // CalculateResult();
        // Serial.println("hello world");

        Calculate();
        Display();
        return;
      } else {
        return;
      }
    }

    if (key == 'C') {
      clear();
      return;
    }

    if (result != "" && numeric.indexOf(key) != -1) {
      clear();
    }

    if (!gotNum1) {
      Num1 += key;
      lcd.print(key);

    } else {
      Num2 += key;
      lcd.print(key);
    }
  }
  // delay(500);
  Serial.println("num1 : " + Num1);
  Serial.println(action);
  Serial.println("num2 : " + Num2);
}

void Calculate() {
  if (action == '+') {
    result += Num1.toFloat() + Num2.toFloat();
  } else if (action == '-') {
    result += Num1.toFloat() - Num2.toFloat();
  } else if (action == '*') {
    result += Num1.toFloat() * Num2.toFloat();
  } else if (action == '/') {
    result += Num1.toFloat() / Num2.toFloat();
  }
}
void Display() {
  lcd.setCursor(0, 1);
  lcd.print(result);
}

void continueAction() {
  if (result != "") {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(result);
    Num1 = result;
    Num2 = "";
    result = "";
    action = 'j';
  }
}

void clear() {
  Num1 = "";
  Num2 = "";
  gotNum1 = false;
  result = "";
  action = 'j';
  lcd.clear();
}
