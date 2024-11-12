#include "changesizerequestwindow.h"
#include "ui_changesizerequestwindow.h"

changeSizeRequestWindow::changeSizeRequestWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::changeSizeRequestWindow)
{
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &changeSizeRequestWindow::changeSize);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &changeSizeRequestWindow::donotChangeSize);
}

void changeSizeRequestWindow::changeSize(){
    emit sendNewSize(QSize(ui->sizeSpinBox->value(), ui->sizeSpinBox->value()));
    this->close();
}

void changeSizeRequestWindow::donotChangeSize(){
    this->close();
}

changeSizeRequestWindow::~changeSizeRequestWindow()
{
    delete ui;
}
