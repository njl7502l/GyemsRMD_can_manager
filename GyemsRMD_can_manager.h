#ifndef GyemsRMD_can_manager_h
#define GyemsRMD_can_manager_h

#include <Arduino.h>
#include <FlexCAN_T4_manager.h>
#include <GyemsRMD_base.h>

class GyemsRMD_can_manager : public GyemsRMD_base {
private:
  const uint8_t CONTROL_COMMAND[24] = {
      0,    0x30, 0x31, 0x32, 0x33, 0x34, 0x90, 0x91, 0x19, 0x92, 0x94, 0x9A,
      0x9B, 0x9C, 0x9D, 0x80, 0x81, 0x88, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6};

  int motorId = 0;

public:
  void setId(int Id);
  void read(FlexCAN_T4_manager *canmanager);
};

#endif
