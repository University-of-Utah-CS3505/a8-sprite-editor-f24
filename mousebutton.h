#ifndef MOUSEBUTTON_H
#define MOUSEBUTTON_H
#include <QMouseEvent>

enum buttonType{
    leftButtonUp,
    leftButtonDown,
    rightButtonDown,
    rightButtonUp,
    middleButtonScroll,
    mouseMove
};

class mouseButton
{
    buttonType buttonType;
    QPointF pos;
    int amount;
public:
    mouseButton(enum buttonType btn, QPointF pos, int amount);
    const enum buttonType& getButtonType();
    int getAmount();
    QPointF getPos();
};

#endif // MOUSEBUTTON_H
