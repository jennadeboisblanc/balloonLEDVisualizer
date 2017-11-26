/*
   Esp8266 Transmitter Code
   Luna Fête 2017 Interactive Balloons

*/

// MODES --------------------------- //
#define NUM_MODES 15
enum  lightmode {
  // David and Sam
  PULSE_DS, NEWMAN_DS, DOUG_DS,

  // Griffen and Foster
  RAINBOW_GF, NEWMAN_GF, FADE_GF,

  // Will and Connor
  BOUNCE_WC, HEARTBEAT_WC,

  // James and James
  RAINBOWBLINK_JJ, HALFROLL_JJ, COLORBLINK_JJ, BACKFORTH_JJ,

  // deBB and/or other
  RAINBOW, RAINBOW_CYCLE, FADE, LAST
};
lightmode  ActiveMode;





enum  gomode {
  GOTIME_GF, LAST_GO
};
gomode GoMode;
boolean goTime = false;

// MESH ----------------------------- //
#include <painlessMesh.h>
#define   MESH_SSID       "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555
painlessMesh  mesh;
bool calc_delay = false;
SimpleList<uint32_t> nodes;
void sendMessage() ; // Prototype
Task taskSendMessage( TASK_SECOND * 1, TASK_FOREVER, &sendMessage ); // start with a one second interval
bool onFlag = false;

// BALLOONS -------------------------- //
unsigned long modeSelectTime;
unsigned long lastChecked;
int currentBalloon = -1;
int rainbowIndex = 0;
int pulseIndex = 0;
int ledIndex = 0;
int colorIndex = 0;
int currentBrightness = 0;
int brightnessDirection = 0;
boolean rainbowOn = false;
int fadeRandom = 0;
int fadeColor[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int goalRed[] = {255, 0, 255, 255, 0, 0, 255, 255, 255, 0};
int goalGreen[] = {255, 0, 0, 255, 255, 0, 255, 255, 0, 0};
int goalBlue[] = {255, 0, 255, 0, 255, 255, 0, 255, 0};
int redStates[] = {110, 110, 110, 110, 110, 110, 110, 110, 110, 110};
int greenStates[] = {110, 110, 110, 110, 110, 110, 110, 110, 110, 110};
int blueStates[] = {110, 110, 110, 110, 110, 110, 110, 110, 110};
int goalColour[] = {255, 0, 255, 255, 0, 0, 255, 0, 255, 255};
int colour[] = {110, 110, 110, 110, 110, 110, 110, 110, 110, 110};
float redOnes[10];
float blueOnes[10];
float greenOnes[10];

unsigned long Interval;
uint16_t TotalSteps;
uint32_t Color1;
uint32_t Color2;
uint16_t Index;
enum  direction { FORWARD, REVERSE };
direction Direction;
int numBalloons = 10;
byte balloons[30] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


///////////////////////////////////////////////////////////
// The important stuff
///////////////////////////////////////////////////////////

void setup() {
  Serial.begin(115200);
  initMesh();
  setFade(Wheel(10), Wheel(40), 50, 10, FORWARD);
}

void loop() {
  updateLightMode();
  setLightMode();
  mesh.update();
}

///////////////////////////////////////////////////////////
// light mode stuff
///////////////////////////////////////////////////////////

void setLightMode() {
  if (goTime) {
    switch (GoMode) {
      case GOTIME_GF:
        setGoTimeGF(50);
        break;
    }
  }
  else {
    switch (ActiveMode) {
      case RAINBOW_CYCLE:
        rainbowCycle(5);
        break;
      case FADE:
        fadeUpdate();
        break;

      // David and Sam
      case PULSE_DS:
        setPulsingDS(3);
        break;
      case NEWMAN_DS:
        setNewmanColorsDS(3);
        break;
      case DOUG_DS:
        setDougDS(3);
        break;

      // Griffen and Foster
      case RAINBOW_GF:
        setRainbowLineGF(100);
        break;
      case NEWMAN_GF:
        setNewmanGradientGF(100);
        break;
      case FADE_GF:
        setFadeGF(); // kind of the same as the one below
        break;

      // Will and Connor
      // can't do accidental b/c needs to change too quickly?
      case BOUNCE_WC:
        setBounceWC(100);
        break;
      case HEARTBEAT_WC:
        setHeartbeatWC(150, Wheel(0));
        break;

      // James and James
      case RAINBOWBLINK_JJ:
        rainbowBlinkJJ(200);
        break;
      case HALFROLL_JJ:
        halfRollOutJJ(100);
        break;
      case COLORBLINK_JJ:
        colorBlinkJJ(200);
        break;
      case BACKFORTH_JJ:
        backForthJJ(200);
        break;

      // deBB

      default:
        break;
    }
  }
}

void updateLightMode() {
  if (gallierTime()) {
    goTime = true;
    Direction = FORWARD;
    cycleGoMode(10000);
  }
  else if (tchoupTime()) {
    goTime = true;
    Direction = REVERSE;
    cycleGoMode(10000);
  }
  else {
    goTime = false;
    cycleLightMode(4000);
  }
}

void cycleGoMode(int rate) {
  if (millis() - modeSelectTime > rate) {
    GoMode = gomode((GoMode+1) % (LAST_GO));
  }
}

void cycleLightMode(int rate) {
  if (millis() - modeSelectTime > rate) {
    ActiveMode = lightmode((ActiveMode+1) % (LAST));
  }
}

///////////////////////////////////////////////////////////
// time stuff
///////////////////////////////////////////////////////////

boolean gallierTime() {
  // TODO
  return false;
}


boolean tchoupTime() {
  // TODO
  return false;
}

///////////////////////////////////////////////////////////
// sam and david
///////////////////////////////////////////////////////////
void setNewmanColorsDS(int rate) {
  pulseIndex += rate;
  if (pulseIndex > 255) pulseIndex = 0;
  for (int j = 0; j < 10; j++) {
    if (j % 2 == 0) {
      // this is even
      setBalloon(j, 0, pulseIndex, 0);
    } else {
      setBalloon(j, pulseIndex, pulseIndex, pulseIndex);
    }
  }
}

void setPulsingDS(int rate) {
  pulseIndex += rate;
  if (pulseIndex > 255) pulseIndex = 0;
  setAllBalloons(0, 0, pulseIndex);
}

void setDougDS(int rate) {
  clearBalloons();
  for (int i = 0; i < 10; i++) {
    setBalloon(i, WheelR(byte((pulseIndex - 25 * i) % 255)), WheelG(byte((pulseIndex - 25 * i) % 255)), WheelB(byte((pulseIndex - 25 * i) % 255)));
  }
  pulseIndex += rate;
  if (pulseIndex > 255) pulseIndex = 0;
}

///////////////////////////////////////////////////////////
// foster and griffin
///////////////////////////////////////////////////////////
void setRainbowLineGF(int cycleRate) {
  if (millis() - lastChecked > cycleRate) {
    lastChecked = millis();
    pulseIndex++;
    if (pulseIndex % 7 == 0) ledIndex++;
    colorIndex = pulseIndex % 6;
  }
  int colorsDown[][6] = {
    {255, 0, 0},
    {255, 60, 0},
    {155, 155, 0},
    {0, 255, 0},
    {0, 0, 255},
    {155, 0, 155}
  };
  setAllBalloons(WheelR(byte((pulseIndex) % 255)), WheelG(byte((pulseIndex) % 255)), WheelB(byte((pulseIndex) % 255)));
  setBalloon(ledIndex % 10, colorsDown[colorIndex][0], colorsDown[colorIndex][1], colorsDown[colorIndex][2]);
}

void setNewmanGradientGF(int rate) {
  int pixelColors[] = { 0, 0, 50, 100, 200, 255, 200, 100, 50, 0};
  if (millis() - lastChecked > rate) {
    lastChecked = millis();
    pulseIndex++;
    if (pulseIndex > 18) pulseIndex = 0;
  }
  if (pulseIndex < 11) {
    for (int i = 0; i < 10; i++) {
      setBalloon(i, pixelColors[(i + pulseIndex) % 10], 255, pixelColors[(i + pulseIndex) % 10]);
    }
  } else if (pulseIndex < 20) {
    int j = 20 - pulseIndex;
    for (int i = 0; i < 10; i++) {
      setBalloon(i, pixelColors[(i + j) % 10], 255, pixelColors[(i + j) % 10]);
    }
  }
}

void setFadeGF() {
  pulseIndex++;
  if (pulseIndex % 100 == 0) {
    fadeRandom = int(random(0, 10));
    fadeColor[fadeRandom] = int(random(0, 255));
  }
  for (int i = 0; i < 10; i++) {
    fadeColor[i] = fadeColor[i] - 1;
    setBalloon(i, WheelR(byte(fadeColor[i])), WheelG(byte(fadeColor[i])), WheelB(byte(fadeColor[i])));
  }
}

void setRandomColourGF() {
  for (int i = 0; i < 10; i++) {
    if (colour[i] < goalColour[i]) {
      colour[i]++;
    } else if (colour[i] > goalColour[i]) {
      colour[i]--;
    } else if (colour[i] == goalColour[i]) {
      goalColour[i] = int(random(0, 255));
    }
    setBalloon(i, WheelR(byte(colour[i])), WheelG(byte(colour[i])), WheelB(byte(colour[i])));
  }
}

void setRandomWhiteGF() {
  for (int i = 0; i < 10; i++) {
    if (redStates[i] < goalRed[i]) {
      redStates[i]++;
    } else if (redStates[i] > goalRed[i]) {
      redStates[i]--;
    } else if (redStates[i] == goalRed[i]) {
      goalRed[i] = int(random(0, 255));
    }
    if (greenStates[i] < goalGreen[i]) {
      greenStates[i]++;
    } else if (greenStates[i] > goalGreen[i]) {
      greenStates[i]--;
    } else if (greenStates[i] == goalGreen[i]) {
      goalGreen[i] = int(random(0, 255));
    }
    if (blueStates[i] < goalBlue[i]) {
      blueStates[i]++;
    } else if (blueStates[i] > goalBlue[i]) {
      blueStates[i]--;
    } else if (blueStates[i] == goalBlue[i]) {
      goalBlue[i] = int(random(0, 255));
    }
    setBalloon(i, int(redStates[i]), int(greenStates[i]), int(blueStates[i]));
  }
}

void setGoTimeGF(int cycleRate) {
  if (millis() - lastChecked > cycleRate) {
    lastChecked = millis();
    if (Direction == FORWARD) {
      pulseIndex++;
      if (pulseIndex > 10) {
        ledIndex++;
        pulseIndex = 0;
      }
    }
    else {
      pulseIndex--;
      if (pulseIndex < 0) {
        ledIndex++;
        pulseIndex = 9;
      }
    }
  }

  clearBalloons();
  if (ledIndex % 4 == 0) setBalloon(pulseIndex, 255, 0, 0);
  else if (ledIndex % 4 == 1) setBalloon(pulseIndex, 0, 255, 0);
  else if (ledIndex % 4 == 2) setBalloon(pulseIndex, 0, 0, 255);
  else setBalloon(pulseIndex, int(random(255)), int(random(255)), int(random(255)));
}

///////////////////////////////////////////////////////////
// Will and Connor
///////////////////////////////////////////////////////////
void setAccidentalWC(int rate) {
  if (millis() - lastChecked > rate) {
    lastChecked = millis();
    rainbowOn = !rainbowOn;

    if (!rainbowOn) pulseIndex += 10;
    if (pulseIndex > 255) pulseIndex = 0;
  }

  if (rainbowOn) {
    ledIndex += 10;
    if (ledIndex > 255) ledIndex = 0;
    for (int i = 0; i < 10; i++) {
      setBalloon (i, Wheel(ledIndex));
    }
  } else {
    for (int i = 0; i < 10; i++) {
      setBalloon (i, Wheel(pulseIndex));
    }
  }
}

// bounce
void setBounceWC(int rate) {
  if (millis() - lastChecked > rate) {
    lastChecked = millis();
    if (Direction == FORWARD) pulseIndex++;
    else pulseIndex--;
    if (pulseIndex > 8) {
      pulseIndex = 9;
      Direction = REVERSE;
    }
    else if (pulseIndex < 0) {
      pulseIndex = 0;
      Direction = FORWARD;
      ledIndex += 30;
      if (ledIndex > 255) ledIndex = 0;
    }
  }
  clearBalloons();
  setBalloon(pulseIndex, Wheel(ledIndex));
}

// heartbeat
void setHeartbeatWC(int rate, uint32_t col) {
  if (millis() - lastChecked > rate) {
    lastChecked = millis();
    pulseIndex++;
    if (pulseIndex > 5) pulseIndex = 0;
    // on long, off, on short, off
    // on, on, off, on, off
  }
  if (pulseIndex != 2 && pulseIndex != 4) setAllBalloons(col);
  else setAllBalloons(0, 0, 0);
}

///////////////////////////////////////////////////////////
// James and James
///////////////////////////////////////////////////////////

void rainbowBlinkJJ(int rate) { //old light function
  if (millis() - lastChecked > rate) {
    lastChecked = millis();
    pulseIndex++;
    if (pulseIndex > 6) pulseIndex = 0;
    rainbowOn = !rainbowOn;
  }
  int split = 2;
  if (rainbowOn) {
    clearBalloons();
  } else {
    for (int j = 0; j <  (10 / split); j++) {
      redStates[0] = 0;
      greenStates[0] = 0;
      blueStates[0] = 0;
      if (pulseIndex == 0)redStates[0] = 255;
      else if (pulseIndex == 1)greenStates[0] = 255;
      else if (pulseIndex == 2)blueStates[0] = 255;
      else if (pulseIndex == 3) {
        redStates[0] = 255;
        blueStates[0] = 255;
      } else if (pulseIndex == 4) {
        redStates[0] = 255;
        greenStates[0] = 255;
      } else if (pulseIndex == 5) {
        blueStates[0] = 255;
        greenStates[0] = 255;
      } else if (pulseIndex == 6) {
        redStates[0] = 255;
      }
      for (int i = 0; i < split; i++) {
        setBalloon(j + (i *  10 / split), redStates[0], greenStates[0], blueStates[0]);
      }
    }
  }
}

void backForthJJ(int rate) { //old light function
  if (millis() - lastChecked > rate) {
    lastChecked = millis();
    rainbowOn = !rainbowOn;
    clearBalloons();
  }

  for (int i = 0; i < 10; i++) {
    if (i % 2 == 0) {
      greenStates[0] = 0;
      blueStates[0] = 0;
      redStates[0] = 0;
      if (rainbowOn) {
        redStates[0] = 255;
      } else blueStates[0] = 255;
    }
    if ((i - 1) % 2 == 0) {
      redStates[0] = 0;
      greenStates[0] = 0;
      blueStates[0] = 0;
      if (rainbowOn) {
        blueStates[0] = 255;
      } else redStates[0] = 255;
    }
    setBalloon(i, redStates[0], greenStates[0], blueStates[0]);
  }
}

void colorBlinkJJ(int rate) {  //james N light function
  if (millis() - lastChecked > rate) {
    lastChecked = millis();
    pulseIndex = int(random(8));
    rainbowOn = !rainbowOn;
  }
  if (rainbowOn) clearBalloons();
  else {
    redStates[0] = 0;
    greenStates[0] = 0;
    blueStates[0] = 0;
    if (pulseIndex == 0) redStates[0] = 255;
    else if (pulseIndex == 1) {
      redStates[0] = 255;
      greenStates[0] = 72;
    } else if (pulseIndex == 2) {
      redStates[0] = 255;
      greenStates[0] = 233;
    } else if (pulseIndex == 3) {
      greenStates[0] = 255;
    } else if (pulseIndex == 4) {
      blueStates[0] = 255;
    } else if (pulseIndex == 5) {
      redStates[0] = 167;
      greenStates[0] = 66;
      blueStates[0] = 244;
    } else if (pulseIndex == 6) {
      redStates[0] = 178;
      greenStates[0] = 0;
      blueStates[0] = 255;
    } else if (pulseIndex == 7) {
      redStates[0] = 52;
      greenStates[0] = 38;
      blueStates[0] = 232;
    }
    setAllBalloons(int(redStates[0]), int(greenStates[0]), int(blueStates[0]));
  }
}

int start_pin;



void halfRollOutJJ(int rate) { //old light function
  if (millis() - lastChecked > rate) {
    lastChecked = millis();
    pulseIndex++;
    if (pulseIndex > 6) pulseIndex = 1;
    rainbowOn = !rainbowOn;
  }
  if (start_pin < 0) {
    start_pin = 10;
    clearBalloons();
    rainbowOn = true;
    lastChecked = millis();
  }
  else if (start_pin > 10) {
    start_pin = -1;
    clearBalloons();
    rainbowOn = true;
    lastChecked = millis();
  }

  if (!rainbowOn) {
    start_pin --;

    redStates[0] = 0;
    greenStates[0] = 0;
    blueStates[0] = 0;
    if (pulseIndex == 0)redStates[0] = 255;
    if (pulseIndex == 1)greenStates[0] = 255;
    if (pulseIndex == 2)blueStates[0] = 255;
    if (pulseIndex == 3) {
      redStates[0] = 255;
      blueStates[0] = 255;
    }
    if (pulseIndex == 4) {
      redStates[0] = 255;
      greenStates[0] = 255;
    }
    if (pulseIndex == 5) {
      blueStates[0] = 255;
      greenStates[0] = 255;
    }
    if (pulseIndex == 6) {

      redStates[0] = 255;
    }
    setBalloon(start_pin, redStates[0], greenStates[0], blueStates[0]);
  }
}



///////////////////////////////////////////////////////////
// deBB
///////////////////////////////////////////////////////////
void setPulse(int hue, int wait) {
  if (millis() - lastChecked > wait) {
    lastChecked = millis();
    currentBrightness += brightnessDirection;
    if (currentBrightness > 255) brightnessDirection = -5;
    else if (currentBrightness < 0) brightnessDirection = 5;
  }
  int r = int(WheelR(hue) * (currentBrightness / 255.0));
  int g = int(WheelG(hue) * (currentBrightness / 255.0));
  int b = int(WheelB(hue) * (currentBrightness / 255.0));
  setAllBalloons(r, g, b);
}

void setWave(int r, int g, int b, int wait) {
  clearBalloons();
  if (millis() - lastChecked > wait) {
    lastChecked = millis();
    currentBalloon++;
    if (currentBalloon > 10) currentBalloon = 0;
  }
  setBalloon(currentBalloon, r, g, b);
}


///////////////////////////////////////////////////////////
// Mesh functions
///////////////////////////////////////////////////////////
void initMesh() {
  mesh.setDebugMsgTypes(ERROR | DEBUG | CONNECTION);  // set before init() so that you can see startup messages
  mesh.init(MESH_SSID, MESH_PASSWORD, MESH_PORT);
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);
  mesh.onNodeDelayReceived(&delayReceivedCallback);
  mesh.scheduler.addTask( taskSendMessage );
  taskSendMessage.enable();
}

void sendMessage() {

  String msg = "";
  msg += getTransmitString();

  String sending = msg.c_str();
  bool error = mesh.sendBroadcast(msg);
  taskSendMessage.setInterval(250);
}

void receivedCallback(uint32_t from, String & msg) {
  //Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
}

void newConnectionCallback(uint32_t nodeId) {
  // Reset blink task
  onFlag = false;

  //Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}
void changedConnectionCallback() {
  //Serial.printf("Changed connections %s\n", mesh.subConnectionJson().c_str());
  // Reset blink task
  onFlag = false;

  nodes = mesh.getNodeList();
  //Serial.printf("Num nodes: %d\n", nodes.size());
  //Serial.printf("Connection list:");
  SimpleList<uint32_t>::iterator node = nodes.begin();
  while (node != nodes.end()) {
    //Serial.printf(" %u", *node);
    node++;
  }
  Serial.println();
  calc_delay = true;
}
void nodeTimeAdjustedCallback(int32_t offset) {
  //Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(), offset);
}
void delayReceivedCallback(uint32_t from, int32_t delay) {
  //Serial.printf("Delay to node %u is %d us\n", from, delay);
}

String getTransmitString() {
  String msg = "";
  for (int i = 0; i < 30; i++) {
    String val = String(balloons[i], HEX);
    if (val.length() < 2) msg += '0';
    msg += val;
  }
  //Serial.printf("Sending message: %s\n", msg.c_str());
  return msg;
}

///////////////////////////////////////////////////////////
// Adapted from Adafruit Neopixel
///////////////////////////////////////////////////////////
void rainbowCycle(int amt) {
  rainbowIndex += amt;
  if (rainbowIndex > 255) rainbowIndex = 0;
  for (int i = 0; i < numBalloons; i++) {
    setBalloon(i, Wheel(((i * 256 / numBalloons) + rainbowIndex) & 255));
  }
}

// Initialize for a Fade
void setFade(uint32_t color1, uint32_t color2, uint16_t steps, uint8_t interval, direction dir = FORWARD) {
  Interval = interval;
  TotalSteps = steps;
  Color1 = color1;
  Color2 = color2;
  Index = 0;
  Direction = dir;
}

// Update the Fade Pattern
void fadeUpdate() {
  Increment();
  uint8_t red = ((Red(Color1) * (TotalSteps - Index)) + (Red(Color2) * Index)) / TotalSteps;
  uint8_t green = ((Green(Color1) * (TotalSteps - Index)) + (Green(Color2) * Index)) / TotalSteps;
  uint8_t blue = ((Blue(Color1) * (TotalSteps - Index)) + (Blue(Color2) * Index)) / TotalSteps;
  setAllBalloons(red, green, blue);
}

// Increment the Index and reset at the end
void Increment() {
  if (Direction == FORWARD) {
    Index++;
    if (Index >= TotalSteps) {
      Index = 0;
    }
  }
  else {
    --Index;
    if (Index <= 0) {
      Index = TotalSteps - 1;
    }
  }
}

// Returns the Red component of a 32-bit color
uint8_t Red(uint32_t color) {
  return (color >> 16) & 0xFF;
}

// Returns the Green component of a 32-bit color
uint8_t Green(uint32_t color) {
  return (color >> 8) & 0xFF;
}

// Returns the Blue component of a 32-bit color
uint8_t Blue(uint32_t color) {
  return color & 0xFF;
}

// Return color, dimmed by 75%
uint32_t DimColor(uint32_t color) {
  uint32_t dimColor = Color(Red(color) >> 1, Green(color) >> 1, Blue(color) >> 1);
  return dimColor;
}

uint32_t Color(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  else {
    WheelPos -= 170;
    return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

byte WheelR(int WheelPos) {
  return Red(Wheel(WheelPos));
}

byte WheelG(int WheelPos) {
  return Green(Wheel(WheelPos));
}

byte WheelB(int WheelPos) {
  return Blue(Wheel(WheelPos));
}

///////////////////////////////////////////////////////////
// Balloon functions
///////////////////////////////////////////////////////////
void setAllBalloons(int r, int g, int b) {
  for (int i = 0; i < 10; i++) {
    setBalloon(i, r, g, b);
  }
}

void setAllBalloons(uint32_t c) {
  for (int i = 0; i < 10; i++) {
    setBalloon(i, c);
  }
}

void clearBalloons() {
  for (int i = 0; i < numBalloons * 3; i++) {
    balloons[i] = 0;
  }
}

void setBalloon(byte ind, uint32_t c) {
  if (ind >= 0 && ind < numBalloons) {
    balloons[ind * 3] = Red(c);
    balloons[ind * 3 + 1] = Green(c);
    balloons[ind * 3 + 2] = Blue(c);
  }
}

void setBalloon(byte ind, byte r, byte g, byte b) {
  if (ind >= 0 && ind < numBalloons) {
    balloons[ind * 3] = r;
    balloons[ind * 3 + 1] = g;
    balloons[ind * 3 + 2] = b;
  }
}

