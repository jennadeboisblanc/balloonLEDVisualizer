// light modes
//EDITS BY LIBBY
int RAINBOW = 1;
int WAVE = 2;
int BLINK = 3;
int RAINBOWBLINK=4;
int RIGHTWAVE=5;
int LEFTWAVE=6;
int RIGHTFILL=7;
int LEFTFILL=8;
int RAINBOWWAVE=9;
int MOVINGRAINBOW=10;
boolean on = true; 
int mode = RIGHTFILL;

int [] balloons; // balloons is an array of 30 RGB values

int currentBalloon = 0;
long lastChecked;

int h=1;
int numBalloons=10;
int balloonSpeed=10;
int fillNum = 10;
int spotNum = -1;

void setup() {
  size(600, 200);

  balloons = new int[30];
  resetBalloons();
}

void draw() {
  background(0);
  if (mode == RAINBOW) setRainbow();
  else if (mode == WAVE) setWave(0, 255, 255, 100);
  else if (mode == BLINK) setBlink(0, 255, 255, 100);
  else if (mode == RAINBOWBLINK) setRainbowBlink(200);
  else if (mode == RIGHTWAVE) setRight(255,0,0);
  else if (mode == RAINBOWWAVE) setRainbowWave(100);
  else if (mode == LEFTWAVE) setLeft(255,0,0);
  else if (mode == RIGHTFILL) setFillUpRight(255,0,0,500);
  else if (mode == LEFTFILL) setFillUpLeft(255,0,0,500);
  else if (mode == MOVINGRAINBOW) setMovingRainbow(100);
  drawBalloons();
  transmitBalloons();  
}

void transmitBalloons() {
  // send the balloon states with RF module
}

void setRainbow() {
  colorMode(HSB, 255);
  for (int i = 0; i < balloons.length; i++) {
    color c = color(i * 25, 255, 255);
    setBalloon(i, int(red(c)), int(green(c)), int(blue(c)));
  }
  colorMode(RGB, 255);
}

void setMovingRainbow(int wait) {
  resetBalloons();
  colorMode(HSB, 255);
  if (h*5<=260) {
    if (millis() - lastChecked > wait) {
      lastChecked = millis();
      color c=color(h*5, 255, 255);
      setBalloon(currentBalloon, int(red(c)), int(green(c)), int(blue(c)));
      delay(300);
      currentBalloon++;
      if (currentBalloon > 10) currentBalloon = 0; 
      h++;
    }
    colorMode(RGB, 255);
  }
  if (h*5>=255) {
    h=0;
  }
}

void setBlink(int r, int g, int b, int wait) {
  resetBalloons();
  if (millis() - lastChecked > wait) {
    lastChecked = millis();
    on = !on;
  }
  if (on == true) {
    setAllBalloons(r, g, b);
  }
  if (on == false) {
    resetBalloons();
  }
}

void setRainbowWave(int wait) {
  resetBalloons();
  colorMode(HSB, 255);
  if (millis() - lastChecked > 5*wait) {
    lastChecked = millis();
    color c=color(currentBalloon*25, 255, 255);
    setBalloon(currentBalloon, int(red(c)), int(green(c)), int(blue(c)));
    currentBalloon++;
    if (currentBalloon > 10) currentBalloon = 0;
  }
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

//blinking rainbow
void setRainbowBlink(int wait) {
  resetBalloons();
  if (millis() - lastChecked > wait) {
    lastChecked = millis();
    on = !on;
  }
  if (on == true) {
    setRainbow();
  }
  if (on == false) {
    resetBalloons();
  }
}

void setRight(int r, int g, int b) {
  balloonSpeed=100;
  resetBalloons();
  if (millis()-lastChecked > balloonSpeed) {
    lastChecked = millis();
    balloonSpeed+=50*currentBalloon;
    delay(balloonSpeed);
    currentBalloon++;
    if (currentBalloon > 10) {
      currentBalloon=0;
    }
  }
  setBalloon(currentBalloon, r, g, b);
}

void setFillUpRight(int r, int g, int b, int wait) {
  if (millis() - lastChecked > wait) {
    lastChecked = millis();
    spotNum++;
    if (spotNum == fillNum) {
      fillNum--;
      spotNum = 0;
    }
  }
  resetBalloons();
  setBalloon(spotNum, r,g,b);
  for (int i = fillNum; i < 10; i++) {
    setBalloon(i, r,g,b);
  }
}

void setFillUpLeft(int r, int g, int b, int wait) {
  if (millis() - lastChecked > wait) {
    lastChecked = millis();
    fillNum--;
    if (fillNum == spotNum) {
      spotNum++;
      fillNum = 10;
    }
  }
  resetBalloons();
  setBalloon(fillNum, r,g,b);
  for (int i = spotNum; i >= 0; i--) {
    setBalloon(i,r,g,b);
  }
}

void setLeft(int r, int g, int b) {
  balloonSpeed=100;
  resetBalloons();
  if (millis()-lastChecked > balloonSpeed) {
    lastChecked = millis();
    balloonSpeed+=50*((10-currentBalloon%10));
    delay(balloonSpeed);
    currentBalloon--;
    if (currentBalloon < 0 ) {
      currentBalloon=10;
    }
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

void setAllBalloons(int r, int g, int b) {
  for (int i=0; i<10; i++) {
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