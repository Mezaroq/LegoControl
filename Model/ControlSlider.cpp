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

void ControlSlider::setControlValue()
{
    if (value() == 0)
        controlValue = 8;
    else
        controlValue = value();
}

int ControlSlider::getControlValue()
{
    return controlValue;
}

void ControlSlider::sliderValueChanged(int value)
{
    label->setText(QString::number(value));
    setControlValue();
}
