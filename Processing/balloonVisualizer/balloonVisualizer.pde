import processing.serial.*;
import cc.arduino.*;
import org.firmata.*;
Arduino arduino;
Serial myPort;

boolean debugging = false;

// light modes
int RAINBOW = 0;
int PULSE = 1;
int WAVE = 2;
int TWINKLE = 3;
int numModes = 4;
int mode = TWINKLE;

long lastCycle;

Strip strip;

int pulseIndex = 0;
int colorIndex = 0;
int ledIndex = 0;

void setup() {
  size(600, 200);
  strip = new Strip();
  //initTwitter();

  println(Arduino.list());
  arduino = new Arduino(this, Arduino.list()[5], 115200);
  String portName = Serial.list()[5]; //change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 115200);
}

void draw() {
  background(0);
  cycleModes();
  playMode();

  //drawTwitter();
  //transmitBalloons();

  // SAM AND DAVID
  //strip.setPulsingDS(3);
  //strip.setNewmanColorsDS(3);
  //strip.setDougDS(3);
  // DNA was pulsing back and forth
  
  // GRIFFEN AND FOSTER
  //strip.setRainbowLine(100);
  //strip.setNewmanGradientGF(100); 
  //strip.setFadeGF(); // kind of the same as the one below
  //strip.setGoTimeGF(50);
  //strip.setRandomWhite();  
  //strip.setRandomColour();
  
  // WILL AND CONNOR
  //strip.setAccidentalWC(500);
  
  // JAMES AND JAMES
  //strip.halfRollOutJJ(100);
  //strip.rainbowBlinkJJ(200);
  
  
  //strip.colorBlinkJJ(200);
  
  //strip.setWave(0, 255, 255, 100);
  //strip.setRainbow(10);
  //strip.show();
}


void keyPressed() {
  if (keyCode == RIGHT) {
    println(mode);
    mode++;
    if (mode >= numModes) mode = 0;
  }
}

void playMode() {
  if (mode == RAINBOW) strip.setRainbow(10);
  else if (mode == PULSE) strip.setPulse(0, 255, 255, 1);
  else if (mode == WAVE) strip.setWave(0, 255, 255, 100);
  else if (mode == TWINKLE) strip.twinkle();
  strip.show();
}

void cycleModes() {
  if (millis() - lastCycle > 2000) {
    lastCycle = millis();
    mode++;
    if (mode >= numModes) mode = 0;
  }
}

void transmitBalloons() {
  // send the balloon states with RF module
  strip.transmit();
}

color Wheel(int WheelPos) {
  WheelPos %= 255;
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  println(WheelPos * 3, 255 - WheelPos * 3, 0);
  return color(WheelPos * 3, 255 - WheelPos * 3, 0);
}


color Wheel(byte WheelPos) {
  WheelPos = byte(255 - WheelPos);
  if (WheelPos < 85) {
    return color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  println(WheelPos * 3, 255 - WheelPos * 3, 0);
  return color(WheelPos * 3, 255 - WheelPos * 3, 0);
}