//
// Created by james on 03/03/19.
//

#include "Distance.h"
#include "../Message.h"

Distance::Distance(Direction dirtection, int irPin)
    :SharpIR(irPin, SENSOR_MODEL){
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
    union {
        int measureInt;
        uint8_t measureUint8[2];
    };

    int measureInt = distance();
    if (measure>0 && measure < 100) {
        uint8_t distantMessage[] = {DISTANCE, static_cast<uint8_t >(_direction), measureUint8};
        for (int i = 0; i < sizeof(distantMessage); i++)
            _raspberryPi.write_ui8(distantMessage[i]);
    }
}