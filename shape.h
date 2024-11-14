#ifndef SHAPE_H
#define SHAPE_H
#include <QColor>

/**
 *  Team Name : Sam's Club
 *
 *  Team Members : Rohith Veeramachaneni, Shu Chen, Bingkun Han and PING-HSUN HSIEH
 *
 *  Contributor's Names of shape.h : Shu Chen, PING-HSUN HSIEH
 *
 *  Date Modified : November 10, 2024
 *
 *  Header class for shape class
 */

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
