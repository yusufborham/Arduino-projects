 int pin = 7;
 byte laser = 10;
 byte green_led= 11;
 byte red_led = 12;
 byte sw;
 float sp;
 float duration;

void setup() {
   Serial.begin(9600);
   pinMode(pin, INPUT); 
   pinMode(6, INPUT_PULLUP);
   pinMode(laser,OUTPUT);
   pinMode(green_led,OUTPUT);
   pinMode(red_led,OUTPUT);
   pinMode(13,OUTPUT);
}

void loop() {
 digitalWrite(green_led,LOW);
 digitalWrite(red_led,LOW);
 digitalWrite(laser,LOW);
  sw=digitalRead(6);
  /* if(sw==0){
    delay(1000);
    digitalWrite(laser,HIGH);
    delay(100);
    digitalWrite(green_led, HIGH);
    delay(100);
    for(int i=0;i<5;i++){
    duration = pulseIn(pin, HIGH);
    sp= 40000/duration;
    Serial.println(sp);}
    delay(1000);
    digitalWrite(green_led,LOW);
    digitalWrite(red_led ,HIGH);
    Serial.println(sp);  */
    delay(1000);
    digitalWrite(laser,HIGH);
    duration = pulseIn(pin, HIGH);
    sp= 40000/duration;
    Serial.println(sp);
    digitalWrite(laser,LOW);
    delay(1000);
  // }
  
    
  //else{sw=digitalRead(6);}
}
