//
//
//Balloons::Balloons() {
//  numBalloons = 10;
//  balloons[30] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//}
//
//
//String Balloons::getTransmitString() {
//  String msg = "";
//  for (int i = 0; i < 30; i++) {
//    String val = String(balloons[i], HEX);
//    if (val.length() < 2) msg += '0';
//    msg += val;
//  }
//  //Serial.printf("IND: %i, R: %i, G: %i, B: %i \n", rainbowIndex, getRed(sending), getGreen(sending), getBlue(sending));
//  //Serial.printf("Sending message: %s\n", msg.c_str());
//  return msg;
//}
//
//int Balloons::getRed(String incomingString) {
//  char val[2];
//  val[0] = incomingString[BALLOON_NUM * 3 * 2];
//  val[1] = incomingString[BALLOON_NUM * 3 * 2 + 1];
//  int r = strtol( &val[0], NULL, 16);
//  return r;
//}
//
//int Balloons::getGreen(String incomingString) {
//  char val[2];
//  val[0] = incomingString[BALLOON_NUM * 3 * 2 + 2];
//  val[1] = incomingString[BALLOON_NUM * 3 * 2 + 3];
//  int g = strtol( &val[0], NULL, 16);
//  return g;
//}
//
//int Balloons::getBlue(String incomingString) {
//  char val[2];
//  val[0] = incomingString[BALLOON_NUM * 3 * 2 + 4];
//  val[1] = incomingString[BALLOON_NUM * 3 * 2 + 5];
//  int b = strtol( &val[0], NULL, 16);
//  return b;
//}
//
//void Balloons::setAllBalloons(int r, int g, int b) {
//  for (int i = 0; i < 10; i++) {
//    setBalloon(i, r, g, b);
//  }
//}
//
//void Balloons::clearBalloons() {
//  for (int i = 0; i < numBalloons * 3; i++) {
//    balloons[i] = 0;
//  }
//}
//
//void Balloons::setBalloon(byte ind, byte r, byte g, byte b) {
//  if (ind >= 0 && ind < numBalloons) {
//    balloons[ind * 3] = r;
//    balloons[ind * 3 + 1] = g;
//    balloons[ind * 3 + 2] = b;
//  }
//}
//
/////////////////////////////////////////////////////////////
//// sam and david
//void Balloons::setNewmanColorsDS(int rate) {
//  pulseIndex += rate;
//  if (pulseIndex > 255) pulseIndex = 0;
//  for (int j = 0; j < 10; j++) {
//    if (j % 2 == 0) {
//      // this is even
//      setBalloon(j, strip.Color(0, pulseIndex, 0));
//    } else {
//      setBalloon(j, strip.Color(pulseIndex, pulseIndex, pulseIndex));
//    }
//  }
//}
//
//void Balloons::setPulsing(int rate) {
//  pulseIndex += rate;
//  if (pulseIndex > 255) pulseIndex = 0;
//  setAllBalloons(0, 0, pulseIndex);
//}
//
//void Balloons::setDougDS(int rate) {
//  clearBalloons();
//  setBalloon(0, Wheel(byte(pulseIndex)));
//  setBalloon(1, Wheel(byte((pulseIndex - 25) % 255)));
//  setBalloon(2, Wheel(byte(((pulseIndex - 50)) % 255)));
//  setBalloon(3, Wheel(byte(((pulseIndex - 75)) % 255)));
//  setBalloon(4, Wheel(byte(((pulseIndex - 100)) % 255)));
//  setBalloon(5, Wheel(byte(((pulseIndex - 125)) % 255)));
//  setBalloon(6, Wheel(byte(((pulseIndex - 150)) % 255)));
//  setBalloon(7, Wheel(byte(((pulseIndex - 175)) % 255)));
//  setBalloon(8, Wheel(byte(((pulseIndex - 200)) % 255)));
//  setBalloon(9, Wheel(byte(((pulseIndex - 225)) % 255)));
//  //strip.setAllBalloons(255, 0, 0);
//  //strip.setBalloon(1, strip.Color(255, 0, 0));
//  pulseIndex += rate;
//  if (pulseIndex > 255) pulseIndex = 0;
//}
//
////////////////////////
//void Balloons::setRainbowLine(int cycleRate) {
//  if (millis() - lastChecked > cycleRate) {
//    lastChecked = millis();
//    pulseIndex++;
//    if (pulseIndex % 7 == 0) ledIndex++;
//    colorIndex = pulseIndex % 6;
//  }
//  int [][] colorsDown = {
//    {255, 0, 0},
//    {255, 60, 0},
//    {155, 155, 0},
//    {0, 255, 0},
//    {0, 0, 255},
//    {155, 0, 155}
//  };
//  setAllBalloons(Wheel(byte((pulseIndex) % 255)));
//  setBalloon(ledIndex % 10, colorsDown[colorIndex][0], colorsDown[colorIndex][1], colorsDown[colorIndex][2]);
//}
//
//void Balloons::setNewmanGradientGF(int rate) {
//  int pixelColors[] = { 0, 0, 50, 100, 200, 255, 200, 100, 50, 0};
//  if (millis() - lastChecked > rate) {
//    lastChecked = millis();
//    pulseIndex++;
//    if (pulseIndex > 18) pulseIndex = 0;
//  }
//  if (pulseIndex < 11) {
//    for (int i = 0; i < 10; i++) {
//      setBalloon(i, strip.Color(pixelColors[(i + pulseIndex) % 10], 255, pixelColors[(i + pulseIndex) % 10]));
//    }
//  } else if (pulseIndex < 20) {
//    int j = 20 - pulseIndex;
//    for (int i = 0; i < 10; i++) {
//      setBalloon(i, strip.Color(pixelColors[(i + j) % 10], 255, pixelColors[(i + j) % 10]));
//    }
//  }
//}
//
//void Balloons::setFadeGF() {
//  pulseIndex++;
//  if (pulseIndex % 100 == 0) {
//    fadeRandom = int(random(0, 10));
//    fadeColor[fadeRandom] = int(random(0, 255));
//  }
//  for (int i = 0; i < 10; i++) {
//    fadeColor[i] = fadeColor[i] - 1;
//    setBalloon(i, Wheel(byte(fadeColor[i])));
//  }
//}
//
//void Balloons::setRandomColour() {
//  for (int i = 0; i < 10; i++) {
//    if (colour[i] < goalColour[i]) {
//      colour[i]++;
//    } else if (colour[i] > goalColour[i]) {
//      colour[i]--;
//    } else if (colour[i] == goalColour[i]) {
//      goalColour[i] = int(random(0, 255));
//    }
//    setBalloon(i, Wheel(byte(colour[i])));
//  }
//}
//
//void Balloons::setRandomWhite() {
//  for (int i = 0; i < 10; i++) {
//    if (redStates[i] < goalRed[i]) {
//      redStates[i]++;
//    } else if (redStates[i] > goalRed[i]) {
//      redStates[i]--;
//    } else if (redStates[i] == goalRed[i]) {
//      goalRed[i] = int(random(0, 255));
//    }
//    if (greenStates[i] < goalGreen[i]) {
//      greenStates[i]++;
//    } else if (greenStates[i] > goalGreen[i]) {
//      greenStates[i]--;
//    } else if (greenStates[i] == goalGreen[i]) {
//      goalGreen[i] = int(random(0, 255));
//    }
//    if (blueStates[i] < goalBlue[i]) {
//      blueStates[i]++;
//    } else if (blueStates[i] > goalBlue[i]) {
//      blueStates[i]--;
//    } else if (blueStates[i] == goalBlue[i]) {
//      goalBlue[i] = int(random(0, 255));
//    }
//    setBalloon(i, strip.Color(int(redStates[i]), int(greenStates[i]), int(blueStates[i])));
//  }
//}
//
//void Balloons::setGoTimeGF(int cycleRate) {
//  if (millis() - lastChecked > cycleRate) {
//    lastChecked = millis();
//    pulseIndex++;
//    if (pulseIndex > 10) {
//      ledIndex++;
//      pulseIndex = 0;
//    }
//  }
//
//  clearBalloons();
//  if (ledIndex % 4 == 0) setBalloon(pulseIndex, 255, 0, 0);
//  else if (ledIndex % 4 == 1) setBalloon(pulseIndex, 0, 255, 0);
//  else if (ledIndex % 4 == 2) setBalloon(pulseIndex, 0, 0, 255);
//  else setBalloon(pulseIndex, int(random(255)), int(random(255)), int(random(255)));
//
//}
//////////////////////////////
//
//// Adapted from Adafruit Neopixel
//void rainbowCycle(int amt) {
//  rainbowIndex += amt;
//  if (rainbowIndex > 255) rainbowIndex = 0;
//  for (int i = 0; i < numBalloons; i++) {
//    byte r =  WheelR(((i * 256 / numBalloons) + rainbowIndex) & 255);
//    byte g =  WheelG(((i * 256 / numBalloons) + rainbowIndex) & 255);
//    byte b = WheelB(((i * 256 / numBalloons) + rainbowIndex) & 255);
//    setBalloon(i, r, g, b);
//  }
//}
//
//byte Balloons::WheelR(int WheelPos) {
//  WheelPos = 255 - WheelPos;
//  if (WheelPos < 85) {
//    return 255 - WheelPos * 3;
//  }
//  if (WheelPos < 170) {
//    return 0;
//  }
//  WheelPos -= 170;
//  return WheelPos * 3;
//}
//
//byte WheelG(int WheelPos) {
//  WheelPos = 255 - WheelPos;
//  if (WheelPos < 85) {
//    return 0;
//  }
//  if (WheelPos < 170) {
//    WheelPos -= 85;
//    return WheelPos * 3;
//  }
//  WheelPos -= 170;
//  return 255 - WheelPos * 3;
//}
//
//byte Balloons::WheelB(int WheelPos) {
//  WheelPos = 255 - WheelPos;
//  if (WheelPos < 85) {
//    return WheelPos * 3;
//  }
//  if (WheelPos < 170) {
//    WheelPos -= 85;
//    return 255 - WheelPos * 3;
//  }
//  WheelPos -= 170;
//  return 0;
//}
//
//

