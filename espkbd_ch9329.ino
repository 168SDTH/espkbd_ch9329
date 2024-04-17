#include <Arduino.h>
#include <CH9329_Keyboard.h>

byte k2 = 12;
byte k4 = 5;
byte k3 = 14;
byte k1 = 13;
int status[4] = { 0, 0, 0, 0 };
int key[4] = { 0, 0, 0, 0 };
int keyset[4] = { 'z', '.', 'c', ' ' }; //可自定义
int sumend = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(k1, INPUT_PULLUP);
  pinMode(k2, INPUT_PULLUP);
  pinMode(k3, INPUT_PULLUP);
  pinMode(k4, INPUT_PULLUP);

  Serial.begin(115200);
  Serial1.begin(115200);
  CH9329_Keyboard.begin(Serial1);
}



void keybd() {
  key[0] = 0;
  key[1] = 0;
  key[2] = 0;
  key[3] = 0;

  for (byte i = 0; i < 50; i++) {
    key[0] = key[0] + digitalRead(k1);
    key[1] = key[1] + digitalRead(k2);
    key[2] = key[2] + digitalRead(k3);
    key[3] = key[3] + digitalRead(k4);
  }
  for (byte k = 0; k < 4; k++) {
    if (key[k] < 1 && status[k] == 0) {
      CH9329_Keyboard.press(keyset[k]);
      status[k] = 1;
    } else if (key[k] > 48 && status[k] == 1) {
      CH9329_Keyboard.release(keyset[k]);
      status[k] = 0;
    }
  }
}


void loop() {
  // put your main code here, to run repeatedly:
  keybd();
  delay(1);
}
