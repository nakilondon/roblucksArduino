//
// Created by james on 18/02/19.
//

#include "RoblucksServo.h"

#include "../Message.h"
#include "../SerialIO/SerialIO.h"

bool RoblucksServo::processRequest()
{
    SerialIO serialIO;
    ServoCmd servoCmd = (ServoCmd) serialIO.read_i8();
    uint8_t howFar = serialIO.read_i8();
    serialIO.writeMessage(STRING);
    String msgToPI = "In Servo, cmd: ";
    msgToPI += String(servoCmd);
    msgToPI += " how far: ";
    msgToPI += String(howFar);
    msgToPI += '\n';
    Serial.write(msgToPI.c_str());

    return true;
}
