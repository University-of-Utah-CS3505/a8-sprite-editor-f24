#ifndef BRUSH_H
#define BRUSH_H
#include "shape.h"

enum BrushType
{
    drawBrush,
    eraseBrush,
    shapeBrush
};

/**
 * @brief The Brush class
 *
 * Team Name : Sam's Club
 *
 *  Team Members : Rohith Veeramachaneni, Shu Chen, Bingkun Han and PING-HSUN HSIEH
 *
 *  Contributor's Names of Brush.h : Shu Chen
 *
 *  Date Modified : November 10, 2024
 *
 *  Header file for Brush class containing method declarations
 *
 */


class Brush
{
    BrushType brushType;
    Shape shape;

public:
    Brush(BrushType brushType, Shape shape);
    Brush();
    const BrushType &getBrushType() const;
    const Shape &getShape() const;
    void setBrushType(const BrushType &newBrushType);
    void setShape(const Shape &newShape);
};

#endif // BRUSH_H
