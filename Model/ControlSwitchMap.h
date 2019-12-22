#ifndef CONTROLSWITCHMAP_H
#define CONTROLSWITCHMAP_H

#include <Model/ControlSwitch.h>
#include <Model/ControlRail.h>
#include <QMap>

class ControlSwitchMap
{
public:
    ControlSwitchMap();
    void setSwitches(QMap<int, ControlSwitch*> switches);
    void setRails(QMap<int, ControlRail*> rails);
    void removeSwitchReservation(ControlRail::RailID from, ControlTrain::TrainDirection direction);
    bool checkSwitchesAreNotReserved(ControlRail::RailID from, ControlRail::RailID to, ControlTrain::TrainDirection direction);
    void setSwitchReservationAndState(ControlRail::RailID from, ControlRail::RailID to, ControlTrain::TrainDirection direction);

private:
    QMap<int, ControlSwitch*> switches;
    QMap<int, ControlRail*> rails;
};

#endif // CONTROLSWITCHMAP_H
