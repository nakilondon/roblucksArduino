#include <Arduino.h>
#include <stdint.h>
#include "Message.h"
#include "SerialIO/SerialIO.h"
#include "Motor/Motor.h"
#include "parameters.h"
#include "RoblucksServo/RoblucksServo.h"
#include "Distance/Distance.h"
#include "Timer/Timer.h"
#include "../../../../usr/lib/gcc/avr/5.4.0/include/stdint-gcc.h"

Motor               motor;
RoblucksServo       servo;
SerialIO            raspberryPi;
bool isConnected =  false;

Distance frontDistance(DIRECTION_FRONT, FRONT_ECHO_PIN, FRONT_TRIGGER_PIN);
Distance backDistance(DIRECTION_BACK, BACK_ECHO_PIN, BACK_TRIGGER_PIN);
Distance leftDistance(DIRECTION_LEFT, LEFT_ECHO_PIN, LEFT_TRIGGER_PIN);
Distance rightDistance(DIRECTION_RIGHT, RIGHT_ECHO_PIN, RIGHT_TRIGGER_PIN);

Timer timer;

bool getMessageFromServer(){
    if(Serial.available()) {
        Message msgRecevied = raspberryPi.readMessage();

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
                raspberryPi.writeMessage(ALREADY_CONNECTED);
                break;
            }
            case ALREADY_CONNECTED: {
                isConnected = true;
                raspberryPi.writeMessage(ALREADY_CONNECTED);
                break;
            }
            case OPERATION:{
                switch (raspberryPi.read_ui8()) {
                    case SET_LOG_LEVEL:{
                        LogLevel newLogLevel = static_cast<LogLevel>(raspberryPi.read_ui8());
                        raspberryPi.setLogLevel(newLogLevel);
                    }
                    default:
                        raspberryPi.logMsg(LOG_ERROR, "Unknown operation");
                        break;
                }
                break;
            }
            default: {
                raspberryPi.logMsg(LOG_ERROR, "Unknown message recevied");
                return false;
            }
        }
    }
    return false;
}

void outputDistances(void* context){
    raspberryPi.logMsg(LOG_DEBUG, "In Output Distances");
    frontDistance.writeDistance();
    backDistance.writeDistance();
    leftDistance.writeDistance();
    rightDistance.writeDistance();
}


void setup() {
    Serial.begin(SERIAL_BAUD);
    raspberryPi.setLogLevel(LOG_INFO);

    while(!isConnected)
    {
        raspberryPi.writeMessage(HELLO);
        raspberryPi.wait_for_bytes(1, 1000);
        getMessageFromServer();
    }

    raspberryPi.logMsg(LOG_INFO, "Connected to PI");

    motor.begin(MOTOR_PIN, &raspberryPi);
    servo.begin(SERVO_PIN, &raspberryPi);

    frontDistance.begin(&raspberryPi);
    backDistance.begin(&raspberryPi);
    leftDistance.begin(&raspberryPi);
    rightDistance.begin(&raspberryPi);

    timer.every(75, outputDistances,0 );
}

void loop() {
    getMessageFromServer();
    timer.update();
}

