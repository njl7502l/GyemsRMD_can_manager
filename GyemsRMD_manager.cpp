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
    myMath.i32c.write(data[4], data[5], data[6], data[7]);
    gotData.accel.current = myMath.i32c.read();
    break;
  case 0x34:
    myMath.i32c.write(data[4], data[5], data[6], data[7]);
    gotData.accel.target = myMath.i32c.read();
    break;
  case 0x90:
    myMath.ui16c.write(data[2], data[3]);
    gotData.encoder.current = myMath.ui16c.read();
    myMath.ui16c.write(data[4], data[5]);
    gotData.encoder.original = myMath.ui16c.read();
    myMath.ui16c.write(data[6], data[7]);
    gotData.encoder.offset = myMath.ui16c.read();
    break;
  case 0x91:
  case 0x19:
    myMath.ui16c.write(data[6], data[7]);
    gotData.encoder.offset = myMath.ui16c.read();
    break;
  case 0x92:
    myMath.i64c.write(data[1], data[2], data[3], data[4], data[5], data[6],
                      data[7], 0);
    gotData.angle.rawMultiTurn = myMath.i64c.read();
    gotData.angle.multiTurn = (0.01 * gotData.angle.rawMultiTurn);
    break;
  case 0x94:
    myMath.ui16c.write(data[6], data[7]);
    gotData.angle.rawSingleTurn = myMath.ui16c.read();
    gotData.angle.singleTurn = (0.01 * gotData.angle.rawSingleTurn);
    break;
  case 0x9A:
    gotData.information.temperature = data[1];
    myMath.ui16c.write(data[3], data[4]);
    gotData.information.rawVoltage = myMath.ui16c.read();
    gotData.information.voltage = (0.1 * gotData.information.rawVoltage);
    gotData.information.error.rawState = data[7];
    gotData.information.error.lowVoltageProtection =
        bitRead(gotData.information.error.rawState, 0);
    gotData.information.error.overTemperatureProtection =
        bitRead(gotData.information.error.rawState, 3);
    break;
  case 0x9C:
    gotData.information.temperature = data[1];
    myMath.i16c.write(data[2],data[3]);
    gotData.torque.rawIq = myMath.i16c.read();
    gotData.torque.iq = myMath.map(gotData.torque.rawIq,-2048,2048,-330e-1,330e-1);
    myMath.i16c.write(data[4],data[5]);
    gotData.speed.current = myMath.i16c.read();
    myMath.ui16c.write(data[6],data[7]);
    gotData.encoder.current = myMath.ui16c.read();
    break;
  case 0x9D:

    break;
  default:
    break;
  }
}
