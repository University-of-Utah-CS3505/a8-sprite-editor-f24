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
    Brush();
};

#endif // BRUSH_H
