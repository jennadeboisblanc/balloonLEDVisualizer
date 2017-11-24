class Strip {


  byte [] balloons; // balloons is an array of 30 RGB values

  int currentBalloon = 0;
  long lastChecked;
  int currentBrightness = 0;
  int brightnessDirection = 5;
  int rainbowIndex = 0;

  float redStates[];
  float blueStates[];
  float greenStates[];
  float fadeRate = 0.98;
  int fadeRandom = 0;
  int fadeColor[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int goalRed[] = {255, 0, 255, 255, 0, 0, 255, 255, 255, 0};
  int goalGreen[] = {255, 0, 0, 255, 255, 0, 255, 255, 0, 0};
  int goalBlue[] = {255, 0, 255, 0, 255, 255, 0, 255, 0, 0};
  int goalColour[] = {255, 0, 255, 255, 0, 0, 255, 0, 255, 255};
  int colour[] = {110, 110, 110, 110, 110, 110, 110, 110, 110, 110};
  boolean rainbowTime = false;

  Strip() {
    balloons = new byte[30];

    redStates = new float[10];
    greenStates = new float[10];
    blueStates = new float[10];
    for (int l = 0; l < 10; l++) {
      redStates[l] = 0;
      greenStates[l] = 0;
      blueStates[l] = 0;
    }

    resetBalloons();
  }

  void transmit() {

    for (int i = 0; i < balloons.length; i++) {
      myPort.write(balloons);
    }
  }

  void setRainbow(int wait) {
    colorMode(HSB, 255);
    if (millis() - lastChecked > wait) {
      lastChecked = millis();
      rainbowIndex++;
    }
    for (int i = 0; i < 10; i++) {
      setBalloon(i, color(((i * 25) - rainbowIndex)%255, 255, 255));
    }
    colorMode(RGB, 255);
  }

  void twinkle() {
    if (int(random(5)) == 1) {
      int i = int(random(10));
      if (redStates[i] < 1 && greenStates[i] < 1 && blueStates[i] < 1) {
        redStates[i] = random(256);
        greenStates[i] = random(256);
        blueStates[i] = random(256);
      }
    }

    for (int l = 0; l < 10; l++) {
      if (redStates[l] > 1 || greenStates[l] > 1 || blueStates[l] > 1) {
        setBalloon(l, redStates[l], greenStates[l], blueStates[l]);
        if (redStates[l] > 1) {
          redStates[l] = redStates[l] * fadeRate;
        } else {
          redStates[l] = 0;
        }
        if (greenStates[l] > 1) {
          greenStates[l] = greenStates[l] * fadeRate;
        } else {
          greenStates[l] = 0;
        }
        if (blueStates[l] > 1) {
          blueStates[l] = blueStates[l] * fadeRate;
        } else {
          blueStates[l] = 0;
        }
      } else {
        setBalloon(l, 0, 0, 0);
      }
    }
  }

  void setPulse(int r, int g, int b, int wait) {
    float value = hue(color(r, g, b));
    if (millis() - lastChecked > wait) {
      lastChecked = millis();
      currentBrightness += brightnessDirection;
      if (currentBrightness > 255) brightnessDirection = -5;
      else if (currentBrightness < 0) brightnessDirection = 5;
    }
    colorMode(HSB, 255);
    setAllBalloons(color(value, 255, currentBrightness));
    colorMode(RGB, 255);
  }

  void setWave(int r, int g, int b, int wait) {
    resetBalloons();
    if (millis() - lastChecked > wait) {
      lastChecked = millis();
      currentBalloon++;
      if (currentBalloon > 10) currentBalloon = 0;
    }
    setBalloon(currentBalloon, r, g, b);
  }

  // -------------------
  // sam and david
  void setNewmanColorsDS(int rate) {
    pulseIndex += rate;
    if (pulseIndex > 255) pulseIndex = 0;
    for (int j = 0; j < 10; j++) {
      if (j % 2 == 0) {
        // this is even
        setBalloon(j, strip.Color(0, pulseIndex, 0));
      } else {
        setBalloon(j, strip.Color(pulseIndex, pulseIndex, pulseIndex));
      }
    }
  }

  void setPulsing(int rate) {
    pulseIndex+=rate;
    if (pulseIndex > 255) pulseIndex = 0;
    setAllBalloons(0, 0, pulseIndex);
  }

  void setDougDS(int rate) {
    clear();
    setBalloon(0, Wheel(byte(pulseIndex)));
    setBalloon(1, Wheel(byte((pulseIndex - 25)%255)));
    setBalloon(2, Wheel(byte(((pulseIndex - 50))%255)));
    setBalloon(3, Wheel(byte(((pulseIndex - 75))%255)));
    setBalloon(4, Wheel(byte(((pulseIndex - 100))%255)));
    setBalloon(5, Wheel(byte(((pulseIndex - 125))%255)));
    setBalloon(6, Wheel(byte(((pulseIndex - 150))%255)));
    setBalloon(7, Wheel(byte(((pulseIndex - 175))%255)));
    setBalloon(8, Wheel(byte(((pulseIndex - 200))%255)));
    setBalloon(9, Wheel(byte(((pulseIndex - 225))%255)));
    //strip.setAllBalloons(255, 0, 0);
    //strip.setBalloon(1, strip.Color(255, 0, 0));
    strip.show();
    pulseIndex += rate;
    if (pulseIndex > 255) pulseIndex = 0;
  }

  //////////////////////
  void setRainbowLine(int cycleRate) {
    if (millis() - lastChecked > cycleRate) {
      lastChecked = millis();
      pulseIndex++;
      if (pulseIndex % 7 == 0) ledIndex++;
      colorIndex = pulseIndex%6;
    }
    int [][] colorsDown = {
      {255, 0, 0}, 
      {255, 60, 0}, 
      {155, 155, 0}, 
      {0, 255, 0}, 
      {0, 0, 255}, 
      {155, 0, 155}
    };
    setAllBalloons(Wheel(byte((pulseIndex)%255)));
    setBalloon(ledIndex%10, colorsDown[colorIndex][0], colorsDown[colorIndex][1], colorsDown[colorIndex][2]);
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
        setBalloon(i, strip.Color(pixelColors[(i + pulseIndex) % 10], 255, pixelColors[(i + pulseIndex) % 10]));
      }
    } else if (pulseIndex < 20) {
      int j = 20 - pulseIndex;
      for (int i = 0; i < 10; i++) {
        setBalloon(i, strip.Color(pixelColors[(i + j) % 10], 255, pixelColors[(i + j) % 10]));
      }
    }
  }

  void setFadeGF() {
    pulseIndex++;
    if (pulseIndex%100 == 0) {
      fadeRandom = int(random(0, 10));
      fadeColor[fadeRandom] = int(random(0, 255));
    }
    for (int i = 0; i<10; i++) {
      fadeColor[i] = fadeColor[i]-1;
      setBalloon(i, Wheel(byte(fadeColor[i])));
    }
  }

  void setRandomColour() {
    for (int i = 0; i<10; i++) {
      if (colour[i]<goalColour[i]) {
        colour[i]++;
      } else if (colour[i]>goalColour[i]) {
        colour[i]--;
      } else if (colour[i]==goalColour[i]) {
        goalColour[i] = int(random(0, 255));
      }
      setBalloon(i, Wheel(byte(colour[i])));
      strip.show();
    }
  }

  void setRandomWhite() {
    for (int i = 0; i<10; i++) {
      if (redStates[i]<goalRed[i]) {
        redStates[i]++;
      } else if (redStates[i]>goalRed[i]) {
        redStates[i]--;
      } else if (redStates[i]==goalRed[i]) {
        goalRed[i] = int(random(0, 255));
      }
      if (greenStates[i]<goalGreen[i]) {
        greenStates[i]++;
      } else if (greenStates[i]>goalGreen[i]) {
        greenStates[i]--;
      } else if (greenStates[i]==goalGreen[i]) {
        goalGreen[i] = int(random(0, 255));
      }
      if (blueStates[i]<goalBlue[i]) {
        blueStates[i]++;
      } else if (blueStates[i]>goalBlue[i]) {
        blueStates[i]--;
      } else if (blueStates[i]==goalBlue[i]) {
        goalBlue[i] = int(random(0, 255));
      }
      setBalloon(i, strip.Color(int(redStates[i]), int(greenStates[i]), int(blueStates[i])));
      strip.show();
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

    clear();
    if (ledIndex%4 == 0) setBalloon(pulseIndex, 255, 0, 0);
    else if (ledIndex%4 == 1) setBalloon(pulseIndex, 0, 255, 0);
    else if (ledIndex%4 == 2) setBalloon(pulseIndex, 0, 0, 255);
    else setBalloon(pulseIndex, int(random(255)), int(random(255)), int(random(255)));

    // delayTime = delayTime*.90;

    //for (int y=0; y<7; y++) {
    //  for (int x=0; x<25; x++) {
    //    for (int i=0; i<10; i++) {
    //      clear();
    //      setBalloon(i, strip.Color(150-(25*y), 10*x, y*40));
    //      strip.show();
    //      delay(50);
    //    }
    //  }
    //}
  }


  // Will and Connor 
  void setAccidentalWC(int rate) {
    if (millis() - lastChecked > rate) {
      lastChecked = millis();
      rainbowTime = !rainbowTime;

      if (!rainbowTime) pulseIndex += 10;
      if (pulseIndex > 255) pulseIndex = 0;
    }

    if (rainbowTime) {
      ledIndex+=10;
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



  ////////-------------------------
  void resetBalloons() {
    for (int i = 0; i < 10; i++) {
      setBalloon(i, 0, 0, 0);
    }
  }

  void clear() {
    resetBalloons();
  }

  void setBalloon(int index, int r, int g, int b) {
    if (index >= 0 && index < 10) {
      balloons[index*3] = byte(r);
      balloons[index*3+1] = byte(g); 
      balloons[index*3+2] = byte(b);
    }
  }

  void setBalloon(int index, float r, float g, float b) {
    setBalloon(index, int(r), int(g), int(b));
  }

  void setBalloon(int index, color c) {
    if (index >= 0 && index < 10) {
      balloons[index*3] = byte(constrain(red(c), 0, 255));
      balloons[index*3+1] = byte(constrain(green(c), 0, 255)); 
      balloons[index*3+2] = byte(constrain(blue(c), 0, 255));
    }
  }

  void setPixelColor(int index, color c) {
    setBalloon(index, c);
  }

  color Color(int r, int g, int b) {
    return color(r, g, b);
  }

  void setAllBalloons(int r, int g, int b) {
    for (int i = 0; i < balloons.length; i++) {
      setBalloon(i, r, g, b);
    }
  }

  void setAllBalloons(color c) {
    for (int i = 0; i < balloons.length; i++) {
      setBalloon(i, c);
    }
  }

  void show() {
    stroke(255);
    strokeWeight(2);
    for (int i = 0; i < 10; i++) {
      int c0 = balloons[i*3] & 0xFF;
      int c1 = balloons[i*3 + 1] & 0xFF;
      int c2 = balloons[i*3 + 2] & 0xFF;
      fill(c0, c1, c2);
      ellipse(i * 60 + 30, 50, 50, 50);
      line(i * 60 + 30, 75, i * 60 + 30, 150);
    }
    line(0, 150, width, 150);
  }
}