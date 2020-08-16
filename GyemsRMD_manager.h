#ifndef GyemsRMD_manager_h
#define GyemsRMD_manager_h

#include <Arduino.h>
#include <FlexCAN_T4_manager.h>

class GyemsRMD_manager {
private:
  const uint8_t CONTROL_COMMAND[24] = {
      0,    0x30, 0x31, 0x32, 0x33, 0x34, 0x90, 0x91, 0x19, 0x92, 0x94, 0x9A,
      0x9B, 0x9C, 0x9D, 0x80, 0x81, 0x88, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6};
  
  union Int16toChar {
    int16_t i;
    uint8_t c[2];
  } i16tc;
  union Int32toChar {
    int32_t i;
    uint8_t c[4];
  } i32tc;
  union Int64toChar {
    int64_t i;
    uint8_t c[8];
  } i64tc;
  union Uint16toChar {
    uint16_t i;
    uint8_t c[2];
  } ui16tc;

  class Values {
  public:
    class Pid { // 0-255 uint value
    public:
      uint8_t angleKp, angleKi;
      uint8_t speedKp, speedKi;
      uint8_t iqKp, iqKi;
    } pid;

    class Accel { // unit 1[dps/s]
    public:
      int32_t current;
      int32_t target;
    } accel;

    class Encoder { // 14bit encoder value range 0-0x3FFF
    public:
      uint16_t current;
      uint16_t original;
      uint16_t offset;
    } encoder;

    class Angle {
    public:
      int64_t rawMultiTurn; // unit 0.01[deg/LSB]
      double multiTurn;     // unit [deg]

      uint16_t rawSingleTurn; // unit 0.01[deg/LSB]
      double singleTurn;      // unit [deg] (unsigned)
    } angle;

    class Torque{
      int16_t rawIq;
    }torque;

    class Information {
    public:
      int8_t temperature; // unit 1[c'/LSB]
      uint16_t rawVoltage;   // unit 0.1[v/LSB]
      double voltage;
      class Error{
        public:
        uint8_t rawState;
        bool lowVoltageProtection;
        bool overTemperatureProtection;
      }error;
    } information;
  };

  int motorId = 0;

public:
  void setId(int Id);
  void read(FlexCAN_T4_manager *canmanager);

  Values gotData;
};

#endif
