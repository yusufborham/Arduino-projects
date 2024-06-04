#include <LiquidCrystal.h>

unsigned long mySec, myMin,myMs, pausedtime = 0,resumedtime=0,elapsedTime;

const int rs = 12, en = 13, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int butnew;
int butold=1;
int paused = 1;
int butpin=7;

void setup() {
  lcd.begin(16, 2);
  pinMode(7, INPUT_PULLUP);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  lcd.setCursor(0, 0);
  lcd.print("Ready to start");
}

void loop() {
  
 butnew=digitalRead(butpin);

if(butold==1 && butnew==0){
   if (paused == 0){
     pausedtime=elapsedTime;
     paused = 1;
     lcd.setCursor(0, 1);
     lcd.print("Time Stopped");
     digitalWrite(3,0);
     digitalWrite(4,1);
     tone(2,800,100);
   }
  else {
    paused = 0;
    resumedtime=millis();
    if (elapsedTime<200){
     lcd.clear();
     lcd.setCursor(0, 1);
     lcd.print("Time started");
    }

    else{
     lcd.setCursor(0, 1);
     lcd.print("Time Resumed");
    }
     digitalWrite(3,1);
     digitalWrite(4,0);
     tone(2,1000,100);
     delay(200);
     tone(2,1000,100);
    }
}
delay(10);
butold=butnew;
 


  if(paused == 0){
    
  elapsedTime = millis()+pausedtime-resumedtime;
  myMs = (elapsedTime)%1000;
  mySec = (elapsedTime / 1000) % 60;
  myMin = (elapsedTime / 1000) / 60;

  lcd.setCursor(0, 0);
  lcd.print(myMin / 10);
  lcd.print(myMin % 10);
  lcd.print(':');
  lcd.print(mySec / 10);
  lcd.print(mySec % 10);
  lcd.print(':');
  lcd.print(myMs / 10);
  lcd.print(myMs % 10);
  delay(1);
 }
}
