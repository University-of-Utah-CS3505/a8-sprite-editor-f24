#ifndef SPRITEEDITOR_H
#define SPRITEEDITOR_H

#include <QMainWindow>
#include <QGraphicsSceneMouseEvent>
#include "model.h"
#include "canvaslabel.h"
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
    QList<IntSignalButton*> frameSelectorButtonList;
    QWidget *frameOverviewContainer;
    QHBoxLayout *frameOverviewLayout;

    void setFrameButtonSelected(IntSignalButton* button);
    void setFrameButtonUnselected(IntSignalButton* button);
    void updateAllChangedFrameButton();
public:
    SpriteEditor(Model& m, QWidget *parent = nullptr);
    ~SpriteEditor();

public slots:
    void selectFrame(int frameIndex);
    void addFrame();
    void removeFrame();
    void cloneFrame();
    void updateFrameSequence(const QImage& image);
    void display(const QImage& image, float scale, const QPointF& offset);

signals:
    void sendSelectedFrameIndex(int index);

private:
    Ui::SpriteEditor *ui;
};
#endif // SPRITEEDITOR_H
