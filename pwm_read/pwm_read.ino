const int px = 4;
double value;

void setup(){
  pinMode(px, OUTPUT);
  Serial.begin(57600);
}

void loop(){
 //value = pulseIn(px, HIGH);
 Serial.print(value);
 Serial.println("ms");
 for(int i = 0; i<256; i++){
   digitalWrite(px, i);
   delay(25);
 }
}
