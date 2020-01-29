#include "ButtonModel.h"

ButtonModel::ButtonModel(QWidget *parent) : QPushButton(parent)
{

}

void ButtonModel::setID(int id)
{
    this->buttonID = id;
}

void ButtonModel::setSlider(SliderModel *slider)
{
    this->slider = slider;
    connect(this, SIGNAL(clicked()), this, SLOT(buttonClicked()));
}

void ButtonModel::buttonClicked()
{
    slider->setValue(0);
}
