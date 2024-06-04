int x,y,z,last=0;
 #include <Servo.h> 
 Servo myservo;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(9);
}

void loop() {
  // put your main code here, to run repeatedly:
x=analogRead(A0);
y=analogRead(A1);
/*z=myservo.read();
myservo.write(z);*/
/*Serial.print("x is  ");
Serial.print(x);
Serial.print("  y is  ");
Serial.print(y);
Serial.print(" \n");
delay(100);*/
  for(int i=last;(x-y)>50;i++){
   myservo.write(i);
   delay(50);
   x=analogRead(A0);
   y=analogRead(A1);
   if(abs(x-y)<50){last=i;}
  }
  for(int i=last;(y-x)>50;i--){
   myservo.write(i);
   delay(50);
   x=analogRead(A0);
   y=analogRead(A1);
   if(abs(x-y)<50){last=i;}
  }
}
