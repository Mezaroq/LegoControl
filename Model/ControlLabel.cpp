#include "ControlLabel.h"
#include <QDebug>

ControlLabel::ControlLabel(QWidget *parent) : QLabel(parent)
{

}

void ControlLabel::setID(qint32 id)
{
    this->ID = id;
}
