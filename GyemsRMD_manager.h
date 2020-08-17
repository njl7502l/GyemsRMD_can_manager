#ifndef GyemsRMD_manager_h
#define GyemsRMD_manager_h

#include <Arduino.h>
#include <FlexCAN_T4_manager.h>
#include <MyMath.h>

class GyemsRMD_manager {
private:
  MyMath myMath;
  const uint8_t CONTROL_COMMAND[24] = {
      0,    0x30, 0x31, 0x32, 0x33, 0x34, 0x90, 0x91, 0x19, 0x92, 0x94, 0x9A,
      0x9B, 0x9C, 0x9D, 0x80, 0x81, 0x88, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6};

  class RawData {
  public:
    int write(uint8_t data[8]);

    struct {
      struct {
        uint8_t kp, ki;
      } position, speed, torque;
    } pid;
    struct {
      uint8_t current[4], target[4];
    } accel;
    struct {
      uint8_t current[2], original[2], offset[2];
    } encoder;
    struct {
      uint8_t multiTurn[8];
      uint8_t singleTurn[2];
    } angle;
    struct {
      uint8_t temperature;
      uint8_t voltage[2];
      uint8_t errorState;
    } information;
    struct {
      uint8_t iq[2];
    } current;
    struct {
      uint8_t current[2];
    } speed;

  } rawData;

  struct Values {
    struct { // 0-255 uint value
      uint8_t angleKp, angleKi;
      uint8_t speedKp, speedKi;
      uint8_t iqKp, iqKi;
    } pid;

    struct { // unit 1[dps/s]
      int32_t current;
      int32_t target;
    } accel;

    struct {
      int16_t rawIq; // -2048~2048 map -33~33[A]
      double iq;     // -33~33[A]
      int16_t rawIa; // -2048~2048 map -33~33[A]
      double ia;     // -33~33[A]
      int16_t rawIb; // -2048~2048 map -33~33[A]
      double ib;     // -33~33[A]
      int16_t rawIc; // -2048~2048 map -33~33[A]
      double ic;     // -33~33[A]
    } torque;

    struct {
      int16_t current;
    } speed;

    struct { // 14bit encoder value range 0-0x3FFF
      uint16_t current;
      uint16_t original;
      uint16_t offset;
    } encoder;

    struct {
      int64_t rawMultiTurn; // unit 0.01[deg/LSB]
      double multiTurn;     // unit [deg]

      uint16_t rawSingleTurn; // unit 0.01[deg/LSB]
      double singleTurn;      // unit [deg] (unsigned)
    } angle;

    struct {
      int8_t temperature;  // unit 1[c'/LSB]
      uint16_t rawVoltage; // unit 0.1[v/LSB]
      double voltage;
      struct {
        uint8_t rawState;
        bool lowVoltageProtection;
        bool overTemperatureProtection;
      } error;
    } information;
  };

  int motorId = 0;

public:
  void setId(int Id);
  void read(FlexCAN_T4_manager *canmanager);

  Values gotData;
};

#endif
