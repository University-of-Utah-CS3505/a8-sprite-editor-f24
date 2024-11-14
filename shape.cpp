#include "shape.h"

/**
 *  Team Name : Sam's Club
 *
 *  Team Members : Rohith Veeramachaneni, Shu Chen, Bingkun Han and PING-HSUN HSIEH
 *
 *  Contributor's Names of shape.cpp :Shu Chen, PING-HSUN HSIEH
 *
 *  Date Modified : November 10, 2024
 *
 *  Shape class that has an enum that specifies all the shapes that the sprite editor is able to draw
 */


Shape::Shape(enum shapeType shapeType, float size, QColor color) : shapeType(shapeType), size(size), color(color)
{
}

// Defualt constructor that draws line with size of 1 pt and with black pencil
Shape::Shape() : shapeType(line), size(1.0f), color(Qt::black) {}
