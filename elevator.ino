#include <Stepper.h>
#include <EEPROM.h>
#define STEPS 200
Stepper stepper(STEPS, 8, 9, 10, 11);
byte addr = 5;
byte last_dor;                                            // last floor
byte targeted_floor;                                      // floor targeted
byte targeted_floor_not_constrained;                      // floor right now
float st;                                                 // step right now
byte v;                                                   // value of the displayed floor through the trip
int lst_st, trgt_st;                                      // last step , targetd step
byte elev_enable = 12;                                    // relay for power to elevator
int latchPin = 3;                                         // store to register pin
int clockPin = 4;                                         //  clock
int dataPin = 5;                                          //Data
int a[7] = { 0xf6, 0x60, 0xd5, 0xf1, 0x63, 0xb3, 0xb7 };  // the codes for the shift register to display the floor in hex in the form of an array
int pin = 7;
unsigned long duration1, t;
float f;
void setup() {
  Serial.begin(115200);
  stepper.setSpeed(250);  // speed of the elevator
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(pin, INPUT);
  lst_st = (EEPROM.read(addr)) * 1000;  // last state of the elevator
  //lst_st = 0;
  pinMode(elev_enable, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), stop, FALLING);  // emergrncy stop cuts off current to the motor
  digitalWrite(elev_enable, HIGH);                           // at first no power to the motor
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, a[EEPROM.read(addr)]);
  digitalWrite(latchPin, HIGH);
  delay(2500);
  Serial.println(lst_st);
  delay(1000);
  Serial.println("1111");
}

void loop() {
  while (Serial.available() == 0) {
    check();
  }  // while nothing is recived do nothing


  targeted_floor_not_constrained = Serial.read() - 48;  // input the targeted floor and minus 48 to get the real value not the asci
  targeted_floor = constrain(targeted_floor_not_constrained, 0, 6);
  trgt_st = 1000 * targeted_floor;  // each floor has 1000 steps so the targeted step will be the floor targeted*1000

  if (trgt_st > lst_st) {            // if the targeted step bigger than the last step so the elevator will go up
    digitalWrite(elev_enable, LOW);  // enable power to the motor
    st = lst_st;                     // right now step must be equal to the last step
    while (st != trgt_st) {          // keep going until the step right now equals the targeted step
      if ((trgt_st - st) < 350) {
        stepper.setSpeed(50);
      } else if ((trgt_st - st) > 350) {
        stepper.setSpeed(250);
      }
      stepper.step(st - lst_st + 1);                // go when step higher each time
      st = st + 1;                                  // increase the right now step
      lst_st = st;                                  // last step is now equal to the right now step
      v = st / 1000;                                //convert step to right now floor
      digitalWrite(latchPin, LOW);                  // store/latch pin on register is low to input data
      shiftOut(dataPin, clockPin, LSBFIRST, a[v]);  //display the floor right noe on the 7 segment display
      digitalWrite(latchPin, HIGH);
      // check();
      t = millis();
    }
    EEPROM.write(addr, (lst_st / 1000));
    Serial.println("1111");
    digitalWrite(elev_enable, HIGH);  // cut off power to the elevator
    while ((millis() - t) < 4000) {   // don't do anything except after 4 seconds passing
      check();
    }
    Serial.println("1111");
  }

  if (trgt_st < lst_st) {
    digitalWrite(elev_enable, LOW);
    st = lst_st;
    while (st != trgt_st) {
      if ((st - trgt_st) < 350) {
        stepper.setSpeed(50);
      } else if ((st - trgt_st) > 350) {
        stepper.setSpeed(250);
      }
      stepper.step(st - lst_st - 1);
      st = st - 1;
      lst_st = st;
      v = (st + 999) / 1000;
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST, a[v]);
      digitalWrite(latchPin, HIGH);
      //check();
      t = millis();
    }
    EEPROM.write(addr, (lst_st / 1000));
    Serial.println("1111");  // send code to inform python that the elevator arrived
    digitalWrite(elev_enable, HIGH);
    while ((millis() - t) < 4000) {
      check();
    }
    Serial.println("1111");
  }
}
void stop() {
  digitalWrite(elev_enable, HIGH);
}
void check() {
  duration1 = pulseIn(pin, HIGH);
  f = 1000000 / (duration1 * 2);  // measures the frequency of the pulse made by the 555 timer where each resistance R2 is connected to a switch
  if (f > 5 && f < 20) {          //100k
    Serial.println("0");
    delay(200);
  } else if (f > 36 && f < 50) {  //15.6k
    Serial.println("1");
    delay(200);
  } else if (f > 60 && f < 75) {  //10k
    Serial.println("2");
    delay(200);
  } else if (f > 85 && f < 100) {  //7.1k
    Serial.println("3");
    delay(200);
  } else if (f > 110 && f < 125) {  //5.6k
    Serial.println("4");
    delay(200);
  } else if (f > 160 && f < 180) {  //3.7k
    Serial.println("5");
    delay(200);
  } else if (f > 260 && f < 300) {  //2.2k
    Serial.println("6");
    delay(200);
  }
}
