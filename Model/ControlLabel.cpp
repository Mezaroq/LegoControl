#include "ControlLabel.h"
#include <QDebug>

ControlLabel::ControlLabel(QWidget *parent) : QLabel(parent)
{

}

void ControlLabel::setID(int id)
{
    this->labelID = id;
}
