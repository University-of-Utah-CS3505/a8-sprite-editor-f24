#include "mousebutton.h"

mouseButton::mouseButton(enum buttonType btn, QPointF pos, int amount)
    : buttonType(btn), pos(pos), amount(amount)
{

}

const enum buttonType& mouseButton::getButtonType(){
    return buttonType;
}

int mouseButton::getAmount(){
    return amount;
}

QPointF mouseButton::getPos(){
    return pos;
}
