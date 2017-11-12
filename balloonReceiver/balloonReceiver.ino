// Luna Fete 2017 XBee Receiver Code for Big Balloons
// Adapted from Michalis Vasilakis // Date:2/3/2016 // Info: www.ardumotive.com // Licence: CC BY-NC-SA
// and Adafruit Neopixel Library

#define BALLOON_NUM 0

// NEOPIXELS
#include <Adafruit_NeoPixel.h>
#define PIN 6
#define NUM_PIXELS 200
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

// XBEE CONSTANTS
bool started = false;   // True: Message is started
bool ended   = false;    // True: Message is finished
char incomingByte ;     // Variable to store the incoming byte
char msg[30];           // Incoming message with RGB values for each balloon
byte index;             // Index of array

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
  int r = msg[BALLOON_NUM*3];
  int g = msg[BALLOON_NUM*3 + 1];
  int b = msg[BALLOON_NUM*3 + 2];
  for (int i = 0; i < NUM_PIXELS; i++) {
    strip.setPixel(i, strip.Color(r, g, b));
  }
}


void getMessage() {
  while (Serial.available() > 0) {  //Read the incoming byte
    incomingByte = Serial.read();
    //Start the message when the '<' symbol is received
    if (incomingByte == '<')
    {
      started = true;
      index = 0;
      msg[index] = '\0'; // Throw away any incomplete packet
    }
    //End the message when the '>' symbol is received
    else if (incomingByte == '>')
    {
      ended = true;
      break; // Done reading - exit from while loop!
    }
    //Read the message!
    else
    {
      if (index < 4) // Make sure there is room
      {
        msg[index] = incomingByte; // Add char to array
        index++;
        msg[index] = '\0'; // Add NULL to end
      }
    }
  }

  if (started && ended)
  {
    int value = atoi(msg);
    analogWrite(ledPin, value);
    //Serial.println(value); //Only for debugging
    index = 0;
    msg[index] = '\0';
    started = false;
    ended = false;
  }
}

