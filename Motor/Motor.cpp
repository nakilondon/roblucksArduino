//
// Created by james on 17/02/19.
//

#include "Motor.h"
#include "../Message.h"
#include "SerialIO/SerialIO.h"


bool Motor::processRequest()
{
    SerialIO serialIO;
    MotorCmd motorCmd = (MotorCmd) serialIO.read_i8();
    uint8_t speed = serialIO.read_i8();
    serialIO.writeMessage(STRING);
    String msgToPI = "In Motor, cmd: ";
    msgToPI += String(motorCmd);
    msgToPI += " speed: ";
    msgToPI += String(speed);
    msgToPI += '\n';
    Serial.write(msgToPI.c_str());

    return true;
}