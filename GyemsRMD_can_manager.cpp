#include <GyemsRMD_can_manager.h>

void GyemsRMD_can_manager::setId(int Id) { motorId = 0x140 + Id; }

void GyemsRMD_can_manager::read(FlexCAN_T4_manager *canmanager) {
  uint8_t data[8] = {};
  canmanager->getBus3(motorId, data);
  canEncode(data);
}
