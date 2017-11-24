class Strip {


  byte [] balloons; // balloons is an array of 30 RGB values

  int currentBalloon = 0;
  long lastChecked;
  int currentBrightness = 0;
  int brightnessDirection = 5;
  int rainbowIndex = 0;

  int direction = 1;

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
  boolean rainbowOn = false;

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
      if (true) {
        pulseIndex++;
        if (pulseIndex > 10) {
          ledIndex++;
          pulseIndex = 0;
        }
      } else {
        pulseIndex--;
        if (pulseIndex < 0) {
          ledIndex++;
          pulseIndex = 9;
        }
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
      rainbowOn = !rainbowOn;

      if (!rainbowOn) pulseIndex += 10;
      if (pulseIndex > 255) pulseIndex = 0;
    }

    if (rainbowOn) {
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

  // heartbeat
  void setHeartbeatWC(int rate, color col) {
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

  // bounce
  void setBounceWC(int rate) {
    if (millis() - lastChecked > rate) {
      lastChecked = millis();
      pulseIndex += direction;
      if (pulseIndex > 8) {
        pulseIndex = 9;
        direction = -1;
      } else if (pulseIndex < 0) {
        pulseIndex = 0;
        direction = 1;
        ledIndex += 30;
        if (ledIndex > 255) ledIndex = 0;
      }
    }
    resetBalloons();
    setBalloon(pulseIndex, Wheel(ledIndex));
  }
  ///////////////////
  void rainbowBlinkJJ(int rate) { //old light function
    if (millis() - lastChecked > rate) {
      lastChecked = millis();
      pulseIndex++;
      if (pulseIndex > 6) pulseIndex = 0;
      rainbowOn = !rainbowOn;
    }
    int split = 2;
    if (rainbowOn) {
      clear();
    } else {
      for (int j = 0; j <  (10/split); j++) {
        redStates[0] =0;
        greenStates[0] =0;
        blueStates[0] = 0;
        if (pulseIndex == 0)redStates[0] =255;
        else if (pulseIndex == 1)greenStates[0] =255;
        else if (pulseIndex == 2)blueStates[0] = 255;
        else if (pulseIndex == 3) {
          redStates[0] =255;
          blueStates[0] = 255;
        } else if (pulseIndex == 4) {
          redStates[0] =255;
          greenStates[0] =255;
        } else if (pulseIndex == 5) {
          blueStates[0] = 255;
          greenStates[0] =255;
        } else if (pulseIndex == 6) {
          redStates[0] =255;
        }
        for (int i = 0; i < split; i++) {
          setBalloon(j + (i *  10/split), redStates[0], greenStates[0], blueStates[0]);
        }
      }
    }
  }

  void backForthJJ(int rate) { //old light function
    if (millis() - lastChecked > rate) {
      lastChecked = millis();
      rainbowOn = !rainbowOn;
      clear();
    }

    for (int i = 0; i < 10; i++) {
      if (i % 2 == 0) {
        greenStates[0] =0;
        blueStates[0] = 0;
        redStates[0] =0;
        if (rainbowOn) {
          redStates[0] =255;
        } else blueStates[0] = 255;
      }
      if ((i-1) % 2 == 0) {
        redStates[0] =0;
        greenStates[0] =0;
        blueStates[0] = 0;
        if (rainbowOn) {
          blueStates[0] = 255;
        } else redStates[0] =255;
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
    if (rainbowOn) clear();
    else {
      redStates[0] = 0;
      greenStates[0] = 0;
      blueStates[0] = 0;
      if (pulseIndex == 0) redStates[0] = 255;
      else if (pulseIndex == 1) {
        redStates[0] = 255;
        greenStates[0] =72;
      } else if (pulseIndex == 2) {
        redStates[0] = 255;
        greenStates[0] =233;
      } else if (pulseIndex == 3) {
        greenStates[0] =255;
      } else if (pulseIndex == 4) {
        blueStates[0] = 255;
      } else if (pulseIndex == 5) {
        redStates[0] =167;
        greenStates[0] =66;
        blueStates[0] = 244;
      } else if (pulseIndex == 6) {
        redStates[0] =178;
        greenStates[0] =0;
        blueStates[0] = 255;
      } else if (pulseIndex == 7) {
        redStates[0] =52;
        greenStates[0] =38;
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
      clear();
      rainbowOn = true;
      lastChecked = millis();
    } else if (start_pin > 10) {
      start_pin = -1;
      clear();
      rainbowOn = true;
      lastChecked = millis();
    }

    if (!rainbowOn) {
      start_pin --;

      redStates[0] =0;
      greenStates[0] =0;
      blueStates[0] = 0;
      if (pulseIndex == 0)redStates[0] =255;
      if (pulseIndex == 1)greenStates[0] =255;
      if (pulseIndex == 2)blueStates[0] = 255;
      if (pulseIndex == 3) {
        redStates[0] =255;
        blueStates[0] = 255;
      }
      if (pulseIndex == 4) {
        redStates[0] =255;
        greenStates[0] =255;
      }
      if (pulseIndex == 5) {
        blueStates[0] = 255;
        greenStates[0] =255;
      }
      if (pulseIndex == 6) {

        redStates[0] =255;
      }
      setBalloon(start_pin, redStates[0], greenStates[0], blueStates[0]);
    }
  }

  ////////-------------------------
  void clearBalloons() {
    resetBalloons();
  }

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