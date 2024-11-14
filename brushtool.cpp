#include "brushtool.h"
#include <QPainter>

/**
 * @brief The BrushTool class
 *
 * Team Name : Sam's Club
 *
 * Team Members : Rohith Veeramachaneni, Shu Chen, Bingkun Han and PING-HSUN HSIEH
 *
 * Contributor's Names of BrushTool.cpp : TO BE UPDATED
 *
 * Date Modified : November 10, 2024
 *
 *  BrushTool class contains methods such as paint,dragShape,erase,drawShapeOnImage assisting user to draw some shapes on a plain
 *  canvas or draw shape on an uploaded image existing on canvas, erase unnecessary shapess or frames on canvas
 */

/**
 * @brief BrushTool::BrushTool
 *  Default constructor
 */
BrushTool::BrushTool()
{
    end = QPointF(0, 0);
    start = QPointF(0, 0);
}

/**
 * @brief BrushTool::paint
 * @param image image to be drawn on the canvas
 * @param input MouseButton input from the user
 * @param shape Shape to be drawn over the image on canvas
 * @param pos   Position to draw image at
 *
 *
 */
void BrushTool::paint(QImage &image, const MouseButton &input, const Shape &shape, const QPointF pos)
{

    // Stores a pixellated version of the image uploaded as a painter object
    QPainter painter(&image);

    // set painter style
    painter.setPen(Qt::NoPen);     // no border
    painter.setBrush(shape.color); // inside color

    drawShapeOnImage(shape, pos, painter);

    if (input.getButtonType() == leftButtonUp)
    {
        buffer = image;
    }
}

/**
 * @brief BrushTool::dragShape
 * @param image Image where the shape is being drawn
 * @param input MouseButton input event to determine action to be done
 * @param shape Shape of the object that is being drawn
 * @param pos   Position where the shape is to be drawn - the mouse position in Floating point representation
 *
 *  DragShape method is called when shape is drageed over to be drawn where this method can understnad type of action
 *  to be performed with the shape i.e : start drawing shape or end drawing or continue moving mouse to drag
 *  while holding left mouse etc..
 */
void BrushTool::dragShape(QImage &image, const MouseButton &input, const Shape &shape, const QPointF pos)
{

    ///
    /// IF mousebutton event is leftButtonDown, meaning user is holding left mouse to continue drawing, hence records the current
    /// mouse cursor position and starts drawing from there until mouse button is up when it stops recording the plane points for drawing
    if (input.getButtonType() == leftButtonDown)
    {
        qDebug() << "New shape start at" << pos;
        start = pos;
        // backup the image
        buffer = image;

        if (shape.shapeType == shapeType::polygon)
        {
            polygon = QPolygonF();
            polygon.append(pos);
        }
        return;
    }

    ///
    /// IF mousebutton event is leftButtonUp, meaning user is done drawing, hence records the current
    /// mouse cursor position as last position for the shape and ends drawing by making the buffer to be image again from where its left
    /// and clearing the polygon points

    if (input.getButtonType() == leftButtonUp)
    {
        buffer = image;
        polygon.clear();
        return;
    }

    ///
    /// If mouseButton is moving mouse, then stores the current buffer into image to keep track of the image
    if (input.getButtonType() == mouseMove)
    {

        image = buffer;
    }

    ///
    /// If mouseButton is right button down, adds a new point at the curernt mouse cursor postiion into the polygon object storing
    /// all the plane points
    ///
    if (input.getButtonType() == rightButtonDown)
    {
        polygon.append(pos);
        qDebug() << polygon;
    }

    QPainter painter(&image);
    // set painter style
    painter.setPen(Qt::NoPen);     // bound color
    painter.setBrush(shape.color); // inside color

    end = pos;

    QPen pen(shape.color);
    pen.setWidth(shape.size);

    /// draws the shape based on the shape object info available to us in the arguments
    switch (shape.shapeType)
    {
    case shapeType::line:
        painter.setPen(pen);
        painter.drawLine(start, end);
        break;
    case shapeType::rect:
        painter.drawRect(std::min(start.x(), end.x()),  // topLeft.x
                         std::min(start.y(), end.y()),  // topLeft.y
                         std::abs(start.x() - end.x()), // width
                         std::abs(start.y() - end.y())  // height
        );
        break;
    case shapeType::roundedRect:
        painter.drawRoundedRect(std::min(start.x(), end.x()),  // topLeft.x
                                std::min(start.y(), end.y()),  // topLeft.y
                                std::abs(start.x() - end.x()), // width
                                std::abs(start.y() - end.y()), // height
                                shape.size / 4.0,
                                shape.size / 4.0);
        break;
    case shapeType::ellipse:
        painter.drawEllipse(std::min(start.x(), end.x()),  // topLeft.x
                            std::min(start.y(), end.y()),  // topLeft.y
                            std::abs(start.x() - end.x()), // width
                            std::abs(start.y() - end.y())  // height
        );
        break;
    case shapeType::polygon:
        if (polygon.size() < 3)
            break;

        painter.drawPolygon(polygon);
        painter.drawEllipse(input.getPos(), shape.size / 2.0, shape.size / 2.0);
        break;
    }
}

/**
 * @brief BrushTool::erase
 * @param image Reference to the image where the shape needs to be erased
 * @param input MouseButton input event received
 * @param shape Shape type currently selected
 * @param pos   Mouse cursor position to start erasing on canvas
 *
 *  This method is called when shape or anything drawn over the canvas should be erased
 */
void BrushTool::erase(QImage &image, const MouseButton &input, const Shape &shape, const QPointF pos)
{
    /// Painter object that stores image reference
    QPainter painter(&image);
    // set painter style
    painter.setCompositionMode(QPainter::CompositionMode_Clear);
    painter.setPen(Qt::NoPen);
    painter.setBrush(shape.color);
    drawShapeOnImage(shape, pos, painter);

    if (input.getButtonType() == leftButtonUp)
    {
        buffer = image;
    }
}

/**
 * @brief BrushTool::drawShapeOnImage
 * @param shape     Shape type currently selected
 * @param pos       Position in Floating point type where shape needs to be drawn over canvas at
 * @param painter   Painter object that has the image stored
 *
 *  Draws the selected shape over the canvas at the position given in argument with the painter object given
 */
void BrushTool::drawShapeOnImage(const Shape &shape, const QPointF pos, QPainter &painter)
{

    switch (shape.shapeType)
    {
    case shapeType::line:
        painter.drawRect(pos.x() - shape.size / 2.0, pos.y() - shape.size / 2.0, shape.size, shape.size);
        break;
    case shapeType::rect:
        painter.drawRect(pos.x() - shape.size / 2.0, pos.y() - shape.size / 2.0, shape.size, shape.size);
        break;
    case shapeType::roundedRect:
        painter.drawRoundedRect(pos.x() - shape.size / 2.0, pos.y() - shape.size / 2.0,
                                shape.size, shape.size, shape.size / 4.0, shape.size / 4.0);
        break;
    case shapeType::ellipse:
        painter.drawEllipse(pos, shape.size / 2.0, shape.size / 2.0);
        break;
    case shapeType::polygon:
        painter.drawEllipse(pos, shape.size / 2.0, shape.size / 2.0);
        break;
    }
}
