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
#include "../../../../usr/share/arduino/hardware/arduino/cores/arduino/WString.h"

Motor               motor;
RoblucksServo       servo;
SerialIO            raspberryPi;
bool isConnected =  false;
bool sendDistances = false;
int8_t distanceTimerId = 0;

Distance frontDistance(DIRECTION_FRONT, FRONT_PIN);
//Distance backDistance(DIRECTION_BACK, BACK_PIN);
Distance leftDistance(DIRECTION_LEFT, LEFT_PIN);
Distance rightDistance(DIRECTION_RIGHT, RIGHT_PIN);

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
                raspberryPi.logMsg(LOG_INFO, "Hello received");
                raspberryPi.writeMessage(ALREADY_CONNECTED);
                break;
            }
            case ALREADY_CONNECTED: {
                isConnected = true;
                raspberryPi.logMsg(LOG_INFO, "Already Connected received");
                raspberryPi.writeMessage(ALREADY_CONNECTED);
                break;
            }
            case OPERATION: {
                if (raspberryPi.wait_for_bytes(1, 1000)) {
                    switch (static_cast<Operation>(raspberryPi.read_ui8())) {
                        case SET_LOG_LEVEL: {
                            if (raspberryPi.wait_for_bytes(1, 1000)) {
                                LogLevel newLogLevel = static_cast<LogLevel>(raspberryPi.read_ui8());
                                raspberryPi.logMsg(LOG_INFO, "Setting Log Level to " + String(newLogLevel));
                                raspberryPi.setLogLevel(newLogLevel);
                            } else {
                                raspberryPi.logMsg(LOG_ERROR, "log level timed out");
                            }
                            break;
                        }
                        case TURN_DISTANCES_ON: {
                            raspberryPi.logMsg(LOG_INFO, "Turning distance on requested");
                            sendDistances = true;
                            if (distanceTimerId == 0) {
                                distanceTimerId = timer.every(110, outputDistances, 0);
                                raspberryPi.logMsg(LOG_INFO, "Turning distance timer on");
                            } else
                                raspberryPi.logMsg(LOG_INFO, "Distance timer already set");
                            break;
                        }
                        case TURN_DISTANCES_OFF: {
                            sendDistances = false;
                            raspberryPi.logMsg(LOG_INFO,
                                               "Turning distance off requested, sendDistances = " +
                                               String(sendDistances));

                            if (distanceTimerId != 0) {
                                raspberryPi.logMsg(LOG_INFO, "Turning distance timer off");
                                timer.stop(distanceTimerId);
                                distanceTimerId = 0;
                            } else
                                raspberryPi.logMsg(LOG_INFO, "Distance timer not set");

                            break;
                        }
                        default: {
                            raspberryPi.logMsg(LOG_ERROR, "Unknown operation");
                            break;
                        }

                    }
                } else {
                    raspberryPi.logMsg(LOG_ERROR, "Operation message timed out");
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

    if (!sendDistances) {
        timer.stop(distanceTimerId);
        return;
    }

    raspberryPi.logMsg(LOG_DEBUG, "In Output Distances" );
    delay(10);
    frontDistance.writeDistance();
    delay(10);
  //  backDistance.writeDistance();
    leftDistance.writeDistance();
    delay(10);
    rightDistance.writeDistance();
    delay(10);
}

void setup() {
    Serial.begin(SERIAL_BAUD);
    raspberryPi.setLogLevel(LOG_INFO);

    while(!isConnected)
    {
        raspberryPi.writeMessage(HELLO);
        if(raspberryPi.wait_for_bytes(1, 1000))
            getMessageFromServer();
    }

    delay(1000);

    raspberryPi.logMsg(LOG_INFO, "Connected to PI");

    motor.begin(MOTOR_PIN, &raspberryPi);
    servo.begin(SERVO_PIN, &raspberryPi);

    frontDistance.begin(&raspberryPi);
//    backDistance.begin(&raspberryPi);
    leftDistance.begin(&raspberryPi);
    rightDistance.begin(&raspberryPi);

    if (sendDistances)
        distanceTimerId = timer.every(100, outputDistances,0 );
}

void loop() {
    getMessageFromServer();
    timer.update();
}

