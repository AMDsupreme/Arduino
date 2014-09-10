#include <Adafruit_NeoPixel.h>
const int pin = 1;

//18 LEDs
Adafruit_NeoPixel strip = Adafruit_NeoPixel(18, PIN, NEO_GRB + NEO_KHZ800);


void setup(){
  strip.begin()
  strip.show()
}
