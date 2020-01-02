#ifndef COMTOOLWINDOW_H
#define COMTOOLWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "ui_comtoolwindow.h"
#include "myserial.h"

class MyComToolWindow : public QMainWindow, Ui::ComToolWindow
{
    Q_OBJECT

public:
    explicit MyComToolWindow(QWidget *parent = 0);
    ~MyComToolWindow();


private slots:
    void on_openPortButton_clicked();
    void on_clearTextButton_clicked();
    void on_clearSendButton_clicked();
    void on_sendButton_clicked();
    void readSerialData();

    void PortNameDisplay();

private:
    QTimer *scanPorttimer;
    Serial *mySerial;
};

#endif // COMTOOLWINDOW_H
