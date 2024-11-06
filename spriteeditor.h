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
    int frameIndex = -1;
    QList<IntSignalButton*> frameSelectorButtonList;
    QWidget *frameOverviewContainer;
    QHBoxLayout *frameOverviewLayout;
public:
    SpriteEditor(Model& m, QWidget *parent = nullptr);
    ~SpriteEditor();

public slots:
    void addFrame();
    void deleteFrame();
    void cloneFrame();
    void updateFrameSequence(const QImage& image);
    void display(const QImage& image, float scale, const QPointF& offset);

private:
    Ui::SpriteEditor *ui;
};
#endif // SPRITEEDITOR_H
