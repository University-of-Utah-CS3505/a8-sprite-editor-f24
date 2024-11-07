#ifndef BRUSH_H
#define BRUSH_H
#include "shape.h"

enum BrushType{
    drawBrush,
    eraseBrush,
    shapeBrush
};

class Brush
{
    BrushType brushType;
    Shape shape;
public:
    Brush(BrushType brushType, Shape shape);
    Brush();
    const BrushType& getBrushType() const;
    const Shape& getShape() const;
    void setBrushType(const BrushType& newBrushType);
    void setShape(const Shape& newShape);
};

#endif // BRUSH_H
