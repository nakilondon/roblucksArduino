//
// Created by james on 17/02/19.
//

#ifndef ROBLUCKSARDUINO_SERIALMSG_H
#define ROBLUCKSARDUINO_SERIALMSG_H

#include <Arduino.h>
#include <string.h>
#include "../Message.h"

class SerialIO {
private:
    LogLevel _loglevel;

public:
    void setLogLevel(LogLevel loglevel);
    void wait_for_bytes(int num_bytes, unsigned long timeout);
    uint8_t read_ui8();
    void writeMessage(enum Message message);
    void write_ui8(uint8_t num);
    Message readMessage();
    void logMsg(LogLevel logLevel, String traceMsg);
};


#endif //ROBLUCKSARDUINO_SERIALMSG_H
