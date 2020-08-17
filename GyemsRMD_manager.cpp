#include <GyemsRMD_manager.h>

void GyemsRMD_manager::setId(int Id) { motorId = 0x140 + Id; }

void GyemsRMD_manager::read(FlexCAN_T4_manager *canmanager) {
  uint8_t data[8] = {};
  canmanager->getBus3(motorId, data);
  rawData.write(data);
}

int GyemsRMD_manager::RawData::write(uint8_t data[8]) {
  switch (data[0]) {
  case 0x30:
  case 0x31:
  case 0x32:
    pid.position.kp = data[2];
    pid.position.ki = data[3];
    pid.speed.kp = data[4];
    pid.speed.ki = data[5];
    pid.torque.kp = data[6];
    pid.torque.ki = data[7];
    break;
  case 0x33:
    accel.current[0] = data[4];
    accel.current[1] = data[5];
    accel.current[2] = data[6];
    accel.current[3] = data[7];
    break;
  case 0x34:
    accel.target[0] = data[4];
    accel.target[1] = data[5];
    accel.target[2] = data[6];
    accel.target[3] = data[7];
    break;
  case 0x90:
    encoder.current[0] = data[2];
    encoder.current[1] = data[3];
    encoder.original[0] = data[4];
    encoder.original[1] = data[5];
    encoder.offset[0] = data[6];
    encoder.offset[1] = data[7];
    break;
  case 0x91:
  case 0x19:
    encoder.offset[0] = data[6];
    encoder.offset[1] = data[7];
    break;
  case 0x92:
    angle.multiTurn[0] = data[1];
    angle.multiTurn[1] = data[2];
    angle.multiTurn[2] = data[3];
    angle.multiTurn[3] = data[4];
    angle.multiTurn[4] = data[5];
    angle.multiTurn[5] = data[6];
    angle.multiTurn[6] = data[7];
    angle.multiTurn[7] = 0;
    break;
  case 0x94:
    angle.singleTurn[0] = data[6];
    angle.singleTurn[1] = data[7];
    break;
  case 0x9A:
    information.temperature = data[1];
    information.voltage[0] = data[3];
    information.voltage[1] = data[4];
    information.errorState = data[7];
    break;
  case 0x9C:
    information.temperature = data[1];
    current.iq[0] = data[2];
    current.iq[1] = data[3];
    speed.current[0] = data[4];
    speed.current[1] = data[5];
    encoder.current[0] = data[6];
    encoder.current[1] = data[7];
    break;
  case 0x9D:

    break;
  default:
    break;
  }
}