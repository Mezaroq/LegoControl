#ifndef CONTROLSTATION_H
#define CONTROLSTATION_H

#include <QObject>

class StationModel : public QObject
{
    Q_OBJECT
public:
    enum StationID{
        CENTRAL_STATION,
        NORTH_STATION,
        SOUTH_STATION
    };
    explicit StationModel(StationID stationID, QObject *parent = nullptr);

private:
    StationID stationID;

signals:

};

#endif // CONTROLSTATION_H
