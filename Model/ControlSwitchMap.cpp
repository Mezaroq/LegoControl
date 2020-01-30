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
                break;
            case RailModel::RAIL_SECTION_6:
                switches.value(SwitchModel::SWITCH_2)->setToggle(false);
                switches.value(SwitchModel::SWITCH_5)->setToggle(true);
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
                break;
            case RailModel::RAIL_SECTION_6:
                switches.value(SwitchModel::SWITCH_2)->setToggle(true);
                switches.value(SwitchModel::SWITCH_4)->setToggle(true);
                switches.value(SwitchModel::SWITCH_5)->setToggle(true);
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
                break;
            case RailModel::RAIL_SECTION_6:
                switches.value(SwitchModel::SWITCH_2)->setToggle(true);
                switches.value(SwitchModel::SWITCH_4)->setToggle(false);
                switches.value(SwitchModel::SWITCH_5)->setToggle(true);
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
                break;
            case RailModel::RAIL_SECTION_9:
                switches.value(SwitchModel::SWITCH_6)->setToggle(false);
                switches.value(SwitchModel::SWITCH_7)->setToggle(true);
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
                break;
            case RailModel::RAIL_SECTION_9:
                switches.value(SwitchModel::SWITCH_6)->setToggle(true);
                switches.value(SwitchModel::SWITCH_7)->setToggle(true);
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
                break;
            case RailModel::RAIL_SECTION_2:
                switches.value(SwitchModel::SWITCH_8)->setToggle(true);
                switches.value(SwitchModel::SWITCH_1)->setToggle(true);
                switches.value(SwitchModel::SWITCH_3)->setToggle(true);
                break;
            case RailModel::RAIL_SECTION_3:
                switches.value(SwitchModel::SWITCH_8)->setToggle(true);
                switches.value(SwitchModel::SWITCH_1)->setToggle(true);
                switches.value(SwitchModel::SWITCH_3)->setToggle(false);
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
                break;
            case RailModel::RAIL_SECTION_2:
                switches.value(SwitchModel::SWITCH_8)->setToggle(false);
                switches.value(SwitchModel::SWITCH_1)->setToggle(true);
                switches.value(SwitchModel::SWITCH_3)->setToggle(true);
                break;
            case RailModel::RAIL_SECTION_3:
                switches.value(SwitchModel::SWITCH_8)->setToggle(false);
                switches.value(SwitchModel::SWITCH_1)->setToggle(true);
                switches.value(SwitchModel::SWITCH_3)->setToggle(false);
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
                break;
            case RailModel::RAIL_SECTION_9:
                switches.value(SwitchModel::SWITCH_1)->setToggle(false);
                switches.value(SwitchModel::SWITCH_8)->setToggle(false);
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
                break;
            case RailModel::RAIL_SECTION_9:
                switches.value(SwitchModel::SWITCH_1)->setToggle(true);
                switches.value(SwitchModel::SWITCH_3)->setToggle(true);
                switches.value(SwitchModel::SWITCH_8)->setToggle(false);
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
                break;
            case RailModel::RAIL_SECTION_9:
                switches.value(SwitchModel::SWITCH_1)->setToggle(true);
                switches.value(SwitchModel::SWITCH_3)->setToggle(false);
                switches.value(SwitchModel::SWITCH_8)->setToggle(false);
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
                break;
            case RailModel::RAIL_SECTION_2:
                switches.value(SwitchModel::SWITCH_5)->setToggle(false);
                switches.value(SwitchModel::SWITCH_2)->setToggle(true);
                switches.value(SwitchModel::SWITCH_4)->setToggle(true);
                break;
            case RailModel::RAIL_SECTION_3:
                switches.value(SwitchModel::SWITCH_5)->setToggle(false);
                switches.value(SwitchModel::SWITCH_2)->setToggle(true);
                switches.value(SwitchModel::SWITCH_4)->setToggle(false);
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
                break;
            case RailModel::RAIL_SECTION_2:
                switches.value(SwitchModel::SWITCH_5)->setToggle(true);
                switches.value(SwitchModel::SWITCH_2)->setToggle(true);
                switches.value(SwitchModel::SWITCH_4)->setToggle(true);
                break;
            case RailModel::RAIL_SECTION_3:
                switches.value(SwitchModel::SWITCH_5)->setToggle(true);
                switches.value(SwitchModel::SWITCH_2)->setToggle(true);
                switches.value(SwitchModel::SWITCH_4)->setToggle(false);
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
                break;
            case RailModel::RAIL_SECTION_6:
                switches.value(SwitchModel::SWITCH_7)->setToggle(false);
                switches.value(SwitchModel::SWITCH_6)->setToggle(true);
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

                break;
            case RailModel::RAIL_SECTION_6:
                switches.value(SwitchModel::SWITCH_7)->setToggle(true);
                switches.value(SwitchModel::SWITCH_6)->setToggle(true);
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
