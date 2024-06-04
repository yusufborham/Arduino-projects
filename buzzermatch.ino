int bz=6,ld1=4,ld2=5,sw1=2,sw2=3,sw1i,sw2i,swo;
int state=0; 
float t ;
void flash (int x);
#include <LiquidCrystal.h>
const int rs = 12, en = 13, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  // put your setup code here, to run once:
  pinMode(bz,OUTPUT);
  pinMode(ld1,OUTPUT);
  pinMode(ld2,OUTPUT);
  pinMode(sw1,INPUT_PULLUP);
  pinMode(sw2,INPUT_PULLUP);
   

  lcd.begin(16, 1);
    

  lcd.setCursor(0, 0);
  lcd.print("Welcome to the game the first one to press answers first");
  for(int c=0;c<45;c++){
  lcd.scrollDisplayLeft();
  delay(100);
  }
  lcd.clear();
  lcd.print("Let's start");
  delay(500);
  lcd.clear();
  tone(bz,700,200);
  delay(300);
  tone(bz,700,200);
  delay(300);
  tone(bz,700,200);
  delay(300);

  digitalWrite(ld1,1);
  digitalWrite(ld2,1);
  delay(300);
  digitalWrite(ld1,0);
  digitalWrite(ld2,0);
  

    for(t=9.0;t>=0.00;t=t-0.01){
    
   // Serial.println(t);
    lcd.setCursor(7, 0);
    lcd.print(t);
    sw1i=digitalRead(2);
    sw2i=digitalRead(3);
    // tone(bz,1000,50);
    if(sw1i==0 || sw2i==0) break ;
    if(t<0.20) goto timeout ;
    delay(10);
    } 

    while(1) {
    if(sw1i==0)
     {
      flash(ld1);
      lcd.setCursor(0, 0);
      lcd.print("Player one ");
      break;
     }
   if(sw2i==0)
     {
      flash(ld2);
      lcd.setCursor(0, 0);
      lcd.print("Player two ");
      break;
    }

    }

 if (t<0.05){
  timeout:
 
{
  tone(bz,800,300);
  delay(350);
  tone(bz,400,300);
  delay(350);
  tone(bz,200,300);
  delay(350);
  for (int i=0 ;i<10;i++){
     state=!state;
     digitalWrite(ld1,state);
     digitalWrite(ld2,state);
     delay(100);
   }
  lcd.setCursor(0, 0);
  lcd.print("No one pressed");
   
   
 }
  }
  }
  
void loop() {}
 
   

 
 void flash (int x){
   int state=0;
  delay(50);
  digitalWrite(x,1);
  tone(bz,300,1000); 
  
   for (int i=0 ;i<20;i++){
     state=!state;
     digitalWrite(x,state);
     delay(100);
   }
} 
