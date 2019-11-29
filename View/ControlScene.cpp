#include "ControlScene.h"
#include <QDebug>

ControlScene::ControlScene() : QGraphicsScene()
{

}

void ControlScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QGraphicsScene::mousePressEvent(event);
        if (focusItem()) {
            ControlObject* object = static_cast<ControlObject*>(focusItem());
            emit controlObjectClicked(object->getObjectType(), object->getObjectID());
        }
    }
}
