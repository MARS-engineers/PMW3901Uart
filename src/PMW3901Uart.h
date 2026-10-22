#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <cstdint>

#define SENSOR_BAUD 19200
#define PACKET_SIZE 9
const uint8_t HEADER = 0xFE;
const uint8_t FOOTER = 0xBB;

class PMW3901Uart {
public:
  ~PMW3901Uart();
  PMW3901Uart(pin_size_t rxPin);
  void begin();
  bool update();
  void reset();
  void resetPosition();
  void calculateAbsolutePosition(int16_t &x, int16_t &y);
  int16_t getDx() const { return _dx; }
  int16_t getDy() const { return _dy; }
  uint8_t getFps() const { return _fps; }
  uint8_t getSurfaceQuality() const { return _surfaceQuality; }
private:
  SoftwareSerial OFSerial;
  bool decodePacket();
  int16_t _dx = 0;                   // X movement
  int16_t _dy = 0;                   // Y movement
  uint8_t _surfaceQuality = 0;      // Surface quality indicator
  uint8_t _fps = 0;                 // Frames per second
  unsigned long lastUpdateTime = 0; // Last update time for FPS calculation
  uint8_t packet[PACKET_SIZE];
  uint8_t updateIndex = 0; // Index for packet assembly
};
