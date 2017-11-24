//int array1[][loops][7] = {
//  {
//    {10, 0, 7, 255, 500, 100}, 
//    {0, 10, 7, 255, 500, 100}, 
//  }, 
//  {
//    {0, 10, 7, 255, 500, 100, 1}, 
//    {0, 10, 1, 255, 500, 0, 1}, 
//    {0, 10, 7, 255, 500, 100, 1}, 
//    {0, 10, 2, 255, 500, 0, 1}, 
//    {0, 10, 7, 255, 500, 100, 1}, 
//    {0, 10, 3, 255, 500, 0, 1}, 
//    {0, 10, 7, 255, 500, 100, 1}, 
//    {0, 10, 4, 255, 500, 0, 1}, 
//    {0, 10, 7, 255, 500, 100, 1}, 
//    {0, 10, 5, 255, 500, 0, 1}, 
//    {0, 10, 7, 255, 500, 100, 1}, 
//    {0, 10, 6, 255, 500, 0, 1}
//  }, 
//  {
//    {0, 4, 1, 255, 500, 000, 1}, 
//    {5, 10, 2, 255, 500, 000, 1}, 

//    {0, 4, 1, 255, 500, 000, 1}, 
//    {5, 10, 2, 255, 500, 000, 1}, 

//    {0, 4, 1, 255, 500, 000, 1}, 
//    {5, 10, 2, 255, 500, 000, 1}, 
//  }, 
//  {
//    {1, 10, 1, 255, 500, 100, 2}, 
//    {0, 9, 3, 255, 500, 100, 2}, 
//  }
//};


//int redStates[0] =0;
//int greenStates[0] =0;
//int blueStates[0] = 0;
////int pulseIndex = -1;

//int start_pin;
//int ledPin = 0;
//int speed = 150;
//int accel = 0;
//int pattern = 2;

//boolean rotate = false;


//int function = -1;

//void function1() {
//  for (int loop = 0; loop < loops; loop++) {
//    clear();
//    int start_led = array1[function][loop][0];
//    int end_led = array1[function][loop][1];
//    int hue = array1[function][loop][2];
//    int intensity = array1[function][loop][3];
//    int milliseconds = array1[function][loop][4];
//    int milliseconds2 = array1[function][loop][5];
//    int pattern = array1[function][loop][6]; 
//    if (pattern == 0) pattern = 1;
//    int coloredStates[0] =hue;
//    if (start_led == 0 && end_led == 0)continue;
//    if (hue == 7)coloredStates[0] =0;
//    Serial.println(start_led);
//    for (int led = start_led; (led < PIXEL_COUNT + pattern) && (led >= 0); (start_led > end_led ? led-=pattern : led+=pattern)) {
//      //Serial.println(led);
//      if (hue == 7) {
//        color++;
//      }
//      int redStates[0] =0;
//      int greenStates[0] =0;
//      int blueStates[0] = 0;
//      if (color > 6)coloredStates[0] =1;
//      if (color == 1)redStates[0] =intensity;
//      if (color == 2)greenStates[0] =intensity;
//      if (color == 3)blueStates[0] = intensity;
//      if (color == 4) {
//        redStates[0] =intensity;
//        greenStates[0] =intensity;
//      }
//      if (color == 5) {
//        redStates[0] =intensity;
//        blueStates[0] = intensity;
//      }
//      if (color == 6) {
//        greenStates[0] =intensity;
//        blueStates[0] = intensity;
//      }
//      setBalloon(led, redStates[0], greenStates[0], blueStates[0]);
//      strip.show();
//      if (milliseconds2 > 0)delay(milliseconds2);
//    }
//    if (milliseconds > 0)delay(milliseconds);
//  }
//} 





// same as rainbowblink except maybe more just random colors
//void colorBlink(int rate) {  //james N light function
//  if (millis() - lastChecked > rate) {
//    lastChecked = millis();
//    pulseIndex = random(8);
//    rainbowOn = !rainbowOn;
//  }
//  if (rainbowOn) clear();
//  else {
//    redStates[0] = 0;
//    greenStates[0] = 0;
//    blueStates[0] = 0;
//    if (pulseIndex == 0) redStates[0] = 255;
//    else if (pulseIndex == 1) {
//      redStates[0] = 255;
//      greenStates[0] =72;
//    } else if (pulseIndex == 2) {
//      redStates[0] = 255;
//      greenStates[0] =233;
//    } else if (pulseIndex == 3) {
//      greenStates[0] =255;
//    } else if (pulseIndex == 4) {
//      blueStates[0] = 255;
//    } else if (pulseIndex == 5) {
//      redStates[0] =167;
//      greenStates[0] =66;
//      blueStates[0] = 244;
//    } else if (pulseIndex == 6) {
//      redStates[0] =178;
//      greenStates[0] =0;
//      blueStates[0] = 255;
//    } else if (pulseIndex == 7) {
//      redStates[0] =52;
//      greenStates[0] =38;
//      blueStates[0] = 232;
//    }
//    setAllBalloons(redStates[0], greenStates[0], blueStates[0]);
//  }
//}


// rainbowBlink
//void pattern0() { //old light function
//  if (millis() - lastChecked > rate) {
//    lastChecked = millis();
//    pulseIndex++;
//    rainbowOn = !rainbowOn;
//  }
//  int split = 2;
//  if (rainbowOn) {
//    clear();
//  } else {
//    for (int j = 0; j <  (10/split); j++) {
//      redStates[0] =0;
//      greenStates[0] =0;
//      blueStates[0] = 0;
//      pulseIndex++;
//      if (pulseIndex == 0)redStates[0] =255;
//      else if (pulseIndex == 1)greenStates[0] =255;
//      else if (pulseIndex == 2)blueStates[0] = 255;
//      else if (pulseIndex == 3) {
//        redStates[0] =255;
//        blueStates[0] = 255;
//      } else if (pulseIndex == 4) {
//        redStates[0] =255;
//        greenStates[0] =255;
//      } else if (pulseIndex == 5) {
//        blueStates[0] = 255;
//        greenStates[0] =255;
//      } else if (pulseIndex == 6) {
//        pulseIndex = 1;
//        redStates[0] =255;
//      }
//      for (int i = 0; i < split; i++) {
//        setBalloon(j + (i *  10/split), strip.Color(redStates[0], greenStates[0], blueStates[0]));
//      }
//    }
//  }
//}

// flash back forth
//void pattern1() { //old light function
//  clear();
//  rotate = !rotate;
//  for (int i = 0; i < 10; i++) {
//    if (i % 2 == 0) {
//      greenStates[0] =0;
//      blueStates[0] = 0;
//      redStates[0] =0;
//      if (rotate) {
//        redStates[0] =255;
//      } else blueStates[0] = 255;
//    }
//    if ((i-1) % 2 == 0) {
//      redStates[0] =0;
//      greenStates[0] =0;
//      blueStates[0] = 0;
//      if (rotate) {
//        blueStates[0] = 255;
//      } else redStates[0] =255;
//    }
//    setBalloon(i, strip.Color(r, g, b));
//  }
//  delay(500);
//  strip.show();
//}


// what is pattern doing? doesn't seem like anything
// what is ledpin doing? seems like nothing
//void pattern2() { //old light function
//  pulseIndex = -1;
//  if (start_pin < 0) {
//    start_pin = 10;
//    clear();
//    strip.show();
//    delay(150);
//  }
//  if (start_pin > 10) {
//    start_pin = -1;
//    clear();
//    strip.show();
//    delay(150);
//  }

//  if (ledPin == 0) {
//    start_pin --;
//  } else {
//    start_pin ++;
//  }
//  if (pattern == 1) {
//    setBalloon(start_pin, strip.Color(redStates[0], greenStates[0], blueStates[0]));
//  } else if (pattern == 2) {
//    pulseIndex++;
//    redStates[0] =0;
//    greenStates[0] =0;
//    blueStates[0] = 0;
//    if (pulseIndex == 0)redStates[0] =255;
//    if (pulseIndex == 1)greenStates[0] =255;
//    if (pulseIndex == 2)blueStates[0] = 255;
//    if (pulseIndex == 3) {
//      redStates[0] =255;
//      blueStates[0] = 255;
//    }
//    if (pulseIndex == 4) {
//      redStates[0] =255;
//      greenStates[0] =255;
//    }
//    if (pulseIndex == 5) {
//      blueStates[0] = 255;
//      greenStates[0] =255;
//    }
//    if (pulseIndex == 6) {
//      pulseIndex = 1;
//      redStates[0] =255;
//    }
//    setBalloon(start_pin, strip.Color(redStates[0], greenStates[0], blueStates[0]));
//  }
//}