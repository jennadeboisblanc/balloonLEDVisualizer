//void accidentalButWorks() {
//  for (int j = 0; j < 255; j += 30) {
//    for (int i = 0; i < pixelCount; i++) {
//      strip.setPixelColor (i, Wheel(j));
//      strip.show();
//    }

//    delay(100);
//    strip.clear();
//    strip.show();
//    delay(100);
//    for (int k = 255; k > 0; k--)
//      for (int i = 0; i < pixelCount; i++) {
//        strip.setPixelColor (i, Wheel(k));
//        strip.show();
//      }
//    delay(100);
//    stopBlinking();
//  }
//}
//void stopBlinking() {
//  strip.clear();
//  strip.show();
//  delay(500);
//}

//// lightFunction1


//void lightFunction1 (int t) {
//  for (int q = 0; q < 255; q += 30) {
//    for  (int i = 0; i < pixelCount; i++) {

//      strip.setPixelColor (i, Wheel(q));
//      strip.show ();
//      delay (t);
//      strip.clear ();



//    }
//    //Reverses the function
//    for  (int w = 9; w >= 0; w--) {

//      strip.setPixelColor (w, Wheel(q));
//      strip.show ();
//      delay (t);
//      strip.clear ();

//    }
//  }

//  delay (t);
//}

//void bounce (int t) {
//  for (int q = 0; q < 255; q += 30) {
//    for  (int i = 0; i < 10; i++) {

//      strip.setPixelColor (i, Wheel(q));
//      strip.show ();
//      delay (t);
//      strip.clear ();

//    }
//    delay (t);
//  }
//}



//void bounceOtherWay (int t) {
//  for (int q = 0; q < 255; q += 30) {
//    for  (int i = 10; i > -1; i--) {

//      strip.setPixelColor (i, Wheel(q));
//      strip.show ();
//      delay (t);
//      strip.clear ();

//    }
//    delay (t);
//  }
//}