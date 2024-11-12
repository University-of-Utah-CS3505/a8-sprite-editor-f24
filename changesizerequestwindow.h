#ifndef CHANGESIZEREQUESTWINDOW_H
#define CHANGESIZEREQUESTWINDOW_H

#include <QDialog>

namespace Ui {
class changeSizeRequestWindow;
}

class changeSizeRequestWindow : public QDialog
{
    Q_OBJECT

public:
    explicit changeSizeRequestWindow(QWidget *parent = nullptr);
    ~changeSizeRequestWindow();

public slots:
    void changeSize();
    void donotChangeSize();
signals:
    void sendNewSize(QSize size);

private:
    Ui::changeSizeRequestWindow *ui;
};

#endif // CHANGESIZEREQUESTWINDOW_H
