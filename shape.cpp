#include "shape.h"

Shape::Shape(enum shapeType shapeType, float size, QColor color) : shapeType(shapeType), size(size), color(color)
{
}

Shape::Shape() : shapeType(line), size(1.0f), color(Qt::black) {}
