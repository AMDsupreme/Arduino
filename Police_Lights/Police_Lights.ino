#include <Adafruit_NeoPixel.h>
const int pin = 3, PX = 4, numLEDs = 20, half = (int)(numLEDs/2);
int PXon;
int OnValue = 0; //This is the variable to change for the PWM on/off trigger
//18 LEDs
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLEDs, pin, NEO_GRB + NEO_KHZ800);


void setup(){
  strip.begin();
  strip.show();
  pinMode(pin, OUTPUT); //Output to NeoPixel
  pinMode(PX, INPUT); //RC input from the Pixhawk
  Serial.begin(9600);

}

void loop(){
  PXon = pulseIn(PX, HIGH, 2000); //read PWM signal from the
  if(PXon > 1300){
    LightsOn();
  }
  else{
    LightsOff();
  }


}


void LightsOn(){
  //red lights
  for(int i = 0; i < 4; i++){
    for(int i = 0; i <= half; i++){
      strip.setPixelColor(i, strip.Color(255,0,0));
      strip.setPixelColor((i + half), strip.Color(0,0,0));
    }
    strip.show();
    delay(50);
    for(int i = 0; i <= half; i++){
      strip.setPixelColor(i, strip.Color(0,0,0));
      strip.setPixelColor((i + half), strip.Color(0,0,0));
    }
    strip.show();
    delay(50);
  }
  for(int i = 0; i <= half; i++){
    strip.setPixelColor(i, strip.Color(255,0,0));
    strip.setPixelColor((i + half), strip.Color(0,0,0));
  }
  strip.show();
  delay(75);
  
  //blue lights
  for(int i = 0; i < 4; i++){
    for(int i = 0; i <= half; i++){
      strip.setPixelColor(i, strip.Color(0,0,0));
      strip.setPixelColor((i + half), strip.Color(0,0,255));
    }
    strip.show();
    delay(50);
    for(int i = 0; i <= half; i++){
      strip.setPixelColor(i, strip.Color(0,0,0));
      strip.setPixelColor((i + half), strip.Color(0,0,0));
    }
    strip.show();
    delay(50);
  }
  for(int i = 0; i <= half; i++){
    strip.setPixelColor(i, strip.Color(0,0,0));
    strip.setPixelColor((i + half), strip.Color(0,0,255));
  }
  strip.show();
  delay(75);

}

void LightsOff(){
  for(int i = 0; i < numLEDs; i++){
    strip.setPixelColor(i, strip.Color(0,0,0));
  }
  strip.show();
}




