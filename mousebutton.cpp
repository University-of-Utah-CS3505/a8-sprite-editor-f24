#include "mousebutton.h"

MouseButton::MouseButton(enum buttonType btn, QPointF pos, int amount)
    : buttonType(btn), pos(pos), amount(amount)
{

}

const enum buttonType& MouseButton::getButtonType(){
    return buttonType;
}

int MouseButton::getAmount(){
    return amount;
}

QPointF MouseButton::getPos(){
    return pos;
}
