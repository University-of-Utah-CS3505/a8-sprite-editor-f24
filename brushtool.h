#ifndef BRUSHTOOL_H
#define BRUSHTOOL_H
#include <QImage>
#include "mousebutton.h"
#include "shape.h"

class BrushTool
{
public:
    BrushTool();
    void static paint(QImage& image, const MouseButton input, const Shape shape);
    void static dragShape(QImage& image, const MouseButton input, const Shape shape);
    void static erase(QImage& image, const MouseButton input, const Shape shape);
};

#endif // BRUSHTOOL_H
