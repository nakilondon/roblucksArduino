//
// Created by james on 03/03/19.
//

#include "Distance.h"
#include "../Message.h"

Distance::Distance(Direction dirtection, int echoPin, int triggerPin)
    : NewPing(triggerPin,echoPin,DEFAULT_MAX_DISTANCE){
    _direction = dirtection;
}

void Distance::begin(SerialIO *raspberryPi) {
    _raspberryPi = *raspberryPi;
}

void Distance::setAlertDistances(int alertMin, int alertMax) {
    _alertMax = alertMax;
    _alertMin = alertMin;
}

void Distance::writeDistance() {
    uint8_t distance = ping_cm();
    uint8_t distantMessage[] = {DISTANCE, static_cast<uint8_t >(_direction), distance};
    for(int i = 0; i < sizeof(distantMessage); i++)
        _raspberryPi.write_ui8(distantMessage[i]);
}