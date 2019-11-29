#ifndef CONTROLRAIL_H
#define CONTROLRAIL_H

#include <Model/ControlObject.h>

class ControlRail : public ControlObject
{
public:
    enum RailID{
        RAIL_SECTION_01,
        RAIL_SECTION_02,
        RAIL_SECTION_03,
        RAIL_SECTION_04,
        RAIL_SECTION_05,
        RAIL_SECTION_06,
        RAIL_SECTION_07,
        RAIL_SECTION_08,
        RAIL_SECTION_09,
        RAIL_SECTION_10,
        RAIL_SECTION_11
    };
    explicit ControlRail(RailID railID);
    static QString getResource(RailID railID);

private:
    RailID railID;
};

#endif // CONTROLRAIL_H
