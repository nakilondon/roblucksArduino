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
    int measure = distance();

    String msgToPI = "In writeDistance, sensor: ";
    msgToPI += String(_direction);
    msgToPI += " distance: ";
    msgToPI += String(measure);
    _raspberryPi.logMsg(LOG_DEBUG, msgToPI);

    if (measure>0 && measure < 100) {

      //  uint8_t measureu8 = static_cast<uint8_t >(measure);
        uint8_t distantMessage[] = {DISTANCE, static_cast<uint8_t >(_direction)};
        for (int i = 0; i < sizeof(distantMessage); i++)
            _raspberryPi.write_ui8(distantMessage[i]);
        delay(10);
        _raspberryPi.write_int(measure);
    } else {
        _raspberryPi.logMsg(LOG_DEBUG, "Not sending distance");
    }
}

