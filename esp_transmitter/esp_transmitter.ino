

#define  PULSE_DS     1
#define  NEWMAN_DS    2
#define  DOUG_DS      3
#define  RAINBOW_GF   4
#define  NEWMAN_GF    5
#define  FADE_GF      6
#define  GOTIME_GF    7
#define  RAINBOW      8
#define  RAINBOW_CYCLE 9
#define  SPARKLE      10


#include <painlessMesh.h>
#define   MESH_SSID       "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555
painlessMesh  mesh;
bool calc_delay = false;
SimpleList<uint32_t> nodes;
void sendMessage() ; // Prototype
Task taskSendMessage( TASK_SECOND * 1, TASK_FOREVER, &sendMessage ); // start with a one second interval
// Task to blink the number of nodes
bool onFlag = false;

// BALLOONS
#define BALLOON_NUM 0
#define DEBUG false
unsigned long startTimeSeconds;
unsigned long lastChecked;
int currentBalloon = -1;
int rainbowIndex = 0;
int mode = 0;
int pulseIndex = 0;
int ledIndex = 0;
int colorIndex = 0;
int fadeRandom = 0;
int fadeColor[] = {0,0,0,0,0,0,0,0,0,0};
int goalRed[] = {255,0,255,255,0,0,255,255,255,0};
int goalGreen[] = {255,0,0,255,255,0,255,255,0,0};
int goalBlue[] = {255,0,255,0,255,255,0,255,0};
int redStates[] = {110,110,110,110,110,110,110,110,110,110};
int greenStates[] = {110,110,110,110,110,110,110,110,110,110};
int blueStates[] = {110,110,110,110,110,110,110,110,110};
int goalColour[] = {255,0,255,255,0,0,255,0,255,255};
int colour[] = {110,110,110,110,110,110,110,110,110,110};
float redOnes[10];
float blueOnes[10];
float greenOnes[10];

int numBalloons = 10;
byte balloons[30] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


//Balloons balloons;

void setup() {
  Serial.begin(115200);
  initMesh();
}

void loop() {
  setLightMode();
  mesh.update();
}

void setLightMode() {
  if (mode == RAINBOW_CYCLE) rainbowCycle(5);

  // Sam and David
  else if (mode == PULSE_DS) setPulsingDS(3);
  else if (mode == NEWMAN_DS) setNewmanColorsDS(3);
  else if (mode == DOUG_DS) setDougDS(3);

  // Griffen and Foster
  else if (mode == RAINBOW_GF) setRainbowLine(100);
  else if (mode == NEWMAN_GF) setNewmanGradientGF(100); 
  else if (mode == FADE_GF) setFadeGF(); // kind of the same as the one below
  else if (mode == GOTIME_GF) setGoTimeGF(50);

  // deBB
  
}

///////////////////////////////////////////////////////////
// MESH
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
  //Serial.printf("IND: %i, R: %i, G: %i, B: %i \n", rainbowIndex, getRed(sending), getGreen(sending), getBlue(sending));
  //Serial.printf("Sending message: %s\n", msg.c_str());
  return msg;
}

int getRed(String incomingString) {
  char val[2];
  val[0] = incomingString[BALLOON_NUM * 3 * 2];
  val[1] = incomingString[BALLOON_NUM * 3 * 2 + 1];
  int r = strtol( &val[0], NULL, 16);
  return r;
}

int getGreen(String incomingString) {
  char val[2];
  val[0] = incomingString[BALLOON_NUM * 3 * 2 + 2];
  val[1] = incomingString[BALLOON_NUM * 3 * 2 + 3];
  int g = strtol( &val[0], NULL, 16);
  return g;
}

int getBlue(String incomingString) {
  char val[2];
  val[0] = incomingString[BALLOON_NUM * 3 * 2 + 4];
  val[1] = incomingString[BALLOON_NUM * 3 * 2 + 5];
  int b = strtol( &val[0], NULL, 16);
  return b;
}

void setAllBalloons(int r, int g, int b) {
  for (int i = 0; i < 10; i++) {
    setBalloon(i, r, g, b);
  }
}

void clearBalloons() {
  for (int i = 0; i < numBalloons * 3; i++) {
    balloons[i] = 0;
  }
}

void setBalloon(byte ind, byte r, byte g, byte b) {
  if (ind >= 0 && ind < numBalloons) {
    balloons[ind * 3] = r;
    balloons[ind * 3 + 1] = g;
    balloons[ind * 3 + 2] = b;
  }
}

///////////////////////////////////////////////////////////
// sam and david
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
  setBalloon(0, WheelR(byte(pulseIndex)), WheelG(byte(pulseIndex)), WheelB(byte(pulseIndex)));
  setBalloon(1, WheelR(byte((pulseIndex - 25) % 255)), WheelG(byte((pulseIndex - 25) % 255)), WheelB(byte((pulseIndex - 25) % 255)));
  setBalloon(2, WheelR(byte(((pulseIndex - 50)) % 255)), WheelG(byte(((pulseIndex - 50)) % 255)), WheelB(byte(((pulseIndex - 50)) % 255)));
  setBalloon(3, WheelR(byte(((pulseIndex - 75)) % 255)), WheelG(byte(((pulseIndex - 75)) % 255)), WheelB(byte(((pulseIndex - 75)) % 255)));
  setBalloon(4, WheelR(byte(((pulseIndex - 100)) % 255)), WheelG(byte(((pulseIndex - 100)) % 255)), WheelB(byte(((pulseIndex - 100)) % 255)));
  setBalloon(5, WheelR(byte(((pulseIndex - 125)) % 255)), WheelG(byte(((pulseIndex - 125)) % 255)), WheelB(byte(((pulseIndex - 125)) % 255)));
  setBalloon(6, WheelR(byte(((pulseIndex - 150)) % 255)), WheelG(byte(((pulseIndex - 150)) % 255)), WheelB(byte(((pulseIndex - 150)) % 255)));
  setBalloon(7, WheelR(byte(((pulseIndex - 175)) % 255)), WheelG(byte(((pulseIndex - 175)) % 255)), WheelB(byte(((pulseIndex - 175)) % 255)));
  setBalloon(8, WheelR(byte(((pulseIndex - 200)) % 255)), WheelG(byte(((pulseIndex - 200)) % 255)), WheelB(byte(((pulseIndex - 200)) % 255)));
  setBalloon(9, WheelR(byte(((pulseIndex - 225)) % 255)), WheelG(byte(((pulseIndex - 225)) % 255)), WheelB(byte(((pulseIndex - 225)) % 255)));
  //strip.setAllBalloons(255, 0, 0);
  //strip.setBalloon(1, strip.Color(255, 0, 0));
  pulseIndex += rate;
  if (pulseIndex > 255) pulseIndex = 0;
}

///////////////////////////////////////////////////////////
// foster and griffin
void setRainbowLine(int cycleRate) {
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

void setRandomColour() {
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

void setRandomWhite() {
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
    pulseIndex++;
    if (pulseIndex > 10) {
      ledIndex++;
      pulseIndex = 0;
    }
  }

  clearBalloons();
  if (ledIndex % 4 == 0) setBalloon(pulseIndex, 255, 0, 0);
  else if (ledIndex % 4 == 1) setBalloon(pulseIndex, 0, 255, 0);
  else if (ledIndex % 4 == 2) setBalloon(pulseIndex, 0, 0, 255);
  else setBalloon(pulseIndex, int(random(255)), int(random(255)), int(random(255)));
}

///////////////////////////////////////////////////////////
// deBB


///////////////////////////////////////////////////////////
// Adapted from Adafruit Neopixel
void rainbowCycle(int amt) {
  rainbowIndex += amt;
  if (rainbowIndex > 255) rainbowIndex = 0;
  for (int i = 0; i < numBalloons; i++) {
    byte r =  WheelR(((i * 256 / numBalloons) + rainbowIndex) & 255);
    byte g =  WheelG(((i * 256 / numBalloons) + rainbowIndex) & 255);
    byte b = WheelB(((i * 256 / numBalloons) + rainbowIndex) & 255);
    setBalloon(i, r, g, b);
  }
}

byte WheelR(int WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return 255 - WheelPos * 3;
  }
  if (WheelPos < 170) {
    return 0;
  }
  WheelPos -= 170;
  return WheelPos * 3;
}

byte WheelG(int WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return 0;
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return WheelPos * 3;
  }
  WheelPos -= 170;
  return 255 - WheelPos * 3;
}

byte WheelB(int WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return WheelPos * 3;
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return 255 - WheelPos * 3;
  }
  WheelPos -= 170;
  return 0;
}



