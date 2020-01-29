#include "SceneView.h"
#include <QDebug>

SceneView::SceneView() : QGraphicsScene()
{

}

void SceneView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QGraphicsScene::mousePressEvent(event);
        if (focusItem()) {
            ObjectModel* object = static_cast<ObjectModel*>(focusItem());
            emit controlObjectClicked(object->getObjectType(), object->getObjectID());
        }
    }
}
