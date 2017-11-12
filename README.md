# balloonLEDs

**Balloon visualizer** is the Processing sketch for developing light functions.

**Balloon transmitter** is the Arduino sketch for sending color data to balloons. The sketch uses an Xbee to send an array of 30 bytes- the r, g, and b values of all 10 balloons. Constantly sending data (maybe this isn't wise from a power perspective?).

**Balloon receiver** is the Arduino sketch loaded on the Arduino Nanos of each big balloon. This sketch receives the Xbee 30-byte array, picks out which bytes are relevant to the particular balloon, and sets all of the Neopixels to this particular color.
