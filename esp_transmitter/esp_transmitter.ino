#define BALLOON_NUM 0

#include <painlessMesh.h>
#define   MESH_SSID       "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555
#define NUM_LEDS 8
painlessMesh  mesh;
bool calc_delay = false;
SimpleList<uint32_t> nodes;
void sendMessage() ; // Prototype
Task taskSendMessage( TASK_SECOND * 1, TASK_FOREVER, &sendMessage ); // start with a one second interval
// Task to blink the number of nodes
bool onFlag = false;

// BALLOONS
#define DEBUG false
#define RAINBOW 1
#define SPARKLE 4
unsigned long startTimeSeconds;
int mode = 0;
int numBalloons = 10;
byte balloons[30] = {
  255, 0, 0,
  0, 255, 0,
  0, 0, 255,
  0, 255, 255,
  255, 0, 255,
  0, 255, 0,
  255, 0, 0,
  255, 255, 0,
  0, 0, 255,
  0, 255, 255
};
unsigned long lastChecked;
int currentBalloon = -1;
int rainbowIndex = 0;


void setup() {
  Serial.begin(115200);
  //mesh.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
  //mesh.setDebugMsgTypes(ERROR | DEBUG | CONNECTION | COMMUNICATION);  // set before init() so that you can see startup messages
  mesh.setDebugMsgTypes(ERROR | DEBUG | CONNECTION);  // set before init() so that you can see startup messages
  mesh.init(MESH_SSID, MESH_PASSWORD, MESH_PORT);
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);
  mesh.onNodeDelayReceived(&delayReceivedCallback);
  mesh.scheduler.addTask( taskSendMessage );
  taskSendMessage.enable() ;


}
void loop() {
  mesh.update();
}


void sendMessage() {
  rainbowCycle(1);
  //  int rgb_msg = random(0, 255);
  //  String msg = String(rgb_msg);
  String msg = "";

  for (int i = 0; i < 30; i++) {
    String val = String(balloons[i], HEX);
    msg += val;
  }
  String sending = msg.c_str();
  Serial.printf("IND: %i, R: %i, G: %i, B: %i \n", rainbowIndex, getRed(sending), getGreen(sending), getBlue(sending));
  //Serial.printf("Sending message: %s\n", msg.c_str());
  bool error = mesh.sendBroadcast(msg);
  taskSendMessage.setInterval(500);  // between 1 and 5 seconds
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


// Adapted from Adafruit Neopixel
void rainbowCycle(int amt) {
  rainbowIndex+= amt;
  if (rainbowIndex > 255) rainbowIndex = 0;
  for (int i = 0; i < numBalloons; i++) {
    byte r =  WheelR(((i * 256 / numBalloons) + rainbowIndex) & 255);
    byte g =  WheelG(((i * 256 / numBalloons) + rainbowIndex) & 255);
    byte b = WheelB(((i * 256 / numBalloons) + rainbowIndex) & 255);
    setBalloon(i, r, g, b);
  }
}

void setAllBalloons(int r, int g, int b) {
  for (int i = 0; i < numBalloons; i++) {
    setBalloon(i, r, g, b);
  }
}

//void rainbowCycle(uint8_t wait) {
//  if (millis() - lastChecked > wait) {
//    lastChecked = millis();
//    rainbowIndex++;
//    if (rainbowIndex > 256) rainbowIndex = 0;
//  }
//  for (int i = 0; i < numBalloons; i++) {
//    byte r =  WheelR(((i * 256 / numBalloons) + rainbowIndex) & 255);
//    byte g =  WheelG(((i * 256 / numBalloons) + rainbowIndex) & 255);
//    byte b = WheelB(((i * 256 / numBalloons) + rainbowIndex) & 255);
//    setBalloon(i, r, g, b);
//  }
//}

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

/////////////////////////////////////////
// node, color


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
