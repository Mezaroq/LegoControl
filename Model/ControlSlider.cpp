#include "ControlSlider.h"

ControlSlider::ControlSlider(QWidget *parent) : QSlider(parent)
{
    connect(this, SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged(int)));
}

void ControlSlider::setID(int id)
{
    this->sliderID = id;
}

void ControlSlider::setLabel(ControlLabel *label)
{
    this->label = label;
}

void ControlSlider::sliderValueChanged(int value)
{
    label->setText(QString::number(value));
}
