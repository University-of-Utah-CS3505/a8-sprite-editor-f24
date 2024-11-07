#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QImage>
#include <QPainter>
#include <qtimer.h>
#include "brush.h"
#include "brushtool.h"

#include "mousebutton.h"

class Model : public QObject
{
    Q_OBJECT
    float scale;
    float inFrameScale;
    bool leftMouseKeyDown;
    bool rightMouseKeyDown;
    int frameIndex;
    Brush brush;
    BrushTool brushTool;
    QTimer* drawTimer;
    QSize picSize;
    QPointF initialOffset;
    QPointF offset;
    QPointF mousePos;
    QPointF previousMousePos;
    QList<QImage> frameSequence;
    MouseButton userInput;

public:
    explicit Model(QObject *parent = nullptr);

public slots:
    void receiveMouseEvent(MouseButton button);
    void receiveCurrentFrameIndex(int frameIndex);
    void addNewFrameAtCurrentFrame();
    void removeCurrentFrame();
    void cloneCurrentFrame();

    void receiveFPS(int fps);


    //Brush tool
    void receiveBrushType(Brush brush);
    void draw();
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
    void sendCanvasImage(const QImage& image, float scale, const QPointF& offset);
    void sendSequencePlayerImage(const QImage& image);


};

#endif // MODEL_H
