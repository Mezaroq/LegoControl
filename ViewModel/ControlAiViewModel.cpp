#include "ControlAiViewModel.h"
#include <QDebug>

ControlAiViewModel::ControlAiViewModel(QObject *parent) : QObject(parent)
{

}

void ControlAiViewModel::run()
{
    manageMovingTrains();
    manageStopTrains();
    antiBlocker();
}

void ControlAiViewModel::setAiEnabled(bool state)
{
    if (state && timetables.isEmpty()) {
        generateTimetables();
        for (ControlTimetable *timetable : timetables) {
            stopTrains.insert(trains.value(timetable->getTrainID())->getTrainPriority(), timetable->getTrainID());
        }
    } else {
        timetables.clear();
        stopTrains.clear();
        for (ControlTrain *train : trains) {
            train->setTrainSpeed(ControlTrain::SPEED_BREAKE);
        }
        for (ControlLight *light : lights) {
            light->setToggle(ControlLight::STATE_RED);
        }
        for (ControlSwitch *cswitch : switches) {
            cswitch->setReservation(false);
            cswitch->setToggle(false);
        }
        for (ControlRail *rail : rails) {
            if (rail->getTrain())
                continue;
            rail->setReservation(false);
        }
    }

    this->aiIsEnabled = state;
}

void ControlAiViewModel::setSwitches(QMap<int, ControlSwitch *> switches)
{
    this->switches = switches;
}

void ControlAiViewModel::setRails(QMap<int, ControlRail *> rails)
{
    this->rails = rails;
}

void ControlAiViewModel::setTrains(QMap<int, ControlTrain *> trains)
{
    this->trains = trains;
}

void ControlAiViewModel::setLights(QMap<int, ControlLight *> lights)
{
    this->lights = lights;
}

void ControlAiViewModel::setSwitchMap(ControlSwitchMap *switchMap)
{
    this->switchMap = switchMap;
}

void ControlAiViewModel::supportManualDriving(ControlTrain::TrainID trainID, ControlRail::RailID railID)
{
    ControlRail *rail = rails.value(railID);
    ControlTrain *train = trains.value(trainID);

    switch (train->getTrainDirectionFromSpeed()) {
    case ControlTrain::DIRECTION_FORWARD:
        if (rail->getNextRails().first()->getTrain() || !rail->getNextLight()->getLightState()) {
            train->setTrainSpeed(ControlTrain::SPEED_BREAKE);
            rail->getNextLight()->setToggle(ControlLight::STATE_RED);
        } else {
            for (ControlRail *nextRail : rail->getNextRails().first()->getNextRails()) {
                if (nextRail->getTrain()) {
                    if (nextRail->getTrain()->getTrainDirectionFromSpeed() == ControlTrain::DIRECTION_REVERSE) {
                        train->setTrainSpeed(ControlTrain::SPEED_BREAKE);
                        rail->getNextLight()->setToggle(ControlLight::STATE_RED);
                        break;
                    }
                }
            }
        }
        break;
    case ControlTrain::DIRECTION_REVERSE:
        if (rail->getLastRails().first()->getTrain() || !rail->getLastLight()->getLightState()) {
            train->setTrainSpeed(ControlTrain::SPEED_BREAKE);
            rail->getLastLight()->setToggle(ControlLight::STATE_RED);
        } else {
            for (ControlRail *nextRail : rail->getLastRails().first()->getLastRails()) {
                if (nextRail->getTrain()) {
                    if (nextRail->getTrain()->getTrainDirectionFromSpeed() == ControlTrain::DIRECTION_FORWARD) {
                        train->setTrainSpeed(ControlTrain::SPEED_BREAKE);
                        rail->getLastLight()->setToggle(ControlLight::STATE_RED);
                        break;
                    }
                }
            }
        }
        break;
    }
}

void ControlAiViewModel::generateTimetables()
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

void ControlAiViewModel::manageMovingTrains()
{
    QMapIterator<ControlTrain*, ControlTrain::TrainSpeed> trains(movingTrains);
    while (trains.hasNext()) {
        trains.next();
        trains.key()->setTrainSpeed(trains.value());
    }
    movingTrains.clear();
}

void ControlAiViewModel::manageStopTrains()
{
    for (auto trainID : stopTrains) {
        if (trains.value(trainID)->isWaiting())
            continue;

        timetable = timetables.value(trainID);
        if (timetable->isEndLoop()) {
            if (timetable->getCurrentRailID() == timetable->getDestinationRailID()) {
                trains.value(trainID)->setWaiting(WAITING_TIME);
                timetable = ControlTimetable::generateTimetable(trainID, timetable->getCurrentRailID());
                timetables.insert(trainID, timetable);
                continue;
            }
        }

        if (prepareTrainWay(trains.value(trainID), rails.value(timetable->getCurrentRailID()), rails.value(timetable->getDestinationRailID()), timetable->getDirection(), timetable->isEndLoop(), timetable->isIgnoreTrain())) {
            trains.value(trainID)->setTrainSpeed(ControlTrain::TrainSpeed(STARTING_SPEED * timetable->getDirection()));
            stopTrains.remove(trains.value(trainID)->getTrainPriority());
        } else {
            trains.value(trainID)->setTrainSpeed(ControlTrain::SPEED_BREAKE);
        }
    }
}

void ControlAiViewModel::antiBlocker()
{
    if (!aiIsEnabled)
        return;

    int counter = 0;
    ControlTrain *train = nullptr;
    ControlRail *from = nullptr;

    for (auto trainID : stopTrains) {
        if (!trains.value(trainID)->isWaiting()) {
            timetable = timetables.value(trainID);
            switch (timetable->getDirection()) {
            case ControlTrain::DIRECTION_FORWARD:
            {
                from = rails.value(timetable->getCurrentRailID());
                for (ControlRail *rail : from->getNextRails().first()->getNextRails()) {
                    if (rail->getTrain()) {
                        if (timetables.value(rail->getTrain()->getTrainID())->getDirection() == ControlTrain::DIRECTION_REVERSE) {
                            counter++;
                        }
                    }
                }
                if (counter == from->getNextRails().first()->getNextRails().size()) {
                    for (ControlRail *rail : from->getNextRails().first()->getNextRails()) {
                        if (rail->getTrain() && train == nullptr) {
                            train = rail->getTrain();
                        } else if (rail->getTrain()) {
                            if (rail->getTrain()->getTrainPriority() < train->getTrainPriority())
                                train = rail->getTrain();
                        }
                    }
                    timetables.value(train->getTrainID())->setIgnoreTrain(true);
                }
                break;
            }
            case ControlTrain::DIRECTION_REVERSE:
            {
                from = rails.value(timetable->getCurrentRailID());
                for (ControlRail *rail : from->getLastRails().first()->getLastRails()) {
                    if (rail->getTrain()) {
                        if (timetables.value(rail->getTrain()->getTrainID())->getDirection() == ControlTrain::DIRECTION_FORWARD) {
                            counter++;
                        }
                    }
                }
                if (counter == from->getLastRails().first()->getLastRails().size()) {
                    for (ControlRail *rail : from->getLastRails().first()->getLastRails()) {
                        if (rail->getTrain() && train == nullptr) {
                            train = rail->getTrain();
                        } else if (rail->getTrain()) {
                            if (rail->getTrain()->getTrainPriority() < train->getTrainPriority())
                                train = rail->getTrain();
                        }
                    }
                    timetables.value(train->getTrainID())->setIgnoreTrain(true);
                }
                break;
            }
            }
        }
        counter = 0;
        train = nullptr;
        from = nullptr;
    }
}

void ControlAiViewModel::manageTrainSpeed(ControlTrain::TrainID trainID, SpeedType speedType)
{
    ControlTrain *train = trains.value(trainID);

    switch (trainID) {
    case ControlTrain::TRAIN_1:
    case ControlTrain::TRAIN_2:
        if (speedType == ENTERS) {
            movingTrains.insert(train, ControlTrain::TrainSpeed(ControlTrain::SPEED_FORWARD_3 * train->getTrainDirectionFromSpeed()));
        } else {
            movingTrains.insert(train, ControlTrain::TrainSpeed(ControlTrain::SPEED_FORWARD_5 * train->getTrainDirectionFromSpeed()));
        }
        break;
    case ControlTrain::TRAIN_3:
        if (speedType == ENTERS) {
            movingTrains.insert(train, ControlTrain::TrainSpeed(ControlTrain::SPEED_FORWARD_3 * train->getTrainDirectionFromSpeed()));
        } else {
            movingTrains.insert(train, ControlTrain::TrainSpeed(ControlTrain::SPEED_FORWARD_5 * train->getTrainDirectionFromSpeed()));
        }
        break;
    default:
        break;
    }
}

bool ControlAiViewModel::prepareTrainWay(ControlTrain *train, ControlRail *from, ControlRail *to, ControlTrain::TrainDirection direction, bool isEndLoop, bool ignoreFlag)
{
    if (checkIfNotExistTrainWithHigherPriority(direction, from, train->getTrainPriority(), ignoreFlag)) {
        if (checkIfRailsAreNotReseved(direction, from, to, isEndLoop)) {
            if (switchMap->checkSwitchesAreNotReserved(from->getRailID(), to->getRailID(), direction)) {
                setTrainWay(direction, from, to, isEndLoop);
                return true;
            }
        }
    }
    return false;
}

void ControlAiViewModel::setTrainWay(ControlTrain::TrainDirection direction, ControlRail *from, ControlRail *to, bool isEndLoop)
{
    ControlRail *destinationRail;

    switch (direction) {
    case ControlTrain::DIRECTION_FORWARD:
        from->setReservation(true);
        from->getNextRails().first()->setReservation(true);

        for (ControlRail *rail : from->getNextRails().first()->getNextRails()) {
            if (isEndLoop) {
                if (rail->getRailID() == to->getRailID()) {
                    destinationRail = rail;
                    break;
                } else if (!rail->isReserved()) {
                    destinationRail = rail;
                }
            } else if (!rail->isReserved()) {
                destinationRail = rail;
                break;
            }
        }
        if (destinationRail) {
            destinationRail->setReservation(true);
            from->getNextLight()->setToggle(ControlLight::STATE_GREEN);
            switchMap->setSwitchReservationAndState(from->getRailID(), destinationRail->getRailID(), ControlTrain::DIRECTION_FORWARD);
        }
        break;
    case ControlTrain::DIRECTION_REVERSE:
        from->setReservation(true);
        from->getLastRails().first()->setReservation(true);

        for (ControlRail *rail : from->getLastRails().first()->getLastRails()) {
            if (isEndLoop) {
                if (rail->getRailID() == to->getRailID()) {
                    destinationRail = rail;
                    break;
                } else if (!rail->isReserved()) {
                    destinationRail = rail;
                }
            } else if (!rail->isReserved()) {
                destinationRail = rail;
                break;
            }
        }
        if (destinationRail) {
            destinationRail->setReservation(true);
            from->getLastLight()->setToggle(ControlLight::STATE_GREEN);
            switchMap->setSwitchReservationAndState(from->getRailID(), destinationRail->getRailID(), ControlTrain::DIRECTION_REVERSE);
        }
        break;
    }
}

bool ControlAiViewModel::checkIfNotExistTrainWithHigherPriority(ControlTrain::TrainDirection direction, ControlRail *from, ControlTrain::TrainPriority priority, bool ignoreFlag)
{
    if (ignoreFlag) {
        timetables.value(from->getTrain()->getTrainID())->setIgnoreTrain(false);
        return true;
    }

    switch (direction) {
    case ControlTrain::DIRECTION_FORWARD:
        for (ControlRail *rail : from->getNextRails().first()->getNextRails()) {
            ControlTrain *train = rail->getTrain();
            if (train) {
                if (train->getTrainPriority() < priority) {
                    timetable = timetables.value(train->getTrainID());
                    if (timetable->getDirection() == ControlTrain::DIRECTION_REVERSE) {
                        if (timetable->getDestinationRailID() != rail->getRailID() || (timetable->getDestinationRailID() == rail->getRailID() && !timetable->isEndLoop()) ) {
                            return false;
                        }
                    }
                }
            }
        }
        break;
    case ControlTrain::DIRECTION_REVERSE:
        for (ControlRail *rail : from->getLastRails().first()->getLastRails()) {
            ControlTrain *train = rail->getTrain();
            if (train) {
                if (train->getTrainPriority() < priority) {
                    timetable = timetables.value(train->getTrainID());
                    if (timetable->getDirection() == ControlTrain::DIRECTION_FORWARD) {
                        if (timetable->getDestinationRailID() != rail->getRailID() || (timetable->getDestinationRailID() == rail->getRailID() && !timetable->isEndLoop()) ) {
                            return false;
                        }
                    }
                }
            }
        }
        break;
    }

    return true;
}

bool ControlAiViewModel::checkIfRailsAreNotReseved(ControlTrain::TrainDirection direction, ControlRail *from, ControlRail *to, bool isEndLoop)
{
    bool endLoopFreeRail = false;

    switch (direction) {
    case ControlTrain::DIRECTION_FORWARD:
    {
        if (from->getNextRails().first()->isReserved())
            return false;

        for (ControlRail *rail : from->getNextRails().first()->getNextRails()) {
            if (isEndLoop) {
                if (rail->getRailID() == to->getRailID()) {
                    if (rail->isReserved()) {
                        if (to->getTrain()) {
                            if (timetables.value(to->getTrain()->getTrainID())->getDirection() == ControlTrain::DIRECTION_REVERSE)  //  REMOVE
                                timetables.value(to->getTrain()->getTrainID())->setIgnoreTrain(true);                               //  REMOVE, ponizej tez
                        }
                        return false;
                    } else
                        return true;
                } else if (!rail->isReserved()) {
                    endLoopFreeRail = true;
                }
            } else if (!rail->isReserved()) {
                return true;
            }
        }
        break;
    }
    case ControlTrain::DIRECTION_REVERSE:
    {
        if (from->getLastRails().first()->isReserved())
            return false;

        for (ControlRail *rail : from->getLastRails().first()->getLastRails()) {
            if (isEndLoop) {
                if (rail->getRailID() == to->getRailID()) {
                    if (rail->isReserved()) {
                        if (to->getTrain()) {
                            if (timetables.value(to->getTrain()->getTrainID())->getDirection() == ControlTrain::DIRECTION_FORWARD)
                                timetables.value(to->getTrain()->getTrainID())->setIgnoreTrain(true);
                        }
                        return false;
                    } else
                        return true;
                } else if (!rail->isReserved()) {
                    endLoopFreeRail = true;
                }
            } else if (!rail->isReserved()) {
                return true;
            }
        }
        break;
    }
    }
    if (endLoopFreeRail)
        return true;
    else
        return false;
}

QMap<ControlTrain::TrainID, ControlTimetable *> *ControlAiViewModel::getTimetables()
{
    return &timetables;
}

void ControlAiViewModel::trainEnters(ControlTrain::TrainID trainID, ControlRail::RailID railID)
{
    if (aiIsEnabled) {
        manageTrainSpeed(trainID, ENTERS);
    }
}

void ControlAiViewModel::trainEntered(ControlTrain::TrainID trainID, ControlRail::RailID railID)
{
    if (aiIsEnabled) {
        ControlRail *rail;
        switch (timetables.value(trainID)->getDirection()) {
        case ControlTrain::DIRECTION_FORWARD:
            rail = rails.value(railID);
            rail->getLastRails().first()->setReservation(false);
            rail->getLastRails().first()->getNextLight()->setToggle(ControlLight::STATE_RED);
            switchMap->removeSwitchReservation(rail->getRailID(), ControlTrain::DIRECTION_REVERSE);
            break;
        case ControlTrain::DIRECTION_REVERSE:
            rail = rails.value(railID);
            rail->getNextRails().first()->setReservation(false);
            rail->getNextRails().first()->getLastLight()->setToggle(ControlLight::STATE_RED);
            switchMap->removeSwitchReservation(rail->getRailID(), ControlTrain::DIRECTION_FORWARD);
            break;
        }
    }
}

void ControlAiViewModel::trainLeaving(ControlTrain::TrainID trainID, ControlRail::RailID railID)
{
    if (aiIsEnabled) {
        manageTrainSpeed(trainID, LEAVING);
    }
}

void ControlAiViewModel::trainLeft(ControlTrain::TrainID trainID, ControlRail::RailID railID)
{
    if (aiIsEnabled) {
        ControlRail *rail;
        switch (timetables.value(trainID)->getDirection()) {
        case ControlTrain::DIRECTION_FORWARD:
            rail = rails.value(railID);
            rail->setReservation(false);
            rail->getNextLight()->setToggle(ControlLight::STATE_RED);
            rail->getNextRails().first()->getNextLight()->setToggle(ControlLight::STATE_GREEN);
            switchMap->removeSwitchReservation(rail->getRailID(), ControlTrain::DIRECTION_FORWARD);
            break;
        case ControlTrain::DIRECTION_REVERSE:
            rail = rails.value(railID);
            rail->setReservation(false);
            rail->getLastLight()->setToggle(ControlLight::STATE_RED);
            rail->getLastRails().first()->getLastLight()->setToggle(ControlLight::STATE_GREEN);
            switchMap->removeSwitchReservation(rail->getRailID(), ControlTrain::DIRECTION_REVERSE);
            break;
        }
    }
}

void ControlAiViewModel::stopSensorActivated(ControlTrain::TrainID trainID, ControlRail::RailID railID)
{
    if (aiIsEnabled) {
        timetable = timetables.value(trainID);
        timetable->setCurrentRailID(railID);
        timetable->increaseLoopCounter();
        stopTrains.insert(trains.value(trainID)->getTrainPriority(), trainID);
    } else {
//        supportManualDriving(trainID, railID);
    }
}
