#include "spriteeditor.h"
#include "ui_spriteeditor.h"

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QImage>
#include <QGraphicsPixmapItem>
#include <QColorDialog>
#include <QFileDialog>
#include "changesizerequestwindow.h"
/**
 *
 *  Team Name : Sam's Club
 *
 *  Team Members : Rohith Veeramachaneni, Shu Chen, Bingkun Han and PING-HSUN HSIEH
 *
 *  Contributor's Names of canvasLabel.h : Shu Chen, Bingkun Han
 *
 *  Date Modified : November 10, 2024
 *
 *  Header class for ImageTool.h

*/

SpriteEditor::SpriteEditor(class Model &model, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::SpriteEditor)
{
    ui->setupUi(this);

    // Setup icon

    // Default is pen tool
    lastBrushButtonSelected = ui->brushTool_PenButton;
    lastBrushButtonSelected->setEnabled(false);

    // Add shapes to comboBox
    ui->brushTool_shapeComboBox->addItem("line");
    ui->brushTool_shapeComboBox->addItem("rect");
    ui->brushTool_shapeComboBox->addItem("roundedRect");
    ui->brushTool_shapeComboBox->addItem("ellipse");
    ui->brushTool_shapeComboBox->addItem("polygon");
    ui->brushTool_shapeComboBox->setCurrentIndex(3);

    //-----------Connect ui singal to model slot------------------
    connect(ui->canvasLabel, &CanvasLabel::sendMouseEvent, &model, &Model::receiveMouseEvent);
    connect(this, &SpriteEditor::sendAddFrame, &model, &Model::addNewFrameAtCurrentFrame);
    connect(this, &SpriteEditor::sendCloneFrame, &model, &Model::cloneCurrentFrame);
    connect(this, &SpriteEditor::sendRemoveFrame, &model, &Model::removeCurrentFrame);
    connect(this, &SpriteEditor::sendBrushType, &model, &Model::receiveBrushType);
    connect(this, &SpriteEditor::sendFPS, &model, &Model::receiveFPS);
    connect(this, &SpriteEditor::sendSelectedFrameIndex, &model, &Model::receiveCurrentFrameIndex);
    // image tool
    connect(ui->imageTool_FlipAlongYButton, &QPushButton::pressed, &model, &Model::flipImageAlongY);
    connect(ui->imageTool_FlipAlongXButton, &QPushButton::pressed, &model, &Model::flipImageAlongX);
    connect(ui->imageTool_RotateButton, &QPushButton::pressed, &model, &Model::rotateImage);
    connect(this, &SpriteEditor::sendFillBlankArea, &model, &Model::fillBlankArea);
    connect(ui->imageTool_ClearCanvasButton, &QPushButton::pressed, &model, &Model::clearCanvas);
    connect(ui->imageTool_LoadImageButton, &QPushButton::pressed, this, &SpriteEditor::loadImage);
    connect(this, &SpriteEditor::sendLoadImagePath, &model, &Model::loadImage);
    connect(ui->imageTool_SetFrameSizeButton, &QPushButton::pressed, this, &SpriteEditor::callSetFrameSizeWindow);
    connect(this, &SpriteEditor::initializeModel, &model, &Model::initialize);
    connect(this, &SpriteEditor::sendSaveImagePath, &model, &Model::saveImage);
    // Save and load
    connect(this, &SpriteEditor::sendSaveFilePath, &model, &Model::saveFile);
    connect(this, &SpriteEditor::sendLoadFilePath, &model, &Model::loadFile);

    //----------Connect ui signal to self slot------------
    connect(ui->fpsSlider, &QSlider::sliderMoved, this, &SpriteEditor::setFPS);
    // frame sequence part
    connect(ui->addFrameButton, &QPushButton::pressed, this, &SpriteEditor::addFrame);
    connect(ui->removeFrameButton, &QPushButton::pressed, this, &SpriteEditor::removeFrame);
    connect(ui->cloneFrameButton, &QPushButton::pressed, this, &SpriteEditor::cloneFrame);
    // brush part
    connect(ui->brushTool_shapeComboBox, &QComboBox::activated, this, &SpriteEditor::selectShape);
    connect(ui->brushTool_PenButton, &QPushButton::pressed, this, &SpriteEditor::selectDrawBrush);
    connect(ui->brushTool_EraseButton, &QPushButton::pressed, this, &SpriteEditor::selectEraseBrush);
    connect(ui->brushTool_ShapeButton, &QPushButton::pressed, this, &SpriteEditor::selectShapeBrush);
    connect(ui->brushTool_colorSelectorButton, &QPushButton::pressed, this, &SpriteEditor::selectColor);
    connect(ui->brushTool_BrushSizeSlider, &QSlider::sliderMoved, this, &SpriteEditor::setBrushSize);
    connect(ui->brushTool_AlphaSlider, &QSlider::sliderMoved, this, &SpriteEditor::setAlpha);
    connect(ui->imageTool_FillBlankButton, &QPushButton::pressed, this, &SpriteEditor::fillBlankArea);
    connect(ui->imageTool_Export, &QPushButton::pressed, this, &SpriteEditor::saveImage);

    connect(ui->saveButton, &QPushButton::pressed, this, &SpriteEditor::saveFile);
    connect(ui->loadButton, &QPushButton::pressed, this, &SpriteEditor::loadFile);

    // Connect model signal to ui slot
    connect(&model, &Model::sendCanvasImage, this, &SpriteEditor::updateCanvas);
    connect(&model, &Model::sendAllImages, this, &SpriteEditor::receiveAllImages);
    connect(&model, &Model::sendSequencePlayerImage, this, &SpriteEditor::updateFrameSequence);

    // setup the scroll area
    frameOverviewContainer = new QWidget;
    frameOverviewLayout = new QHBoxLayout(frameOverviewContainer);
    frameOverviewLayout->setAlignment(Qt::AlignHCenter);
    frameOverviewLayout->setContentsMargins(0, 0, 0, 0);
    frameOverviewLayout->setSpacing(10); // set button spacing
    frameOverviewContainer->setLayout(frameOverviewLayout);
    ui->scrollArea->setWidget(frameOverviewContainer);

    initialize(QSize(64, 64));

    // helpMessage
    connect(ui->showHelpDocButton, &QPushButton::clicked, this, &SpriteEditor::showHelpMessage);

    // Popup window
    connect(&setFrameSizeWindow, &changeSizeRequestWindow::sendNewSize, this, &SpriteEditor::setFrameSize);
}

/**
 * @brief SpriteEditor::
 *
 *  The slot select color allows the users to select the color with which they want to draw shapes or fill the canvas with
 *
 */
void SpriteEditor::selectColor()
{
    QColor color = QColorDialog::getColor(brush.getShape().color, this, "Select Color");

    if (color.isValid())
    {
        brush.setShape(Shape(brush.getShape().shapeType, brush.getShape().size,
                             QColor(color.red(), color.green(), color.blue(), brush.getShape().color.alpha())));

        // get text color(inverse)
        QColor textColor = QColor(255 - color.red(), 255 - color.green(), 255 - color.blue());

        QString colorWithAlpha = QString("rgba(%1, %2, %3, %4)")
                                     .arg(color.red())
                                     .arg(color.green())
                                     .arg(color.blue())
                                     .arg(brush.getShape().color.alpha() / 255.0); // 透明度范围为 0.0 到 1.0

        // 将颜色应用到按钮背景和文字
        ui->brushTool_colorSelectorButton->setStyleSheet(QString("background-color: %1; color: %2;")
                                                             .arg(colorWithAlpha)
                                                             .arg(textColor.name()));
    }
    emit sendBrushType(brush);
}

/**
 * @brief SpriteEditor::loadImage
 *
 *  LoadImage slot which loads the image from the selected path
 */
void SpriteEditor::loadImage()
{
    // popup the selector window
    QString filePath = QFileDialog::getOpenFileName(
        this,                                     // parent window
        "Select the Image",                       // title
        "",                                       // default path
        "ImgFile (*.png *.jpg);;All Files (*.*)", // filter
        nullptr,                                  // default
        QFileDialog::ReadOnly                     // readonly
    );

    if (!filePath.isEmpty())
    {
        emit sendLoadImagePath(filePath);
    }
}

/**
 * @brief SpriteEditor::saveImage
 *
 *   saveImage slot which saves the image at the selected path
 */
void SpriteEditor::saveImage()
{
    // popup the selector window
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save File path"), "", tr("PNG(*.png)"));

    if (!filePath.isEmpty())
    {
        emit sendSaveImagePath(filePath);
    }
}

/**
 * @brief SpriteEditor::callSetFrameSizeWindow
 *
 *  Displays the popup window to set frame size
 */
void SpriteEditor::callSetFrameSizeWindow()
{
    setFrameSizeWindow.show();
}

/**
 * @brief SpriteEditor::setFrameSize
 * @param size the user desired canvas size
 *
 *  Lets the user set the canvas frame size to desired size
 */
void SpriteEditor::setFrameSize(const QSize &size)
{
    initialize(size);
}

/**
 * @brief SpriteEditor::initialize
 * @param size the size with which the canvas frame is to be initialised with
 *
 *  Clears the canvas frame and then resizes the canvas to user desired size
 */
void SpriteEditor::initialize(const QSize &size)
{
    removeAllFrame();

    // add a frame
    IntSignalButton *button = new IntSignalButton(0);
    setFrameButtonSelected(button);
    button->setFixedSize(75, 75);
    button->setIconSize(QSize(70, 70));
    frameSelectorButtonList.push_back(button);
    frameOverviewLayout->addWidget(button);
    connect(frameSelectorButtonList[0], &IntSignalButton::sendSelfValue, this, &SpriteEditor::selectFrame);

    frameIndex = 0;
    emit initializeModel(size);
}

/**
 * @brief SpriteEditor::removeAllFrame
 *
 *   Clears all the frames in the current project
 */
void SpriteEditor::removeAllFrame()
{
    for (auto &button : frameSelectorButtonList)
    {
        frameOverviewLayout->removeWidget(button);
        button->deleteLater();
    }
    frameSelectorButtonList.clear();
}

/**
 * @brief SpriteEditor::updateCanvas
 * @param image Reference to the image object which has to be updateds
 * @param scale The size by which canvas has to be scaled to be updated
 * @param offset new offset for the canvas after resizing
 */
void SpriteEditor::updateCanvas(const QImage &image, float scale, const QPointF &offset)
{
    // stores the current canvas in a pixmap object
    QPixmap pixmap = QPixmap::fromImage(image);

    // stores width and height properties of the current canvas frame scaled by the scaling factor
    int width = pixmap.width() * scale;
    int height = pixmap.height() * scale;

    // stores the new pixMap which is scaled version of existing pixMap
    QPixmap scaledPixmap = pixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::FastTransformation);

    ui->canvasLabel->setOffset(offset);

    // sets current canvas frame's pixmap to be sclaedPixmap object
    ui->canvasLabel->setPixmap(scaledPixmap);

    // update the picture at buttom list
    frameSelectorButtonList[frameIndex]->setIcon(QPixmap::fromImage(image));
    qDebug() << frameIndex;
    qDebug() << frameSelectorButtonList.size();
}

/**
 * @brief SpriteEditor::setAlpha
 * @param value the value to be which alpha value is to be set to
 *
 *  Sets the alpha value(opacity) with which drawings will be drawn with
 */
void SpriteEditor::setAlpha(int value)
{
    const Shape &s = brush.getShape();
    QColor color = QColor(s.color.red(), s.color.green(), s.color.blue(), value);

    QString colorWithAlpha = QString("rgba(%1, %2, %3, %4)")
                                 .arg(color.red())
                                 .arg(color.green())
                                 .arg(color.blue())
                                 .arg(value / 255.0); // 透明度范围为 0.0 到 1.0

    brush.setShape(Shape(s.shapeType, s.size, color));

    // get text color(inverse)
    QColor textColor = QColor(255 - color.red(), 255 - color.green(), 255 - color.blue());

    /// changes the color select button to be the same color selected from the color wheel
    ui->brushTool_colorSelectorButton->setStyleSheet(QString("background-color: %1; color: %2;")
                                                         .arg(colorWithAlpha)
                                                         .arg(textColor.name()));

    ui->brushTool_alphaValueLabel->setText(QString::number(value));
    emit sendBrushType(brush);
}

/**
 * @brief SpriteEditor::setBrushSize
 * @param size the size to which set the brush size has to be set to
 *
 *  Sets the brush size to desired brush size
 */
void SpriteEditor::setBrushSize(int size)
{
    const Shape &s = brush.getShape();
    brush.setShape(Shape(s.shapeType, size, s.color));
    ui->brushTool_BrushSizeLabel->setText(QString::number(size) + " px");
    emit sendBrushType(brush);
}

/**
 * @brief SpriteEditor::setFPS
 * @param fps the new fps value at which sequence of frames has to be played at
 *
 *  The frame speec with which sequence of frames will be played at
 */
void SpriteEditor::setFPS(int fps)
{
    ui->textLabel_FPSData->setText(QString::number(fps));
    emit sendFPS(fps);
}

/**
 * @brief SpriteEditor::selectShape
 * @param shapeID the shapeID to recognise the type of shape
 *
 *  Selects shape to be drawn recognising from the shapeID received
 */
void SpriteEditor::selectShape(int shapeID)
{
    switch (shapeID)
    {
    case 0:
        brush.setShape(Shape(shapeType::line, brush.getShape().size, brush.getShape().color));
        break;
    case 1:
        brush.setShape(Shape(shapeType::rect, brush.getShape().size, brush.getShape().color));
        break;
    case 2:
        brush.setShape(Shape(shapeType::roundedRect, brush.getShape().size, brush.getShape().color));
        break;
    case 3:
        brush.setShape(Shape(shapeType::ellipse, brush.getShape().size, brush.getShape().color));
        break;
    case 4:
        brush.setShape(Shape(shapeType::polygon, brush.getShape().size, brush.getShape().color));
        break;
    default:
        break;
    }

    emit sendBrushType(brush);
}

/**
 * @brief SpriteEditor::selectDrawBrush
 *
 *  This slot is connected to select the draw brush to draw with on canvas
 */
void SpriteEditor::selectDrawBrush()
{
    lastBrushButtonSelected->setEnabled(true);
    ui->brushTool_PenButton->setEnabled(false);
    lastBrushButtonSelected = ui->brushTool_PenButton;
    brush.setBrushType(drawBrush);
    emit sendBrushType(brush);
}

/**
 * @brief SpriteEditor::selectEraseBrush
 *
 * This slot is connected to select the erase brush to erase the drawings/shapes on canvas
 */

void SpriteEditor::selectEraseBrush()
{
    lastBrushButtonSelected->setEnabled(true);
    ui->brushTool_EraseButton->setEnabled(false);
    lastBrushButtonSelected = ui->brushTool_EraseButton;
    brush.setBrushType(eraseBrush);
    emit sendBrushType(brush);
}

/**
 * @brief SpriteEditor::selectShapeBrush
 *
 *  This slot is connected to select the shape drawing brush to draw shapes on canvas
 */

void SpriteEditor::selectShapeBrush()
{
    lastBrushButtonSelected->setEnabled(true);
    ui->brushTool_ShapeButton->setEnabled(false);
    lastBrushButtonSelected = ui->brushTool_ShapeButton;
    brush.setBrushType(shapeBrush);
    emit sendBrushType(brush);
}

/**
 * @brief SpriteEditor::addFrame
 *
 *  Slot called to add a new frame to the current project
 */
void SpriteEditor::addFrame()
{
    // select
    frameIndex++;

    IntSignalButton *button = new IntSignalButton(frameIndex);
    setFrameButtonSelected(button);
    button->setFixedSize(75, 75);
    button->setIconSize(QSize(70, 70));

    if (frameIndex >= frameSelectorButtonList.size() || frameIndex < 0)
    {
        frameSelectorButtonList.push_back(button);
        frameOverviewLayout->addWidget(button);
    }
    else
    {
        frameSelectorButtonList.insert(frameIndex, button);
        frameOverviewLayout->insertWidget(frameIndex, button);
    }

    setFrameButtonUnselected(frameSelectorButtonList[frameIndex - 1]);

    updateAllChangedFrameButton();

    frameOverviewContainer->adjustSize(); // adjust button to center
    emit sendAddFrame();
    selectFrame(frameIndex);
    // emit sendSelectedFrameIndex(frameIndex);
}

/**
 * @brief SpriteEditor::removeFrame
 *
 *  Slot called to remove the current selected frame
 */
void SpriteEditor::removeFrame()
{

    if (frameSelectorButtonList.size() < 2)
        return;

    // Start to remove the button
    IntSignalButton *buttonToRemove = frameSelectorButtonList[frameIndex];
    frameOverviewLayout->removeWidget(buttonToRemove); // Note: this will only remove the button in lay out, need use delete later method to remove it
    buttonToRemove->deleteLater();
    frameSelectorButtonList.removeAt(frameIndex);

    frameIndex = std::max(0, --frameIndex);
    updateAllChangedFrameButton();

    frameOverviewContainer->adjustSize();
    update();
    emit sendRemoveFrame();
    selectFrame(frameIndex);
    emit sendSelectedFrameIndex(frameIndex);
}

/**
 * @brief SpriteEditor::fillBlankArea
 *
 *  This slot emits the signal to fill the current frame canvas area with the current color selection
 */
void SpriteEditor::fillBlankArea()
{
    emit sendFillBlankArea(brush.getShape().color);
}

/**
 * @brief SpriteEditor::cloneFrame
 *
 *  Slot clones and adds the currently selected frame
 */
void SpriteEditor::cloneFrame()
{
    addFrame();
    frameSelectorButtonList[frameIndex]->setIcon(frameSelectorButtonList[frameIndex - 1]->icon());
    emit sendCloneFrame();
    // emit sendSelectedFrameIndex(frameIndex);
}

/**
 * @brief SpriteEditor::updateAllChangedFrameButton
 *
 *  Updates all the frames with value of current frame selected
 */
void SpriteEditor::updateAllChangedFrameButton()
{
    for (int i = frameIndex; i < frameSelectorButtonList.size(); i++)
    {
        frameSelectorButtonList[i]->setValue(i);
        connect(frameSelectorButtonList[i], &IntSignalButton::sendSelfValue, this, &SpriteEditor::selectFrame);
    }
}

/**
 * @brief SpriteEditor::selectFrame
 * @param newFrameIndex the new frame to be selected amongst the list of frames
 *
 *  sets active frame to be the newFrameIndex received
 */
void SpriteEditor::selectFrame(int newFrameIndex)
{
    setFrameButtonUnselected(frameSelectorButtonList[this->frameIndex]);
    setFrameButtonSelected(frameSelectorButtonList[newFrameIndex]);

    this->frameIndex = newFrameIndex;
    emit sendSelectedFrameIndex(newFrameIndex);
}

/**
 * @brief SpriteEditor::updateFrameSequence
 * @param image Reference of the image objects
 *
 *  Updates the sequence player with the new drawings on the current frame and plays the updated frames
 */
void SpriteEditor::updateFrameSequence(const QImage &image)
{
    QPixmap img = QPixmap::fromImage(image);
    img = img.scaled(ui->animationPlayerLabel->size(), Qt::KeepAspectRatio, Qt::FastTransformation);
    ui->animationPlayerLabel->setPixmap(img);
}

void SpriteEditor::setFrameButtonSelected(IntSignalButton *button)
{
    button->setStyleSheet("QPushButton {"
                          "  border: 2px solid blue;" // 设置2像素宽的黑色描边
                          "  border-radius: 5px;"     // 圆角半径，可选
                          "  padding: 5px;"           // 内容与边框之间的间距
                          "}");
    button->setEnabled(false);
}

void SpriteEditor::setFrameButtonUnselected(IntSignalButton *button)
{
    button->setStyleSheet("QPushButton {"
                          "  padding: 5px;" // 内容与边框之间的间距
                          "}");
    button->setEnabled(true);
}

/**
 * @brief SpriteEditor::showHelpMessage
 *
 *  Slot called when help button is clicked in the UI. It displays all the options available for the sprite editor
 *  alongwith how each of them can be used by the user
 */
void SpriteEditor::showHelpMessage()
{
    QWidget *w = new QWidget(this);
    w->setWindowFlags(Qt::Popup);
    w->setGeometry(300, 300, 350, 600);
    w->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *label = new QLabel("This is the help message.\n"
                               "\n"
                               "1. The left top is the anime preview.\n"
                               "\n"
                               "2. There is a slide bar to adjust the FPS of the preview.\n"
                               "\n"
                               "3. The next bar is main tools we can use, we can use pen tool, shape tool, erase tool and size of the pen. Shape tool (the second one) can let users to drag shape on the canvas. If the user want to drag polygon shape, they need to hold left button, and at same time to press right mouse button to add more vertices.\n"
                               "\n"
                               "4. Color selector can be used to select color and change alpha value by a slider under it\n"
                               "\n"
                               "5. In the middle we have sub tools like: rescale, export current frame, fill blank area with color, flip image along y, clean the canvas, import image, rotate image, flip image along x.\n"
                               "\n"
                               "6. Frame operation, we can add frame, delete frame, copy the frame to the frame list\n"
                               "\n"
                               "7. the last bar is save and load button, we can save our sprite or load other existed sprite."
                               "\n"
                               "\n"
                               "8. the buttom button list is our sprite anime sequence, each button represent each frame.\n"
                               "\n"
                               "9. The right big canvas is our drawing canvas, user can use mouse to scroll on the canvas, after the canvas is larger than the view port, user can hold right click to drag the canvas around\n",
                               w);
    label->setAlignment(Qt::AlignCenter);
    label->setWordWrap(true);
    label->setGeometry(10, 10, 300, 600);
    w->show();
}

/// Destructor
SpriteEditor::~SpriteEditor()
{
    delete ui;
}

/**
 * @brief SpriteEditor::saveFile
 *
 *  Slot connected to when save file button is clicked by user
 */
void SpriteEditor::saveFile()
{
    // popup the selector window
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File path"), "", tr("spriteFile(*.sprite)"));
    if (!fileName.isEmpty())
    {
        emit sendSaveFilePath(fileName);
    }
};

/**
 * @brief SpriteEditor::loadFile
 *  Slot connected to when load file button is clicked by user
 */
void SpriteEditor::loadFile()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,                   // parent window
        "Select the File",      // title
        "",                     // default path
        "spriteFile(*.sprite)", // filter
        nullptr,                // default
        QFileDialog::ReadOnly   // readonly
    );

    if (!fileName.isEmpty())
    {
        emit sendLoadFilePath(fileName);
    }
};


void SpriteEditor::receiveAllImages(const QList<QImage> &images)
{

    removeAllFrame();

    for (int i = 0; i < images.size(); i++)
    {
        IntSignalButton *button = new IntSignalButton(i);
        button->setFixedSize(75, 75);
        button->setIconSize(QSize(70, 70));
        button->setIcon(QPixmap::fromImage(images[i]));
        frameSelectorButtonList.push_back(button);
        frameOverviewLayout->addWidget(button);
    }
    frameIndex = 0;
    updateAllChangedFrameButton();
    setFrameButtonSelected(frameSelectorButtonList[0]);
    emit sendSelectedFrameIndex(0);

    frameOverviewContainer->adjustSize();
}
