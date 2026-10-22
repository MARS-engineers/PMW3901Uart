
#include <PMW3901Uart.h>

#define SENSOR_RX_PIN 39
PMW3901Uart flow(SENSOR_RX_PIN);

void setup() {
  Serial.begin(115200);
  delay(3000);
  Serial.println(F("PMW3901 uart optical flow test " __FILE__ " from " __DATE__ "\r\n"));

  flow.begin();
}
void loop() {
  if (flow.update()) {
    int16_t dx = flow.getDx();
    int16_t dy = flow.getDy();
    int16_t absX, absY;
    flow.calculateAbsolutePosition(absX, absY);

    if (!(dx == 0 && dy == 0)) {
      String m = "dX:" + (String)dx + ",\tdY:" + (String)dy + ",\tQ:" + (String)flow.getSurfaceQuality() + ",\tFPS:" + (String)flow.getFps();
      Serial.println(m);
    }
    String m = "X:" + (String)absX + ",\tY:" + (String)absY + ",\tQ:" + (String)flow.getSurfaceQuality() + ",\tFPS:" + (String)flow.getFps();
    Serial.println(m);
  }
}
