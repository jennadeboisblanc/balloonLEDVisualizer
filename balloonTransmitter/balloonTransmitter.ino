// Luna Fete 2017
// Xbee transmitter code to send color data to big balloons

#define DEBUG false
#define RAINBOW 1
#define TO_GALLIER 2
#define TO_TCHOUP 3
#define SPARKLE 4

unsigned long startTimeSeconds;
int mode = 0;
int numBalloons = 10;
byte balloons[31] = {
  47,
  0, 0, 0,
  0, 0, 0,
  0, 0, 0,
  0, 0, 0,
  0, 0, 0,
  0, 0, 0,
  0, 0, 0,
  0, 0, 0,
  0, 0, 0,
  0, 0, 0
};
unsigned long lastChecked;
int currentBalloon = -1;
int rainbowIndex = 0;
int startHour, startMin;

void setup()  {
  Serial.begin(9600);
}

void loop() {
  //  if (isGallierTime()) toGallier(100);
  //  else if (isTchoupTime()) toTchoup(100);
  //  else rainbowCycle(10);
  rainbowCycle(10);
  sendBalloons();
  //sendAndDelay(100);
  //  setAllBalloons(0, 255, 0);
  //  sendAndDelay(100);
  //
  //
  //  setAllBalloons(0, 0, 255);
  //  sendAndDelay(100);
  //
  //  setAllBalloons(255, 0, 0);
  //  sendAndDelay(100);
  //
  //  setAllBalloons(0, 255, 255);
  //  sendAndDelay(100);
  //printTime();
}

void sendAndDelay(int wait) {
  long t = millis();
  while (millis() - t < wait) sendBalloons();
}

void setAllBalloons(int r, int g, int b) {
  for (int i = 0; i < 10; i++) {
    setBalloon(i, r, g, b);
  }
}

void sendBalloons() {
  Serial.write(balloons, sizeof(balloons));
}

void clearBalloons() {
  for (int i = 1; i < numBalloons * 3 + 1; i++) {
    balloons[i] = 0;
  }
}



void setBalloon(byte ind, byte r, byte g, byte b) {
  if (ind >= 0 && ind < numBalloons) {
    balloons[ind * 3 + 1] = r;
    balloons[ind * 3 + 1 + 1] = g;
    balloons[ind * 3 + 2 + 1] = b;
  }
}


// Adapted from Adafruit Neopixel
void rainbowCycle(uint8_t wait) {
  if (millis() - lastChecked > wait) {
    lastChecked = millis();
    rainbowIndex++;
    if (rainbowIndex > 256) rainbowIndex = 0;
  }
  for (int i = 0; i < numBalloons; i++) {
    byte r =  WheelR(((i * 256 / numBalloons) + rainbowIndex) & 255);
    byte g =  WheelG(((i * 256 / numBalloons) + rainbowIndex) & 255);
    byte b = WheelB(((i * 256 / numBalloons) + rainbowIndex) & 255);
    setBalloon(i, r, g, b);
  }
}

// Adafruit Neopixel Strandtest
byte WheelR(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) return 255 - WheelPos * 3;
  if (WheelPos < 170) {
    WheelPos -= 85;
    return 0;
  }
  WheelPos -= 170;
  return WheelPos * 3;
}

byte WheelG(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) return 0;
  if (WheelPos < 170) {
    WheelPos -= 85;
    return WheelPos * 3;
  }
  WheelPos -= 170;
  return 255 - WheelPos * 3;
}

byte WheelB(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) return WheelPos * 3;
  if (WheelPos < 170) {
    WheelPos -= 85;
    return 255 - WheelPos * 3;
  }
  WheelPos -= 170;
  return 0;
}

