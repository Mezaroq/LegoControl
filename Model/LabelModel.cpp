#include "LabelModel.h"
#include <QDebug>

LabelModel::LabelModel(QWidget *parent) : QLabel(parent)
{

}

void LabelModel::setID(int id)
{
    this->labelID = id;
}
