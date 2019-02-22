//
// Created by james on 17/02/19.
//

#ifndef ROBLUCKSARDUINO_SERIALMSG_H
#define ROBLUCKSARDUINO_SERIALMSG_H

#include "../Message.h"

class SerialIO {
private:
    bool _sendTrace;

public:
    void setTrace(bool sendTrace);
    void wait_for_bytes(int num_bytes, unsigned long timeout);
    void read_signed_bytes(int8_t *buffer, size_t n);
    int8_t read_i8();
    int16_t read_i16();
    int32_t read_i32();
    void writeMessage(enum Message message);
    void write_i8(int8_t num);
    void write_i16(int16_t num);
    void write_i32(int32_t num);
    Message readMessage();
    void logMsg(LogLevel logLevel, String traceMsg);
};


#endif //ROBLUCKSARDUINO_SERIALMSG_H
