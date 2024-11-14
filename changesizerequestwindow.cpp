#include "changesizerequestwindow.h"
#include "ui_changesizerequestwindow.h"

/**
 *  Team Name : Sam's Club
 *
 *  Team Members : Rohith Veeramachaneni, Shu Chen, Bingkun Han and PING-HSUN HSIEH
 *
 *  Contributor's Names of changeSizeRequestWindow.h :Shu Chen, Bingkun Han and PING-HSUN HSIEH
 *
 *  Date Modified : November 10, 2024
 *
 *  changeSizeRequestWindow class contains methods such as changeSize, doNotChangeSize to allow user to change
 *  canvas frame size
 */

changeSizeRequestWindow::changeSizeRequestWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::changeSizeRequestWindow)
{
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &changeSizeRequestWindow::changeSize);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &changeSizeRequestWindow::donotChangeSize);
}

void changeSizeRequestWindow::changeSize()
{
    emit sendNewSize(QSize(ui->sizeSpinBox->value(), ui->sizeSpinBox->value()));
    this->close();
}

void changeSizeRequestWindow::donotChangeSize()
{
    this->close();
}

// Destructor
changeSizeRequestWindow::~changeSizeRequestWindow()
{
    delete ui;
}
