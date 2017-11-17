// jdeboi

// light modes
int RAINBOW = 0;
int PULSE = 1;
int WAVE = 2;
int TWINKLE = 3;
int mode = TWINKLE;

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

void setup() {
  size(600, 200);

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
  
  initTwitter();
}

void draw() {
  background(0);
  if (mode == RAINBOW) setRainbowCycle(10);
  else if (mode == PULSE) setPulse();
  if (mode == RAINBOW) setRainbow(10);
  else if (mode == PULSE) setPulse(0, 255, 255, 1);
  else if (mode == WAVE) setWave(0, 255, 255, 100);
  else if (mode == TWINKLE) twinkle();
  drawTwitter();
  drawBalloons();
  transmitBalloons();
}


void keyPressed() {
  if (keyCode == RIGHT) {
    println(mode);
    mode++;
    if (mode > 2) mode = 0;
  }
}

void transmitBalloons() {
  // send the balloon states with RF module
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

void resetBalloons() {
  for (int i = 0; i < 10; i++) {
    setBalloon(i, 0, 0, 0);
  }
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

void drawBalloons() {
  stroke(255);
  strokeWeight(2);
  for (int i = 0; i < 10; i++) {
    fill(balloons[i*3], balloons[i*3+1], balloons[i*3 +2]);
    ellipse(i * 60 + 30, 50, 50, 50);
    line(i * 60 + 30, 75, i * 60 + 30, 150);
  }
  line(0, 150, width, 150);
}

//------------------------------------------------------------------------------\
void setPulse() {
  // TODO
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

// Adapted from Adafruit Neopixel
void setRainbowCycle(int wait) {
  if (millis() - lastChecked > wait) {
    lastChecked = millis();
    rainbowIndex++;
    if (rainbowIndex > 256) rainbowIndex = 0;
  }
  for (int i = 0; i < 10; i++) {
    int ind = ((i * 256 / 10) + rainbowIndex) & 255;
    int r =  Wheel(ind)[0];
    int g =  Wheel(ind)[1];
    int b = Wheel(ind)[2];
    setBalloon(i, r, g, b);
  }
}

// Adapted from Adafruit Neopixel
// Input a value 0 to 255 to get back a color from red to purple 
// in the form of an array of RGB values.
// The colours are a transition r - g - b - back to r.
int[] Wheel(int WheelPos) {
  WheelPos = 255 - WheelPos;
  //int rgb[] = new int[3];
  if(WheelPos < 85) {
    int rgb[] = {255 - WheelPos * 3, 0, WheelPos * 3};
    return rgb;
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    int rgb[] = {0, WheelPos * 3, 255 - WheelPos * 3};
    return rgb;
  }
  WheelPos -= 170;
  int rgb[] = {WheelPos * 3, 255 - WheelPos * 3, 0};
  return rgb;
}