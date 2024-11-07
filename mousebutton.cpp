#include "mousebutton.h"

//this is the constructor of Mouse Button class, auto set button type, mouse position, and amout
MouseButton::MouseButton(enum buttonType btn, QPointF pos, int amount)
    : buttonType(btn), pos(pos), amount(amount)
{
}

//to get what type action this mouse button is
const enum buttonType& MouseButton::getButtonType() const{
    return buttonType;
}

//to get how many types this mouse buttons did
int MouseButton::getAmount() const{
    return amount;
}

//get where this mouse button action happened.
QPointF MouseButton::getPos() const{
    return pos;
}
