#ifndef BRUSHTOOL_H
#define BRUSHTOOL_H
#include <QImage>
#include <QPolygon>
#include <QList>
#include "mousebutton.h"
#include "shape.h"

/**
 * @brief The BrushTool class
 *
 * Team Name : Sam's Club
 *
 * Team Members : Rohith Veeramachaneni, Shu Chen, Bingkun Han and PING-HSUN HSIEH
 *
 * Contributor's Names of BrushTool.h : TO BE UPDATED
 *
 * Date Modified : November 10, 2024
 *
 *  Header class for BrushTool class
 */

class BrushTool
{
    QImage buffer;
    QPointF start;
    QPointF end;
    QPolygonF polygon;
    ///
    /// \brief BrushTool::paint
    /// \param image canvas image
    /// \param input mouse button data
    /// \param shape shape for user currently selected
    /// \param canvasScale current scale of canvas
    /// \param offset offset from center for cuttent canvas
    /// \param painter set color of painter
    ///
    void drawShapeOnImage(const Shape &shape, const QPointF pos, QPainter &painter);

    void dragShapeOnImage(const Shape &shape, const QPointF startPos, const QPointF endPos, QPainter &painter);

public:
    BrushTool();
    ///
    /// \brief BrushTool::paint
    /// \param image canvas image
    /// \param input mouse button data
    /// \param shape shape for user currently selected
    /// \param canvasScale current scale of canvas
    /// \param offset offset from center for cuttent canvas
    ///
    void paint(QImage &image, const MouseButton &input, const Shape &shape, const QPointF pos);
    ///
    /// \brief BrushTool::paint
    /// \param image canvas image
    /// \param input mouse button data
    /// \param shape shape for user currently selected
    /// \param canvasScale current scale of canvas
    /// \param offset offset from center for cuttent canvas
    ///
    void dragShape(QImage &image, const MouseButton &input, const Shape &shape, const QPointF pos);
    ///
    /// \brief BrushTool::paint
    /// \param image canvas image
    /// \param input mouse button data
    /// \param shape shape for user currently selected
    /// \param canvasScale current scale of canvas
    /// \param offset offset from center for cuttent canvas
    ///
    void erase(QImage &image, const MouseButton &input, const Shape &shape, const QPointF pos);
};

#endif // BRUSHTOOL_H
