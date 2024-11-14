#include "intsignalbutton.h"


/**
 *
 *  Team Name : Sam's Club
 *
 *  Team Members : Rohith Veeramachaneni, Shu Chen, Bingkun Han and PING-HSUN HSIEH
 *
 *  Contributor's Names of intSignalButton.h : TO BE UPDATED
 *
 *  Date Modified : November 10, 2024
 *
 *  IntSignalButton class has two methods pushed and setValue where pushed method emits
 *  signal for sending self value

*/

/**
 * @brief IntSignalButton::IntSignalButton
 * @param value value that need to be updated
 * @param parent Pointer to the parent object
 */
IntSignalButton::IntSignalButton(int value, QWidget *parent)
    : QPushButton{parent}, value(value)
{
    connect(this, &QPushButton::clicked, this, &IntSignalButton::pushed);
}

void IntSignalButton::pushed()
{
    emit sendSelfValue(value);
}

void IntSignalButton::setValue(int val)
{
    value = val;
}
