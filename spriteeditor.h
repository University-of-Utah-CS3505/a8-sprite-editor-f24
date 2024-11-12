#ifndef SPRITEEDITOR_H
#define SPRITEEDITOR_H

#include <QMainWindow>
#include <QGraphicsSceneMouseEvent>
#include "model.h"
#include <QPushButton>
#include <QHBoxLayout>
#include "intsignalbutton.h"
#include "changesizerequestwindow.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class SpriteEditor;
}
QT_END_NAMESPACE

class SpriteEditor : public QMainWindow
{
    Q_OBJECT
    int frameIndex = 0;
    Brush brush;
    QList<IntSignalButton*> frameSelectorButtonList;
    QWidget *frameOverviewContainer;
    QHBoxLayout *frameOverviewLayout;
    QPushButton* lastBrushButtonSelected;
    changeSizeRequestWindow setFrameSizeWindow;


    void setFrameButtonSelected(IntSignalButton* button);
    void setFrameButtonUnselected(IntSignalButton* button);
    void updateAllChangedFrameButton();
    void setFrameSize(const QSize& size);
    void initialize(const QSize& size);
    void removeAllFrame();
public:
    SpriteEditor(Model& m, QWidget *parent = nullptr);
    ~SpriteEditor();

public slots:
    void selectShape(int shapeId);
    void selectDrawBrush();
    void selectEraseBrush();
    void selectShapeBrush();
    void selectFrame(int frameIndex);
    void selectColor();
    void addFrame();
    void removeFrame();
    void cloneFrame();
    void updateFrameSequence(const QImage& image);
    void updateCanvas(const QImage& image, float scale, const QPointF& offset);
    void setAlpha(int value);
    void setFPS(int fps);
    void setBrushSize(int value);
    void showHelpMessage();
    void fillBlankArea();
    void loadImage();
    void saveFile();
    void loadFile();
    void receiveAllImages(const QList<QImage>& images);
    void callSetFrameSizeWindow();
    void saveImage();

signals:
    void sendSelectedFrameIndex(int index);
    void sendBrushType(Brush brush);
    void sendFPS(int fps);
    void sendAddFrame();
    void sendCloneFrame();
    void sendRemoveFrame();
    void sendFillBlankArea(const QColor& color);
    void sendLoadImagePath(const QString& imagePath);
    void sendSaveFilePath(const QString& filePath);
    void sendLoadFilePath(const QString& filePath);
    void initializeModel(const QSize& size);
    void sendSaveImagePath(const QString& imagePath);

private:
    Ui::SpriteEditor *ui;
};
#endif // SPRITEEDITOR_H
