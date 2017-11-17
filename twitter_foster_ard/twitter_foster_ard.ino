
#include <Adafruit_NeoPixel.h>

#define PIN 13


Adafruit_NeoPixel strip = Adafruit_NeoPixel(10, PIN, NEO_GRB + NEO_KHZ800);

int fadeRandom = 0;
int fadeColor[] = {0,0,0,0,0,0,0,0,0,0};
int fadeTimer = 0;
int inByte0;
int inByte1;
int inByte2;
int inByte3;
int inByte4;
int delayTime = 500;
int goalRed[] = {255,0,255,255,0,0,255,255,255,0};
int goalGreen[] = {255,0,0,255,255,0,255,255,0,0};
int goalBlue[] = {255,0,255,0,255,255,0,255,0};
int red[] = {110,110,110,110,110,110,110,110,110,110};
int green[] = {110,110,110,110,110,110,110,110,110,110};
int blue[] = {110,110,110,110,110,110,110,110,110};
 
int goalColour[] = {255,0,255,255,0,0,255,0,255,255};
int colour[] = {110,110,110,110,110,110,110,110,110,110};
float redOnes[10];
float blueOnes[10];
float greenOnes[10];
float Faded = .9;



void setup() {
  strip.begin();
  strip.show();

  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);


  for (uint16_t l = 0; l < 10; l++) {
    redOnes[l] = 0;
    greenOnes[l] = 0;
    blueOnes[l] = 0;
  }
  Serial.begin(9600);
}

void loop () {
  if (Serial.available() > 3) {
    inByte1 = Serial.read();
    inByte2 = Serial.read();
    inByte3 = Serial.read();
    inByte4 = Serial.read();
  }
  strip.setPixelColor(inByte1,strip.Color(inByte2, inByte3, inByte4));
  strip.show();
  if (digitalRead(5) == HIGH) {
    for (int i=0;i<3001;i++) {
      Fade();
    }
    strip.clear();
    strip.show();
  }
  if (digitalRead(6) == HIGH) {
    rainbowLine();
    strip.clear();
    strip.show();
  }
  if (digitalRead(7) == HIGH) {
    newmanGradient();
    strip.clear();
    strip.show();
  }
  if (digitalRead(8) == HIGH) {
    goTime();
    strip.clear();
    strip.show();
  }
  if (digitalRead(9) == HIGH) {
    for (int i=0;i<3001;i++) {
      randomColour();
    }
          strip.clear();
    strip.show();
  }
  if (digitalRead(10) == HIGH) {
    for (int i=0;i<1001;i++) {
        randomWhite();
    }
            strip.clear();
    strip.show();
  }
}


void rainbowLine() {
  for (int i = 0; i <= 9; i++) {
    strip.setPixelColor(i, strip.Color(255, 0, 0));
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(255, 60, 0));
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(155, 155, 0));
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(0, 255, 0));
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(0, 0, 255));
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(155, 0, 155));
    strip.show();
    delay(100);
  }
  for (int i = 0; i <= 9; i++) {

    strip.setPixelColor(i, strip.Color(255, 66, 0));
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(155, 155, 0));
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(0, 255, 0));
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(0, 0, 255));
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(155, 0, 155));
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(255, 0, 0));
    strip.show();
    delay(100);
  }
  for (int i = 0; i <= 9; i++) {

    strip.setPixelColor(i, strip.Color(255, 66, 0));
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(155, 155, 0));
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(0, 255, 0));
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(0, 0, 255));
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(155, 0, 155));
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(255, 0, 0));
    strip.show();
    delay(100);
  }
  for (int i = 0; i <= 9; i++) {


    strip.setPixelColor(i, strip.Color(0, 255, 0));
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(0, 0, 255));
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(155, 0, 155));
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(255, 0, 0));
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(255, 66, 0));
    strip.show();
    delay(100);
  }
  for (int i = 0; i <= 9; i++) {


    strip.setPixelColor(i, strip.Color(0, 0, 255));
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(155, 0, 155));
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(255, 0, 0));
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(255, 66, 0));
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(155, 155, 0));
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(0, 255, 0));
    strip.show();
    delay(100);
  }
  for (int i = 0; i <= 9; i++) {


    strip.setPixelColor(i, strip.Color(155, 0, 155));
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(255, 0, 0));
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(255, 66, 0));
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(155, 155, 0));
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(0, 255, 0));
    strip.show();
    delay(100);
    strip.setPixelColor(i, strip.Color(0, 0, 255));
    strip.show();
    delay(100);
  }


}
void newmanGradient() {
  int pixelColors[] = { 255, 100, 0, 0, 0, 0, 0, 0, 0, 0 };
  for (int j = 1; j <= strip.numPixels(); j++) {
    for (int i = 0; i <= strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(pixelColors[(i + j) % 7], 255, pixelColors[(i + j) % 7]));
    }
    delay(200);
    strip.show();
  }
  //int pixelColors1[] = { 0, 0, 0, 0, 0, 0, 0, 0, 100, 255 };
  for (int j = 9; j >= 2; j--) {
    for (int i = 9; i >= 0; i--) {
      strip.setPixelColor(i, strip.Color(pixelColors[(i + j) % 10], 255, pixelColors[(i + j) % 10]));
    }
    delay(200);
    strip.show();
  }
}
void Fade() {
  if (fadeTimer%100 == 0) {
    fadeRandom = random(0,10);
    fadeColor[fadeRandom] = random(0,255);
  }
  for (int i = 0; i<10;i++) {
    fadeColor[i] = fadeColor[i]-1;
    strip.setPixelColor(i, Wheel(fadeColor[i]));
    strip.show();
  }
  
  fadeTimer++;
}

void randomWhite() {
  for (int i = 0; i<10;i++) {
    if (red[i]<goalRed[i]) {
      red[i]++;
    }
    else if (red[i]>goalRed[i]) {
      red[i]--;
    }
    else if (red[i]==goalRed[i]) {
      goalRed[i] = random(0,255);
    }
    if (green[i]<goalGreen[i]) {
      green[i]++;
    }
    else if (green[i]>goalGreen[i]) {
      green[i]--;
    }
    else if (green[i]==goalGreen[i]) {
      goalGreen[i] = random(0,255);
    }
    if (blue[i]<goalBlue[i]) {
      blue[i]++;
    }
    else if (blue[i]>goalBlue[i]) {
      blue[i]--;
    }
    else if (blue[i]==goalBlue[i]) {
      goalBlue[i] = random(0,255);
    }
    strip.setPixelColor(i, strip.Color(red[i],green[i],blue[i]));
    strip.show();
  }
}
 
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
 
void randomColour() {
  for (int i = 0; i<10;i++) {
    if (colour[i]<goalColour[i]) {
      colour[i]++;
    }
    else if (colour[i]>goalColour[i]) {
      colour[i]--;
    }
    else if (colour[i]==goalColour[i]) {
      goalColour[i] = random(0,255);
    }
    strip.setPixelColor(i, Wheel(colour[i]));
    strip.show();
  }
}
void goTime() {
  for(int x=0;x<20;x++) {
    for(int i=0;i<10;i++){
      strip.clear();
      strip.setPixelColor(i, strip.Color(255,0,0));
      strip.show();
      delay(delayTime);
    }
    for(int i=0;i<10;i++){
      strip.clear();
      strip.setPixelColor(i, strip.Color(0,255,0));
      strip.show();
      delay(delayTime);
    }
    for(int i=0;i<10;i++){
      strip.clear();
      strip.setPixelColor(i, strip.Color(0,0,255));
      strip.show();
      delay(delayTime);
    }
    for(int i=0;i<10;i++){
      strip.setPixelColor(i, strip.Color(random(0, 255),random(0, 255),random(0, 255)));
      strip.show();
      delay(delayTime);
    }
    delayTime = delayTime*.90;
  }
 
  for(int y=0;y<7;y++) {
    for(int x=0;x<25;x++) {
     for(int i=0;i<10;i++){
      strip.clear();
      strip.setPixelColor(i, strip.Color(150-(25*y),10*x,y*40));
      strip.show();
      delay(50);
     }
    }
  }
}

