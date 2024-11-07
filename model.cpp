#include "model.h"

Model::Model(QObject *parent)
    : QObject{parent}, userInput(MouseButton(mouseMove, QPointF(0,0), 0))
{
    drawTimer = new QTimer();
    frameIndex = 0;
    brushTool = BrushTool();
    scale = 5.0;
    offset = QPointF(0,0);
    // TODO update this
    picSize = QSize(64,64);
    inFrameScale = std::min(750.0 / picSize.width(), 750.0 / picSize.height());

    rightMouseKeyDown = false;
    leftMouseKeyDown = false;

    initialOffset = QPointF(750.0/2 - picSize.width() / 2.0 * scale ,750.0/2 - picSize.height() / 2.0 * scale);
    frameSequence.push_back(QImage(picSize, QImage::Format_ARGB32));



    connect(drawTimer, &QTimer::timeout, this, &Model::draw);
}


void Model::receiveMouseEvent(MouseButton button){
    userInput = button;
    switch(button.getButtonType()){
    case middleButtonScroll:
        //qDebug()<<button.getAmount() / 200.0;
        scale += (button.getAmount() / 200.0);
        scale = std::max(scale, 1.0f);
        if(inFrameScale > scale){
            offset = QPointF(0,0);
        }

        initialOffset = QPointF(750.0/2 - picSize.width() / 2.0 * scale ,750.0/2 - picSize.height() / 2.0 * scale);
        emit sendCanvasImage(frameSequence[frameIndex], scale, offset + initialOffset);
        break;

    case leftButtonDown:
        drawTimer->start(10);
        mousePos = button.getPos();
        leftMouseKeyDown = true;
        break;

    case mouseMove:
        mousePos = button.getPos();
        if(rightMouseKeyDown){
            if(inFrameScale < scale){
                offset += mousePos - previousMousePos;
            }

            qDebug() << "offset" << offset;
            previousMousePos = button.getPos();
            emit sendCanvasImage(frameSequence[frameIndex], scale, offset + initialOffset);
        }

        qDebug() << "pos" << mousePos/scale - offset/scale;

        break;

    case leftButtonUp:
        drawTimer->stop();
        break;

    case rightButtonDown:
        previousMousePos = button.getPos();
        mousePos = button.getPos();
        rightMouseKeyDown = true;
        qDebug()<<"right down";
        break;

    case rightButtonUp:
        rightMouseKeyDown = false;
        break;

    }
}

void Model::receiveCurrentFrameIndex(int frameIndex){

}

void Model::addNewFrameAtCurrentFrame(){
    //TODO update this
    frameSequence.push_back(QImage(picSize, QImage::Format_ARGB32));
}

void Model::removeCurrentFrame(){

}

void Model::cloneCurrentFrame(){

}

void Model::receiveFPS(int fps){

}

void Model::receiveBrushType(Brush brush){
    qDebug() << "brush" <<  brush.getBrushType() <<"color" << brush.getShape().color;
    this->brush = brush;
}

void Model::draw() {
    //calculate pos
    QPointF pos = mousePos/scale - offset/scale;
    switch(brush.getBrushType()){
    case drawBrush:
        brushTool.paint(frameSequence[frameIndex], userInput, brush.getShape(), pos);
        break;
    case eraseBrush:
        brushTool.erase(frameSequence[frameIndex], userInput, brush.getShape(), pos);
        break;
    case shapeBrush:
        brushTool.dragShape(frameSequence[frameIndex], userInput, brush.getShape(), pos);
    }

    qDebug() << "pos" << pos << "offset" << offset<< "scale"<<scale;
    emit sendCanvasImage(frameSequence[frameIndex], scale, offset + initialOffset);
}


//Image tool
void Model::rotateImage(){}
void Model::flipImageAlongY(){}
void Model::flipImageAlongX(){}
void Model::loadImage(QString imagePath){}
void Model::fillBlankArea(){}
void Model::clearCanvas(){}
//Saving
void Model::openFile(QString fileName){}
void Model::saveFile(QString fileName){}
