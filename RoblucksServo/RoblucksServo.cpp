//
// Created by james on 18/02/19.
//

#include "RoblucksServo.h"

#include "../Message.h"
#include "../SerialIO/SerialIO.h"

void RoblucksServo::begin(short pin, SerialIO *serialIO, bool sendToServo) {
    _pin = pin;
    _sendToServo = sendToServo;
    _servoControl.attach(_pin);
    _serialIO = *serialIO;
}

bool RoblucksServo::processRequest()
{
    ServoCmd servoCmd = (ServoCmd)_serialIO.read_ui8();

    String msgToPI = "In Servo, cmd: ";
    msgToPI += String(servoCmd);

    uint8_t howFar = 0;
    if(servoCmd != CENTER) {
        howFar = static_cast<uint8_t >(_serialIO.read_ui8());
        msgToPI += " how far: ";
        msgToPI += String(howFar);
    }
    _serialIO.logMsg(LOG_DEBUG, msgToPI);

    switch (servoCmd) {
        case RIGHT: {
             _serialIO.logMsg(LOG_DEBUG,"Right requested");
            _ServoOpertation(static_cast<int>(map(howFar, 0, 100, SERVO_CENTER, SERVO_RIGHT)));
            break;
        }
        case LEFT: {
            _serialIO.logMsg(LOG_DEBUG,"Left requested");
            _ServoOpertation(static_cast<int>(map(howFar, 0, 100, SERVO_CENTER, SERVO_LEFT)));
            break;
        }
        case CENTER: {
            _serialIO.logMsg(LOG_DEBUG, "Center requested");
            _ServoOpertation(SERVO_CENTER);
            break;
        }
        default: {
            _serialIO.logMsg(LOG_ERROR, "Invalid servo command");
            break;
        }
    }
    return true;
}

void RoblucksServo::_ServoOpertation(int requestedDirection) {
    if (requestedDirection > SERVO_LEFT || requestedDirection < SERVO_RIGHT){
        _serialIO.logMsg(LOG_ERROR, "Invalid servo direction: " + String(requestedDirection));
        return;
    }

    if (_sendToServo) {
        _serialIO.logMsg(LOG_DEBUG, "Sending to Servo " + String(requestedDirection));
        _servoControl.writeMicroseconds(requestedDirection);
    }
}