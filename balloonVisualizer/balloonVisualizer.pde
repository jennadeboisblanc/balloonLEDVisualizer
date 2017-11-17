// light modes
int RAINBOW = 0;
int PULSE = 1;
int WAVE = 2;
int mode = RAINBOW;

int [] balloons; // balloons is an array of 30 RGB values

int currentBalloon = 0;
int rainbowIndex = 0;
long lastChecked;

void setup() {
  size(600, 200);

  balloons = new int[30];
  resetBalloons();
}

void draw() {
  background(0);
  if (mode == RAINBOW) setRainbowCycle(10);
  else if (mode == PULSE) setPulse();
  else if (mode == WAVE) setWave(0, 255, 255, 100);
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