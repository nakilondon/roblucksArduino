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
    static LogLevel _loglevel;

public:
    void setLogLevel(LogLevel loglevel);
    bool wait_for_bytes(int num_bytes, unsigned long timeout);
    uint8_t read_ui8();
    void writeMessage(enum Message message);
    void write_ui8(uint8_t num);
    void write_int(int num);
    Message readMessage();
    void logMsg(LogLevel logLevel, String traceMsg);
};


#endif //ROBLUCKSARDUINO_SERIALMSG_H
