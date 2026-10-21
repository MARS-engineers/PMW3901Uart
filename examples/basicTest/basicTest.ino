
#include <PMW3901Uart.h>

#define SENSOR_RX_PIN 39
PMW3901Uart flow(SENSOR_RX_PIN);

void setup() {
  Serial.begin(115200);
  delay(3000);
  Serial.println(F("MARS-Engineers optical flow test " __FILE__ " from " __DATE__ "\r\n"));

  flow.begin();
}
void loop() {
  if (flow.update()) {
    int16_t x = flow.getX();
    int16_t y = flow.getY();
    if (!(x == 0 && y == 0)) {
      String m = "X:" + (String)x + ",\tY:" + (String)y + ",\tQ:" + (String)flow.getSurfaceQuality() + ",\tFPS:" + (String)flow.getFps();
      Serial.println(m);
    }
  }
}
