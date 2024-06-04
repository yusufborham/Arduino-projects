#include <Keypad.h>
#include <LiquidCrystal.h>
#include <math.h>
int getn();
void disp(char opp);
const int rs = 12, en = 13, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const byte ROWS = 4;  //four rows
const byte COLS = 3;  //three columns
char keys[ROWS][COLS] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};

byte rowPins[ROWS] = { 0, 1, 2, 3 };  //connect to the row pinouts of the keypad
byte colPins[COLS] = { 4, 5, 6 };     //connect to the column pinouts of the keypad

Keypad kp = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String inputString;
long n1, n2;

void setup() {
  lcd.begin(16, 2);
  inputString.reserve(10);
  lcd.setCursor(0, 0);
  lcd.print("  Welcome to my calculator");
  for (int c = 0; c < 10; c++) {
    lcd.scrollDisplayLeft();
    delay(400);
  }
  lcd.clear();
  delay(1000);
  lcd.print("to enter number  ");
  lcd.setCursor(0, 1);
  lcd.print("press #");
  delay(2000);
  lcd.clear();
}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Please choose from below");
  for (int c = 0; c < 10; c++) {
    lcd.scrollDisplayLeft();
    delay(400);
  }
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1)Basic");
  lcd.setCursor(0, 1);
  lcd.print("operations");
  char pk = kp.waitForKey();
  lcd.clear();



  if (pk) {
    if (pk == '1') {
      lcd.setCursor(4, 0);
      lcd.print("Basic");
      lcd.setCursor(2, 1);
      lcd.print("operations");
      delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("1)+    2)-");
      lcd.setCursor(0, 1);
      lcd.print("3)*    4)/");
      pk = '0';
      char tv = kp.waitForKey();

      if (tv) {

        if (tv == '1') {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Enter 1st number");
          n1 = getn();

          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Enter 2nd number");
          n2 = getn();



          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(n1);
          lcd.print("+");
          lcd.print(n2);
          lcd.setCursor(7, 0);
          lcd.print("= ");
          lcd.print(n1 + n2);
          lcd.setCursor(0, 1);
          lcd.print("press any key");
          char y = kp.waitForKey();
        }

        else if (tv == '2') {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Enter 1st number");
          n1 = getn();

          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Enter 2nd number");
          n2 = getn();



          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(n1);
          lcd.print("-");
          lcd.print(n2);
          lcd.setCursor(7, 0);
          lcd.print("= ");
          lcd.print(n1 - n2);
          lcd.setCursor(0, 1);
          lcd.print("press any key");
          char y = kp.waitForKey();

        }


        else if (tv == '3') {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Enter 1st number");
          n1 = getn();

          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Enter 2nd number");
          n2 = getn();



          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(n1);
          lcd.print("*");
          lcd.print(n2);
          lcd.setCursor(7, 0);
          lcd.print("= ");
          lcd.print(n1 * n2);
          lcd.setCursor(0, 1);
          lcd.print("press any key");
          char y = kp.waitForKey();
        }

        else if (tv == '4') {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Enter 1st number");
          float n11 = getn();

          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Enter 2nd number");
          float n22 = getn();



          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(n11);
          lcd.print("/");
          lcd.print(n22);
          lcd.setCursor(0, 1);
          lcd.print("=");
          lcd.setCursor(1, 1);
          lcd.print(n11 / n22);
          delay(2000);
          lcd.setCursor(0, 0);
          lcd.print("press any key");
          char y = kp.waitForKey();
        }
      }
    }
  }
}

int getn() {
  int n;
  lcd.setCursor(0, 1);
  while (1) {
    char x = kp.waitForKey();
    if (x) {
      lcd.print(x);
      delay(200);
      if (x >= '0' && x <= '9') {  // only act on numeric keys
        inputString += x;          // append new character to input string
      } else if (x == '#') {
        if (inputString.length() > 0) {
          n = inputString.toInt();
          lcd.setCursor(0, 1);
          lcd.print(n);
          delay(500);
          lcd.clear();
          inputString = "";
          break;  // clear input
        } else if (x == '*') {
          inputString = "";  // clear input
        }
      }
    }
  }
  return (n);
}
void disp(char opp) {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(n1);
  lcd.print(opp);
  lcd.print(n2);
  lcd.setCursor(6, 0);
  lcd.print(" = ");
  lcd.print(n1 + n2);
  lcd.setCursor(0, 1);
  lcd.print("press any key");
  char y = kp.waitForKey();
}
