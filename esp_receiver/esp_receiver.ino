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
uint16_t irColor[67];
uint16_t redData[67] = {9054, 4540,  546, 592,  542, 594,  540,
      594,  542, 594,  542, 594,  542, 594,
      540, 596,  540, 594,  542, 1696,
      548, 1694,  544, 1698,  546, 1696,
      546, 1696,  544, 1698,  542, 1702,
      540, 1700,  544, 594,  540, 1700,
      546, 1698,  546, 592,  540, 1700,
      544, 592,  542, 594,  542, 594,
      540, 1700,  546, 592,  542, 594,
      540, 1698,  544, 594,  540, 1698,
      544, 1698,  544, 1698,  544};  // NEC FF6897
uint16_t greenData[67] = {9092, 4500,  594, 546,  590, 566,  568, 568,  568, 568,
        568, 568,  568, 566,  568, 566,  568, 568,  568, 1648,
        590, 1652,  590, 1652,  590, 1652,  590, 1652,  590, 1650,
        590, 1654,  588, 1652,  592, 1652,  590, 568,  568, 568,
        568, 1650,  590, 1652,  590, 570,  566, 568,  568, 568,
        568, 568,  568, 1650,  590, 1652,  590, 570,  566, 568,
        566, 1650,  590, 1652,  590, 1652,  592};  // NEC FF9867
uint16_t blueData[67] = {9088, 4496,  592, 546,  590, 568,  568, 566,  566, 568,
       568, 568,  568, 566,  568, 568,  568, 566,  568, 1650,
       592, 1650,  592, 1650,  590, 1652,  592, 1650,  590, 1652,
       592, 1650,  590, 1652,  592, 1650,  590, 568,  568, 1650,
       590, 1652,  592, 568,  570, 566,  570, 566,  568, 566,
       568, 566,  568, 1648,  592, 568,  568, 566,  568, 1648,
       592, 1650,  592, 1652,  590, 1652,  592};  // NEC FFB04F
uint16_t orangeData[67] = {9024, 4574,  518, 622,  518, 640,  496, 642,  494, 640,
         494, 640,  496, 642,  494, 642,  494, 640,  496, 1724,
         518, 1724,  516, 1728,  516, 1724,  518, 1724,  516, 1726,
         518, 1726,  518, 1726,  516, 644,  496, 640,  496, 1724,
         516, 1728,  518, 640,  496, 640,  496, 642,  494, 640,
         494, 1724,  516, 1728,  516, 642,  494, 642,  494, 1726,
         518, 1724,  518, 1724,  516, 1726,  518};  // NEC FF30CF
uint16_t lightGreenData[67] = {9018, 4574,  518, 620,  548, 608,  492, 642,  526, 610,  526, 608,  528, 606,  528, 608,  526, 608,  526, 1692,  550, 1692,  516, 1726,  548, 1694,  552, 1690,  548, 1694,  550, 1692,  550, 1692,  556, 602,  532, 602,  532, 602,  530, 1688,  552, 1690,  552, 606,  532, 602,  532, 604,  530, 1686,  548, 1696,  552, 1690,  554, 604,  532, 604,  530, 1688,  554, 1686,  552, 1688,  550};  // NEC FF18E7
uint16_t lightBlueData[67] = {9014, 4574,  518, 620,  516, 642,  494, 642,  492, 642,  492, 642,  494, 640,  494, 640,  494, 642,  492, 1726,  516, 1726,  516, 1726,  516, 1726,  514, 1726,  518, 1726,  514, 1726,  516, 1724,  518, 642,  494, 1726,  516, 1726,  516, 1726,  516, 1726,  516, 642,  494, 1726,  550, 608,  526, 1692,  516, 644,  526, 608,  494, 640,  526, 608,  526, 1692,  514, 644,  528, 1692,  548};  // NEC FF7A85
uint16_t lightOrangeData[67] = {9052, 4534,  594, 544,  592, 566,  568, 566,  568, 566,  568, 566,  568, 568,  568, 568,  568, 566,  568, 1650,  590, 1652,  590, 1654,  590, 1650,  590, 1652,  590, 1652,  592, 1652,  590, 1650,  590, 570,  568, 568,  566, 568,  566, 1650,  592, 568,  568, 568,  566, 568,  568, 568,  566, 1652,  588, 1654,  590, 1652,  590, 568,  568, 1652,  590, 1652,  590, 1654,  588, 1652,  590};  // NEC FF10EF
uint16_t tealData[67] = {9012, 4574,  518, 620,  518, 640,  494, 642,  494, 642,  494, 642,  494, 642,  494, 642,  494, 642,  492, 1724,  518, 1724,  516, 1726,  516, 1726,  516, 1724,  516, 1728,  518, 1724,  516, 1724,  516, 642,  494, 642,  492, 1726,  516, 1726,  516, 1726,  516, 642,  492, 642,  492, 642,  492, 1724,  516, 1724,  516, 642,  494, 642,  494, 642,  492, 1726,  516, 1726,  516, 1726,  516};  // NEC FF38C7
uint16_t purpleData[67] = {9070, 4506,  606, 532,  576, 578,  556, 578,  558, 578,  558, 576,  556, 580,  554, 578,  556, 578,  558, 1660,  580, 1660,  580, 1664,  580, 1662,  580, 1662,  580, 1662,  580, 1660,  582, 1662,  582, 578,  556, 1662,  580, 578,  556, 1662,  580, 1662,  582, 576,  558, 1662,  582, 576,  558, 1660,  580, 578,  558, 1662,  582, 576,  558, 578,  556, 1662,  582, 578,  558, 1660,  582};  // NEC FF5AA5
uint16_t yellowData[67] = {9082, 4518,  518, 620,  516, 642,  494, 642,  494, 642,  494, 642,  494, 642,  492, 642,  492, 642,  492, 1726,  516, 1726,  516, 1726,  518, 1726,  516, 1726,  518, 1726,  516, 1726,  516, 1724,  518, 642,  494, 1724,  518, 642,  494, 642,  494, 642,  494, 640,  494, 1724,  516, 642,  494, 1726,  516, 644,  494, 1726,  516, 1726,  516, 1726,  518, 1726,  518, 642,  494, 1726,  516};  // UNKNOWN 32C6FDF7
uint16_t darkTealData[67] = {9014, 4574,  588, 550,  590, 568,  568, 568,  568, 568,  566, 568,  566, 568,  566, 568,  566, 568,  566, 1650,  588, 1654,  590, 1652,  588, 1656,  590, 1652,  590, 1652,  590, 1654,  586, 1656,  586, 574,  568, 1652,  588, 570,  568, 566,  568, 1650,  586, 574,  568, 1652,  588, 570,  566, 1652,  580, 578,  566, 1654,  588, 1652,  586, 574,  564, 1654,  588, 570,  568, 1652,  586};  // NEC FF4AB5
uint16_t lightPurpleData[67] = {9084, 4498,  590, 548,  586, 572,  564, 572,  562, 572,  564, 572,  564, 570,  564, 570,  564, 572,  562, 1654,  588, 1654,  588, 1656,  584, 1654,  588, 1656,  586, 1654,  588, 1654,  586, 1654,  590, 570,  564, 1654,  586, 572,  564, 1652,  588, 572,  562, 572,  564, 1654,  588, 572,  564, 1654,  590, 570,  564, 1654,  588, 570,  564, 1656,  586, 1656,  588, 570,  564, 1654,  588};  // NEC FF52AD
uint16_t brightUpData[67] = {9082, 4496,  592, 548,  588, 566,  566, 568,  568, 568,  566, 568,  568, 566,  568, 568,  568, 568,  566, 1650,  592, 1652,  588, 1652,  588, 1652,  588, 1654,  590, 1650,  590, 1652,  592, 1652,  590, 1652,  590, 1652,  590, 1652,  590, 570,  566, 568,  566, 568,  566, 568,  566, 568,  564, 568,  566, 568,  566, 570,  566, 1652,  592, 1652,  588, 1652,  590, 1654,  588, 1652,  590};  // NEC FFE01F
uint16_t brightDownData[67] = {9008, 4576,  554, 582,  554, 604,  528, 606,  530, 606,  528, 606,  528, 606,  528, 606,  530, 604,  530, 1688,  550, 1692,  554, 1686,  586, 1656,  554, 1688,  554, 1688,  582, 1660,  580, 1660,  584, 1658,  582, 578,  564, 1654,  580, 578,  566, 1652,  556, 604,  562, 574,  564, 570,  564, 572,  560, 1656,  554, 604,  566, 1654,  586, 572,  566, 1654,  588, 1656,  588, 1654,  560};  // NEC FFA857
uint16_t whiteData[67] = {9078, 4504,  580, 556,  576, 578,  558, 578,  528, 606,  556, 578,  556, 578,  534, 600,  558, 578,  556, 1662,  582, 1660,  582, 1660,  578, 1664,  580, 1662,  582, 1660,  584, 1658,  580, 1662,  582, 1660,  582, 576,  556, 578,  556, 1664,  582, 576,  556, 578,  556, 578,  556, 578,  554, 580,  554, 1662,  580, 1662,  580, 556,  550, 1688,  584, 1660,  580, 1662,  576, 1664,  580};  // NEC FF906F
//uint16_t strobeData[67] = {9082, 4498,  592, 546,  590, 566,  568, 566,  568, 566,  568, 566,  568, 568,  566, 568,  568, 566,  568, 1650,  590, 1652,  590, 1652,  590, 1650,  592, 1650,  590, 1652,  590, 1652,  590, 1650,  590, 568,  568, 566,  568, 1650,  590, 566,  568, 568,  568, 566,  568, 1650,  590, 568,  568, 1652,  588, 1652,  590, 568,  568, 1652,  590, 1650,  590, 1652,  590, 568,  568, 1650,  592};  // NEC FF22DD
//uint16_t fadeData[68] = {9052, 4532,  594, 544,  590, 568,  568, 568,  568, 566,  568, 568,  568, 568,  566, 568,  568, 566,  568, 1650,  592, 1650,  590, 1652,  590, 1652,  590, 1650,  590, 1654,  590, 1652,  590, 1650,  592, 568,  568, 566,  568, 568,  566, 568,  568, 566,  568, 568,  568, 1650,  590, 568,  568, 1652,  590, 1650,  590, 1652,  592, 1652,  588, 1652,  592, 1652,  590, 568,  570, 10,  1638, 590 };  // UNKNOWN B2A94840
//uint16_t smoothData[67] = {9040, 4536,  590, 546,  590, 568,  566, 568,  566, 568,  566, 568,  566, 568,  564, 570,  566, 568,  566, 1650,  588, 1654,  588, 1654,  590, 1654,  588, 1654,  590, 1650,  588, 1654,  590, 1652,  588, 1652,  590, 1652,  590, 570,  566, 568,  568, 566,  566, 568,  566, 1652,  588, 570,  566, 566,  568, 568,  566, 1650,  590, 1652,  590, 1652,  590, 1652,  590, 568,  568, 1650,  590};  // NEC FFC23D
//uint16_t onData[67] = {9076, 4504,  592, 544,  590, 568,  568, 568,  566, 568,  568, 568,  566, 568,  566, 568,  566, 568,  568, 1652,  588, 1652,  590, 1650,  592, 1652,  588, 1652,  588, 1652,  590, 1652,  590, 1650,  590, 1652,  590, 568,  568, 1650,  590, 568,  568, 566,  568, 566,  566, 1652,  590, 568,  566, 570,  566, 1650,  592, 568,  566, 1650,  590, 1652,  590, 1652,  590, 568,  570, 1646,  590};  // NEC FFA25D
//uint16_t offData[67] = {9006, 4572,  518, 618,  514, 642,  492, 642,  492, 642,  492, 642,  494, 642,  492, 642,  492, 642,  492, 1728,  514, 1726,  514, 1726,  516, 1728,  514, 1726,  550, 1692,  552, 1692,  550, 1690,  548, 610,  528, 1690,  548, 1694,  554, 602,  528, 606,  528, 606,  528, 1692,  548, 608,  530, 1688,  548, 610,  530, 604,  528, 1690,  552, 1690,  552, 1688,  550, 610,  528, 1692,  552};  // NEC FF629D
//uint16_t flashData[67] = {9078, 4498,  592, 546,  588, 568,  566, 568,  566, 568,  566, 568,  566, 568,  568, 568,  566, 568,  568, 1650,  590, 1652,  588, 1652,  590, 1652,  588, 1654,  590, 1652,  588, 1652,  590, 1652,  588, 1652,  588, 1654,  588, 1654,  590, 568,  566, 570,  564, 570,  564, 1652,  590, 570,  564, 570,  566, 570,  564, 570,  564, 1654,  588, 1652,  588, 1652,  590, 570,  566, 1652,  588};  // NEC FFE21D

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

  Serial.println("a rawData capture from IRrecvDumpV2 of red");
  //irsend.sendRaw(irColor, 67, 38);  // Send a raw data capture at 38kHz.
  delay(500);
}
void loop() {
  mesh.update();
  setNeopixels();
  ledstrip.show(pixels);

  Serial.println("a rawData capture from IRrecvDumpV2");
  //irsend.sendRaw(irColor, 67, 38);  // Send a raw data capture at 38kHz.
  delay(500);
}

void setIRArray() {
  int r = getRed();
  int g = getGreen();
  int b = getBlue();

  int hue = getHue(r, g, b);
  if (hue < 0) memcpy(irColor, whiteData, sizeof(irColor));
  else if (hue < 20) memcpy(irColor, redData, sizeof(irColor));
  else if (hue < 30) memcpy(irColor, lightOrangeData, sizeof(irColor));
  else if (hue < 50) memcpy(irColor, yellowData, sizeof(irColor));
  else if (hue < 75) memcpy(irColor, lightGreenData, sizeof(irColor));
  else if (hue < 100) memcpy(irColor, greenData, sizeof(irColor));
  else if (hue < 115) memcpy(irColor, tealData, sizeof(irColor));
  else if (hue < 130) memcpy(irColor, darkTealData, sizeof(irColor));
  else if (hue < 140) memcpy(irColor, lightBlueData, sizeof(irColor));
  else if (hue < 180) memcpy(irColor, blueData, sizeof(irColor));
  else if (hue < 200) memcpy(irColor, purpleData, sizeof(irColor));
  else if (hue < 230) memcpy(irColor, lightPurpleData, sizeof(irColor));
  else memcpy(irColor, redData, sizeof(irColor));
}

// ---------------------------

void receivedCallback(uint32_t from, String & msg) {
  incomingString = msg.c_str();
  Serial.printf("R: %i, G: %i, B: %i \n", getRed(), getGreen(), getBlue());
}

void newConnectionCallback(uint32_t nodeId) {
  // Reset blink task
  onFlag = false;
  Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}

// adapted from
// https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both
int getHue(int r, int g, int b) {
  double h, s, v;
  double saturationThresh = .3;
  double brightnessThresh = 50;
  int black = -2;
  int white = -1;
  double      min, max, delta;

  min = r < g ? r : g;
  min = min  < b ? min  : b;
  max = r > g ? r : g;
  max = max  > b ? max  : b;

  // brightness is the value of the brightest pixel
  v = max;                                   
  delta = max - min;
  if (delta < 0.00001)
  {
    // No saturation (no diff between color levels)
    // totally white
    // hue is undefined, maybe nan?
    s = 0;
    h = 0; 

    if (v > brightnessThresh) return white; // no saturation and some brightness- white
    return black;    // no saturation and no brightness- black
  }
  if ( max > 0.0 ) { 
    // NOTE: if Max is == 0, this divide would cause a crash
    // If the brightness is above 0, then saturation is the 
    // difference between min and max pixel colors divided by max
    s = (delta / max);
  } else {
    // if max is 0, then r = g = b = 0              
    // s = 0, h is undefined
    // no color, so returning black
    s = 0.0;
    h = 0.0; // or NAN
    return black;
  }
  if ( r >= max ) {                   // > is bogus, just keeps compilor happy
    h = ( g - b ) / delta;            // between yellow & magenta
  } else {
    if (g >= max ) h = 2.0 + (b - r ) / delta;  // between cyan & yellow
    else h = 4.0 + ( r - g ) / delta;  // between magenta & cyan
  }

  h *= 60.0;                              // degrees

  if (h < 0.0 ) h += 360.0;
  if (v < brightnessThresh) return black;      // no saturation and dark = gray / off
  else if (s < saturationThresh) return white; // little saturation but bright enough to call it white?
  double d = h/360.0 * 255;
  return int(d);                        // otherwise, just return the hue
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
  int r = getRed();
  int g = getGreen();
  int b = getBlue();
  
  for (int i = 0; i < NUM_LEDS; i++) {
    pixels[i].R = r;
    pixels[i].G = g;
    pixels[i].B = b;
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

void sendMessage() {
  // deleted
}
