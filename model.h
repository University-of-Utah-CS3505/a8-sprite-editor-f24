#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QImage>
#include <QPainter>
#include <qtimer.h>
#include "brush.h"
#include "brushtool.h"
#include <QColor>
#include "mousebutton.h"
#include "imagetool.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QBuffer>


/**
 * @brief The Model class
 *
 *  Team Name : Sam's Club
 *
 *  Team Members : Rohith Veeramachaneni, Shu Chen, Bingkun Han and PING-HSUN HSIEH
 *
 *  Contributor's Names of Model.h : Rohith Veeramachaneni and Shu Chen
 *
 *  Date Modified : November 10, 2024
 *
 *  Model header file is the model's header in MVP structure for the sprite editor application.Contains declaration of all fields,slots,methods
 *  for model class
 */

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
    QSize picSize;
    QPointF initialOffset;
    QPointF offset;
    QPointF mousePos;
    QPointF previousMousePos;
    QList<QImage> frameSequence;
    MouseButton userInput;
    ImageTool imageTool;

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
    void openFile(QList<QImage> &images, const QString &inputFilePath);
    void saveFile(const QList<QImage> &images, const QString &outputFilePath);

signals:
    void sendCanvasImage(const QImage& image, float scale, const QPointF& offset);
    void sendSequencePlayerImage(const QImage& image);


};

#endif // MODEL_H
