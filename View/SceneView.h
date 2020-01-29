#ifndef CONTROLSCENE_H
#define CONTROLSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <Model/ObjectModel.h>

class SceneView : public QGraphicsScene
{
    Q_OBJECT
public:
    SceneView();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void controlObjectClicked(ObjectModel::ObjectType objectType, int objectID);
};

#endif // CONTROLSCENE_H
