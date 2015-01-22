

/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Encoder.h>

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(2, 3);
//   avoid using pins with LEDs attached

void setup() {
  Serial.begin(115200);
  Serial.println("Basic Encoder Test:");
}

long oldPosition  = -999;
long pTime = 0;
float cpr = 1120.00;

void loop() {
  long dt;
  long newPosition = myEnc.read();
  long nTime = millis();
  if (newPosition != oldPosition) {
    dt = nTime - pTime;
    pTime = millis();
    float dr = 1.0/dt;
    float rpm = dr * 1000000.0;
    oldPosition = newPosition;
    Serial.print(newPosition);
    Serial.print("\t");
    Serial.print(rpm);
    Serial.print("\t");
    Serial.print(millis());
    Serial.print("\t");
    Serial.println(dt);
  }
}
