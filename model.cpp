#include "model.h"

Model::Model(QObject *parent)
    : QObject{parent}, userInput(MouseButton(mouseMove, QPointF(0,0), 0))
{
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

    QTimer::singleShot(100, [=](){
         emit sendCanvasImage(frameSequence[frameIndex], scale, offset + initialOffset);
    });
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
        mousePos = button.getPos();
        leftMouseKeyDown = true;
        draw();
        break;

    case mouseMove:
        mousePos = button.getPos();
        if(rightMouseKeyDown){
            if(inFrameScale < scale){
                offset += mousePos - previousMousePos;
            }

            //qDebug() << "offset" << offset;
            previousMousePos = button.getPos();
            emit sendCanvasImage(frameSequence[frameIndex], scale, offset + initialOffset);
        }

        if(leftMouseKeyDown){
            draw();
        }

        break;

    case leftButtonUp:
        leftMouseKeyDown = false;
        draw();
        break;

    case rightButtonDown:

        previousMousePos = button.getPos();
        mousePos = button.getPos();
        rightMouseKeyDown = true;

        if(leftMouseKeyDown){
            draw();
        }

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

    //qDebug() << "pos" << pos << "offset" << offset<< "scale"<<scale;
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
void Model::saveFile(const QList<QImage> &images, const QString &outputFilePath) {
    QJsonArray jsonArray;

    for (const QImage &image : images) {
        QByteArray byteArray;
        QBuffer buffer(&byteArray);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "PNG");  // 将 QImage 保存为 PNG 格式
        QString base64Image = QString::fromLatin1(byteArray.toBase64());  // 转为 Base64 编码字符串

        jsonArray.append(base64Image);  // 添加到 JSON 数组中
    }

    // 将 JSON 数组保存到文件
    QJsonDocument doc(jsonArray);
    QFile file(outputFilePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson(QJsonDocument::Indented));
        file.close();
    }
}

void Model::openFile(QList<QImage> &images, const QString &inputFilePath) {
    QFile file(inputFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    QJsonArray jsonArray = doc.array();

    for (const QJsonValue &value : jsonArray) {
        QByteArray byteArray = QByteArray::fromBase64(value.toString().toLatin1());
        QImage image;
        image.loadFromData(byteArray, "PNG");  // 从 Base64 编码的 QByteArray 加载 QImage

        images.append(image);
    }
}

