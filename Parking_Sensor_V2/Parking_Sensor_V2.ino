#include <Adafruit_NeoPixel.h>
#include <NewPing.h>

//Settings
int mode = 0;
int ledCount = 30;
int ledHalf = ledCount/2;
int distSetting = 12; //default setting for the golden distance
int distSettingPin = A0;
int ledPin = 3;
int tPin = 4, ePin = 5;

NewPing sonar(tPin, ePin, 305); // 306 = approx. 10 feet. For timeout reasons.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(ledCount, ledPin, NEO_GRB + NEO_KHZ800);

uint32_t red = strip.Color(255,0,0);
uint32_t green = strip.Color(0,255,0);
uint32_t yellow = strip.Color(255,255,0);

void setup(){
  Serial.begin(9600);
  setDistanceSetting();

}

void loop(){
  checkSettings();

}

void checkSettings(){
  int analogValue = analogRead(distSettingPin);
  int potCheck = (analogValue/1024.0) * 48;
  
  if(abs(potCheck-distSetting) >= 1){
    setDistanceSetting();
  }
}

void setDistanceSetting(){
  int analogValue = analogRead(distSettingPin);
  int distCheck = (analogValue/1024.0) * 48; //48 inches or 4 ft max distance (any further would be a small window)
  if(distCheck <= 3){ //check to see if the distance is less than 3, and if it is, change it to 3
    distSetting = 3;
  }
  else{
    distSetting = distCheck;
  }
  Serial.println(distSetting);
  displayDistanceSetting();
}

void displayDistanceSetting(){
  int reading = sonar.convert_in(sonar.ping_median(3));
  uint32_t setDistColor = yellow;

  if(reading = distSetting){
    setDistColor = green; 
  }

  if(reading > ledCount){
    int leftover = distSetting - ledCount;
    for(int i = 0; i < ledCount; i++){
      strip.setPixelColor(i, setDistColor);
      strip.show();
      delay(1);
    }
    for(int i = ledCount; i < leftover; i++){
      strip.setPixelColor(i, setDistColor);
      strip.show();
      delay(1);
    }
  }
    else{
      for(int i = 0; i < ledCount; i++){
        strip.setPixelColor(i, setDistColor);
        strip.show();
        delay(1);
      }    
    }
  }

