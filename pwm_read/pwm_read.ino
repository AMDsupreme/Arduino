const int px = 4;
int value;

void setup(){
  pinMode(px, INPUT);
  Serial.begin(57600);
}

void loop(){
 value = pulseIn(px, HIGH);
 Serial.print(value);
 Serial.println("ms");
}
