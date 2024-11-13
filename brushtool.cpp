#include "brushtool.h"
#include <QPainter>

BrushTool::BrushTool()
{
    end = QPointF(0, 0);
    start = QPointF(0, 0);
}

void BrushTool::paint(QImage &image, const MouseButton &input, const Shape &shape, const QPointF pos)
{

    // 创建 QPainter 对象，用于在 QImage 上绘制
    QPainter painter(&image);
    // set painter style
    painter.setPen(Qt::NoPen);     // no border
    painter.setBrush(shape.color); // inside color
    // qDebug() << QPen(shape.color);
    drawShapeOnImage(shape, pos, painter);

    if (input.getButtonType() == leftButtonUp)
    {
        buffer = image;
    }
}

void BrushTool::dragShape(QImage &image, const MouseButton &input, const Shape &shape, const QPointF pos)
{

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

    if (input.getButtonType() == leftButtonUp)
    {
        buffer = image;
        polygon.clear();
        return;
    }

    if (input.getButtonType() == mouseMove)
    {
        // qDebug()<< "reDraw shape";
        image = buffer;
    }

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

void BrushTool::erase(QImage &image, const MouseButton &input, const Shape &shape, const QPointF pos)
{
    // 创建 QPainter 对象，用于在 QImage 上绘制
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
