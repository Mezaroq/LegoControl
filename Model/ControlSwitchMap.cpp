#include "ControlSwitchMap.h"
#include <QDebug>

ControlSwitchMap::ControlSwitchMap()
{

}

void ControlSwitchMap::setSwitches(QMap<int, SwitchModel *> switches)
{
    this->switches = switches;
}

void ControlSwitchMap::setRails(QMap<int, RailModel *> rails)
{
    this->rails = rails;
}

void ControlSwitchMap::removeSwitchReservation(RailModel::RailID from, TrainModel::TrainDirection direction)
{
    switch (direction) {
    case TrainModel::DIRECTION_FORWARD:
        switch (from) {
        case RailModel::RAIL_SECTION_1:
            switches.value(SwitchModel::SWITCH_2)->setReservation(false);
            break;
        case RailModel::RAIL_SECTION_2:
        case RailModel::RAIL_SECTION_3:
            switches.value(SwitchModel::SWITCH_2)->setReservation(false);
            switches.value(SwitchModel::SWITCH_4)->setReservation(false);
            break;
        case RailModel::RAIL_SECTION_5:
        case RailModel::RAIL_SECTION_6:
            switches.value(SwitchModel::SWITCH_6)->setReservation(false);
            break;
        case RailModel::RAIL_SECTION_8:
        case RailModel::RAIL_SECTION_9:
            switches.value(SwitchModel::SWITCH_8)->setReservation(false);
            break;
        default:
            break;
        }
        break;
    case TrainModel::DIRECTION_REVERSE:
        switch (from) {
        case RailModel::RAIL_SECTION_1:
            switches.value(SwitchModel::SWITCH_1)->setReservation(false);
            break;
        case RailModel::RAIL_SECTION_2:
        case RailModel::RAIL_SECTION_3:
            switches.value(SwitchModel::SWITCH_1)->setReservation(false);
            switches.value(SwitchModel::SWITCH_3)->setReservation(false);
            break;
        case RailModel::RAIL_SECTION_5:
        case RailModel::RAIL_SECTION_6:
            switches.value(SwitchModel::SWITCH_5)->setReservation(false);
            break;
        case RailModel::RAIL_SECTION_8:
        case RailModel::RAIL_SECTION_9:
            switches.value(SwitchModel::SWITCH_7)->setReservation(false);
            break;
        default:
            break;
        }
        break;
    }
}

bool ControlSwitchMap::checkSwitchesAreNotReserved(RailModel::RailID from,RailModel::RailID to, TrainModel::TrainDirection direction)
{
    switch (direction) {
    case TrainModel::DIRECTION_FORWARD:
        switch (from) {
        case RailModel::RAIL_SECTION_1:
            if (switches.value(SwitchModel::SWITCH_2)->isReserved() || switches.value(SwitchModel::SWITCH_5)->isReserved())
                return false;
            break;
        case RailModel::RAIL_SECTION_2:
        case RailModel::RAIL_SECTION_3:
            if (switches.value(SwitchModel::SWITCH_2)->isReserved() || switches.value(SwitchModel::SWITCH_4)->isReserved() || switches.value(SwitchModel::SWITCH_5)->isReserved())
                return false;
            break;
        case RailModel::RAIL_SECTION_5:
        case RailModel::RAIL_SECTION_6:
            if (switches.value(SwitchModel::SWITCH_6)->isReserved() || switches.value(SwitchModel::SWITCH_7)->isReserved())
                return false;
            break;
        case RailModel::RAIL_SECTION_8:
        case RailModel::RAIL_SECTION_9:
            if (to == RailModel::RAIL_SECTION_2 || to == RailModel::RAIL_SECTION_3)
                if (switches.value(SwitchModel::SWITCH_8)->isReserved() || switches.value(SwitchModel::SWITCH_1)->isReserved() || switches.value(SwitchModel::SWITCH_3)->isReserved())
                    return false;
            if (switches.value(SwitchModel::SWITCH_8)->isReserved() || switches.value(SwitchModel::SWITCH_1)->isReserved())
                return false;
            break;
        default:
            break;
        }
        break;
    case TrainModel::DIRECTION_REVERSE:
        switch (from) {
        case RailModel::RAIL_SECTION_1:
            if (switches.value(SwitchModel::SWITCH_1)->isReserved() || switches.value(SwitchModel::SWITCH_8)->isReserved())
                return false;
            break;
        case RailModel::RAIL_SECTION_2:
        case RailModel::RAIL_SECTION_3:
            if (switches.value(SwitchModel::SWITCH_1)->isReserved() || switches.value(SwitchModel::SWITCH_3)->isReserved() || switches.value(SwitchModel::SWITCH_8)->isReserved())
                return false;
            break;
        case RailModel::RAIL_SECTION_5:
        case RailModel::RAIL_SECTION_6:
            if (to == RailModel::RAIL_SECTION_2 || to == RailModel::RAIL_SECTION_3)
                if (switches.value(SwitchModel::SWITCH_5)->isReserved() || switches.value(SwitchModel::SWITCH_2)->isReserved() || switches.value(SwitchModel::SWITCH_4)->isReserved())
                    return false;
            if (switches.value(SwitchModel::SWITCH_5)->isReserved() || switches.value(SwitchModel::SWITCH_2)->isReserved())
                return false;
            break;
        case RailModel::RAIL_SECTION_8:
        case RailModel::RAIL_SECTION_9:
            if (switches.value(SwitchModel::SWITCH_7)->isReserved() || switches.value(SwitchModel::SWITCH_6)->isReserved())
                return false;
            break;
        default:
            break;
        }
    }

    return true;
}

void ControlSwitchMap::setSwitchReservationAndState(RailModel::RailID from, RailModel::RailID to, TrainModel::TrainDirection direction)
{
    switch (direction) {
    case TrainModel::DIRECTION_FORWARD:
        switch (from) {
        case RailModel::RAIL_SECTION_1:
            switch (to) {
            case RailModel::RAIL_SECTION_5:
                switches.value(SwitchModel::SWITCH_2)->setToggle(false);
                switches.value(SwitchModel::SWITCH_5)->setToggle(false);
                switches.value(SwitchModel::SWITCH_2)->setReservation(true);
                switches.value(SwitchModel::SWITCH_5)->setReservation(true);
                break;
            case RailModel::RAIL_SECTION_6:
                switches.value(SwitchModel::SWITCH_2)->setToggle(false);
                switches.value(SwitchModel::SWITCH_5)->setToggle(true);
                switches.value(SwitchModel::SWITCH_2)->setReservation(true);
                switches.value(SwitchModel::SWITCH_5)->setReservation(true);
                break;
            default:
                break;
            }
            break;
        case RailModel::RAIL_SECTION_2:
            switch (to) {
            case RailModel::RAIL_SECTION_5:
                switches.value(SwitchModel::SWITCH_2)->setToggle(true);
                switches.value(SwitchModel::SWITCH_4)->setToggle(true);
                switches.value(SwitchModel::SWITCH_5)->setToggle(false);
                switches.value(SwitchModel::SWITCH_2)->setReservation(true);
                switches.value(SwitchModel::SWITCH_4)->setReservation(true);
                switches.value(SwitchModel::SWITCH_5)->setReservation(true);
                break;
            case RailModel::RAIL_SECTION_6:
                switches.value(SwitchModel::SWITCH_2)->setToggle(true);
                switches.value(SwitchModel::SWITCH_4)->setToggle(true);
                switches.value(SwitchModel::SWITCH_5)->setToggle(true);
                switches.value(SwitchModel::SWITCH_2)->setReservation(true);
                switches.value(SwitchModel::SWITCH_4)->setReservation(true);
                switches.value(SwitchModel::SWITCH_5)->setReservation(true);
                break;
            default:
                break;
            }
            break;
        case RailModel::RAIL_SECTION_3:
            switch (to) {
            case RailModel::RAIL_SECTION_5:
                switches.value(SwitchModel::SWITCH_2)->setToggle(true);
                switches.value(SwitchModel::SWITCH_4)->setToggle(false);
                switches.value(SwitchModel::SWITCH_5)->setToggle(false);
                switches.value(SwitchModel::SWITCH_2)->setReservation(true);
                switches.value(SwitchModel::SWITCH_4)->setReservation(true);
                switches.value(SwitchModel::SWITCH_5)->setReservation(true);
                break;
            case RailModel::RAIL_SECTION_6:
                switches.value(SwitchModel::SWITCH_2)->setToggle(true);
                switches.value(SwitchModel::SWITCH_4)->setToggle(false);
                switches.value(SwitchModel::SWITCH_5)->setToggle(true);
                switches.value(SwitchModel::SWITCH_2)->setReservation(true);
                switches.value(SwitchModel::SWITCH_4)->setReservation(true);
                switches.value(SwitchModel::SWITCH_5)->setReservation(true);
                break;
            default:
                break;
            }
            break;
        case RailModel::RAIL_SECTION_5:
            switch (to) {
            case RailModel::RAIL_SECTION_8:
                switches.value(SwitchModel::SWITCH_6)->setToggle(false);
                switches.value(SwitchModel::SWITCH_7)->setToggle(false);
                switches.value(SwitchModel::SWITCH_6)->setReservation(true);
                switches.value(SwitchModel::SWITCH_7)->setReservation(true);
                break;
            case RailModel::RAIL_SECTION_9:
                switches.value(SwitchModel::SWITCH_6)->setToggle(false);
                switches.value(SwitchModel::SWITCH_7)->setToggle(true);
                switches.value(SwitchModel::SWITCH_6)->setReservation(true);
                switches.value(SwitchModel::SWITCH_7)->setReservation(true);
                break;
            default:
                break;
            }
            break;
        case RailModel::RAIL_SECTION_6:
            switch (to) {
            case RailModel::RAIL_SECTION_8:
                switches.value(SwitchModel::SWITCH_6)->setToggle(true);
                switches.value(SwitchModel::SWITCH_7)->setToggle(false);
                switches.value(SwitchModel::SWITCH_6)->setReservation(true);
                switches.value(SwitchModel::SWITCH_7)->setReservation(true);
                break;
            case RailModel::RAIL_SECTION_9:
                switches.value(SwitchModel::SWITCH_6)->setToggle(true);
                switches.value(SwitchModel::SWITCH_7)->setToggle(true);
                switches.value(SwitchModel::SWITCH_6)->setReservation(true);
                switches.value(SwitchModel::SWITCH_7)->setReservation(true);
                break;
            default:
                break;
            }
            break;
        case RailModel::RAIL_SECTION_8:
            switch (to) {
            case RailModel::RAIL_SECTION_1:
                switches.value(SwitchModel::SWITCH_8)->setToggle(true);
                switches.value(SwitchModel::SWITCH_1)->setToggle(false);
                switches.value(SwitchModel::SWITCH_8)->setReservation(true);
                switches.value(SwitchModel::SWITCH_1)->setReservation(true);
                break;
            case RailModel::RAIL_SECTION_2:
                switches.value(SwitchModel::SWITCH_8)->setToggle(true);
                switches.value(SwitchModel::SWITCH_1)->setToggle(true);
                switches.value(SwitchModel::SWITCH_3)->setToggle(true);
                switches.value(SwitchModel::SWITCH_8)->setReservation(true);
                switches.value(SwitchModel::SWITCH_1)->setReservation(true);
                switches.value(SwitchModel::SWITCH_3)->setReservation(true);
                break;
            case RailModel::RAIL_SECTION_3:
                switches.value(SwitchModel::SWITCH_8)->setToggle(true);
                switches.value(SwitchModel::SWITCH_1)->setToggle(true);
                switches.value(SwitchModel::SWITCH_3)->setToggle(false);
                switches.value(SwitchModel::SWITCH_8)->setReservation(true);
                switches.value(SwitchModel::SWITCH_1)->setReservation(true);
                switches.value(SwitchModel::SWITCH_3)->setReservation(true);
                break;
            default:
                break;
            }
            break;
        case RailModel::RAIL_SECTION_9:
            switch (to) {
            case RailModel::RAIL_SECTION_1:
                switches.value(SwitchModel::SWITCH_8)->setToggle(false);
                switches.value(SwitchModel::SWITCH_1)->setToggle(false);
                switches.value(SwitchModel::SWITCH_8)->setReservation(true);
                switches.value(SwitchModel::SWITCH_1)->setReservation(true);
                break;
            case RailModel::RAIL_SECTION_2:
                switches.value(SwitchModel::SWITCH_8)->setToggle(false);
                switches.value(SwitchModel::SWITCH_1)->setToggle(true);
                switches.value(SwitchModel::SWITCH_3)->setToggle(true);
                switches.value(SwitchModel::SWITCH_8)->setReservation(true);
                switches.value(SwitchModel::SWITCH_1)->setReservation(true);
                switches.value(SwitchModel::SWITCH_3)->setReservation(true);
                break;
            case RailModel::RAIL_SECTION_3:
                switches.value(SwitchModel::SWITCH_8)->setToggle(false);
                switches.value(SwitchModel::SWITCH_1)->setToggle(true);
                switches.value(SwitchModel::SWITCH_3)->setToggle(false);
                switches.value(SwitchModel::SWITCH_8)->setReservation(true);
                switches.value(SwitchModel::SWITCH_1)->setReservation(true);
                switches.value(SwitchModel::SWITCH_3)->setReservation(true);
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
        break;
    case TrainModel::DIRECTION_REVERSE:
        switch (from) {
        case RailModel::RAIL_SECTION_1:
            switch (to) {
            case RailModel::RAIL_SECTION_8:
                switches.value(SwitchModel::SWITCH_1)->setToggle(false);
                switches.value(SwitchModel::SWITCH_8)->setToggle(true);
                switches.value(SwitchModel::SWITCH_1)->setReservation(true);
                switches.value(SwitchModel::SWITCH_8)->setReservation(true);
                break;
            case RailModel::RAIL_SECTION_9:
                switches.value(SwitchModel::SWITCH_1)->setToggle(false);
                switches.value(SwitchModel::SWITCH_8)->setToggle(false);
                switches.value(SwitchModel::SWITCH_1)->setReservation(true);
                switches.value(SwitchModel::SWITCH_8)->setReservation(true);
                break;
            default:
                break;
            }
            break;
        case RailModel::RAIL_SECTION_2:
            switch (to) {
            case RailModel::RAIL_SECTION_8:
                switches.value(SwitchModel::SWITCH_1)->setToggle(true);
                switches.value(SwitchModel::SWITCH_3)->setToggle(true);
                switches.value(SwitchModel::SWITCH_8)->setToggle(true);
                switches.value(SwitchModel::SWITCH_1)->setReservation(true);
                switches.value(SwitchModel::SWITCH_3)->setReservation(true);
                switches.value(SwitchModel::SWITCH_8)->setReservation(true);
                break;
            case RailModel::RAIL_SECTION_9:
                switches.value(SwitchModel::SWITCH_1)->setToggle(true);
                switches.value(SwitchModel::SWITCH_3)->setToggle(true);
                switches.value(SwitchModel::SWITCH_8)->setToggle(false);
                switches.value(SwitchModel::SWITCH_1)->setReservation(true);
                switches.value(SwitchModel::SWITCH_3)->setReservation(true);
                switches.value(SwitchModel::SWITCH_8)->setReservation(true);
                break;
            default:
                break;
            }
            break;
        case RailModel::RAIL_SECTION_3:
            switch (to) {
            case RailModel::RAIL_SECTION_8:
                switches.value(SwitchModel::SWITCH_1)->setToggle(true);
                switches.value(SwitchModel::SWITCH_3)->setToggle(false);
                switches.value(SwitchModel::SWITCH_8)->setToggle(true);
                switches.value(SwitchModel::SWITCH_1)->setReservation(true);
                switches.value(SwitchModel::SWITCH_3)->setReservation(true);
                switches.value(SwitchModel::SWITCH_8)->setReservation(true);
                break;
            case RailModel::RAIL_SECTION_9:
                switches.value(SwitchModel::SWITCH_1)->setToggle(true);
                switches.value(SwitchModel::SWITCH_3)->setToggle(false);
                switches.value(SwitchModel::SWITCH_8)->setToggle(false);
                switches.value(SwitchModel::SWITCH_1)->setReservation(true);
                switches.value(SwitchModel::SWITCH_3)->setReservation(true);
                switches.value(SwitchModel::SWITCH_8)->setReservation(true);
                break;
            default:
                break;
            }
            break;
        case RailModel::RAIL_SECTION_5:
            switch (to) {
            case RailModel::RAIL_SECTION_1:
                switches.value(SwitchModel::SWITCH_5)->setToggle(false);
                switches.value(SwitchModel::SWITCH_2)->setToggle(false);
                switches.value(SwitchModel::SWITCH_5)->setReservation(true);
                switches.value(SwitchModel::SWITCH_2)->setReservation(true);
                break;
            case RailModel::RAIL_SECTION_2:
                switches.value(SwitchModel::SWITCH_5)->setToggle(false);
                switches.value(SwitchModel::SWITCH_2)->setToggle(true);
                switches.value(SwitchModel::SWITCH_4)->setToggle(true);
                switches.value(SwitchModel::SWITCH_5)->setReservation(true);
                switches.value(SwitchModel::SWITCH_2)->setReservation(true);
                switches.value(SwitchModel::SWITCH_4)->setReservation(true);
                break;
            case RailModel::RAIL_SECTION_3:
                switches.value(SwitchModel::SWITCH_5)->setToggle(false);
                switches.value(SwitchModel::SWITCH_2)->setToggle(true);
                switches.value(SwitchModel::SWITCH_4)->setToggle(false);
                switches.value(SwitchModel::SWITCH_5)->setReservation(true);
                switches.value(SwitchModel::SWITCH_2)->setReservation(true);
                switches.value(SwitchModel::SWITCH_4)->setReservation(true);
                break;
            default:
                break;
            }
            break;
        case RailModel::RAIL_SECTION_6:
            switch (to) {
            case RailModel::RAIL_SECTION_1:
                switches.value(SwitchModel::SWITCH_5)->setToggle(true);
                switches.value(SwitchModel::SWITCH_2)->setToggle(false);
                switches.value(SwitchModel::SWITCH_5)->setReservation(true);
                switches.value(SwitchModel::SWITCH_2)->setReservation(true);
                break;
            case RailModel::RAIL_SECTION_2:
                switches.value(SwitchModel::SWITCH_5)->setToggle(true);
                switches.value(SwitchModel::SWITCH_2)->setToggle(true);
                switches.value(SwitchModel::SWITCH_4)->setToggle(true);
                switches.value(SwitchModel::SWITCH_5)->setReservation(true);
                switches.value(SwitchModel::SWITCH_2)->setReservation(true);
                switches.value(SwitchModel::SWITCH_4)->setReservation(true);
                break;
            case RailModel::RAIL_SECTION_3:
                switches.value(SwitchModel::SWITCH_5)->setToggle(true);
                switches.value(SwitchModel::SWITCH_2)->setToggle(true);
                switches.value(SwitchModel::SWITCH_4)->setToggle(false);
                switches.value(SwitchModel::SWITCH_5)->setReservation(true);
                switches.value(SwitchModel::SWITCH_2)->setReservation(true);
                switches.value(SwitchModel::SWITCH_4)->setReservation(true);
                break;
            default:
                break;
            }
            break;
        case RailModel::RAIL_SECTION_8:
            switch (to) {
            case RailModel::RAIL_SECTION_5:
                switches.value(SwitchModel::SWITCH_7)->setToggle(false);
                switches.value(SwitchModel::SWITCH_6)->setToggle(false);
                switches.value(SwitchModel::SWITCH_7)->setReservation(true);
                switches.value(SwitchModel::SWITCH_6)->setReservation(true);
                break;
            case RailModel::RAIL_SECTION_6:
                switches.value(SwitchModel::SWITCH_7)->setToggle(false);
                switches.value(SwitchModel::SWITCH_6)->setToggle(true);
                switches.value(SwitchModel::SWITCH_7)->setReservation(true);
                switches.value(SwitchModel::SWITCH_6)->setReservation(true);
                break;
            default:
                break;
            }
            break;
        case RailModel::RAIL_SECTION_9:
            switch (to) {
            case RailModel::RAIL_SECTION_5:
                switches.value(SwitchModel::SWITCH_7)->setToggle(true);
                switches.value(SwitchModel::SWITCH_6)->setToggle(false);
                switches.value(SwitchModel::SWITCH_7)->setReservation(true);
                switches.value(SwitchModel::SWITCH_6)->setReservation(true);
                break;
            case RailModel::RAIL_SECTION_6:
                switches.value(SwitchModel::SWITCH_7)->setToggle(true);
                switches.value(SwitchModel::SWITCH_6)->setToggle(true);
                switches.value(SwitchModel::SWITCH_7)->setReservation(true);
                switches.value(SwitchModel::SWITCH_6)->setReservation(true);
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
        break;
    }
}
