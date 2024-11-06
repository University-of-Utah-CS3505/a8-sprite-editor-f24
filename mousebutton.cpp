#include "mousebutton.h"

MouseButton::MouseButton(enum buttonType btn, QPointF pos, int amount)
    : buttonType(btn), pos(pos), amount(amount)
{

}

const enum buttonType& MouseButton::getButtonType() const{
    return buttonType;
}

int MouseButton::getAmount() const{
    return amount;
}

QPointF MouseButton::getPos() const{
    return pos;
}
