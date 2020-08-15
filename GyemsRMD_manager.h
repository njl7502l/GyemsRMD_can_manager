#ifndef GyemsRMD_manager_h
#define GyemsRMD_manager_h

#include <Arduino.h>
#include <FlexCAN_T4_manager.h>

class GyemsRMD_manager {
private:
  const uint8_t CONTROL_COMMAND[24] = {
      0,    0x30, 0x31, 0x32, 0x33, 0x34, 0x90, 0x91, 0x19, 0x92, 0x94, 0x9A,
      0x9B, 0x9C, 0x9D, 0x80, 0x81, 0x88, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6};
  
  union i32toC {
    int32_t i;
    uint8_t c[4];
  };
  union ui16toC {
    uint16_t i;
    uint8_t c[2];
  };

  i32toC rawAccel;       // unit: 1dps/s
  i32toC rawTargetAccel; // unit: 1dps/s

  class values {
  public:
    uint8_t anglePidKp, anglePidKi;
    uint8_t speedPidKp, speedPidKi;
    uint8_t iqPidKp, iqPidKi;

    int32_t accel;
    int32_t targetAccel;
  };

  int motorId = 0;

public:
  void setId(int Id);
  void read(FlexCAN_T4_manager *canmanager);

  values gotData;
};

#endif
