#include "ControlRail.h"

ControlRail::ControlRail(RailID railID) : ControlObject(ControlObject::OBJECT_RAIL, railID)
{
    setPixmap(getResource(railID));
}

QString ControlRail::getResource(ControlRail::RailID railID)
{
    return ":/control/resources/objects/object_rail_section_" + QString::number(railID) + ".png";
}
