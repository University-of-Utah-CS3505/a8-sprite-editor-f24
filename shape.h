#ifndef SHAPE_H
#define SHAPE_H
#include <QColor>

enum shapeType
{
    line,
    rect,
    roundedRect,
    ellipse,
    polygon
};

class Shape
{
public:
    shapeType shapeType;
    float size;
    QColor color;
    Shape(enum shapeType shapeType, float size, QColor color);
    Shape();
};

#endif // SHAPE_H
