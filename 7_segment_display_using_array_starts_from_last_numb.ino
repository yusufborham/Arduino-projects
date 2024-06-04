#include <EEPROM.h>
int addr = 0;
int nk ;
long a[7][10]={
{1,0,1,1,0,1,1,1,1,1},
{1,1,1,1,1,0,0,1,1,1},
{1,1,0,1,1,1,1,1,1,1},
{1,0,1,1,0,1,1,0,1,1},
{1,0,1,0,0,0,1,0,1,0},
{1,0,0,0,1,1,1,0,1,1},
{0,0,1,1,1,1,1,0,1,1}};
void setup() {
   for (int i=0;i<7;i++){
     pinMode(i,OUTPUT);
   }
   pinMode(13,OUTPUT);
   nk=EEPROM.read(addr);
}

void loop() {
  digitalWrite(13,0);
   for(int k=nk;k<10;k++){
     digitalWrite(0,a[0][k]);
     digitalWrite(1,a[1][k]);
     digitalWrite(2,a[2][k]);
     digitalWrite(3,a[3][k]);
     digitalWrite(4,a[4][k]);
     digitalWrite(5,a[5][k]);
     digitalWrite(6,a[6][k]);
     EEPROM.update(addr,k);
     if (k==9){
      digitalWrite(13,1);}
    
     nk=0;
     delay(1000);
   }

}
