//
// Created by james on 16/02/19.
//

#ifndef CMAKELISTS_TXT_ORDER_H
#define CMAKELISTS_TXT_ORDER_H

#include <Arduino.h>

enum Message {
    HELLO = 1,
    SERVO = 2,
    MOTOR = 3,
    ALREADY_CONNECTED = 4,
    ERROR = 5,
    RECEIVED = 6,
 //   STOP = 6,
    LOG = 7
};

enum MotorCmd {
    FORWARD = 1,
    REVERSE = 2,
    STOP = 3,
    ARM = 4
};

enum ServoCmd{
    CENTER = 1,
    LEFT = 2,
    RIGHT = 3
};

typedef enum Message Message;

enum LogLevel {
    LOG_DEBUG = 0,
    LOG_INFO = 1,
    LOG_WARNING = 2,
    LOG_ERROR = 3,
    LOG_CRITICAL = 4
};

#endif //CMAKELISTS_TXT_ORDERS_H
