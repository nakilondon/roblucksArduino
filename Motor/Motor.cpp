//
// Created by james on 17/02/19.
//

#include "Motor.h"
#include "../Message.h"
#include "SerialIO/SerialIO.h"

void Motor::begin(short pin, bool sendToMotor) {
    _pin = pin;
    _sendToMotor = sendToMotor;
    _motorControl.attach(_pin);
    _Arm();
}

bool Motor::processRequest()
{
    MotorCmd motorCmd = static_cast<MotorCmd>(_serialIO.read_i8());
    uint8_t speed = 0;

    String msgToPI = "In Motor, cmd: ";
    msgToPI += String(motorCmd);

    if (motorCmd == FORWARD || motorCmd == REVERSE) {
        speed = static_cast<uint8_t>(_serialIO.read_i8());
        msgToPI += " speed: ";
        msgToPI += String(speed);
    }
    _serialIO.outputTrace(msgToPI);

    switch (motorCmd){
        case FORWARD:{
            _serialIO.outputTrace("Forward requested");

            if (_lastMotorCmd == REVERSE){
                stop();
            }

            _Speed(static_cast<int>(map(speed, 0, 100, FORWARD_MIN, FORWARD_MAX)));
            break;
        }
        case REVERSE:{
            _serialIO.outputTrace("Reverse requested");

            if (_lastMotorCmd == FORWARD){
                stop();
            }

            _Speed(static_cast<int>(map(speed, 0, 100, REVERSE_MIN, REVERSE_MAX)));
            break;

        }
        case STOP:{
            _serialIO.outputTrace("Stop requested");
            stop();
            break;
        }
        case ARM:{
            _serialIO.outputTrace("Arm requested");
            _Arm();
            break;
        }
        default:{
            _serialIO.outputTrace("Unkown motor request");
            break;
        }
    }

    _lastMotorCmd = motorCmd;
    return true;
}

void Motor::_Speed(short requestedSpeed) {
    _serialIO.outputTrace("Requested speed: " + String(requestedSpeed));

    if (requestedSpeed > FORWARD_MAX || requestedSpeed < REVERSE_MAX){
        _serialIO.outputTrace("Invalid speed");
        return;
    }

    if (_sendToMotor) {
        _serialIO.outputTrace("Sending to ESC");
        _motorControl.writeMicroseconds(requestedSpeed);
    }
}


void Motor::stop() {
    _serialIO.outputTrace("Stopping");
    _Speed(THROTTLE_BAKE);
    delay(100);
}

void Motor::_Arm() {
    _motorControl.detach();
    delay(2000);
    _motorControl.attach(_pin);
    _Speed(THROTTLE_NETURAL);
    _serialIO.outputTrace("Arming........");   // just some display message
    delay(2000);
    _serialIO.outputTrace("Arming........After delay");
    _Speed(THROTTLE_NETURAL);
}
