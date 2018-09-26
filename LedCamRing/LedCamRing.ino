// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            7

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      12

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 100;

int r[NUMPIXELS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int g[NUMPIXELS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void setup() {

  Serial.begin(9600);

  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  //initialise array
  for (int p = 0; p < NUMPIXELS; p++) {
    r[p] = 0;
  }

  pixels.begin(); // This initializes the NeoPixel library.
}

unsigned long t = millis();
int i = 0;

void loop() {

  if (t + delayval < millis() ) {
    t = millis();
    r[i] = 255;
    i++;
    if (i > NUMPIXELS) i = 0;
  }

  for (int p = 0; p < NUMPIXELS; p++) {
    //         r[p] = int(r[p] / 1.1);
    if(r[p]>0) r[p] = int(r[p]*0.9);
    g[p] = int(r[p]/1.55);
    pixels.setPixelColor(p, pixels.Color(r[p], g[p], 0));
  }
  Serial.println(i);
  Serial.println(r[i]);
  Serial.println(g[i]);
  Serial.println();

  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(10);
}
