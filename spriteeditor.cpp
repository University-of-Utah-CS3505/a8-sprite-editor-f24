#include "spriteeditor.h"
#include "ui_spriteeditor.h"

SpriteEditor::SpriteEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SpriteEditor)
{
    ui->setupUi(this);
}

SpriteEditor::~SpriteEditor()
{
    delete ui;
}
