#include "TrafficManagerPanelViewModel.h"
#include <QDebug>

TrafficManagerPanelViewModel::TrafficManagerPanelViewModel(QObject *parent) : QObject(parent)
{

}

void TrafficManagerPanelViewModel::initPanel()
{
    managerLabels.value(TrafficManagerLabelModel::NORMAL_SPEED)->setText(QString::number(*normalSpeed));
    managerLabels.value(TrafficManagerLabelModel::SLOWDOWN_SPEED)->setText(QString::number(*slowdownSpeed));
    managerLabels.value(TrafficManagerLabelModel::START_SPEED)->setText(QString::number(*startSpeed));

    managerLabels.value(TrafficManagerLabelModel::PRIORITY_TRAIN_1)->setText(QString::number(trains.value(TrainModel::TRAIN_1)->getTrainPriority()));
    managerLabels.value(TrafficManagerLabelModel::PRIORITY_TRAIN_2)->setText(QString::number(trains.value(TrainModel::TRAIN_2)->getTrainPriority()));
    managerLabels.value(TrafficManagerLabelModel::PRIORITY_TRAIN_3)->setText(QString::number(trains.value(TrainModel::TRAIN_3)->getTrainPriority()));

    managerLabels.value(TrafficManagerLabelModel::WAITING_TRAIN_1)->setText(QString::number(timetables->value(TrainModel::TRAIN_1)->getWaitingTime() / TrafficTimetableModel::WAITING_1S) + "s");
    managerLabels.value(TrafficManagerLabelModel::WAITING_TRAIN_2)->setText(QString::number(timetables->value(TrainModel::TRAIN_2)->getWaitingTime() / TrafficTimetableModel::WAITING_1S) + "s");
    managerLabels.value(TrafficManagerLabelModel::WAITING_TRAIN_3)->setText(QString::number(timetables->value(TrainModel::TRAIN_3)->getWaitingTime() / TrafficTimetableModel::WAITING_1S) + "s");

    managerButtons.value(TrafficManagerButtonModel::getButtonIndex(TrafficManagerButtonModel::BUTTON_TRAIN_1, TrafficManagerButtonModel::CENTRAL_STATION))
            ->setChecked(getStopStationSelected(stations.value(StationModel::CENTRAL_STATION), trains.value(TrainModel::TRAIN_1)));
    managerButtons.value(TrafficManagerButtonModel::getButtonIndex(TrafficManagerButtonModel::BUTTON_TRAIN_1, TrafficManagerButtonModel::NORTH_STATION))
            ->setChecked(getStopStationSelected(stations.value(StationModel::NORTH_STATION), trains.value(TrainModel::TRAIN_1)));
    managerButtons.value(TrafficManagerButtonModel::getButtonIndex(TrafficManagerButtonModel::BUTTON_TRAIN_1, TrafficManagerButtonModel::SOUTH_STATION))
            ->setChecked(getStopStationSelected(stations.value(StationModel::SOUTH_STATION), trains.value(TrainModel::TRAIN_1)));
    managerButtons.value(TrafficManagerButtonModel::getButtonIndex(TrafficManagerButtonModel::BUTTON_TRAIN_1, TrafficManagerButtonModel::DIRECTION_BUTTON))
            ->setChecked(timetables->value(TrainModel::TRAIN_1)->getDirection() == 1 ? false : true);
    managerButtons.value(TrafficManagerButtonModel::getButtonIndex(TrafficManagerButtonModel::BUTTON_TRAIN_1, TrafficManagerButtonModel::DIRECTION_BUTTON))
            ->setText(timetables->value(TrainModel::TRAIN_1)->getDirection() == 1 ? "FORWARD" : "REVERSE");
    managerButtons.value(TrafficManagerButtonModel::getButtonIndex(TrafficManagerButtonModel::BUTTON_TRAIN_1, TrafficManagerButtonModel::INVERSE_SPEED))
            ->setChecked(trains.value(TrainModel::TRAIN_1)->isInverse());

    managerButtons.value(TrafficManagerButtonModel::getButtonIndex(TrafficManagerButtonModel::BUTTON_TRAIN_2, TrafficManagerButtonModel::CENTRAL_STATION))
            ->setChecked(getStopStationSelected(stations.value(StationModel::CENTRAL_STATION), trains.value(TrainModel::TRAIN_2)));
    managerButtons.value(TrafficManagerButtonModel::getButtonIndex(TrafficManagerButtonModel::BUTTON_TRAIN_2, TrafficManagerButtonModel::NORTH_STATION))
            ->setChecked(getStopStationSelected(stations.value(StationModel::NORTH_STATION), trains.value(TrainModel::TRAIN_2)));
    managerButtons.value(TrafficManagerButtonModel::getButtonIndex(TrafficManagerButtonModel::BUTTON_TRAIN_2, TrafficManagerButtonModel::SOUTH_STATION))
            ->setChecked(getStopStationSelected(stations.value(StationModel::SOUTH_STATION), trains.value(TrainModel::TRAIN_2)));
    managerButtons.value(TrafficManagerButtonModel::getButtonIndex(TrafficManagerButtonModel::BUTTON_TRAIN_2, TrafficManagerButtonModel::DIRECTION_BUTTON))
            ->setChecked(timetables->value(TrainModel::TRAIN_2)->getDirection() == 1 ? false : true);
    managerButtons.value(TrafficManagerButtonModel::getButtonIndex(TrafficManagerButtonModel::BUTTON_TRAIN_2, TrafficManagerButtonModel::DIRECTION_BUTTON))
            ->setText(timetables->value(TrainModel::TRAIN_2)->getDirection() == 1 ? "FORWARD" : "REVERSE");
    managerButtons.value(TrafficManagerButtonModel::getButtonIndex(TrafficManagerButtonModel::BUTTON_TRAIN_2, TrafficManagerButtonModel::INVERSE_SPEED))
            ->setChecked(trains.value(TrainModel::TRAIN_2)->isInverse());

    managerButtons.value(TrafficManagerButtonModel::getButtonIndex(TrafficManagerButtonModel::BUTTON_TRAIN_3, TrafficManagerButtonModel::CENTRAL_STATION))
            ->setChecked(getStopStationSelected(stations.value(StationModel::CENTRAL_STATION), trains.value(TrainModel::TRAIN_3)));
    managerButtons.value(TrafficManagerButtonModel::getButtonIndex(TrafficManagerButtonModel::BUTTON_TRAIN_3, TrafficManagerButtonModel::NORTH_STATION))
            ->setChecked(getStopStationSelected(stations.value(StationModel::NORTH_STATION), trains.value(TrainModel::TRAIN_3)));
    managerButtons.value(TrafficManagerButtonModel::getButtonIndex(TrafficManagerButtonModel::BUTTON_TRAIN_3, TrafficManagerButtonModel::SOUTH_STATION))
            ->setChecked(getStopStationSelected(stations.value(StationModel::SOUTH_STATION), trains.value(TrainModel::TRAIN_3)));
    managerButtons.value(TrafficManagerButtonModel::getButtonIndex(TrafficManagerButtonModel::BUTTON_TRAIN_3, TrafficManagerButtonModel::DIRECTION_BUTTON))
            ->setChecked(timetables->value(TrainModel::TRAIN_3)->getDirection() == 1 ? false : true);
    managerButtons.value(TrafficManagerButtonModel::getButtonIndex(TrafficManagerButtonModel::BUTTON_TRAIN_3, TrafficManagerButtonModel::DIRECTION_BUTTON))
            ->setText(timetables->value(TrainModel::TRAIN_3)->getDirection() == 1 ? "FORWARD" : "REVERSE");
    managerButtons.value(TrafficManagerButtonModel::getButtonIndex(TrafficManagerButtonModel::BUTTON_TRAIN_3, TrafficManagerButtonModel::INVERSE_SPEED))
            ->setChecked(trains.value(TrainModel::TRAIN_3)->isInverse());
}

void TrafficManagerPanelViewModel::updatePanel()
{
    managerLabels.value(TrafficManagerLabelModel::NORMAL_SPEED)->setText(QString::number(*normalSpeed));
    managerLabels.value(TrafficManagerLabelModel::SLOWDOWN_SPEED)->setText(QString::number(*slowdownSpeed));
    managerLabels.value(TrafficManagerLabelModel::START_SPEED)->setText(QString::number(*startSpeed));

    managerLabels.value(TrafficManagerLabelModel::PRIORITY_TRAIN_1)->setText(QString::number(trains.value(TrainModel::TRAIN_1)->getTrainPriority()));
    managerLabels.value(TrafficManagerLabelModel::PRIORITY_TRAIN_2)->setText(QString::number(trains.value(TrainModel::TRAIN_2)->getTrainPriority()));
    managerLabels.value(TrafficManagerLabelModel::PRIORITY_TRAIN_3)->setText(QString::number(trains.value(TrainModel::TRAIN_3)->getTrainPriority()));

    managerLabels.value(TrafficManagerLabelModel::WAITING_TRAIN_1)->setText(QString::number(timetables->value(TrainModel::TRAIN_1)->getWaitingTime() / TrafficTimetableModel::WAITING_1S) + "s");
    managerLabels.value(TrafficManagerLabelModel::WAITING_TRAIN_2)->setText(QString::number(timetables->value(TrainModel::TRAIN_2)->getWaitingTime() / TrafficTimetableModel::WAITING_1S) + "s");
    managerLabels.value(TrafficManagerLabelModel::WAITING_TRAIN_3)->setText(QString::number(timetables->value(TrainModel::TRAIN_3)->getWaitingTime() / TrafficTimetableModel::WAITING_1S) + "s");

    managerButtons.value(TrafficManagerButtonModel::getButtonIndex(TrafficManagerButtonModel::BUTTON_TRAIN_1, TrafficManagerButtonModel::DIRECTION_BUTTON))
            ->setText(timetables->value(TrainModel::TRAIN_1)->getDirection() == 1 ? "FORWARD" : "REVERSE");
    managerButtons.value(TrafficManagerButtonModel::getButtonIndex(TrafficManagerButtonModel::BUTTON_TRAIN_2, TrafficManagerButtonModel::DIRECTION_BUTTON))
            ->setText(timetables->value(TrainModel::TRAIN_2)->getDirection() == 1 ? "FORWARD" : "REVERSE");
    managerButtons.value(TrafficManagerButtonModel::getButtonIndex(TrafficManagerButtonModel::BUTTON_TRAIN_3, TrafficManagerButtonModel::DIRECTION_BUTTON))
            ->setText(timetables->value(TrainModel::TRAIN_3)->getDirection() == 1 ? "FORWARD" : "REVERSE");
}

void TrafficManagerPanelViewModel::setTrains(QMap<int, TrainModel *> trains)
{
    this->trains = trains;
}

void TrafficManagerPanelViewModel::setStations(QMap<int, StationModel *> stations)
{
    this->stations = stations;
}

void TrafficManagerPanelViewModel::setManagerLabels(QMap<int, TrafficManagerLabelModel *> managerLabels)
{
    this->managerLabels = managerLabels;
}

void TrafficManagerPanelViewModel::setTimetables(QMap<TrainModel::TrainID, TrafficTimetableModel *> *timetables)
{
    this->timetables = timetables;
}

void TrafficManagerPanelViewModel::setNormalSpeed(int *normalSpeed)
{
    this->normalSpeed = normalSpeed;
}

void TrafficManagerPanelViewModel::setSlowdownSpeed(int *slowdownSpeed)
{
    this->slowdownSpeed = slowdownSpeed;
}

void TrafficManagerPanelViewModel::setStartSpeed(int *startSpeed)
{
    this->startSpeed = startSpeed;
}

bool TrafficManagerPanelViewModel::getStopStationSelected(StationModel *station, TrainModel *train)
{
    return timetables->value(train->getTrainID())->getStopStations()->contains(station);
}

void TrafficManagerPanelViewModel::setPriorities()
{
    priorities.clear();
    for (auto train : trains) {
        priorities.append(train->getTrainPriority());
    }
}

void TrafficManagerPanelViewModel::managerButtonClicked(TrafficManagerButtonModel::ButtonCategory buttonCategory, TrafficManagerButtonModel::ButtonType buttonType, bool toggled)
{
    switch (buttonCategory) {
    case TrafficManagerButtonModel::BUTTON_GENERAL:
        switch (buttonType) {
        case TrafficManagerButtonModel::NORMAL_SPEED_INCREASE:
            if ((*normalSpeed + 1) <= TrainModel::SPEED_FORWARD_7) {
                (*normalSpeed)++;
            }
            break;
        case TrafficManagerButtonModel::NORMAL_SPEED_DECREASE:
            if ((*normalSpeed - 1) >= TrainModel::SPEED_FORWARD_1) {
                (*normalSpeed)--;
            }
            break;
        case TrafficManagerButtonModel::SLOWDOWN_SPEED_INCREASE:
            if ((*slowdownSpeed + 1) <= TrainModel::SPEED_FORWARD_7) {
                (*slowdownSpeed)++;
            }
            break;
        case TrafficManagerButtonModel::SLOWDOWN_SPEED_DECREASE:
            if ((*slowdownSpeed - 1) >= TrainModel::SPEED_FORWARD_1) {
                (*slowdownSpeed)--;
            }
            break;
        case TrafficManagerButtonModel::START_SPEED_INCREASE:
            if ((*startSpeed + 1) <= TrainModel::SPEED_FORWARD_7) {
                (*startSpeed)++;
            }
            break;
        case TrafficManagerButtonModel::START_SPEED_DECREASE:
            if ((*startSpeed - 1) >= TrainModel::SPEED_FORWARD_1) {
                (*startSpeed)--;
            }
            break;
        default:
            break;
        }
        break;
    case TrafficManagerButtonModel::BUTTON_TRAIN_1:
        switch (buttonType) {
        case TrafficManagerButtonModel::PRIORITY_INCREASE:
            if (trains.value(TrainModel::TRAIN_1)->getTrainPriority() < TrainModel::PRIORITY_MAX) {
                setPriorities();
                for (unsigned priority = trains.value(TrainModel::TRAIN_1)->getTrainPriority() + 1; priority <= TrainModel::PRIORITY_MAX; priority++) {
                    if (!priorities.contains(priority)) {
                        trains.value(TrainModel::TRAIN_1)->setTrainPrority(priority);
                        break;
                    }
                }
            }
            break;
        case TrafficManagerButtonModel::PRIORITY_DECREASE:
            if (trains.value(TrainModel::TRAIN_1)->getTrainPriority() > TrainModel::PRIORITY_MIN) {
                setPriorities();
                for (unsigned priority = trains.value(TrainModel::TRAIN_1)->getTrainPriority() - 1; priority <= TrainModel::PRIORITY_MAX; priority--) {
                    if (!priorities.contains(priority)) {
                        trains.value(TrainModel::TRAIN_1)->setTrainPrority(priority);
                        break;
                    }
                }
            }
            break;
        case TrafficManagerButtonModel::WAITING_TIME_INCREASE:
            timetable = timetables->value(TrainModel::TRAIN_1);
            if (timetable->getWaitingTime() + TrafficTimetableModel::WAITING_5S <= TrafficTimetableModel::WAITING_30S) {
                timetable->setWaitingTime(TrafficTimetableModel::WaitingTime(timetable->getWaitingTime() + TrafficTimetableModel::WAITING_5S));
            }
            break;
        case TrafficManagerButtonModel::WAITING_TIME_DECREASE:
            timetable = timetables->value(TrainModel::TRAIN_1);
            if (timetable->getWaitingTime() - TrafficTimetableModel::WAITING_5S >= TrafficTimetableModel::WAITING_5S) {
                timetable->setWaitingTime(TrafficTimetableModel::WaitingTime(timetable->getWaitingTime() - TrafficTimetableModel::WAITING_5S));
            }
            break;
        case TrafficManagerButtonModel::CENTRAL_STATION:
            if (toggled) {
                timetables->value(TrainModel::TRAIN_1)->getStopStations()->append(stations.value(StationModel::CENTRAL_STATION));
            } else {
                timetables->value(TrainModel::TRAIN_1)->getStopStations()->removeOne(stations.value(StationModel::CENTRAL_STATION));
            }
            break;
        case TrafficManagerButtonModel::NORTH_STATION:
            if (toggled) {
                timetables->value(TrainModel::TRAIN_1)->getStopStations()->append(stations.value(StationModel::NORTH_STATION));
            } else {
                timetables->value(TrainModel::TRAIN_1)->getStopStations()->removeOne(stations.value(StationModel::NORTH_STATION));
            }
            break;
        case TrafficManagerButtonModel::SOUTH_STATION:
            if (toggled) {
                timetables->value(TrainModel::TRAIN_1)->getStopStations()->append(stations.value(StationModel::SOUTH_STATION));
            } else {
                timetables->value(TrainModel::TRAIN_1)->getStopStations()->removeOne(stations.value(StationModel::SOUTH_STATION));
            }
            break;
        case TrafficManagerButtonModel::DIRECTION_BUTTON:
            timetables->value(TrainModel::TRAIN_1)->setDirection(toggled ? TrainModel::DIRECTION_REVERSE : TrainModel::DIRECTION_FORWARD);
            break;
        case TrafficManagerButtonModel::INVERSE_SPEED:
            trains.value(TrainModel::TRAIN_1)->setInverseSpeed(toggled);
            break;
        default:
            break;
        }
        break;
    case TrafficManagerButtonModel::BUTTON_TRAIN_2:
        switch (buttonType) {
        case TrafficManagerButtonModel::PRIORITY_INCREASE:
            if (trains.value(TrainModel::TRAIN_2)->getTrainPriority() < TrainModel::PRIORITY_MAX) {
                setPriorities();
                for (unsigned priority = trains.value(TrainModel::TRAIN_2)->getTrainPriority() + 1; priority <= TrainModel::PRIORITY_MAX; priority++) {
                    if (!priorities.contains(priority)) {
                        trains.value(TrainModel::TRAIN_2)->setTrainPrority(priority);
                        break;
                    }
                }
            }
            break;
        case TrafficManagerButtonModel::PRIORITY_DECREASE:
            if (trains.value(TrainModel::TRAIN_2)->getTrainPriority() > TrainModel::PRIORITY_MIN) {
                setPriorities();
                for (unsigned priority = trains.value(TrainModel::TRAIN_2)->getTrainPriority() - 1; priority <= TrainModel::PRIORITY_MAX; priority--) {
                    if (!priorities.contains(priority)) {
                        trains.value(TrainModel::TRAIN_2)->setTrainPrority(priority);
                        break;
                    }
                }
            }
            break;
        case TrafficManagerButtonModel::WAITING_TIME_INCREASE:
            timetable = timetables->value(TrainModel::TRAIN_2);
            if (timetable->getWaitingTime() + TrafficTimetableModel::WAITING_5S <= TrafficTimetableModel::WAITING_30S) {
                timetable->setWaitingTime(TrafficTimetableModel::WaitingTime(timetable->getWaitingTime() + TrafficTimetableModel::WAITING_5S));
            }
            break;
        case TrafficManagerButtonModel::WAITING_TIME_DECREASE:
            timetable = timetables->value(TrainModel::TRAIN_2);
            if (timetable->getWaitingTime() - TrafficTimetableModel::WAITING_5S >= TrafficTimetableModel::WAITING_5S) {
                timetable->setWaitingTime(TrafficTimetableModel::WaitingTime(timetable->getWaitingTime() - TrafficTimetableModel::WAITING_5S));
            }
            break;
        case TrafficManagerButtonModel::CENTRAL_STATION:
            if (toggled) {
                timetables->value(TrainModel::TRAIN_2)->getStopStations()->append(stations.value(StationModel::CENTRAL_STATION));
            } else {
                timetables->value(TrainModel::TRAIN_2)->getStopStations()->removeOne(stations.value(StationModel::CENTRAL_STATION));
            }
            break;
        case TrafficManagerButtonModel::NORTH_STATION:
            if (toggled) {
                timetables->value(TrainModel::TRAIN_2)->getStopStations()->append(stations.value(StationModel::NORTH_STATION));
            } else {
                timetables->value(TrainModel::TRAIN_2)->getStopStations()->removeOne(stations.value(StationModel::NORTH_STATION));
            }
            break;
        case TrafficManagerButtonModel::SOUTH_STATION:
            if (toggled) {
                timetables->value(TrainModel::TRAIN_2)->getStopStations()->append(stations.value(StationModel::SOUTH_STATION));
            } else {
                timetables->value(TrainModel::TRAIN_2)->getStopStations()->removeOne(stations.value(StationModel::SOUTH_STATION));
            }
            break;
        case TrafficManagerButtonModel::DIRECTION_BUTTON:
            timetables->value(TrainModel::TRAIN_2)->setDirection(toggled ? TrainModel::DIRECTION_REVERSE : TrainModel::DIRECTION_FORWARD);
            break;
        case TrafficManagerButtonModel::INVERSE_SPEED:
            trains.value(TrainModel::TRAIN_2)->setInverseSpeed(toggled);
            break;
        default:
            break;
        }
        break;
    case TrafficManagerButtonModel::BUTTON_TRAIN_3:
        switch (buttonType) {
        case TrafficManagerButtonModel::PRIORITY_INCREASE:
            if (trains.value(TrainModel::TRAIN_3)->getTrainPriority() < TrainModel::PRIORITY_MAX) {
                setPriorities();
                for (unsigned priority = trains.value(TrainModel::TRAIN_3)->getTrainPriority() + 1; priority <= TrainModel::PRIORITY_MAX; priority++) {
                    if (!priorities.contains(priority)) {
                        trains.value(TrainModel::TRAIN_3)->setTrainPrority(priority);
                        break;
                    }
                }
            }
            break;
        case TrafficManagerButtonModel::PRIORITY_DECREASE:
            if (trains.value(TrainModel::TRAIN_3)->getTrainPriority() > TrainModel::PRIORITY_MIN) {
                setPriorities();
                for (unsigned priority = trains.value(TrainModel::TRAIN_3)->getTrainPriority() - 1; priority <= TrainModel::PRIORITY_MAX; priority--) {
                    if (!priorities.contains(priority)) {
                        trains.value(TrainModel::TRAIN_3)->setTrainPrority(priority);
                        break;
                    }
                }
            }
            break;
        case TrafficManagerButtonModel::WAITING_TIME_INCREASE:
            timetable = timetables->value(TrainModel::TRAIN_3);
            if (timetable->getWaitingTime() + TrafficTimetableModel::WAITING_5S <= TrafficTimetableModel::WAITING_30S) {
                timetable->setWaitingTime(TrafficTimetableModel::WaitingTime(timetable->getWaitingTime() + TrafficTimetableModel::WAITING_5S));
            }
            break;
        case TrafficManagerButtonModel::WAITING_TIME_DECREASE:
            timetable = timetables->value(TrainModel::TRAIN_3);
            if (timetable->getWaitingTime() - TrafficTimetableModel::WAITING_5S >= TrafficTimetableModel::WAITING_5S) {
                timetable->setWaitingTime(TrafficTimetableModel::WaitingTime(timetable->getWaitingTime() - TrafficTimetableModel::WAITING_5S));
            }
            break;
        case TrafficManagerButtonModel::CENTRAL_STATION:
            if (toggled) {
                timetables->value(TrainModel::TRAIN_3)->getStopStations()->append(stations.value(StationModel::CENTRAL_STATION));
            } else {
                timetables->value(TrainModel::TRAIN_3)->getStopStations()->removeOne(stations.value(StationModel::CENTRAL_STATION));
            }
            break;
        case TrafficManagerButtonModel::NORTH_STATION:
            if (toggled) {
                timetables->value(TrainModel::TRAIN_3)->getStopStations()->append(stations.value(StationModel::NORTH_STATION));
            } else {
                timetables->value(TrainModel::TRAIN_3)->getStopStations()->removeOne(stations.value(StationModel::NORTH_STATION));
            }
            break;
        case TrafficManagerButtonModel::SOUTH_STATION:
            if (toggled) {
                timetables->value(TrainModel::TRAIN_3)->getStopStations()->append(stations.value(StationModel::SOUTH_STATION));
            } else {
                timetables->value(TrainModel::TRAIN_3)->getStopStations()->removeOne(stations.value(StationModel::SOUTH_STATION));
            }
            break;
        case TrafficManagerButtonModel::DIRECTION_BUTTON:
            timetables->value(TrainModel::TRAIN_3)->setDirection(toggled ? TrainModel::DIRECTION_REVERSE : TrainModel::DIRECTION_FORWARD);
            break;
        case TrafficManagerButtonModel::INVERSE_SPEED:
            trains.value(TrainModel::TRAIN_3)->setInverseSpeed(toggled);
            break;
        default:
            break;
        }
        break;
    }
    updatePanel();
}

void TrafficManagerPanelViewModel::setManagerButtons(QMap<int, TrafficManagerButtonModel*> managerButtons)
{
    this->managerButtons = managerButtons;
}
