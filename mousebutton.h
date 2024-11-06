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

class MouseButton
{
    buttonType buttonType;
    QPointF pos;
    int amount;
public:
    MouseButton(enum buttonType btn, QPointF pos, int amount);
    const enum buttonType& getButtonType() const;
    int getAmount() const;
    QPointF getPos() const;
};

#endif // MOUSEBUTTON_H
