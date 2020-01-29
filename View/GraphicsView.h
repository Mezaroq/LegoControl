#ifndef CONTROLVIEW_H
#define CONTROLVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QScrollBar>

class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QWidget *parent = nullptr);

private:
    QPoint* startPoint = new QPoint();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
};

#endif // CONTROLVIEW_H
