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
    ///
    /// \brief BrushTool::paint
    /// \param image canvas image
    /// \param input mouse button data
    /// \param shape shape for user currently selected
    /// \param canvasScale current scale of canvas
    /// \param offset offset from center for cuttent canvas
    /// \param painter set color of painter
    ///
    void drawShapeOnImage(const MouseButton& input, const Shape& shape, const float canvasScale, const QPointF& offset, QPainter& painter);

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
    void paint(QImage& image, const MouseButton& input, const Shape& shape, const float canvasScale, const QPointF& offset);
    ///
    /// \brief BrushTool::paint
    /// \param image canvas image
    /// \param input mouse button data
    /// \param shape shape for user currently selected
    /// \param canvasScale current scale of canvas
    /// \param offset offset from center for cuttent canvas
    ///
    void dragShape(QImage& image, const MouseButton& input, const Shape& shape, const float canvasScale, const QPointF& offset);
    ///
    /// \brief BrushTool::paint
    /// \param image canvas image
    /// \param input mouse button data
    /// \param shape shape for user currently selected
    /// \param canvasScale current scale of canvas
    /// \param offset offset from center for cuttent canvas
    ///
    void erase(QImage& image, const MouseButton& input, const Shape& shape, const float canvasScale, const QPointF& offset);

};

#endif // BRUSHTOOL_H
