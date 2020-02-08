#include "ObjectModel.h"

ObjectModel::ObjectModel(ObjectType objectType, int objectID) : QGraphicsPixmapItem()
{
    this->objectType = objectType;
    this->objectID = objectID;
    setZValue(objectType);
}

int ObjectModel::getObjectID()
{
    return objectID;
}

ObjectModel::ObjectType ObjectModel::getObjectType()
{
    return objectType;
}
