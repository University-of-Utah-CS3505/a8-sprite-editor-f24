#include "brushtool.h"
#include <QPainter>

BrushTool::BrushTool() {
    end = QPointF(-100,-100);
    start = QPointF(100,100);
    dir = QPoint(0,0);
}

void BrushTool::paint(QImage& image, const MouseButton& input, const Shape& shape, const QPointF pos){


    // 创建 QPainter 对象，用于在 QImage 上绘制
    QPainter painter(&image);
    // set painter style
    painter.setPen(QPen(shape.color)); //bound color
    painter.setBrush(shape.color); //inside color
    qDebug() << QPen(shape.color);
    drawShapeOnImage(shape, pos, painter);
}

void BrushTool::dragShape(QImage& image, const MouseButton& input, const Shape& shape, const QPointF pos){

    if(input.getButtonType()==leftButtonDown){
        start = pos;
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

void BrushTool::erase(QImage& image, const MouseButton& input, const Shape& shape, const QPointF pos){
    // 创建 QPainter 对象，用于在 QImage 上绘制
    QPainter painter(&image);
    // set painter style
    painter.setCompositionMode(QPainter::CompositionMode_Clear);
    drawShapeOnImage(shape, pos, painter);
}



void BrushTool::drawShapeOnImage(const Shape& shape, const QPointF pos, QPainter& painter) {



    switch(shape.shapeType){
        case shapeType::line:
            start = pos;
            dir = start - end;
            // get line that vertical with dir
            dir = QPointF(dir.y(),dir.x());


            qDebug() << "dir" << dir;
            // divide by it's length to get unit vector
            dir /= std::sqrt(QPointF::dotProduct(dir, dir));
            painter.drawLine(pos + dir * shape.size / 2.0, pos - dir * shape.size / 2.0);
            end = start;
            break;
        case shapeType::rect:
            qDebug() << "a";
            painter.drawRect(pos.x() - shape.size, pos.y() - shape.size, shape.size, shape.size);
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

    //painter.drawEllipse(pos, 1, 1); // (center, radiusX, radiusY)
    //qDebug() << "pos" << pos;
    //emit display(scale, frameSequence[0], offset + initialOffset);
}

