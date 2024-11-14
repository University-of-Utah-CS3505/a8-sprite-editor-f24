#include "brush.h"

/**
 * @brief The Brush class
 *
 * Team Name : Sam's Club
 *
 *  Team Members : Rohith Veeramachaneni, Shu Chen, Bingkun Han and PING-HSUN HSIEH
 *
 *  Contributor's Names of Brush.h : TO BE UPDATED
 *
 *  Date Modified : November 10, 2024
 *
 *  Brush class contains method implementations for few methods such as getBrushType,getShape,setBrushType and setShape that
 *  lets users switch between brushes and shapes by clicking relevant options in the app UI
 */

Brush::Brush(BrushType brushType, Shape shape) : brushType(brushType), shape(shape)
{
}

Brush::Brush() : brushType(drawBrush), shape(Shape(ellipse, 1, QColor(0, 0, 0)))
{
}

/**
 * @brief Brush::getBrushType
 *
 *  Returns the current brush type selected
 *
 * @return current brush type currently selected
 */
const BrushType &Brush::getBrushType() const
{
    return brushType;
}

/**
 * @brief Brush::getShape
 *
 *  Returns the shape that is currently selected when shape drawing brush is selected
 * @return
 */
const Shape &Brush::getShape() const
{
    return shape;
}

/**
 * @brief Brush::setBrushType
 *
 *  Sets the brush to new selection based on user click
 * @param newBrushType new type fo brush user selected
 */
void Brush::setBrushType(const BrushType &newBrushType)
{
    brushType = newBrushType;
}

/**
 * @brief Brush::setShape
 *
 *  Sets curernt shape brush to be drawn to new shape user intends to draw
 * @param newShape new shape user want to draw in canvas
 */
void Brush::setShape(const Shape &newShape)
{
    shape = newShape;
}
