#ifndef CANVASLABEL_H
#define CANVASLABEL_H

#include <QPainter>
#include <QLabel>
#include <QObject>
#include "mousebutton.h"

class canvasLabel : public QLabel
{
    Q_OBJECT
    QPointF offset;
public:
    canvasLabel();
    explicit canvasLabel(const QString &text, QWidget *parent = nullptr);
    explicit canvasLabel(QWidget *parent = nullptr);
    void setOffset(const QPointF& offset);
protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent* event) override;

    void mouseReleaseEvent(QMouseEvent* event) override;

    void wheelEvent(QWheelEvent* event) override;

    void paintEvent(QPaintEvent* event) override;

private:
    QPointF convertToLocalPosition(const QPointF& pos);

signals:
    void sendMouseEvent(mouseButton button);

};

#endif // CANVASLABEL_H
