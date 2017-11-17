// jdeboi

// light modes
int RAINBOW = 0;
int PULSE = 1;
int WAVE = 2;
int TWINKLE = 3;
int mode = TWINKLE;

Strip strip;


void setup() {
  size(600, 200);

  strip = new Strip();

  //initTwitter();
}

void draw() {
  background(0);
  if (mode == RAINBOW) strip.setRainbow(10);
  else if (mode == PULSE) strip.setPulse(0, 255, 255, 1);
  else if (mode == WAVE) strip.setWave(0, 255, 255, 100);
  else if (mode == TWINKLE) strip.twinkle();

  strip.show();
  //drawTwitter();
  //transmitBalloons();
}

void transmitBalloons() {
  // send the balloon states with RF module
}