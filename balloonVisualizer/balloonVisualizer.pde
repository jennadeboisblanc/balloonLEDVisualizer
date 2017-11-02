// light modes
//EDITS BY LIBBY
int RAINBOW = 0;
int PULSE = 1;
int WAVE = 2;
int BLINK = 3;
int RAINBOWBLINK=4;
boolean on = true; 
int mode = PULSE;

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
  else if (mode == PULSE) setPulse(0, 0, 0, 255);
  else if (mode == WAVE) setWave(0, 255, 255, 100);
  else if (mode == BLINK) setBlink(0, 255, 255, 100);
  else if (mode==RAINBOWBLINK) setRainbowBlink(200);
  drawBalloons();
  transmitBalloons();
}

void transmitBalloons() {
  // send the balloon states with RF module
}

//Set rainbow for all balloons 
void setRainbow() {
  resetBalloons();
  int r=255;
  int g=0;
  int b=0;
  setBalloon(0, r,g,b);
  g=g+100;
  setBalloon(1, r,g,b);
  g=g+100;
  setBalloon(2, r,g,b);
  g=g+55;
  setBalloon(3, r,g,b);
  r=r-100;
  setBalloon(4, r,g,b);
  r=r-155;b=b+100;
  setBalloon(5, r,g,b);
  b=b+100;
  setBalloon(6, r,g,b);
  b=b+155;g=g-100;
  setBalloon(7, r,g,b);
  g=g-100;
  setBalloon(8, r,g,b);
  g=g-100;r=r+100;
  setBalloon(9,r,g,b);
  r=r+100;
}

void setPulse(int r, int g, int b, int wait) {
  // TODO
  resetBalloons();
}

void setBlink(int r, int g, int b, int wait) {
  resetBalloons();
  if (millis() - lastChecked > wait) {
    lastChecked = millis();
    on = !on; 
  }
  if (on == true){
    setAllBalloons(r, g, b);
  }
  if (on == false){
    resetBalloons();
  }
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

//blinking rainbow
void setRainbowBlink(int wait){
   resetBalloons();
  if (millis() - lastChecked > wait) {
    lastChecked = millis();
    on = !on; 
  }
  if (on == true){
    setRainbow();
  }
  if (on == false){
    resetBalloons();
  }
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

void setAllBalloons(int r, int g, int b){
  for (int i=0; i<10; i++){
    setBalloon(i, r, g, b);
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