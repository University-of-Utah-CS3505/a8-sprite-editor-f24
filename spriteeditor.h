#ifndef SPRITEEDITOR_H
#define SPRITEEDITOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class SpriteEditor;
}
QT_END_NAMESPACE

class SpriteEditor : public QMainWindow
{
    Q_OBJECT

public:
    SpriteEditor(QWidget *parent = nullptr);
    ~SpriteEditor();

private:
    Ui::SpriteEditor *ui;
};
#endif // SPRITEEDITOR_H
