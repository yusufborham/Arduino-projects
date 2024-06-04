#include <Keypad.h>
#include <LiquidCrystal.h>
const int rs = A1, en = A0, d4 = A2, d5 = A3, d6 = A4, d7 = A5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const byte ROWS = 4;  //four rows
const byte COLS = 3;  //three columns
char keys[ROWS][COLS] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};
byte rowPins[ROWS] = { 6, 5, 4, 3 };  //connect to the row pinouts of the keypad
byte colPins[COLS] = { 2, 1, 0 };     //connect to the column pinouts of the keypad

Keypad kp = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

int a[8] = { 0 };
int b[8] = { 0 };
long num = 0;
char k, m = 0;
long pass;
void setup() {
  lcd.begin(2, 16);          // put your setup code here, to run once:
  pinMode(12, OUTPUT);       // green led
  pinMode(13, OUTPUT);       // speaker
  pinMode(11, OUTPUT);       //red led
  pinMode(8, INPUT_PULLUP);  // lock switch
  lcd.setCursor(0, 0);
  lcd.print("enter pin to set");
  lcd.setCursor(0, 1);
  for (int i = 0; i < 8; i++) {
    m = kp.waitForKey();      // wait for key to be pressed
    tone(13, 1500, 100);      // a high frequency sound each time presses a button
    if (m == '#') break;      // to enter the pin use #
    b[i] = m - 48;            // convert char to integer
    pass = 10 * pass + b[i];  // convert array into number
    lcd.print(b[i]);          // print * as it is an password
  }
  delay(1000);
  lcd.clear();
}

void loop() {
  // lcd.clear();
  lcd.setCursor(2, 0);
  digitalWrite(12, 0);
  digitalWrite(11, 1);

  lcd.print("enter the pin");
  lcd.setCursor(0, 1);

  for (int i = 0; i < 8; i++) {
    k = kp.waitForKey();    // wait for key to be pressed
    tone(13, 1500, 100);    // a high frequency sound each time presses a button
    if (k == '#') break;    // to enter the pin use #
    a[i] = k - 48;          // convert char to integer
    num = 10 * num + a[i];  // convert array into number
    lcd.print("*");         // print * as it is an password
  }
  delay(200);
  lcd.clear();
  if (num == pass) {
    lcd.setCursor(3, 0);
    lcd.print("UNLOCKED");
    tone(13, 1500, 300);
    delay(250);
    tone(13, 1500, 300);
    num = 0;
    while (1) {
      digitalWrite(12, 1);      // green led on
      digitalWrite(11, 0);      // red led off
      byte x = digitalRead(8);  // read input from pushbutton >> lock button
      if (x == 0) {             // if button is pressed print locked
        lcd.setCursor(7, 1);
        lcd.print("LOCKED");
        tone(13, 200, 300);
        delay(300);
        tone(13, 200, 300);
        break;  // get out from unlocked loop and go to the top again
      }
    }
  }

  else {
    tone(13, 200, 600);
    lcd.setCursor(0, 1);
    lcd.print("Wrong pin");
    delay(1000);
    lcd.clear();
    num = 0;
  }
}
