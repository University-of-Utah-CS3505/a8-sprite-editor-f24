#include "canvaslabel.h"

canvasLabel::canvasLabel() {}

canvasLabel::canvasLabel(const QString &text, QWidget *parent): QLabel(text, parent){

}

canvasLabel::canvasLabel(QWidget *parent): QLabel("", parent){

}


void canvasLabel::paintEvent(QPaintEvent *event) {
    QLabel::paintEvent(event);
    QPainter painter(this);
    painter.drawPixmap(offset, this->pixmap());
}


void canvasLabel::setOffset(const QPointF& offset){
    this->offset = offset;
}

void canvasLabel::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
        emit sendMouseEvent(mouseButton(leftButtonDown, convertToLocalPosition(event->pos()), 1));
    }else if(event->button() == Qt::RightButton){
        emit sendMouseEvent(mouseButton(rightButtonDown, convertToLocalPosition(event->pos()), 1));
    }
    QLabel::mousePressEvent(event); // 保持原始事件行为
}

void canvasLabel::mouseMoveEvent(QMouseEvent* event){
    emit sendMouseEvent(mouseButton(mouseMove, convertToLocalPosition(event->pos()), 1));
}

void canvasLabel::mouseReleaseEvent(QMouseEvent* event){
    if (event->button() == Qt::LeftButton) {
        emit sendMouseEvent(mouseButton(leftButtonUp, convertToLocalPosition(event->pos()), 1));
    }else if(event->button() == Qt::RightButton){
        emit sendMouseEvent(mouseButton(rightButtonUp, convertToLocalPosition(event->pos()), 1));
    }
}

void canvasLabel::wheelEvent(QWheelEvent* event){
    // 获取滚动的角度
    QPointF delta = event->angleDelta();
    emit sendMouseEvent(mouseButton(middleButtonScroll, convertToLocalPosition(event->position()), delta.y()));
};


QPointF canvasLabel::convertToLocalPosition(const QPointF& pos){
    QPixmap pixmap = this->pixmap();
    if (pixmap.isNull()) return QPointF(-10000, -10000);
    // 获取 QLabel 的尺寸和 QPixmap 的实际尺寸
    QSize labelSize = this->size();
    QSize pixmapSize = pixmap.size();
    QPointF picTopLeftRelToLableTopLeft = QPointF(labelSize.width() - pixmapSize.width(),
                                                  labelSize.height() - pixmapSize.height()) / 2.0;

    return (pos - picTopLeftRelToLableTopLeft);
}
