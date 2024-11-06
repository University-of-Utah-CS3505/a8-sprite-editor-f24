#include "spriteeditor.h"
#include "ui_spriteeditor.h"

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QImage>
#include <QGraphicsPixmapItem>


SpriteEditor::SpriteEditor(class Model& model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SpriteEditor)
{
    ui->setupUi(this);

    connect(ui->canvasLabel, &CanvasLabel::sendMouseEvent, &model, &Model::receiveMouseEvent);
    //connect(&model, &Model::display, this, &SpriteEditor::display);

    connect(ui->addFrameButton, &QPushButton::pressed, this, &SpriteEditor::addFrame);

    // setup the scroll area
    frameOverviewContainer = new QWidget;
    frameOverviewLayout = new QHBoxLayout(frameOverviewContainer);
    frameOverviewLayout->setAlignment(Qt::AlignHCenter);
    frameOverviewLayout->setContentsMargins(0, 0, 0, 0);
    frameOverviewLayout->setSpacing(10);  // set button spacing
    frameOverviewContainer->setLayout(frameOverviewLayout);
    ui->scrollArea->setWidget(frameOverviewContainer);

    //add a frame
    addFrame();


}

void SpriteEditor::display(const QImage& image, float scale, const QPointF& offset){
    // 将 QImage 转换为 QPixmap
    QPixmap pixmap = QPixmap::fromImage(image);

    // 获取缩放后的尺寸
    int width = pixmap.width() * scale;
    int height = pixmap.height() * scale;

    // 按指定比例缩放图片
    QPixmap scaledPixmap = pixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::FastTransformation);

    ui->canvasLabel->setOffset(offset);
    // 设置缩放后的图片到 QLabel 上
    ui->canvasLabel->setPixmap(scaledPixmap);

    //TODO update the picture at buttom list
}


void SpriteEditor::addFrame(){
    IntSignalButton *button = new IntSignalButton(frameIndex+1);
    button->setStyleSheet("QPushButton {"
                          "  border: 2px solid blue;"  // 设置2像素宽的黑色描边
                          "  border-radius: 5px;"       // 圆角半径，可选
                          "  padding: 5px;"             // 内容与边框之间的间距
                          "}");

    button->setFixedSize(75,75);

    if(frameIndex >= frameSelectorButtonList.size() || frameIndex < 0){
        frameSelectorButtonList.push_back(button);
        frameOverviewLayout->addWidget(button);
    }else{
        frameSelectorButtonList.insert(frameIndex + 1, button);
        frameOverviewLayout->insertWidget(frameIndex + 1, button);
    }

    if(frameSelectorButtonList.size() != 1){
        frameSelectorButtonList[frameIndex]->setStyleSheet("QPushButton {"
                                                           "  padding: 5px;"             // 内容与边框之间的间距
                                                           "}");
    }

    frameIndex++;
    for(int i = frameIndex+1; i < frameSelectorButtonList.size(); i++){
        frameSelectorButtonList[i]->setValue(i);
    }
    //TODO emit index, connect



    frameOverviewContainer->adjustSize();  // adjust button to center

}

void SpriteEditor::deleteFrame(){
    if(frameSelectorButtonList.size() < 2) return;
    frameOverviewLayout->removeWidget(frameSelectorButtonList[frameIndex]);
    frameSelectorButtonList.removeAt(frameIndex);
    frameIndex = std::max(0, --frameIndex);
    //TODO emit index, connect
    for(int i = frameIndex+1; i < frameSelectorButtonList.size(); i++){
        frameSelectorButtonList[i]->setValue(i);
    }
}

void SpriteEditor::cloneFrame(){

}

void SpriteEditor::updateFrameSequence(const QImage& image){

}


SpriteEditor::~SpriteEditor()
{
    delete ui;
}
