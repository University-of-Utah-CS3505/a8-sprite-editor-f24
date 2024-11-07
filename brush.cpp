#include "brush.h"

Brush::Brush(BrushType brushType, Shape shape): brushType(brushType), shape(shape){

}

Brush::Brush():brushType(drawBrush), shape(Shape(ellipse, 1, QColor(0,0,0))){

}


const BrushType& Brush::getBrushType() const{
    return brushType;
}

const Shape& Brush::getShape() const{
    return shape;
}

void Brush::setBrushType(const BrushType& newBrushType){
    brushType = newBrushType;
}

void Brush::setShape(const Shape& newShape){
    shape = newShape;
}
