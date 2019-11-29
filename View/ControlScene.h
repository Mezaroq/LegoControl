#ifndef CONTROLSCENE_H
#define CONTROLSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <Model/ControlObject.h>

class ControlScene : public QGraphicsScene
{
    Q_OBJECT
public:
    ControlScene();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void controlObjectClicked(ControlObject::ObjectType objectType, int objectID);
};

#endif // CONTROLSCENE_H
