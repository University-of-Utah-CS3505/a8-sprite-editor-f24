#ifndef BRUSHTOOL_H
#define BRUSHTOOL_H
#include <QImage>
#include "mousebutton.h"
#include "shape.h"

class BrushTool
{
    QImage buffer;
    QPointF start;
    QPointF end;
    QPointF dir;
    ///
    /// \brief BrushTool::paint
    /// \param image canvas image
    /// \param input mouse button data
    /// \param shape shape for user currently selected
    /// \param canvasScale current scale of canvas
    /// \param offset offset from center for cuttent canvas
    /// \param painter set color of painter
    ///
    void drawShapeOnImage(const Shape& shape, const QPointF pos, QPainter& painter);

    void dragShapeOnImage(const Shape& shape, const QPointF startPos, const QPointF endPos, QPainter& painter);

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
    void paint(QImage& image, const MouseButton& input, const Shape& shape, const QPointF pos);
    ///
    /// \brief BrushTool::paint
    /// \param image canvas image
    /// \param input mouse button data
    /// \param shape shape for user currently selected
    /// \param canvasScale current scale of canvas
    /// \param offset offset from center for cuttent canvas
    ///
    void dragShape(QImage& image, const MouseButton& input, const Shape& shape, const QPointF pos);
    ///
    /// \brief BrushTool::paint
    /// \param image canvas image
    /// \param input mouse button data
    /// \param shape shape for user currently selected
    /// \param canvasScale current scale of canvas
    /// \param offset offset from center for cuttent canvas
    ///
    void erase(QImage& image, const MouseButton& input, const Shape& shape, const QPointF pos);

};

#endif // BRUSHTOOL_H
