
void setup() {
  size(200, 100);
}

void draw() {
  int r = 50;
  int g = 50;
  int b = 50;
  println(r, g, b);
  //getHue(r,g,b);
  println(getHue(r, g, b));

  colorMode(RGB, 255);
  background(255);
  fill(r, g, b);
  rect(0, 0, width/2, height);

  //colorMode(HSB, 255);
  //int h = getHue(r, g, b);
  //if (h == -1) fill(255);
  //else if (h == -2) fill(0);
  //else fill(h, 255, 255);
  //rect(width/2, 0, width/2, height);
  
  colorMode(HSB, 255);
  int h = int(map(mouseX, 0, width, 0, 255));
  if (h == -1) fill(255);
  else if (h == -2) fill(0);
  else fill(h, 255, 255);
  rect(width/2, 0, width/2, height);
  
  println(h);
}

int getHue(int r, int g, int b) {
  double h, s, v;
  double saturationThresh = .3;
  double brightnessThresh = 50;
  int black = -2;
  int white = -1;
  double      min, max, delta;

  min = r < g ? r : g;
  min = min  < b ? min  : b;
  max = r > g ? r : g;
  max = max  > b ? max  : b;

  // brightness is the value of the brightest pixel
  v = max;                                   
  delta = max - min;
  if (delta < 0.00001)
  {
    // No saturation (no diff between color levels)
    // totally white
    // hue is undefined, maybe nan?
    s = 0;
    h = 0; 

    if (v > brightnessThresh) return white; // no saturation and some brightness- white
    return black;    // no saturation and no brightness- black
  }
  if ( max > 0.0 ) { 
    // NOTE: if Max is == 0, this divide would cause a crash
    // If the brightness is above 0, then saturation is the 
    // difference between min and max pixel colors divided by max
    s = (delta / max);
  } else {
    // if max is 0, then r = g = b = 0              
    // s = 0, h is undefined
    // no color, so returning black
    s = 0.0;
    h = 0.0; // or NAN
    return black;
  }
  if ( r >= max ) {                   // > is bogus, just keeps compilor happy
    h = ( g - b ) / delta;            // between yellow & magenta
  } else {
    if (g >= max ) h = 2.0 + (b - r ) / delta;  // between cyan & yellow
    else h = 4.0 + ( r - g ) / delta;  // between magenta & cyan
  }

  h *= 60.0;                              // degrees

  if (h < 0.0 ) h += 360.0;
  if (v < brightnessThresh) return black;      // no saturation and dark = gray / off
  else if (s < saturationThresh) return white; // little saturation but bright enough to call it white?
  Double d = h/360.0 * 255;
  return d.intValue();                        // otherwise, just return the hue
}