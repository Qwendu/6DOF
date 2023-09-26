#include <TCA9548.h>

#include <HID-Project.h>
#include <HID-Settings.h>

#include <VL6180X.h>
#include <Wire.h>

TCA9548 mp(0x77);

struct LinearSensor
{
  VL6180X tof;
  int channel;
  int16_t last;
};

void init(LinearSensor *sensor, int channel)
{
  mp.selectChannel(channel);
  sensor->tof.init();
  sensor->tof.configureDefault();
  sensor->tof.setTimeout(20);
  //sensor->tof.startRangeContinuous(10);
  sensor->channel = channel;
}

int8_t read8(LinearSensor *sensor)
{
  mp.selectChannel(sensor->channel);
  int value = sensor->tof.readRangeSingle();
  if(sensor->tof.timeoutOccurred()) return sensor->last;
  if(value < -128) value = -128;
  if(value > 127)  value = 127;
  sensor->last = value;
  return sensor->last;
}

int16_t read16(LinearSensor *sensor)
{
  mp.selectChannel(sensor->channel);
  int value = sensor->tof.readRangeSingle();
  if(sensor->tof.timeoutOccurred()) return sensor->last;
  if(value < -32768 ) value = -32768;
  if(value > 32767)  value = 32767;
  sensor->last = value;
  return sensor->last;
}

LinearSensor x_sensor;
LinearSensor y_sensor;
LinearSensor z_sensor;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  init(&x_sensor, 1);
  init(&y_sensor, 6);
}

void loop() {
 int x_value = read16(&x_sensor);
 int y_value = read16(&y_sensor);
 Serial.print("x:");
 Serial.print(x_value);
 Serial.print("\ty:");
 Serial.print(y_value);
 Serial.println();
 delay(1);
}


/*
 *  int16_t x = 0x7000;
  int16_t y = 0x8FFF;
  int8_t z = 12;
  int16_t rx = 0;
  int16_t ry = 0;
  int8_t rz = -3;

  Gamepad.xAxis(x);
  Gamepad.yAxis(y);
  Gamepad.zAxis(z);
  Gamepad.rxAxis(rx);
  Gamepad.ryAxis(ry);
  Gamepad.rzAxis(rz);
  delay(300);
  Gamepad.write();
 */
