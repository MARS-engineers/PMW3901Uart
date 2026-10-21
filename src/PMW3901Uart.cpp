#include "PMW3901Uart.h"

PMW3901Uart::PMW3901Uart(pin_size_t rxPin) : OFSerial(rxPin, -1) {}

void PMW3901Uart::begin() {
  // Initialize UART communication here
  OFSerial.begin(SENSOR_BAUD); // RX pin, no TX pin
  lastUpdateTime = millis();
  _fps = 0;
}

bool PMW3901Uart::decodePacket() {
  // Validate packet structure
  if (packet[0] != HEADER || packet[1] != 0x04 || packet[8] != FOOTER) {
    return false;
  }

  // Checksum: sum of motion bytes, modulo 256.
  uint8_t checksum = packet[2] + packet[3] + packet[4] + packet[5];
  if (checksum != packet[6]) {
    return false;
  }

  // Combine high and low bytes
  _x = (int16_t)((packet[2] << 8) | packet[3]);
  _y = (int16_t)((packet[4] << 8) | packet[5]);
  _surfaceQuality = packet[7];

  _fps = 1000 / (millis() - lastUpdateTime);
  lastUpdateTime = millis();

  return true;
}

bool PMW3901Uart::update() {
  while (OFSerial.available()) {
    uint8_t b = OFSerial.read();
    // Wait for packet header
    if (updateIndex == 0) {
      if (b != HEADER)
        continue;

      packet[updateIndex++] = b;

      continue;
    }

    packet[updateIndex++] = b;

    if (updateIndex == PACKET_SIZE) {

      updateIndex = 0;
      return decodePacket();
    }
  }
  return false;
}
