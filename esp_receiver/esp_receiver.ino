#define BALLOON_NUM 0

// MESH
#include <painlessMesh.h>
painlessMesh  mesh;
#define   MESH_SSID       "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555
bool calc_delay = false;
SimpleList<uint32_t> nodes;
void sendMessage() ; // Prototype
Task taskSendMessage( TASK_SECOND * 1, TASK_FOREVER, &sendMessage ); // start with a one second interval
bool onFlag = false;

//#include <IRremoteESP8266.h>
//#include <IRsend.h>
//IRsend irsend(2);  // An IR LED is controlled by GPIO pin 4 (D2)

// NEOPIXELS
#include <ws2812_i2s.h>
#define NUM_LEDS 8
static WS2812 ledstrip;
static Pixel_t pixels[NUM_LEDS];

// INCOMING
String incomingString;           // Incoming message with RGB values for each balloon


void setup() {
  Serial.begin(115200);
  ledstrip.init(NUM_LEDS);
  mesh.setDebugMsgTypes(ERROR | DEBUG | CONNECTION);  // set before init() so that you can see startup messages
  mesh.init(MESH_SSID, MESH_PASSWORD, MESH_PORT);
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);
  mesh.onNodeDelayReceived(&delayReceivedCallback);
  mesh.scheduler.addTask( taskSendMessage );
  taskSendMessage.enable() ;
  randomSeed(analogRead(A0));
}
void loop() {
  mesh.update();
  setNeopixels();
  ledstrip.show(pixels);
}
void sendMessage() {
  // deleted
}
void receivedCallback(uint32_t from, String & msg) {
  incomingString = msg.c_str();
  Serial.printf("R: %i, G: %i, B: %i \n", getRed(), getGreen(), getBlue());
}

void newConnectionCallback(uint32_t nodeId) {
  // Reset blink task
  onFlag = false;
  Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}

int getRed() {
  char val[2];
  val[0] = incomingString[BALLOON_NUM * 3 * 2];
  val[1] = incomingString[BALLOON_NUM * 3 * 2 + 1];
  int r = strtol( &val[0], NULL, 16);
  return r;
}

int getGreen() {
  char val[2];
  val[0] = incomingString[BALLOON_NUM * 3 * 2 + 2];
  val[1] = incomingString[BALLOON_NUM * 3 * 2 + 3];
  int g = strtol( &val[0], NULL, 16);
  return g;
}

int getBlue() {
  char val[2];
  val[0] = incomingString[BALLOON_NUM * 3 * 2 + 4];
  val[1] = incomingString[BALLOON_NUM * 3 * 2 + 5];
  int b = strtol( &val[0], NULL, 16);
  return b;
}

void setNeopixels() {
  for (int i = 0; i < NUM_LEDS; i++) {
    pixels[i].R = getRed();
    pixels[i].G = getGreen();
    pixels[i].B = getBlue();
  }
}
void changedConnectionCallback() {
  Serial.printf("Changed connections %s\n", mesh.subConnectionJson().c_str());
  // Reset blink task
  onFlag = false;
  nodes = mesh.getNodeList();
  Serial.printf("Num nodes: %d\n", nodes.size());
  Serial.printf("Connection list:");
  SimpleList<uint32_t>::iterator node = nodes.begin();
  while (node != nodes.end()) {
    Serial.printf(" %u", *node);
    node++;
  }
  Serial.println();
  calc_delay = true;
}
void nodeTimeAdjustedCallback(int32_t offset) {
  Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(), offset);
}
void delayReceivedCallback(uint32_t from, int32_t delay) {
  Serial.printf("Delay to node %u is %d us\n", from, delay);
}
