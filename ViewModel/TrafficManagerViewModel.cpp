#include "TrafficManagerViewModel.h"

TrafficManagerViewModel::TrafficManagerViewModel(QObject *parent) : QObject(parent)
{
    map = new TrafficMapModel();
}

void TrafficManagerViewModel::run()
{
    if (trafficManagerEnabled) {
        trafficManagerWaitingTrains();
    }
}

void TrafficManagerViewModel::enable()
{
    initData();
    trafficManagerEnabled = true;
}

void TrafficManagerViewModel::disable()
{
    trafficManagerEnabled = false;
    deinitData();
}

void TrafficManagerViewModel::trafficManagerWaitingTrains()
{
    for (auto train : getTrainsByPriority()) {
        timetable = timetables.value(train->getTrainID());
        if (!timetable->isWaiting()) {
            if (currentStationIsStop() && timetable->isSingleStop()) {
                train->setTrainSpeed(TrainModel::SPEED_BREAKE);
                timetable->enableWaiting();
                timetable->setSingleStop(false);
                continue;
            }

            if (nextRailFree()) {
                if (nextStationIsStop()) {
                    destinationRail = timetable->getCurrentStation()->getNextStation(timetable->getDirection())->getPlatformByTrainType(train->getTrainType());
                    if (destinationRail != nullptr) {
//                        qDebug() << "Train: " << train->getTrainID()+1 << "Z:" << timetable->getCurrentRail()->getRailID()+1 << "Do:" << destinationRail->getRailID()+1 << "(Przystanek)";
                        timetable->getCurrentStation()->getNextRail(timetable->getDirection())->setReservation(true);
                        destinationRail->setReservation(true);
                        map->setSwitch(timetable->getCurrentRail()->getRailID(), destinationRail->getRailID(), timetable->getDirection());
                        train->setTrainSpeed(TrainModel::TrainSpeed(startSpeed * timetable->getDirection()));
                        timetable->getCurrentRail()->getLight(timetable->getDirection() == TrainModel::DIRECTION_FORWARD ? RailModel::FORWARD : RailModel::REVERSE)->setToggle(LightModel::STATE_GREEN);
                        waitingTrains.removeOne(train);
                        continue;
                    }
                } else {
                    destinationRail = timetable->getCurrentStation()->getNextStation(timetable->getDirection())->getFreePlatform();
                    if (destinationRail != nullptr) {
//                        qDebug() << "Train: " << train->getTrainID()+1 << "Z:" << timetable->getCurrentRail()->getRailID()+1 << "Do:" << destinationRail->getRailID()+1 << "(Przejazd)";
                        timetable->getCurrentStation()->getNextRail(timetable->getDirection())->setReservation(true);
                        destinationRail->setReservation(true);
                        map->setSwitch(timetable->getCurrentRail()->getRailID(), destinationRail->getRailID(), timetable->getDirection());
                        train->setTrainSpeed(TrainModel::TrainSpeed(startSpeed * timetable->getDirection()));
                        timetable->getCurrentRail()->getLight(timetable->getDirection() == TrainModel::DIRECTION_FORWARD ? RailModel::FORWARD : RailModel::REVERSE)->setToggle(LightModel::STATE_GREEN);
                        waitingTrains.removeOne(train);
                        continue;
                    }
                }
            }
        }
        train->setTrainSpeed(TrainModel::SPEED_BREAKE);
    }
}

void TrafficManagerViewModel::initData()
{
    waitingTrains.clear();
    for (auto rail : rails) {
        if (rail->getTrain() != nullptr) {
            timetables.value(rail->getTrain()->getTrainID())->setCurrentRail(rail);
            timetables.value(rail->getTrain()->getTrainID())->setCurrentStation(map->getStationByRail(rail->getRailID()));
            waitingTrains.append(rail->getTrain());
        }
    }
}

void TrafficManagerViewModel::deinitData()
{
    for (auto rail : rails) {
        rail->getLight(RailModel::FORWARD)->setToggle(LightModel::STATE_RED);
        rail->getLight(RailModel::REVERSE)->setToggle(LightModel::STATE_RED);
        if (rail->getTrain() == nullptr) {
            rail->setReservation(false);
        }
    }

    for (auto train : trains) {
        train->setTrainSpeed(TrainModel::SPEED_BREAKE);
    }

    if (!breakeEnabled) {
        for (auto cswitch : switches) {
            cswitch->setToggle(false);
        }
    } else {
        breakeEnabled = false;
    }

    waitingTrains.clear();
}

bool TrafficManagerViewModel::nextRailFree()
{
    return !timetable->getCurrentStation()->getNextRail(timetable->getDirection())->isReserved();
}

bool TrafficManagerViewModel::nextStationIsStop()
{
    return timetable->getStopStations()->contains(timetable->getCurrentStation()->getNextStation(timetable->getDirection()));
}

bool TrafficManagerViewModel::currentStationIsStop()
{
    return timetable->getStopStations()->contains(timetable->getCurrentStation());
}

bool TrafficManagerViewModel::isEnabled()
{
    return trafficManagerEnabled;
}

void TrafficManagerViewModel::trafficManagerMovingTrains(TrainModel *train, TrainState trainState)
{
    if (trafficManagerEnabled) {
        if (trainState == TRAIN_ENTERS) {
            switch (train->getTrainType()) {
            case TrainModel::PASSENGER_TRAIN:
                train->setTrainSpeed(TrainModel::TrainSpeed(slowdownSpeed * train->getDirectionMultiplier()));
                break;
            case TrainModel::FREIGHT_TRAIN:
                train->setTrainSpeed(TrainModel::TrainSpeed(slowdownSpeed * train->getDirectionMultiplier()));
                break;
            }
        } else {
            switch (train->getTrainType()) {
            case TrainModel::PASSENGER_TRAIN:
                train->setTrainSpeed(TrainModel::TrainSpeed(normalSpeed * train->getDirectionMultiplier()));
                break;
            case TrainModel::FREIGHT_TRAIN:
                train->setTrainSpeed(TrainModel::TrainSpeed(normalSpeed * train->getDirectionMultiplier()));
                break;
            }
        }
    }
}

void TrafficManagerViewModel::prependTimetables()
{
    timetables.insert(TrainModel::TRAIN_1, new TrafficTimetableModel(TrainModel::TRAIN_1));
    timetables.insert(TrainModel::TRAIN_2, new TrafficTimetableModel(TrainModel::TRAIN_2));
    timetables.insert(TrainModel::TRAIN_3, new TrafficTimetableModel(TrainModel::TRAIN_3));

    timetables.value(TrainModel::TRAIN_1)->setDirection(TrainModel::DIRECTION_REVERSE);
    timetables.value(TrainModel::TRAIN_1)->setWaitingTime(TrafficTimetableModel::WAITING_5S);
    timetables.value(TrainModel::TRAIN_1)->setStopStation(stations.value(StationModel::CENTRAL_STATION));
    timetables.value(TrainModel::TRAIN_1)->setStopStation(stations.value(StationModel::NORTH_STATION));
    timetables.value(TrainModel::TRAIN_1)->setStopStation(stations.value(StationModel::SOUTH_STATION));

    timetables.value(TrainModel::TRAIN_2)->setDirection(TrainModel::DIRECTION_FORWARD);
    timetables.value(TrainModel::TRAIN_2)->setWaitingTime(TrafficTimetableModel::WAITING_10S);
    timetables.value(TrainModel::TRAIN_2)->setStopStation(stations.value(StationModel::CENTRAL_STATION));

    timetables.value(TrainModel::TRAIN_3)->setDirection(TrainModel::DIRECTION_FORWARD);
    timetables.value(TrainModel::TRAIN_3)->setWaitingTime(TrafficTimetableModel::WAITING_15S);
    timetables.value(TrainModel::TRAIN_3)->setStopStation(stations.value(StationModel::SOUTH_STATION));
    timetables.value(TrainModel::TRAIN_3)->setStopStation(stations.value(StationModel::CENTRAL_STATION));
}

void TrafficManagerViewModel::prependTrafficMap()
{
    map->setRails(rails);
    map->setStations(stations);
    map->setSwitches(switches);
}

void TrafficManagerViewModel::setRails(QMap<int, RailModel *> rails)
{
    this->rails = rails;
}

void TrafficManagerViewModel::setTrains(QMap<int, TrainModel *> trains)
{
    this->trains = trains;
}

void TrafficManagerViewModel::setStations(QMap<int, StationModel *> stations)
{
    this->stations = stations;
}

void TrafficManagerViewModel::setSwitches(QMap<int, SwitchModel *> switches)
{
    this->switches = switches;
}

void TrafficManagerViewModel::setBreake()
{
    this->breakeEnabled = true;
}

QMap<TrainModel::TrainID, TrafficTimetableModel *> *TrafficManagerViewModel::getTimetables()
{
    return &timetables;
}

int *TrafficManagerViewModel::getNormalSpeed()
{
    return &normalSpeed;
}

int *TrafficManagerViewModel::getSlowdownSpeed()
{
    return &slowdownSpeed;
}

int *TrafficManagerViewModel::getStartSpeed()
{
    return &startSpeed;
}

QMap<unsigned int, TrainModel *> TrafficManagerViewModel::getTrainsByPriority() //DONE
{
    waitingTrainsBuffor.clear();
    for (auto train : waitingTrains) {
        waitingTrainsBuffor.insert(TrainModel::PRIORITY_MAX - train->getTrainPriority(), train);
    }
    return waitingTrainsBuffor;
}

void TrafficManagerViewModel::trainEnter(TrainModel *train, RailModel *rail)
{
    if (trafficManagerEnabled) {
        RailModel::TrainMove direction = train->getDirectionMultiplier() == TrainModel::DIRECTION_FORWARD ? RailModel::FORWARD : RailModel::REVERSE;
        rail->getRails(direction ? RailModel::FORWARD : RailModel::REVERSE).first()->getLight(direction)->setToggle(LightModel::STATE_RED);
    }
}

void TrafficManagerViewModel::trainLeave(TrainModel *train, RailModel *rail)
{
    if (trafficManagerEnabled) {
        timetables.value(train->getTrainID())->setSingleStop(true);
        RailModel::TrainMove direction = train->getDirectionMultiplier() == TrainModel::DIRECTION_FORWARD ? RailModel::FORWARD : RailModel::REVERSE;
        rail->getLight(direction)->setToggle(LightModel::STATE_RED);
        rail->getRails(direction).first()->getLight(direction)->setToggle(LightModel::STATE_GREEN);
    }
}

void TrafficManagerViewModel::trainEnters(TrainModel *train, RailModel *rail)
{
    trafficManagerMovingTrains(train, TRAIN_ENTERS);
}

void TrafficManagerViewModel::trainLeaves(TrainModel *train, RailModel *rail)
{
    trafficManagerMovingTrains(train, TRAIN_LEAVES);
}

void TrafficManagerViewModel::trainStop(TrainModel *train, RailModel *rail)
{
    timetables.value(train->getTrainID())->setCurrentStation(map->getStationByRail(rail->getRailID()));
    timetables.value(train->getTrainID())->setCurrentRail(rail);
    waitingTrains.append(train);
}
