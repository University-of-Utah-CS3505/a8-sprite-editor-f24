#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QImage>
#include <QPainter>
#include <qtimer.h>
#include "brush.h"

#include "mousebutton.h"

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);

public slots:
    void receiveMouseEvent(MouseButton button);
    void receiveCurrentFrame(int frameIndex);
    void addNewFrameAtCurrentFrame();
    void removeCurrentFrame();
    void cloneCurrentFrame();

    void receiveFPS(int fps);

    //Brush tool
    void receiveBrushType(Brush brush);
    //Image tool
    void rotateImage();
    void flipImageAlongY();
    void flipImageAlongX();
    void loadImage(QString imagePath);
    void fillBlankArea();
    void clearCanvas();
    //Saving
    void openFile(QString fileName);
    void saveFile(QString fileName);

signals:
    void sendCanvasImage(float scale, const QImage& image, const QPointF& offset);
    void sendSequencePlayerImage(const QImage& image);


};

#endif // MODEL_H
