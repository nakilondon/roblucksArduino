//
// Created by james on 17/02/19.
//

#include "SerialIO.h"
#include "../Message.h"
#include <Arduino.h>

bool SerialIO::wait_for_bytes(int num_bytes, unsigned long timeout) {
    unsigned long startTime = millis();
    //Wait for incoming bytes or exit if timeout
    while ((Serial.available() < num_bytes) && (millis() - startTime < timeout)){}

    if (Serial.available() < num_bytes)
        return false;

    return true;
}

void SerialIO::writeMessage(enum Message message) {
    uint8_t Order = static_cast<uint8_t>(message);
    write_ui8(Order);
}

void SerialIO::write_ui8(uint8_t data) {
    Serial.write(data);
}

void SerialIO::write_int(int data) {
    union {
        int dataInt;
        uint8_t dataUi8[2];
    } dataUnion;

    dataUnion.dataInt = data;
    Serial.write(dataUnion.dataUi8, 2);
}

Message SerialIO::readMessage() {
    return (Message) Serial.read();
}

uint8_t SerialIO::read_ui8() {
    wait_for_bytes(1, 100); // Wait for 1 byte with a timeout of 100 ms
    return static_cast<uint8_t >(Serial.read());
}

void SerialIO::logMsg(LogLevel logLevel, String traceMsg) {
    if (_loglevel <= logLevel) {
        writeMessage(LOG);
        String logMsg = "1" + traceMsg;
        Serial.println(logMsg);
    }
}
void SerialIO::setLogLevel(LogLevel loglevel) {
    _loglevel = loglevel;
    logMsg(LOG_INFO, "Log level set = " + String(_loglevel));
}

LogLevel SerialIO::_loglevel = LOG_INFO;
