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
    datas.pid.position.kp = data[2];
    datas.pid.position.ki = data[3];
    datas.pid.speed.kp = data[4];
    datas.pid.speed.ki = data[5];
    datas.pid.torque.kp = data[6];
    datas.pid.torque.ki = data[7];
    break;
  case 0x33:
    datas.accel.current[0] = data[4];
    datas.accel.current[1] = data[5];
    datas.accel.current[2] = data[6];
    datas.accel.current[3] = data[7];
    break;
  case 0x34:
    datas.accel.target[0] = data[4];
    datas.accel.target[1] = data[5];
    datas.accel.target[2] = data[6];
    datas.accel.target[3] = data[7];
    break;
  case 0x90:
    datas.encoder.current[0] = data[2];
    datas.encoder.current[1] = data[3];
    datas.encoder.original[0] = data[4];
    datas.encoder.original[1] = data[5];
    datas.encoder.offset[0] = data[6];
    datas.encoder.offset[1] = data[7];
    break;
  case 0x91:
  case 0x19:
    datas.encoder.offset[0] = data[6];
    datas.encoder.offset[1] = data[7];
    break;
  case 0x92:
    datas.angle.multiTurn[0] = data[1];
    datas.angle.multiTurn[1] = data[2];
    datas.angle.multiTurn[2] = data[3];
    datas.angle.multiTurn[3] = data[4];
    datas.angle.multiTurn[4] = data[5];
    datas.angle.multiTurn[5] = data[6];
    datas.angle.multiTurn[6] = data[7];
    datas.angle.multiTurn[7] = 0;
    break;
  case 0x94:
    datas.angle.singleTurn[0] = data[6];
    datas.angle.singleTurn[1] = data[7];
    break;
  case 0x9A:
    datas.information.temperature = data[1];
    datas.information.voltage[0] = data[3];
    datas.information.voltage[1] = data[4];
    datas.information.errorState = data[7];
    break;
  case 0x9C:
    datas.information.temperature = data[1];
    datas.current.iq[0] = data[2];
    datas.current.iq[1] = data[3];
    datas.speed.current[0] = data[4];
    datas.speed.current[1] = data[5];
    datas.encoder.current[0] = data[6];
    datas.encoder.current[1] = data[7];
    break;
  case 0x9D:

    break;
  default:
    break;
  }
}