#ifndef SPRITEEDITOR_H
#define SPRITEEDITOR_H

#include <QMainWindow>
#include <QGraphicsSceneMouseEvent>
#include "model.h"
#include <QPushButton>
#include <QHBoxLayout>
#include "intsignalbutton.h"


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

    void setFrameButtonSelected(IntSignalButton* button);
    void setFrameButtonUnselected(IntSignalButton* button);
    void updateAllChangedFrameButton();
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

signals:
    void sendSelectedFrameIndex(int index);
    void sendBrushType(Brush brush);
    void sendFPS(int fps);
    void sendAddFrame();
    void sendCloneFrame();
    void sendRemoveFrame();
    void sendFillBlankArea(const QColor& color);

private:
    Ui::SpriteEditor *ui;
};
#endif // SPRITEEDITOR_H
