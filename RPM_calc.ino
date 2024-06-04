float t1,t2;
float t0;
float f ;
void setup() {
  pinMode(8,INPUT);
  Serial.begin(9600);
}

void loop() {
   t1=pulseIn(8,HIGH);
   t2=pulseIn(8,LOW);
   t0=(t1+t2)/1000000;
   f=(1/t0)*60;
   Serial.print(f);8
   Serial.print("\n");
   delay(50);
   
}
