import processing.serial.*;
import cc.arduino.*;
import org.firmata.*;

// light modes
int RAINBOW = 0;
int PULSE = 1;
int WAVE = 2;
int TWINKLE = 3;
int numModes = 4;
int mode = TWINKLE;

long lastCycle;

Strip strip;


void setup() {
  size(600, 200);
  strip = new Strip();
  //initTwitter();

  if (debugging) println(Arduino.list());
  arduino = new Arduino(this, Arduino.list()[0], 57600);
  arduino.pinMode(9, Arduino.OUTPUT);
  arduino.pinMode(10, Arduino.OUTPUT);
  arduino.pinMode(11, Arduino.OUTPUT);
  String portName = Serial.list()[1]; //change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 9600);
}

void draw() {
  background(0);
  cycleModes();
  playMode();

  //drawTwitter();
  transmitBalloons();
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