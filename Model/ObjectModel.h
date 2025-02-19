#ifndef CONTROLOBJECT_H
#define CONTROLOBJECT_H

#include <QGraphicsPixmapItem>
#include <QObject>

class ObjectModel : public QGraphicsPixmapItem, public QObject
{
public:    
    enum ObjectType{
        OBJECT_RAIL,
        OBJECT_SWITCH,
        OBJECT_LIGHT,
    };
    ObjectModel(ObjectType objectType, int objectID);
    int getObjectID();
    ObjectType getObjectType();

private:
    ObjectType objectType;
    int objectID;
};

#endif // CONTROLOBJECT_H
