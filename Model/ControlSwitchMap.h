#ifndef CONTROLSWITCHMAP_H
#define CONTROLSWITCHMAP_H

#include <Model/SwitchModel.h>
#include <Model/RailModel.h>
#include <QMap>

class ControlSwitchMap
{
public:
    ControlSwitchMap();
    void setSwitches(QMap<int, SwitchModel*> switches);
    void setRails(QMap<int, RailModel*> rails);
    void removeSwitchReservation(RailModel::RailID from, TrainModel::TrainDirection direction);
    bool checkSwitchesAreNotReserved(RailModel::RailID from, RailModel::RailID to, TrainModel::TrainDirection direction);
    void setSwitchReservationAndState(RailModel::RailID from, RailModel::RailID to, TrainModel::TrainDirection direction);

private:
    QMap<int, SwitchModel*> switches;
    QMap<int, RailModel*> rails;
};

#endif // CONTROLSWITCHMAP_H
