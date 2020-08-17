#include <GyemsRMD_manager.h>

void GyemsRMD_manager::setId(int Id) { motorId = 0x140 + Id; }

void GyemsRMD_manager::read(FlexCAN_T4_manager *canmanager) {
  uint8_t data[8] = {};
  canmanager->getBus3(motorId, data);
  switch (data[0]) {
  case 0x30:
  case 0x31:
  case 0x32:
    rawData.pid.position.kp = data[2];
    rawData.pid.position.ki = data[3];
    rawData.pid.speed.kp = data[4];
    rawData.pid.speed.ki = data[5];
    rawData.pid.torque.kp = data[6];
    rawData.pid.torque.ki = data[7];
    break;
  case 0x33:
    rawData.accel.current[0] = data[4];
    rawData.accel.current[1] = data[5];
    rawData.accel.current[2] = data[6];
    rawData.accel.current[3] = data[7];
    break;
  case 0x34:
    rawData.accel.target[0] = data[4];
    rawData.accel.target[1] = data[5];
    rawData.accel.target[2] = data[6];
    rawData.accel.target[3] = data[7];
    break;
  case 0x90:
    rawData.encoder.current[0] = data[2];
    rawData.encoder.current[1] = data[3];
    rawData.encoder.original[0] = data[4];
    rawData.encoder.original[1] = data[5];
    rawData.encoder.offset[0] = data[6];
    rawData.encoder.offset[1] = data[7];
    break;
  case 0x91:
  case 0x19:
    rawData.encoder.offset[0] = data[6];
    rawData.encoder.offset[1] = data[7];
    break;
  case 0x92:
    rawData.angle.multiTurn[0] = data[1];
    rawData.angle.multiTurn[1] = data[2];
    rawData.angle.multiTurn[2] = data[3];
    rawData.angle.multiTurn[3] = data[4];
    rawData.angle.multiTurn[4] = data[5];
    rawData.angle.multiTurn[5] = data[6];
    rawData.angle.multiTurn[6] = data[7];
    rawData.angle.multiTurn[7] = 0;
    break;
  case 0x94:
    rawData.angle.singleTurn[0] = data[6];
    rawData.angle.singleTurn[1] = data[7];
    break;
  case 0x9A:
    rawData.information.temperature = data[1];
    rawData.information.voltage[0] = data[3];
    rawData.information.voltage[1] = data[4];
    rawData.information.errorState = data[7];
    break;
  case 0x9C:
    rawData.information.temperature = data[1];
    rawData.current.iq[0] = data[2];
    rawData.current.iq[1] = data[3];
    rawData.speed.current[0] = data[4];
    rawData.speed.current[1] = data[5];
    rawData.encoder.current[0] = data[6];
    rawData.encoder.current[1] = data[7];
    break;
  case 0x9D:

    break;
  default:
    break;
  }
}
