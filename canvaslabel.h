#ifndef CANVASLABEL_H
#define CANVASLABEL_H

#include <QPainter>
#include <QLabel>
#include <QObject>
#include "mousebutton.h"

class CanvasLabel : public QLabel
{
    Q_OBJECT
    QPointF offset;

public:
    CanvasLabel();
    explicit CanvasLabel(const QString &text, QWidget *parent = nullptr);
    explicit CanvasLabel(QWidget *parent = nullptr);
    void setOffset(const QPointF &offset);

protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

private:
    QPointF convertToLocalPosition(const QPointF &pos);

signals:
    void sendMouseEvent(MouseButton button);
};

#endif // CANVASLABEL_H
