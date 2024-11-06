#include "intsignalbutton.h"


IntSignalButton::IntSignalButton(int value, QWidget *parent)
    : QPushButton{parent}, value(value)
{
    connect(this, &QPushButton::clicked, this, &IntSignalButton::pushed);
}

void IntSignalButton::pushed(){
    emit sendSelfValue(value);
}


