#include "canvaslabel.h"

CanvasLabel::CanvasLabel() {}

CanvasLabel::CanvasLabel(const QString &text, QWidget *parent): QLabel(text, parent){

}

CanvasLabel::CanvasLabel(QWidget *parent): QLabel("", parent){

}


void CanvasLabel::paintEvent(QPaintEvent *event) {
    QLabel::paintEvent(event);
    QPainter painter(this);
    painter.drawPixmap(offset, this->pixmap());
}


void CanvasLabel::setOffset(const QPointF& offset){
    this->offset = offset;
}

void CanvasLabel::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
        emit sendMouseEvent(MouseButton(leftButtonDown, convertToLocalPosition(event->pos()), 1));
    }else if(event->button() == Qt::RightButton){
        emit sendMouseEvent(MouseButton(rightButtonDown, convertToLocalPosition(event->pos()), 1));
    }
    QLabel::mousePressEvent(event); // 保持原始事件行为
}

void CanvasLabel::mouseMoveEvent(QMouseEvent* event){
    emit sendMouseEvent(MouseButton(mouseMove, convertToLocalPosition(event->pos()), 1));
}

void CanvasLabel::mouseReleaseEvent(QMouseEvent* event){
    if (event->button() == Qt::LeftButton) {
        emit sendMouseEvent(MouseButton(leftButtonUp, convertToLocalPosition(event->pos()), 1));
    }else if(event->button() == Qt::RightButton){
        emit sendMouseEvent(MouseButton(rightButtonUp, convertToLocalPosition(event->pos()), 1));
    }
}

void CanvasLabel::wheelEvent(QWheelEvent* event){
    // 获取滚动的角度
    QPointF delta = event->angleDelta();
    emit sendMouseEvent(MouseButton(middleButtonScroll, convertToLocalPosition(event->position()), delta.y()));
};


QPointF CanvasLabel::convertToLocalPosition(const QPointF& pos){
    QPixmap pixmap = this->pixmap();
    if (pixmap.isNull()) return QPointF(-10000, -10000);
    // 获取 QLabel 的尺寸和 QPixmap 的实际尺寸
    QSize labelSize = this->size();
    QSize pixmapSize = pixmap.size();
    QPointF picTopLeftRelToLableTopLeft = QPointF(labelSize.width() - pixmapSize.width(),
                                                  labelSize.height() - pixmapSize.height()) / 2.0;

    return (pos - picTopLeftRelToLableTopLeft);
}
