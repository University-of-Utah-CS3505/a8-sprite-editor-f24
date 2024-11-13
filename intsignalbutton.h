#ifndef INTSIGNALBUTTON_H
#define INTSIGNALBUTTON_H

#include <QWidget>
#include <QPushButton>
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
