#include "model.h"
#include <QDebug>

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
 *  Model class is the model in MVP structure for the sprite editor application.Contains slots,methods to communicate with other
 *  tool classes to draw and edit images frames in the canvas editor, play frame sequence from all the current frames.
 */

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

/**
 * @brief Model::receiveMouseEvent
 * @param button MouseButton which was recently used and passed in
 *
 *  Gets the mouseButton and then depending on the type of mouseButton such as LeftButtonUp,RightButtonDown or MouseScrollWheel and other
 *  types of mouse events
 */
void Model::receiveMouseEvent(MouseButton button){
    userInput = button;
    switch(button.getButtonType()){

        /// If the received mouse event was mouseWheelScroll, then increases scale slightly by adding button's amount
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

/**
 * @brief Model::receiveCurrentFrameIndex
 * @param frameIndex current frame index
 *
 *  Based on the given frameIndex, model changes frameIndex in current model with the frameIndex selected in the UI's form file
 */
void Model::receiveCurrentFrameIndex(int frameIndex){

    if(frameIndex >= 0 && frameIndex < frameSequence.size())
    {
        this->frameIndex = frameIndex;
        emit sendCanvasImage(frameSequence[frameIndex], scale, offset + initialOffset);
    }

    else
        qWarning() << " Invalid frame Index : " << frameIndex;
}

/**
 * @brief Model::addNewFrameAtCurrentFrame
 *
 *  Adds a new frame at current frame and then pushes the current frame at that index to the next index
 */
void Model::addNewFrameAtCurrentFrame(){

    if(frameIndex >= 0 && frameIndex < frameSequence.size())
    {
        QImage newFrame(picSize, QImage::Format_ARGB32);
        newFrame.fill(Qt::transparent);
        frameSequence.insert(frameIndex + 1, newFrame);
        emit sendCanvasImage(frameSequence[frameIndex], scale, offset + initialOffset);
    }
    // frameSequence.push_back(QImage(picSize, QImage::Format_ARGB32));
}

/**
 * @brief Model::removeCurrentFrame
 *
 *  Removes the current frame selected and moves the active frameIndex to the previous frame Index.
 *
 *  Note : This method does not remove the last frame in the frame sequence
 */

void Model::removeCurrentFrame(){

    if(frameSequence.size() > 1)
    {
        frameSequence.removeAt(frameIndex);
        frameIndex = std::max(frameIndex - 1, 0);
        emit sendCanvasImage(frameSequence[frameIndex], scale, offset + initialOffset);
    }

    else
    {
        qWarning() << " Cannot remove the last remaining frame !!";
    }

}

/**
 * @brief Model::cloneCurrentFrame
 *
 *  Clones the current frame in the seqeunce section and adds it right next to the current frame in sequence
 */
void Model::cloneCurrentFrame(){

    if(frameIndex >= 0 && frameIndex < frameSequence.size())
    {
        QImage clonedNewImageFrame = frameSequence[frameIndex].copy();
        frameSequence.insert(frameIndex + 1, clonedNewImageFrame);
        emit sendCanvasImage(frameSequence[frameIndex], scale, offset + initialOffset);
    }
}

/**
 * @brief Model::receiveFPS
 * @param fps The current fps information
 *
 *  Gives the current fps information in debug console
 */
void Model::receiveFPS(int fps){
    qDebug() << "Received FPS value : " << fps;
}

void Model::receiveBrushType(Brush brush){
    qDebug() << "brush" <<  brush.getBrushType() <<"color" << brush.getShape().color;
    this->brush = brush;
}

/**
 * @brief Model::draw
 *
 *  Draw method in the model class is one of the vital methods since it helps the user draw images or shapes on the canvas at their mouse
 *  postion with their intended color if draw mode is selected and erases the images/shapes at current location is eraser is selected and draws shape
 *  if shape drawer mode is selected
 */
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

/**
 * @brief Model::rotateImage
 *
 *  Rotates the image in the current frame if image is valid and non-null
 */
void Model::rotateImage(){

    if(frameIndex >= 0 && frameIndex < frameSequence.size())
    {
        imageTool.rotateImage(frameSequence[frameIndex]);
        emit sendCanvasImage(frameSequence[frameIndex],scale, initialOffset + offset);
    }
}

/**
 * @brief Model::flipImageAlongY
 *  Flips the image at the current frame along Y axis direction vertically if image is valid and non-null
 */
void Model::flipImageAlongY(){

    if(frameIndex >= 0 && frameIndex < frameSequence.size())
    {
        imageTool.flipImage(frameSequence[frameIndex], true);
        emit sendCanvasImage(frameSequence[frameIndex],scale, initialOffset + offset);
    }
}

/**
 * @brief Model::flipImageAlongX
 *  Flips the image in the current frame along X axis direction horizontally if image is valid and non-null
 */
void Model::flipImageAlongX(){

    if(frameIndex >= 0 && frameIndex < frameSequence.size())
    {
        imageTool.rotateImage(frameSequence[frameIndex]),false;
        emit sendCanvasImage(frameSequence[frameIndex],scale, initialOffset + offset);
    }

}

/**
 * @brief Model::loadImage
 * @param imagePath the path of the image to be loaded
 *
 *  Loads the image into the current frame based on the path given for the image
 */
void Model::loadImage(QString imagePath){

    QImage loadedImage(imagePath);

    if(!loadedImage.isNull())
    {
        loadedImage = loadedImage.scaled(picSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        frameSequence[frameIndex] = loadedImage;
        emit sendCanvasImage(frameSequence[frameIndex], scale, offset + initialOffset);
    }
    else
    {
        qWarning() << " Failed to load image from the given path !! " << imagePath;
    }
}

/**
 * @brief Model::fillBlankArea
 *
 *  Fills the current frame with blank canvas with white color
 */
void Model::fillBlankArea(){

    if(frameIndex >= 0 && frameIndex < frameSequence.size())
    {
        imageTool.fillBlankWithColor(frameSequence[frameIndex], QColor(255, 255, 255, 255));
    }

}

/**
 * @brief Model::clearCanvas
 *
 *  Clears the canvas in the current frame by making it transparent
 */
void Model::clearCanvas(){

    if(frameIndex >= 0 && frameIndex < frameSequence.size())
    {
        frameSequence[frameIndex].fill(Qt::transparent);
        emit sendCanvasImage(frameSequence[frameIndex], scale, offset + initialOffset);
    }
}

//Saving

/**
 * @brief Model::saveFile
 * @param images All the images used in the frames to be saved
 * @param outputFilePath the path where output file should be saved at
 */
void Model::saveFile(const QList<QImage> &images, const QString &outputFilePath) {
    QJsonArray jsonArray;

    /// Iterates through all list of images and saves every image in PNG format in jsonArray
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

/**
 * @brief Model::openFile
 * @param images All the images to be loaded into the frame sequences
 * @param inputFilePath The path from where the existing sprite sequence should be opened from
 */
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
