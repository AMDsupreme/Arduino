#include <Adafruit_NeoPixel.h>
#include <NewPing.h>

//Settings
int mode = 0;
int ledCount = 30;
int ledHalf = ledCount/2;
int distSetting = 12; //default setting for the golden distance
int distSettingPin = A0;
int ledPin = 12;
int tPin = 4, ePin = 5;
int distSettingAnalogValue = 0;
//delete these variables
int checktimes = 0;

NewPing sonar(tPin, ePin, 305); // 306 = approx. 10 feet. For timeout reasons.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(ledCount, ledPin, NEO_GRB + NEO_KHZ800);

uint32_t red = strip.Color(255,0,0);
uint32_t green = strip.Color(0,255,0);
uint32_t yellow = strip.Color(255,255,0);

void setup(){
  Serial.begin(9600);
  
  pinMode(ledPin, OUTPUT);
  strip.begin();
  strip.setBrightness(20);
  strip.show();
  setDistanceSetting(analogRead(distSettingPin));
}

void loop(){
  checkSettings();

}

void checkSettings(){
  int analogValue1 = analogRead(distSettingPin);
  int potCheck = (analogValue1/1024.0) * 48;
  if(potCheck <= 3){ //check to see if the distance is less than 3, and if it is, change it to 3
    potCheck = 3;
  }

  if(abs(analogValue1-distSettingAnalogValue) >= 10){
    Serial.println(abs(analogValue1-distSettingAnalogValue));
    //Serial.print("checkSetting\t");
    //Serial.println(checktimes);   
    checktimes++;// remember to delete this line
    setDistanceSetting(analogValue1);

  }
}

void setDistanceSetting(int analogv){

  distSettingAnalogValue = analogv;
  //Serial.print(analogValue);
  //Serial.print("\t");
  int distCheck = (analogv/1024.0) * 48; //48 inches or 4 ft max distance (any further would be a small window)
  if(distCheck <= 3){ //check to see if the distance is less than 3, and if it is, change it to 3
    distSetting = 3;
  }
  else{
    distSetting = distCheck;
  }
  //Serial.println(distSetting);
  displayDistanceSetting();
}

void displayDistanceSetting(){
  //int reading = sonar.convert_in(sonar.ping_median(3));
  int reading = 21;
  uint32_t setDistColor = yellow;
  int distSet = 22;
  if(reading == distSetting){
    setDistColor = green;
    Serial.print("True\t");
   Serial.print(distSet);
   Serial.print("\t");
   Serial.println(reading);
  }

  if(reading > ledCount){
    int leftover = distSetting - ledCount;
    for(int i = 0; i < ledCount; i++){
      strip.setPixelColor(i, setDistColor);
      strip.show();
      delay(100);
    }
    for(int i = ledCount; i < leftover; i++){
      strip.setPixelColor(i, setDistColor);
      strip.show();
      delay(100);
    }
  }
    else{
      for(int i = 0; i < distSetting; i++){
        strip.setPixelColor(i, setDistColor);
        strip.show();
        delay(3);
        }
      for(int i = distSetting; i < ledCount; i++){
        strip.setPixelColor(i, 0);
        strip.show();
        delay(2);    
    }
  }
}




//Added Capacitor to help analogRead() noise
//made the setting update check analog based not distance based
//fixed LEDs
//git
//git1


