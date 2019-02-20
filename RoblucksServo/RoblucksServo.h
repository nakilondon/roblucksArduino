//
// Created by james on 18/02/19.
//
#include <Arduino.h>
#include <Servo.h>
#include <../SerialIO/SerialIO.h>

#ifndef ROBLUCKSARDUINO_ROBLUCKSSERVO_H
#define ROBLUCKSARDUINO_ROBLUCKSSERVO_H

#define SERVO_CENTER              1600
#define SERVO_LEFT                1870
#define SERVO_RIGHT               1330

class RoblucksServo {
private:
    Servo _servoControl;
    SerialIO _serialIO;
    bool _sendToServo;

    short _pin;
    void _ServoOpertation(int requestedDirection);

public:
    void begin(short pin, bool sendToServo = true);
    bool processRequest();
};


#endif //ROBLUCKSARDUINO_ROBLUCKSSERVO_H
