#include "spriteeditor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model model;
    SpriteEditor view(model);
    view.show();
    return a.exec();
}
