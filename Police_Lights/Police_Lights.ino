#include <Adafruit_NeoPixel.h>
const int pin = 1, PX = 2, numLEDs = 18, half = (numLEDs/2);
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
  //PXon = pulseIn(PX, HIGH); //read PWM signal from the
  if(PXon > OnValue){
  }
  else{

  }


}


void LightsOn(){
  for(int i = 0; i < 5; i++){
    for(int i = 0; i <= half; i++){
      strip.setPixelColor(i, strip.Color(255,0,0));
      strip.setPixelColor((i + half), strip.Color(0,0,255));
    }
    strip.show();
    delay(50);
    for(int i = 0; i <= half; i++){
      strip.setPixelColor(i, strip.Color(0,0,255));
      strip.setPixelColor((i + half), strip.Color(255,0,0));
    }
    strip.show();
    delay(50);
  }
}

