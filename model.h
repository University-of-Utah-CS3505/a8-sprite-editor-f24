#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QImage>
#include <QPainter>
#include <qtimer.h>

#include "mousebutton.h"

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);

public slots:
    void receiveMouseEvent(MouseButton button);
    void selectFrame(int frameIndex);
    void addNewFrameAtCurrentFrame();
    void removeCurrentFrame();
    void cloneCurrentFrame();

signals:
    void display(float scale, const QImage& image, const QPointF& offset);


};

#endif // MODEL_H
