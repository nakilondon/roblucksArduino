#include <Arduino.h>
#include <stdint.h>
#include "Message.h"
#include "SerialIO/SerialIO.h"
#include "Motor/Motor.h"
#include "parameters.h"
#include "RoblucksServo/RoblucksServo.h"

Motor motor;
RoblucksServo servo;
SerialIO serialIO;

bool isConnected = false;

bool getMessageFromServer(){
    if(Serial.available()) {
        Message msgRecevied = serialIO.readMessage();

        switch(msgRecevied){
            case MOTOR: {
                motor.processRequest();
                break;
            }
            case SERVO:{
                servo.processRequest();
                break;
            }
            case HELLO: {
                isConnected = true;
                serialIO.writeMessage(ALREADY_CONNECTED);
                break;
            }
            case ALREADY_CONNECTED: {
                isConnected = true;
                serialIO.writeMessage(ALREADY_CONNECTED);
                break;
            }
            default: {
                //serialIO.writeMessage(STRING);
                serialIO.outputTrace("Default Message");
                return false;
            }
        }
    }
    return false;
}

void setup() {
    Serial.begin(SERIAL_BAUD);

    while(!isConnected)
    {
        serialIO.writeMessage(HELLO);
        serialIO.wait_for_bytes(1, 1000);
        getMessageFromServer();
    }

    motor.begin(MOTOR_PIN);
    servo.begin(SERVO_PIN);
}

void loop() {
    getMessageFromServer();
}

