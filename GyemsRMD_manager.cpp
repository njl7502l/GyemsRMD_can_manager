#include <GyemsRMD_manager.h>

void GyemsRMD_manager::setId(int Id) { motorId = 0x140 + Id; }

void GyemsRMD_manager::read(FlexCAN_T4_manager *canmanager) {
  uint8_t data[8] = {};
  canmanager->getBus3(motorId, data);
  switch (data[0]) {
  case 0x30:
  case 0x31:
  case 0x32:
    gotData.anglePidKp = data[2];
    gotData.anglePidKi = data[3];
    gotData.speedPidKp = data[4];
    gotData.speedPidKi = data[5];
    gotData.iqPidKp = data[6];
    gotData.iqPidKi = data[7];
    break;
  case 0x33:
    rawAccel.c[0] = data[4];
    rawAccel.c[1] = data[5];
    rawAccel.c[2] = data[6];
    rawAccel.c[3] = data[7];
    gotData.accel = rawAccel.i;
    break;
  case 0x34:
    rawTargetAccel.c[0] = data[4];
    rawTargetAccel.c[1] = data[5];
    rawTargetAccel.c[2] = data[6];
    rawTargetAccel.c[3] = data[7];
    gotData.targetAccel = rawTargetAccel.i;
    break;
  default:
    break;
  }
}
