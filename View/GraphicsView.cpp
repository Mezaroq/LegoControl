#include "GraphicsView.h"

GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    setMouseTracking(true);
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    if (event->button() == Qt::MiddleButton) {
        startPoint->setX(event->x());
        startPoint->setY(event->y());
    }
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
    if (event->buttons() & Qt::MiddleButton) {
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (event->x() - startPoint->x()));
        verticalScrollBar()->setValue(verticalScrollBar()->value() - (event->y() - startPoint->y()));
        startPoint->setX(event->x());
        startPoint->setY(event->y());
    }
}
