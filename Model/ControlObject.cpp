#include "ControlObject.h"

ControlObject::ControlObject(ObjectType objectType, int objectID) : QGraphicsPixmapItem()
{
    this->objectType = objectType;
    this->objectID = objectID;
    setZValue(objectType);
}

int ControlObject::getObjectID()
{
    return objectID;
}

ControlObject::ObjectType ControlObject::getObjectType()
{
    return objectType;
}
