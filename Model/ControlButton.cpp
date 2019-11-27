#include "ControlButton.h"

ControlButton::ControlButton(QWidget *parent) : QPushButton(parent)
{

}

void ControlButton::setID(qint32 id)
{
    this->ID = id;
}
