//
// Created by james on 17/02/19.
//
#include <Arduino.h>
#include <Servo.h>
#include "../SerialIO/SerialIO.h"

#ifndef ARDBIN_MOTOR_H
#define ARDBIN_MOTOR_H

#define FORWARD_MAX         1680
#define FORWARD_MIN         1550
#define REVERSE_MAX         1320
#define REVERSE_MIN         1425
#define THROTTLE_BAKE       1500
#define THROTTLE_NETURAL    1500


class Motor
{
private:
    Servo _motorControl;
    bool _sendToMotor;
    short _pin;
    MotorCmd _lastMotorCmd;
    SerialIO _serialIO;

    void _Arm();
    void _Speed(short requestedSpeed);

public:
    void begin(short pin, SerialIO *serialIO, bool sendToMotor = true);
    bool processRequest();
    void stop();
};

#endif //ARDBIN_MOTOR_H
