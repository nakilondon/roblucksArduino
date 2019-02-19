//
// Created by james on 18/02/19.
//

#include "RoblucksServo.h"

#include "../Message.h"
#include "../SerialIO/SerialIO.h"

RoblucksServo::RoblucksServo(short pin, bool sendToServo) {
    _pin = pin;
    _sendToServo = sendToServo;
    _servoControl.attach(_pin);
}

RoblucksServo::~RoblucksServo() {
    _servoControl.detach();
}

bool RoblucksServo::processRequest()
{
    ServoCmd servoCmd = (ServoCmd)_serialIO.read_i8();

    String msgToPI = "In Servo, cmd: ";
    msgToPI += String(servoCmd);

    uint8_t howFar;
    if(servoCmd != STOP) {
        howFar = _serialIO.read_i8();
        msgToPI += " how far: ";
        msgToPI += String(howFar);
    }
    _serialIO.outputTrace(msgToPI);

    switch (servoCmd) {
        case RIGHT: {
            _serialIO.outputTrace("Right requested");
            _ServoOpertation(map(howFar, 0, 100, SERVO_CENTER, SERVO_RIGHT) );
            break;
        }
        case LEFT: {
            _serialIO.outputTrace("Left requested");
            _ServoOpertation(map(howFar, 0, 100, SERVO_CENTER, SERVO_LEFT) );
            break;
        }
        case CENTER: {
            _serialIO.outputTrace("Center requested");
            _ServoOpertation(SERVO_CENTER);
            break;
        }
        default: {
            _serialIO.outputTrace("Invalid servo command");
            break;
        }
    }
    return true;
}

void RoblucksServo::_ServoOpertation(short requestedDirection) {
    if (requestedDirection > LEFT || requestedDirection < RIGHT){
        _serialIO.outputTrace("Invalid servo direction");
        return;
    }

    if (_sendToServo) {
        _serialIO.outputTrace("Sending to Servo " + String(requestedDirection));
        _servoControl.writeMicroseconds(requestedDirection);
    }
}