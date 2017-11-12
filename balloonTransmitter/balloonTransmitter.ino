// Luna Fete 2017
// Xbee transmitter code to send color data to big balloons

#define DEBUG true
#define RAINBOW 1
#define TO_GALLIER 2
#define TO_TCHOUP 3
#define SPARKLE 4

unsigned long startTimeSeconds;
int mode = 0;
int numBalloons = 10;
byte balloons[30] = {
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
  setStartTime(18, 19);
}

void loop() {
  if (isGallierTime()) toGallier(100);
  else if (isTchoupTime()) toTchoup(100);
  else rainbowCycle(10);
  //printTime();
  sendBalloons();
}

void sendBalloons() {
  // TODO
}


boolean isGallierTime() {
  for (int i = 17; i < 21; i++) {
    // 17- 5:52-6:02
    // 18- 6:52-7:02
    // 19- 7:52-8:02
    // 20- 8:52-9:02
    int startMin = 51;
    int endMin = 3;
    if ((hour() == i && minute() > startMin) || (hour() == i + 1 && minute() < endMin)) return true;
  }
  if (DEBUG) Serial.println("to gallier");
  return false;
}

boolean isTchoupTime() {
  for (int i = 18; i < 21; i++) {
    // 18- 6:10 - 6:20
    int startMin = 10;
    int endMin = 20;
    if (hour() == i && minute() > startMin && minute() < endMin) return true;
  }
  if (DEBUG) Serial.println("to tchoup");
  return false;
}

int hour() {
  unsigned long allSeconds = millis() / 1000;
  int runHours = allSeconds / 3600;
  int secsRemaining = allSeconds % 3600;
  int runMinutes = secsRemaining / 60;
  if (startMin + runMinutes > 60) runHours++;
  return runHours + startHour;
}

byte minute() {
  unsigned long allSeconds = millis() / 1000;
  int runHours = allSeconds / 3600;
  int secsRemaining = allSeconds % 3600;
  int runMinutes = secsRemaining / 60;
  return (startMin+ runMinutes)%60;
}

void printTime() {
  Serial.print(hour());
  Serial.print(":");
  Serial.println(minute());
}
void clearBalloons() {
  for (int i = 0; i < numBalloons * 3; i++) {
    balloons[i] = 0;
  }
}

void toGallier(int wait) {
  if (millis() - lastChecked > wait) {
    currentBalloon++;
    if (currentBalloon > numBalloons) currentBalloon = 0;
    lastChecked = millis();
  }
  clearBalloons();
  setBalloon(currentBalloon, 255, 0, 0);
  showBalloons();
}

void toTchoup(int wait) {
  if (millis() - lastChecked > wait) {
    currentBalloon--;
    if (currentBalloon < 0) currentBalloon = numBalloons;
    lastChecked = millis();
  }
  clearBalloons();
  setBalloon(currentBalloon, 255, 0, 0);
  showBalloons();
}

void setBalloon(byte ind, byte r, byte g, byte b) {
  if (ind >= 0 && ind < numBalloons * 3) {
    balloons[ind * 3] = r;
    balloons[ind * 3 + 1] = g;
    balloons[ind * 3 + 2] = b;
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
  showBalloons();
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

void setStartTime(int h, int m) {
  startHour = h;
  startMin = m;
}

