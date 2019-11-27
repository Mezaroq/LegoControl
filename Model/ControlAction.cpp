#include "ControlAction.h"

ControlAction::ControlAction(const QIcon &icon, const QString &text, QObject *parent) : QAction(icon, text, parent)
{

}

void ControlAction::setID(qint32 id)
{
    this->ID = id;
}
