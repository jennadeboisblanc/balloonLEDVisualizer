// Luna Fete 2017 XBee Receiver Code for Big Balloons
// Adapted from Michalis Vasilakis // Date:2/3/2016 // Info: www.ardumotive.com // Licence: CC BY-NC-SA
// and Adafruit Neopixel Library

#define BALLOON_NUM 0

#define DEBUG false

// NEOPIXELS
#include <Adafruit_NeoPixel.h>
#define PIN 8
#define NUM_PIXELS 10
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

// XBEE CONSTANTS
bool started = false;   // True: Message is started
bool ended   = false;    // True: Message is finished
char incomingByte ;     // Variable to store the incoming byte
char msg[30];           // Incoming message with RGB values for each balloon
int index;             // Index of array

////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600); //Baud rate must be the same as is on xBee module
  strip.begin();
  strip.show();
}

void loop() {
  getMessage();
  setNeopixels();
  strip.show();
}

////////////////////////////////////////////////////////////////
void setNeopixels() {
  int r = msg[BALLOON_NUM * 3];
  int g = msg[BALLOON_NUM * 3 + 1];
  int b = msg[BALLOON_NUM * 3 + 2];
  for (int i = 0; i < NUM_PIXELS; i++) {
    strip.setPixelColor(i, strip.Color(r, g, b));
  }
}

void getMessage() {
  while (Serial.available() > 0) {  //Read the incoming byte
    incomingByte = Serial.read();
    // check for first byte
    if (DEBUG) {
      Serial.print(index);
      Serial.print(" ");
      int b = incomingByte & 0xFF;
      Serial.println(b);
    }
    if (!started) {
      if (incomingByte == 47) {
        index = 0;
        started = true;
      }
    }
    else {
      // read the byte
      if (index < 30) {
        msg[index] = incomingByte; // Add byte to array
        index++;
      }
      // we're done
      else {
        index = 0;
        msg[index] = 0;
        started = false;
        break; // Done reading - exit from while loop!
      }
    }
  }
}


