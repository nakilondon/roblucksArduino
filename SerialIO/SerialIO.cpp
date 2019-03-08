//
// Created by james on 17/02/19.
//

#include "SerialIO.h"
#include "../Message.h"
#include <Arduino.h>

void SerialIO::wait_for_bytes(int num_bytes, unsigned long timeout) {
    unsigned long startTime = millis();
    //Wait for incoming bytes or exit if timeout
    while ((Serial.available() < num_bytes) && (millis() - startTime < timeout)){}
}

void SerialIO::writeMessage(enum Message message) {
    uint8_t Order = static_cast<uint8_t>(message);
    write_ui8(Order);
}

void SerialIO::write_ui8(uint8_t data) {
    Serial.write(data);
}

Message SerialIO::readMessage() {
    return (Message) Serial.read();
}

uint8_t SerialIO::read_ui8() {
    wait_for_bytes(1, 100); // Wait for 1 byte with a timeout of 100 ms
    return static_cast<uint8_t >(Serial.read());
}

void SerialIO::logMsg(enum LogLevel logLevel, String traceMsg) {
    if (logLevel >= _loglevel) {
        writeMessage(LOG);
        String logMsg = logLevel + traceMsg;
        Serial.println(logMsg);
    }
}

void SerialIO::setLogLevel(LogLevel loglevel) {
    _loglevel = loglevel;
}