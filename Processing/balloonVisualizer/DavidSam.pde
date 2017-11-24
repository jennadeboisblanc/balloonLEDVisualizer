

//int storey = 0;


//void pulsingDS(int rate) {
//  pulseIndex+=rate;
//  if (pulseIndex > 255) pulseIndex = 0;
//  strip.setAllBalloons(0, 0, pulseIndex);
//}

//void newmancolorsDS(int rate) {
//  pulseIndex += rate;
//  if (pulseIndex > 255) pulseIndex = 0;
//  for (int j = 0; j < 12; j++) {
//    if (j % 2 == 0) {
//      // this is even
//      strip.setPixelColor(j, strip.Color(0, pulseIndex, 0));
//    } else {
//      strip.setPixelColor(j, strip.Color(pulseIndex, pulseIndex, pulseIndex));
//    }
//  }
//  strip.setPixelColor(0, strip.Color(255, 0, 0));
//  strip.show();
//}

//void dougDS(int rate) {
  //strip.clear();
  //strip.setPixelColor(0, Wheel(pulseIndex));
  //strip.setPixelColor(1, Wheel((pulseIndex - 25)%255));
  //strip.setPixelColor(2, Wheel((pulseIndex - 50))%255);
  //strip.setPixelColor(3, Wheel((pulseIndex - 75))%255);
  //strip.setPixelColor(4, Wheel((pulseIndex - 100))%255);
  //strip.setPixelColor(5, Wheel((pulseIndex - 125))%255);
  //strip.setPixelColor(6, Wheel((pulseIndex - 150))%255);
  //strip.setPixelColor(7, Wheel((pulseIndex - 175))%255);
  //strip.setPixelColor(8, Wheel((pulseIndex - 200))%255);
  //strip.setPixelColor(9, Wheel((pulseIndex - 225))%255);
  //strip.setAllBalloons(255, 0, 0);
//  strip.setBalloon(1, strip.Color(255, 0, 0));
//  strip.show();
//  pulseIndex += rate;
//  if (pulseIndex > 255) pulseIndex = 0;
//}

//--------------------------


//void pulsing() {
//  for (int i = 0; i < 255; i++) {
//    for (int j = 0; j < 12; j++) {
//      strip.setPixelColor(j, strip.Color(0, 0, i));
//      delay(4);
//    }
//    strip.show();
//  }
//}

//void newmancolors() {
//  for (int i = 0; i < 255; i++) {
//    for (int j = 0; j < 12; j++) {
//      if (j % 2 == 0) {
//        // this is even
//        strip.setPixelColor(j, strip.Color(0, i, 0));
//        delay(1);
//      } else {
//        strip.setPixelColor(j, strip.Color(i, i, i));
//      }
//    }
//    strip.show();
//  }
//  strip.show();
//}

// extra brackets
// but why a for loop of 3 times, effectively doing the exact same things 3 times; for loop not serving a purpose
// also, only 10 LEDs so go up to 9, not 12
// too many arguments in setPixelColor - should have two (missing strip.Color() or just Wheel())
// use a for loop to set all the colors
// Wheel() at some points is going to be negative
// wth is storey doing?
void Doug() {
  //strip.clear();
  ////for (int i = 0; i < 3; i++) {
    
  //strip.setPixelColor(0, Wheel(pulseIndex));
  //strip.setPixelColor(1, Wheel(pulseIndex - 25));
  //strip.setPixelColor(2, Wheel(pulseIndex - 50));
  //strip.setPixelColor(3, Wheel(pulseIndex - 75));
  //strip.setPixelColor(4, Wheel(pulseIndex - 100));
  //strip.setPixelColor(5, Wheel(pulseIndex - 125));
  //strip.setPixelColor(6, Wheel(pulseIndex - 150));
  //strip.setPixelColor(7, Wheel(pulseIndex - 175));
  //strip.setPixelColor(8, Wheel(pulseIndex - 200));
  //strip.setPixelColor(9, Wheel(pulseIndex - 225));
  ////}
  //pulseIndex += 1;
  //if (pulseIndex > 255) pulseIndex = 0;
  ////storey += 50;
  ////if (storey > 255) storey = 0;
}

// Wheel got messed up
// not returning arguments if >= 85
//color WheelDS(int WheelPos) {
//  WheelPos = 255 - WheelPos;
//  if (WheelPos < 85) {
//    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
//  } else return color(0);
//}

//void DNA() {
//  for (int fadeValue = 0; fadeValue <= 255; fadeValue += 5) {
//    for (int l = 0; l < 12; l++) {
//      strip.setPixelColor(l, strip.Color(fadeValue, 0, 0));
//      delay(30);
//      strip.show ();
//      strip.clear ();
//    }
//  }

//  for (int fadeValue = 255; fadeValue >= 0; fadeValue -= 5) {
//    for (int l = 12; l > 12; l--) {
//      strip.setPixelColor(l, fadeValue);
//      delay(30);
//      strip.show();
//      strip.clear();
//    }
//  }
//}