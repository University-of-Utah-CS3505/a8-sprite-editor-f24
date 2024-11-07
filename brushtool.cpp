#include "brushtool.h"
#include <QPainter>

BrushTool::BrushTool() {}

void BrushTool::paint(QImage& image, const MouseButton& input, const Shape& shape, const float canvasScale, const QPointF& offset){
    // 创建 QPainter 对象，用于在 QImage 上绘制
    QPainter painter(&image);
    // set painter style
    painter.setPen(QPen(shape.color)); //bound color
    painter.setBrush(shape.color); //inside color
    drawShapeOnImage(input, shape, canvasScale, offset, painter);
}

void BrushTool::dragShape(QImage& image, const MouseButton& input, const Shape& shape, const float canvasScale, const QPointF& offset){

    if(input.getButtonType()==leftButtonDown){
        start = input.getPos()/canvasScale - offset/canvasScale;
        // backup the image
        buffer = image;
        return;
    }

    image = buffer;

    // 创建 QPainter 对象，用于在 QImage 上绘制
    QPainter painter(&image);
    // set painter style
    painter.setPen(QPen(shape.color)); //bound color
    painter.setBrush(shape.color); //inside color


    QPointF pos = input.getPos()/canvasScale - offset/canvasScale;
    end = pos;


    switch(shape.shapeType){
    case line:
        painter.drawLine(start, end);
        break;
    case rect:
        painter.drawRect(std::min(start.x(),end.x()), //topLeft.x
                         std::min(start.y(), end.y()),//topLeft.y
                         std::abs(start.x() - end.x()),//width
                         std::abs(start.y() - end.y())//height
                         );
        break;
    case roundedRect:
        painter.drawRoundedRect(std::min(start.x(),end.x()), //topLeft.x
                                std::min(start.y(), end.y()),//topLeft.y
                                std::abs(start.x() - end.x()),//width
                                std::abs(start.y() - end.y()),//height
                                shape.size,
                                shape.size
                         );
        break;
    case ellipse:
        painter.drawEllipse(std::min(start.x(),end.x()), //topLeft.x
                            std::min(start.y(), end.y()),//topLeft.y
                            std::abs(start.x() - end.x()),//width
                            std::abs(start.y() - end.y())//height
                            );
        break;
    case polygon:
        painter.drawEllipse(input.getPos(), shape.size / 2.0, shape.size / 2.0);
        break;
    }

    end = start;
}

void BrushTool::erase(QImage& image, const MouseButton& input, const Shape& shape, const float canvasScale, const QPointF& offset){
    // 创建 QPainter 对象，用于在 QImage 上绘制
    QPainter painter(&image);
    // set painter style
    painter.setCompositionMode(QPainter::CompositionMode_Clear);
    drawShapeOnImage(input, shape, canvasScale, offset, painter);
}


void BrushTool::drawShapeOnImage(const MouseButton& input, const Shape& shape, const float canvasScale, const QPointF& offset, QPainter& painter) {

    QPointF pos = input.getPos()/canvasScale - offset/canvasScale;
    QPointF dir;

    switch(shape.shapeType){
        case line:
            start = input.getPos();
            dir = start - end;
            // get line that vertical with dir
            dir = QPointF(dir.y(),dir.x());
            // divide by it's length to get unit vector
            dir /= std::sqrt(QPointF::dotProduct(dir, dir));
            painter.drawLine(input.getPos() + dir * shape.size / 2.0, input.getPos() - dir * shape.size / 2.0);
            end = start;
            break;
        case rect:
            painter.drawRect(input.getPos().x(), input.getPos().y(), shape.size, shape.size);
            break;
        case roundedRect:
            painter.drawRoundedRect(input.getPos().x(), input.getPos().y(), shape.size, shape.size, shape.size / 2.0, shape.size / 2.0);
            break;
        case ellipse:
            painter.drawEllipse(input.getPos(), shape.size / 2.0, shape.size / 2.0);
            break;
        case polygon:
            painter.drawEllipse(input.getPos(), shape.size / 2.0, shape.size / 2.0);
            break;
    }

    //painter.drawEllipse(pos, 1, 1); // (center, radiusX, radiusY)
    //qDebug() << "pos" << pos;
    //emit display(scale, frameSequence[0], offset + initialOffset);
}

