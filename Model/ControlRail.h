#ifndef CONTROLRAIL_H
#define CONTROLRAIL_H

#include <Model/ControlObject.h>

class ControlRail : public ControlObject
{
    Q_OBJECT
public:
    enum RailID{
        RAIL_SECTION_1,
        RAIL_SECTION_2,
        RAIL_SECTION_3,
        RAIL_SECTION_4,
        RAIL_SECTION_5,
        RAIL_SECTION_6,
        RAIL_SECTION_7,
        RAIL_SECTION_8,
        RAIL_SECTION_9,
        RAIL_SECTION_10,
        RAIL_SECTION_11
    };
    explicit ControlRail(RailID railID);
    static QString getResource(RailID railID);

signals:
    void objectChanged();

private:
    RailID railID;
};

#endif // CONTROLRAIL_H
