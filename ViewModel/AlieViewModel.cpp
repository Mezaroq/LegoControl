#include "AlieViewModel.h"
#include <QDebug>

AlieViewModel::AlieViewModel(QObject *parent) : QObject(parent)
{
    createSwitchMap();
}

void AlieViewModel::run()
{
    manageMovingTrains();
    manageStopTrains();
}

void AlieViewModel::createSwitchMap()
{
    switchMap.insert(QPair<ControlRail::RailID, ControlRail::RailID>(ControlRail::RAIL_SECTION_1, ControlRail::RAIL_SECTION_5), QList<ControlSwitch*>());
    switchMap.insert(QPair<ControlRail::RailID, ControlRail::RailID>(ControlRail::RAIL_SECTION_1, ControlRail::RAIL_SECTION_6), QList<ControlSwitch*>());
    switchMap.insert(QPair<ControlRail::RailID, ControlRail::RailID>(ControlRail::RAIL_SECTION_1, ControlRail::RAIL_SECTION_8), QList<ControlSwitch*>());
    switchMap.insert(QPair<ControlRail::RailID, ControlRail::RailID>(ControlRail::RAIL_SECTION_1, ControlRail::RAIL_SECTION_9), QList<ControlSwitch*>());

    switchMap.insert(QPair<ControlRail::RailID, ControlRail::RailID>(ControlRail::RAIL_SECTION_2, ControlRail::RAIL_SECTION_5), QList<ControlSwitch*>());
    switchMap.insert(QPair<ControlRail::RailID, ControlRail::RailID>(ControlRail::RAIL_SECTION_2, ControlRail::RAIL_SECTION_6), QList<ControlSwitch*>());
    switchMap.insert(QPair<ControlRail::RailID, ControlRail::RailID>(ControlRail::RAIL_SECTION_2, ControlRail::RAIL_SECTION_8), QList<ControlSwitch*>());
    switchMap.insert(QPair<ControlRail::RailID, ControlRail::RailID>(ControlRail::RAIL_SECTION_2, ControlRail::RAIL_SECTION_9), QList<ControlSwitch*>());

    switchMap.insert(QPair<ControlRail::RailID, ControlRail::RailID>(ControlRail::RAIL_SECTION_3, ControlRail::RAIL_SECTION_5), QList<ControlSwitch*>());
    switchMap.insert(QPair<ControlRail::RailID, ControlRail::RailID>(ControlRail::RAIL_SECTION_3, ControlRail::RAIL_SECTION_6), QList<ControlSwitch*>());
    switchMap.insert(QPair<ControlRail::RailID, ControlRail::RailID>(ControlRail::RAIL_SECTION_3, ControlRail::RAIL_SECTION_8), QList<ControlSwitch*>());
    switchMap.insert(QPair<ControlRail::RailID, ControlRail::RailID>(ControlRail::RAIL_SECTION_3, ControlRail::RAIL_SECTION_9), QList<ControlSwitch*>());

    switchMap.insert(QPair<ControlRail::RailID, ControlRail::RailID>(ControlRail::RAIL_SECTION_5, ControlRail::RAIL_SECTION_8), QList<ControlSwitch*>());
    switchMap.insert(QPair<ControlRail::RailID, ControlRail::RailID>(ControlRail::RAIL_SECTION_5, ControlRail::RAIL_SECTION_9), QList<ControlSwitch*>());
    switchMap.insert(QPair<ControlRail::RailID, ControlRail::RailID>(ControlRail::RAIL_SECTION_6, ControlRail::RAIL_SECTION_8), QList<ControlSwitch*>());
    switchMap.insert(QPair<ControlRail::RailID, ControlRail::RailID>(ControlRail::RAIL_SECTION_6, ControlRail::RAIL_SECTION_9), QList<ControlSwitch*>());
}

void AlieViewModel::setAiEnabled(bool state)
{
    if (state && timetables.isEmpty())
        generateTimetables();
    else
        timetables.clear();

    this->alieIsEnabled = state;
}

void AlieViewModel::setSwitches(QMap<int, ControlSwitch *> switches)
{
    this->switches = switches;
}

void AlieViewModel::setRails(QMap<int, ControlRail *> rails)
{
    this->rails = rails;
}

void AlieViewModel::setTrains(QMap<int, ControlTrain *> trains)
{
    this->trains = trains;
}

void AlieViewModel::generateTimetables()
{
    timetables.insert(ControlTrain::TRAIN_1, ControlTimetable::generateTimetable(ControlTrain::TRAIN_1, -1));
    timetables.insert(ControlTrain::TRAIN_2, ControlTimetable::generateTimetable(ControlTrain::TRAIN_2, -1));
    timetables.insert(ControlTrain::TRAIN_3, ControlTimetable::generateTimetable(ControlTrain::TRAIN_3, -1));

    for (ControlTimetable *timetable : timetables) {
        for (ControlRail *rail : rails) {
            if (rail->getTrain()) {
                if (rail->getTrain()->getTrainID() == timetable->getTrainID()) {
                    timetable->setCurrentRailID(rail->getRailID());
                    break;
                }
            }
        }
    }
}

void AlieViewModel::manageMovingTrains()
{
    QMapIterator<ControlTrain*, ControlTrain::TrainSpeed> trains(movingTrains);
    while (trains.hasNext()) {
        trains.next();
        trains.key()->setTrainSpeed(trains.value());
    }
    movingTrains.clear();
}

void AlieViewModel::manageStopTrains()
{
    for (auto trainID : stopTrains) {
        timetable = timetables.value(trainID);

        if (timetable->getCurrentRailID() == timetable->getDestinationRailID()) {
            if (timetable->isEndLoop()) {
                trains.value(trainID)->setWaiting(WAITING_TIME);
                timetable = ControlTimetable::generateTimetable(trainID, timetable->getCurrentRailID());
                timetables.insert(trainID, timetable);
                continue;
            } else {
                timetable->increaseLoop();
            }
        }
        if (trains.value(trainID)->isWaiting())
            continue;

        if (prepareTrainWay(trains.value(trainID), rails.value(timetable->getCurrentRailID()), rails.value(timetable->getDestinationRailID()), timetable->getDirection(), timetable->isEndLoop())) {
            trains.value(trainID)->setTrainSpeed(ControlTrain::TrainSpeed(SPEED * timetable->getDirection()));
            stopTrains.remove(trains.value(trainID)->getTrainPriority());
        } else {
            trains.value(trainID)->setTrainSpeed(ControlTrain::SPEED_BREAKE);
        }
    }
}

void AlieViewModel::setSwitches(ControlRail *from, ControlRail *to)
{

}

bool AlieViewModel::prepareTrainWay(ControlTrain *train, ControlRail *from, ControlRail *to, ControlTrain::TrainDirection direction, bool isEndLoop)
{
    return true;
    switch (direction) {
    case ControlTrain::DIRECTION_FORWARD:
        if (checkIfRailsAreFree(direction, from, to, isEndLoop)) {
            if (checkIfSwitchesAreFree(from, to)) {
                if (!checkIfExistTrainWithHigherPriority(direction, from, train->getTrainPriority())) {
                    setTrainWay(direction, from, to, isEndLoop);
                    return true;
                }
            }
        }
        break;
    case ControlTrain::DIRECTION_REVERSE:
        break;
    }
    return false;
}

void AlieViewModel::setTrainWay(ControlTrain::TrainDirection direction, ControlRail *from, ControlRail *to, bool isEndLoop)
{
    ControlRail *destinationRail;
    switch (direction) {
    case ControlTrain::DIRECTION_FORWARD:
        from->setReservation(true);

        for (ControlRail *rail : from->getNextRails()) {
            if (isEndLoop) {
                if (rail->getRailID() == to->getRailID()) {
                    destinationRail = rail;
                    break;
                }
            }
            if (!rail->isReserved()) {
                destinationRail = rail;
                break;
            }
        }
        destinationRail->setReservation(true);
        setSwitches(from, to);

        break;
    case ControlTrain::DIRECTION_REVERSE:
        break;


    }
}

bool AlieViewModel::checkIfExistTrainWithHigherPriority(ControlTrain::TrainDirection direction, ControlRail *from, ControlTrain::TrainPriority priority)
{
    switch (direction) {
    case ControlTrain::DIRECTION_FORWARD:
        for (ControlRail *rail : from->getNextRails().first()->getNextRails()) {
            ControlTrain *train = rail->getTrain();
            if (train) {
                if (train->getTrainPriority() > priority) {
                    currentTrainTimetable = timetables.value(train->getTrainID());
                    if (currentTrainTimetable->getDirection() == ControlTrain::DIRECTION_REVERSE && !currentTrainTimetable->isEndLoop())
                        return true;
                }
            }
        }
        break;
    case ControlTrain::DIRECTION_REVERSE:
        for (ControlRail *rail : from->getLastRails().first()->getLastRails()) {
            ControlTrain *train = rail->getTrain();
            if (train) {
                if (train->getTrainPriority() > priority) {
                    currentTrainTimetable = timetables.value(train->getTrainID());
                    if (currentTrainTimetable->getDirection() == ControlTrain::DIRECTION_FORWARD && !currentTrainTimetable->isEndLoop())
                        return true;
                }
            }
        }
        break;
    }
    return false;
}

bool AlieViewModel::checkIfRailsAreFree(ControlTrain::TrainDirection direction, ControlRail *from, ControlRail *to, bool isEndLoop)
{
    switch (direction) {
    case ControlTrain::DIRECTION_FORWARD:
        if (from->getNextRails().first()->isReserved())
            return false;

        for (ControlRail *rail : from->getNextRails().first()->getNextRails()) {
            if (isEndLoop) {
                if (rail->getRailID() == to->getRailID()) {
                    if (rail->isReserved())
                        return false;
                    else
                        return true;
                } else {
                    if (!rail->isReserved())
                        return true;
                }
            } else if (!rail->isReserved()) {
                return true;
            }
        }
        return false;

    case ControlTrain::DIRECTION_REVERSE:
        if (from->getLastRails().first()->isReserved())
            return false;

        for (ControlRail *rail : from->getLastRails().first()->getLastRails()) {
            if (isEndLoop) {
                if (rail->getRailID() == to->getRailID()) {
                    if (rail->isReserved())
                        return false;
                    else
                        return true;
                } else {
                    if (!rail->isReserved())
                        return true;
                }
            } else if (!rail->isReserved()) {
                return true;
            }
        }
        return false;
    }
}

bool AlieViewModel::checkIfSwitchesAreFree(ControlRail *from, ControlRail *to)
{
    QList<ControlSwitch*> switches;

    if (from->getRailID() < to->getRailID()) {
        switches = this->switchMap.value(QPair<int, int>(from->getRailID(), to->getRailID()));
    } else {
        switches = switchMap.value(QPair<int, int>(to->getRailID(), from->getRailID()));
    }

    for (ControlSwitch *currentSwitch : switches) {
        if (currentSwitch->isReserved())
            return false;
    }
    return true;
}

QMap<ControlTrain::TrainID, ControlTimetable *> *AlieViewModel::getTimetables()
{
    return &timetables;
}

void AlieViewModel::trainEnters(ControlTrain::TrainID trainID, ControlRail::RailID railID)
{
    if (alieIsEnabled) {
        ControlTrain *train = trains.value(trainID);
        movingTrains.insert(train, ControlTrain::TrainSpeed(ControlTrain::SPEED_FORWARD_3 * train->getTrainDirectionMultiplier()));
        run();
    }
}

void AlieViewModel::trainEntered(ControlTrain::TrainID trainID, ControlRail::RailID railID)
{

}

void AlieViewModel::trainLeaving(ControlTrain::TrainID trainID, ControlRail::RailID railID)
{
    if (alieIsEnabled) {
        ControlTrain *train = trains.value(trainID);
        movingTrains.insert(train, ControlTrain::TrainSpeed(ControlTrain::SPEED_FORWARD_5 * train->getTrainDirectionMultiplier()));
        run();//debug
    }
}

void AlieViewModel::trainLeft(ControlTrain::TrainID trainID, ControlRail::RailID railID)
{

}

void AlieViewModel::stopSensorActivated(ControlTrain::TrainID trainID, ControlRail::RailID railID)
{
    if (alieIsEnabled) {
        timetable = timetables.value(trainID);
        timetable->setCurrentRailID(railID);
        stopTrains.insert(trains.value(trainID)->getTrainPriority(), trainID);

        run();//debug
    }
}
