#include "ControlSlider.h"

ControlSlider::ControlSlider(QWidget *parent) : QSlider(parent)
{
    connect(this, SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged(int)));
}

void ControlSlider::setID(qint32 id)
{
    this->ID = id;
}

void ControlSlider::setLabel(ControlLabel *label)
{
    this->label = label;
}

void ControlSlider::sliderValueChanged(int value)
{
    label->setText(QString::number(value));
    emit controlValueChanged(ID, value);
}
