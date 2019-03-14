//
// Created by james on 03/03/19.
//

#ifndef ROBLUCKSARDUINO_DISTANCE_H
#define ROBLUCKSARDUINO_DISTANCE_H

#include "../SerialIO/SerialIO.h"
#include "NewPing.h"

#define DEFAULT_MAX_DISTANCE 200
#define DEFAULT_ALERT_MIN 0
#define DEFAULT_ALERT_MAX 0
#define DEFAULT_INTERVAL 500

enum Direction {
    DIRECTION_FRONT = 1,
    DIRECTION_BACK = 2,
    DIRECTION_LEFT = 3,
    DIRECTION_RIGHT = 4,
};


class Distance : NewPing {
private:
    Direction _direction;
    SerialIO _raspberryPi;
    int _maxDistance;
    int _alertMin;
    int _alertMax;

public:
    Distance(Direction dirtection, int echoPin, int triggerPin );
    void begin(SerialIO *raspberryPi);
    void setAlertDistances(int alertMin, int alertMax);
    void writeDistance();
};


#endif //ROBLUCKSARDUINO_DISTANCE_H
