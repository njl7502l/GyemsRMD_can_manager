#include <GyemsRMD_manager.h>

void GyemsRMD_manager::setId(int Id) { motorId = 0x140 + Id; }

void GyemsRMD_manager::read(FlexCAN_T4_manager *canmanager) {
  uint8_t data[8] = {};
  canmanager->getBus3(motorId, data);
  switch (data[0]) {
  case 0x30:
  case 0x31:
  case 0x32:
    gotData.pid.angleKp = data[2];
    gotData.pid.angleKi = data[3];
    gotData.pid.speedKp = data[4];
    gotData.pid.speedKi = data[5];
    gotData.pid.iqKp = data[6];
    gotData.pid.iqKi = data[7];
    break;
  case 0x33:
    i32tc.i = 0;
    i32tc.c[0] = data[4];
    i32tc.c[1] = data[5];
    i32tc.c[2] = data[6];
    i32tc.c[3] = data[7];
    gotData.accel.current = i32tc.i;
    break;
  case 0x34:
    i32tc.i = 0;
    i32tc.c[0] = data[4];
    i32tc.c[1] = data[5];
    i32tc.c[2] = data[6];
    i32tc.c[3] = data[7];
    gotData.accel.target = i32tc.i;
    break;
  case 0x90:
    ui16tc.i = 0;
    ui16tc.c[0] = data[2];
    ui16tc.c[1] = data[3];
    gotData.encoder.current = ui16tc.i;
    ui16tc.i = 0;
    ui16tc.c[0] = data[4];
    ui16tc.c[1] = data[5];
    gotData.encoder.original = ui16tc.i;
    ui16tc.i = 0;
    ui16tc.c[0] = data[6];
    ui16tc.c[1] = data[7];
    gotData.encoder.offset = ui16tc.i;
    break;
  case 0x91:
  case 0x19:
    ui16tc.i = 0;
    ui16tc.c[0] = data[6];
    ui16tc.c[1] = data[7];
    gotData.encoder.offset = ui16tc.i;
    break;
  case 0x92:
    i64tc.i = 0;
    i64tc.c[0] = data[1];
    i64tc.c[1] = data[2];
    i64tc.c[2] = data[3];
    i64tc.c[3] = data[4];
    i64tc.c[4] = data[5];
    i64tc.c[5] = data[6];
    i64tc.c[6] = data[7];
    gotData.angle.rawMultiTurn = i64tc.i;
    gotData.angle.multiTurn = (0.01 * i64tc.i);
    break;
  case 0x94:
    ui16tc.i = 0;
    ui16tc.c[0] = data[6];
    ui16tc.c[1] = data[7];
    gotData.angle.rawSingleTurn = ui16tc.i;
    gotData.angle.singleTurn = (0.01 * ui16tc.i);
    break;
  case 0x9A:
    gotData.information.temperature = data[1];
    ui16tc.i = 0;
    ui16tc.c[0] = data[3];
    ui16tc.c[1] = data[4];
    gotData.information.rawVoltage = ui16tc.i;
    gotData.information.voltage = (0.1 * ui16tc.i);
    gotData.information.error.rawState = data[7];
    gotData.information.error.lowVoltageProtection = bitRead(data[7],0);
    gotData.information.error.overTemperatureProtection = bitRead(data[7],3);
    break;
  case 0x9C:
    gotData.information.temperature = data[1];

    break;
  default:
    break;
  }
}
