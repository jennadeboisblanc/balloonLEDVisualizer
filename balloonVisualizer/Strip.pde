class Strip {


  int [] balloons; // balloons is an array of 30 RGB values

  int currentBalloon = 0;
  long lastChecked;
  int currentBrightness = 0;
  int brightnessDirection = 5;
  int rainbowIndex = 0;

  float redStates[];
  float blueStates[];
  float greenStates[];
  float fadeRate = 0.98;


  Strip() {
    balloons = new int[30];

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
      balloons[index*3] = r;
      balloons[index*3+1] = g; 
      balloons[index*3+2] = b;
    }
  }

  void setBalloon(int index, float r, float g, float b) {
    setBalloon(index, int(r), int(g), int(b));
  }

  void setBalloon(int index, color c) {
    if (index >= 0 && index < 10) {
      balloons[index*3] = int(red(c));
      balloons[index*3+1] = int(green(c)); 
      balloons[index*3+2] = int(blue(c));
    }
  }
  
  void setPixelColor(int index, color c) {
    setBalloon(index, c);
  }
  
  color Color(int r, int g, int b) {
    return color(r, g,b);
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
      fill(balloons[i*3], balloons[i*3+1], balloons[i*3 +2]);
      ellipse(i * 60 + 30, 50, 50, 50);
      line(i * 60 + 30, 75, i * 60 + 30, 150);
    }
    line(0, 150, width, 150);
  }
}