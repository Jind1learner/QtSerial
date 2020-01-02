#include "comtoolwindow.h"

MyComToolWindow::MyComToolWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    recvTextEdit->setReadOnly(true);

    mySerial = new Serial;
    PortNameDisplay();
    baudComboBox->setCurrentIndex(5); //Default 115200

    scanPorttimer = new QTimer;
    scanPorttimer->setInterval(2000);
    scanPorttimer->start();
    connect(scanPorttimer, SIGNAL(timeout()), this, SLOT(PortNameDisplay())); //定时刷新数据
    connect(mySerial, SIGNAL(readSignal()), this, SLOT(readSerialData()));
}

MyComToolWindow::~MyComToolWindow()
{

}

void MyComToolWindow::PortNameDisplay()
{
    QStringList serialStrList;
    serialStrList = mySerial->scanSerial();
    for(int i=0 ;i<serialStrList.size(); i++)
    {
        portComboBox->addItem(serialStrList[i]);
    }
    qDebug() << "enter PortNameDisplay";
}

void MyComToolWindow::on_openPortButton_clicked()
{
    if(openPortButton->text() == tr("打开串口"))
    {
        //打开串口的参数分别为: 串口名称，波特率，数据位，校验位，停止位
        if(mySerial->opened(portComboBox->currentText(),
                            baudComboBox->currentText().toInt(),
                            dataBitComboBox->currentText().toInt(),
                            checkBitComboBox->currentIndex(),
                            stopBitComboBox->currentIndex() ))
        {
            portComboBox->setEnabled(false);
            baudComboBox->setEnabled(false);
            openPortButton->setText(tr("关闭串口"));
        }
    }
    else if(openPortButton->text() == tr("关闭串口"))
    {
        mySerial->closed();

        portComboBox->setEnabled(true);
        baudComboBox->setEnabled(true);
        openPortButton->setText(tr("打开串口"));
    }
}

void MyComToolWindow::on_clearTextButton_clicked()
{
    recvTextEdit->clear();
}

void MyComToolWindow::on_clearSendButton_clicked()
{
    sendTextEdit->clear();
}

void MyComToolWindow::on_sendButton_clicked()
{
    QByteArray byteArray = mySerial->hexStringToByteArray(sendTextEdit->toPlainText());
    mySerial->sendData(byteArray);
}

void MyComToolWindow::readSerialData()
{
    recvTextEdit->append(mySerial->getReadBuf());
    /*
    QString originStr = recvTextEdit->toPlainText();
    recvTextEdit->clear();
    recvTextEdit->setText(originStr);
    recvTextEdit->moveCursor(QTextCursor::End);
    recvTextEdit->insertPlainText(mySerial->getReadBuf());
    recvTextEdit->moveCursor(QTextCursor::End);
    recvTextEdit->insertPlainText(" ");
    mySerial->clearReadBuf();
    */
}
