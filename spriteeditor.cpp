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


    //Connect ui singal to model slot
    connect(ui->canvasLabel, &CanvasLabel::sendMouseEvent, &model, &Model::receiveMouseEvent);
    connect(ui->addFrameButton, &QPushButton::pressed, &model, &Model::addNewFrameAtCurrentFrame);
    connect(ui->removeFrameButton, &QPushButton::pressed, &model, &Model::removeCurrentFrame);
    connect(ui->cloneFrameButton, &QPushButton::pressed, &model, &Model::cloneCurrentFrame);


    //Connect ui signal to self slot
    connect(ui->addFrameButton, &QPushButton::pressed, this, &SpriteEditor::addFrame);
    connect(ui->removeFrameButton, &QPushButton::pressed, this, &SpriteEditor::removeFrame);
    connect(ui->cloneFrameButton, &QPushButton::pressed, this, &SpriteEditor::cloneFrame);

    //Connect model signal to ui slot
    //connect(&model, &Model::display, this, &SpriteEditor::display);

    // setup the scroll area
    frameOverviewContainer = new QWidget;
    frameOverviewLayout = new QHBoxLayout(frameOverviewContainer);
    frameOverviewLayout->setAlignment(Qt::AlignHCenter);
    frameOverviewLayout->setContentsMargins(0, 0, 0, 0);
    frameOverviewLayout->setSpacing(10);  // set button spacing
    frameOverviewContainer->setLayout(frameOverviewLayout);
    ui->scrollArea->setWidget(frameOverviewContainer);

    //add a frame
    IntSignalButton *button = new IntSignalButton(0);
    setFrameButtonSelected(button);
    button->setFixedSize(75,75);
    frameSelectorButtonList.push_back(button);
    frameOverviewLayout->addWidget(button);
    connect(frameSelectorButtonList[0], &IntSignalButton::sendSelfValue, this, &SpriteEditor::selectFrame);

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
    //select
    frameIndex++;

    IntSignalButton *button = new IntSignalButton(frameIndex);
    setFrameButtonSelected(button);
    button->setFixedSize(75,75);

    if(frameIndex >= frameSelectorButtonList.size() || frameIndex < 0){
        frameSelectorButtonList.push_back(button);
        frameOverviewLayout->addWidget(button);
    }else{
        frameSelectorButtonList.insert(frameIndex, button);
        frameOverviewLayout->insertWidget(frameIndex, button);
    }


    setFrameButtonUnselected(frameSelectorButtonList[frameIndex-1]);

    updateAllChangedFrameButton();

    selectFrame(frameIndex);

    frameOverviewContainer->adjustSize();  // adjust button to center
}

void SpriteEditor::removeFrame(){
    if(frameSelectorButtonList.size() < 2) return;

    //Start to remove the button
    IntSignalButton *buttonToRemove = frameSelectorButtonList[frameIndex];
    frameOverviewLayout->removeWidget(buttonToRemove); //Note: this will only remove the button in lay out, need use delete later method to remove it
    buttonToRemove->deleteLater();
    frameSelectorButtonList.removeAt(frameIndex);

    frameIndex = std::max(0, --frameIndex);
    updateAllChangedFrameButton();
    selectFrame(frameIndex);
    frameOverviewContainer->adjustSize();


    update();
}

void SpriteEditor::cloneFrame(){
    addFrame();
    frameSelectorButtonList[frameIndex]->setIcon(frameSelectorButtonList[frameIndex-1]->icon());
}

void SpriteEditor::updateAllChangedFrameButton(){
    for(int i = frameIndex; i < frameSelectorButtonList.size(); i++){
        frameSelectorButtonList[i]->setValue(i);
        connect(frameSelectorButtonList[i], &IntSignalButton::sendSelfValue, this, &SpriteEditor::selectFrame);
    }
}

void SpriteEditor::selectFrame(int newFrameIndex){
    setFrameButtonUnselected(frameSelectorButtonList[this->frameIndex]);
    setFrameButtonSelected(frameSelectorButtonList[newFrameIndex]);

    this->frameIndex = newFrameIndex;
    emit sendSelectedFrameIndex(newFrameIndex);
}

void SpriteEditor::updateFrameSequence(const QImage& image){

}

void SpriteEditor::setFrameButtonSelected(IntSignalButton* button){
    button->setStyleSheet("QPushButton {"
                          "  border: 2px solid blue;"  // 设置2像素宽的黑色描边
                          "  border-radius: 5px;"       // 圆角半径，可选
                          "  padding: 5px;"             // 内容与边框之间的间距
                          "}");
    button->setEnabled(false);
}
void SpriteEditor::setFrameButtonUnselected(IntSignalButton* button){
    button->setStyleSheet("QPushButton {"
                          "  padding: 5px;"             // 内容与边框之间的间距
                          "}");
    button->setEnabled(true);
}



SpriteEditor::~SpriteEditor()
{
    delete ui;
}
