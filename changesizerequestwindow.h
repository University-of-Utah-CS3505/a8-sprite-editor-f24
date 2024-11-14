#ifndef CHANGESIZEREQUESTWINDOW_H
#define CHANGESIZEREQUESTWINDOW_H

#include <QDialog>

namespace Ui
{
    class changeSizeRequestWindow;
}

/**
 *  Team Name : Sam's Club
 *
 *  Team Members : Rohith Veeramachaneni, Shu Chen, Bingkun Han and PING-HSUN HSIEH
 *
 *  Contributor's Names of changeSizeRequestWindow.h : Shu Chen, Bingkun Han and PING-HSUN HSIEH
 *
 *  Date Modified : November 10, 2024
 *
 *  Header class for changeSizeRequestWindow
 */

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
