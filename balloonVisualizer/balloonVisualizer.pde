// light modes
int RAINBOW = 0;
int PULSE = 1;
int WAVE = 2;
int mode = WAVE;

int [] balloons; // balloons is an array of 30 RGB values

int currentBalloon = 0;
long lastChecked;

void setup() {
  size(600, 200);

  balloons = new int[30];
  resetBalloons();
}

void draw() {
  background(0);
  if (mode == RAINBOW) setRainbow();
  else if (mode == PULSE) setPulse();
  else if (mode == WAVE) setWave(0, 255, 255, 100);
  drawBalloons();
  transmitBalloons();
}

void transmitBalloons() {
  // send the balloon states with RF module
}

void setRainbow() {
  // TODO
}

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