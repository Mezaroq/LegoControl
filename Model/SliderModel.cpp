#include "SliderModel.h"

SliderModel::SliderModel(QWidget *parent) : QSlider(parent)
{
    connect(this, SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged(int)));
}

void SliderModel::setID(int id)
{
    this->sliderID = id;
}

void SliderModel::setLabel(LabelModel *label)
{
    this->label = label;
}

void SliderModel::sliderValueChanged(int value)
{
    label->setText(QString::number(value));
}
