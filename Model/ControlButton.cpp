#include "ControlButton.h"

ControlButton::ControlButton(QWidget *parent) : QPushButton(parent)
{

}

void ControlButton::setID(int id)
{
    this->buttonID = id;
}

void ControlButton::setSlider(ControlSlider *slider)
{
    this->slider = slider;
    connect(this, SIGNAL(clicked()), this, SLOT(buttonClicked()));
}

void ControlButton::buttonClicked()
{
    slider->setValue(0);
}
