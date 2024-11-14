#ifndef INTSIGNALBUTTON_H
#define INTSIGNALBUTTON_H

#include <QWidget>
#include <QPushButton>

/**
 *
 *  Team Name : Sam's Club
 *
 *  Team Members : Rohith Veeramachaneni, Shu Chen, Bingkun Han and PING-HSUN HSIEH
 *
 *  Contributor's Names of intSignalButton.h : TO BE UPDATED
 *
 *  Date Modified : November 10, 2024
 *
 *  Header class for intSignalButton.h

*/

class IntSignalButton : public QPushButton
{
    Q_OBJECT
    int value;

public:
    explicit IntSignalButton(int value, QWidget *parent = nullptr);

public slots:
    void pushed();
    void setValue(int val);

signals:
    void sendSelfValue(int value);
};

#endif // INTSIGNALBUTTON_H
