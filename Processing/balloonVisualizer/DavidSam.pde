
int hue = 0;
int storey = 0;

void pulsing() {
  for (int i = 0; i < 255; i++) {
    for (int j = 0; j < 12; j++) {

      strip.setPixelColor(j, strip.Color(0, 0, i));
      delay(4);
    }
    strip.show();
  }
}

void newmancolors() {
  for (int i = 0; i < 255; i++) {
    for (int j = 0; j < 12; j++) {
      if (j % 2 == 0) {
        // this is even
        strip.setPixelColor(j, strip.Color(0, i, 0));
        delay(1);
      } else {
        strip.setPixelColor(j, strip.Color(i, i, i));
      }
    }
    strip.show();
  }
  strip.show();
}

// extra brackets
// but why a for loop of 3 times, effectively doing the exact same things 3 times; for loop not serving a purpose
// also, only 10 LEDs so go up to 9, not 12
// too many arguments in setPixelColor - should have two (missing strip.Color() or just Wheel())
// use a for loop to set all the colors
// Wheel() at some points is going to be negative
// wth is storey doing?
void Doug() {
  strip.clear();
  //for (int i = 0; i < 3; i++) {
  strip.setPixelColor(0, Wheel(hue));
  strip.setPixelColor(1, Wheel(hue - 25));
  strip.setPixelColor(2, Wheel(hue - 50));
  strip.setPixelColor(3, Wheel(hue - 75));
  strip.setPixelColor(4, Wheel(hue - 100));
  strip.setPixelColor(5, Wheel(hue - 125));
  strip.setPixelColor(6, Wheel(hue - 150));
  strip.setPixelColor(7, Wheel(hue - 175));
  strip.setPixelColor(8, Wheel(hue - 200));
  strip.setPixelColor(9, Wheel(hue - 225));
  //}
  hue += 1;
  if (hue > 255) hue = 0;
  //storey += 50;
  //if (storey > 255) storey = 0;
}

// Wheel got messed up
// not returning arguments if >= 85
color Wheel(int WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else return color(0);
}

void DNA() {
  for (int fadeValue = 0; fadeValue <= 255; fadeValue += 5) {
    for (int l = 0; l < 12; l++) {
      strip.setPixelColor(l, strip.Color(fadeValue, 0, 0));
      delay(30);
      strip.show ();
      strip.clear ();
    }
  }

  for (int fadeValue = 255; fadeValue >= 0; fadeValue -= 5) {
    for (int l = 12; l > 12; l--) {
      strip.setPixelColor(l, fadeValue);
      delay(30);
      strip.show();
      strip.clear();
    }
  }
}