#include "comtoolwindow.h"

MyComToolWindow::MyComToolWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    mySerial = new Serial;
    QStringList serialStrList;
    serialStrList = mySerial->scanSerial();
    for(int i=0 ;i<serialStrList.size(); i++)
    {
        portComboBox->addItem(serialStrList[i]);
    }
    baudComboBox->setCurrentIndex(5); //Default 115200
    connect(mySerial, SIGNAL(readSignal()), this, SLOT(readSerialData()));
}

MyComToolWindow::~MyComToolWindow()
{

}

void MyComToolWindow::on_openPortButton_clicked()
{
    if(openPortButton->text() == tr("Open Serial"))
    {
        if(mySerial->open(portComboBox->currentText(), baudComboBox->currentText().toInt()))
        {
            portComboBox->setEnabled(false);
            baudComboBox->setEnabled(false);
            openPortButton->setText(tr("Closed Serial"));
        }
    }
    else if(openPortButton->text() == tr("Closed Serial"))
    {
        mySerial->close();

        portComboBox->setEnabled(true);
        baudComboBox->setEnabled(true);
        openPortButton->setText(tr("Open Serial"));
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

void MyComToolWindow::on_SendButton_clicked()
{
    QByteArray byteArray = mySerial->hexStringToByteArray(sendTextEdit->toPlainText());
    mySerial->sendData(byteArray);
}

void MyComToolWindow::readSerialData()
{
    QString originStr = recvTextEdit->toPlainText();
    recvTextEdit->clear();
    recvTextEdit->setText(originStr);
    recvTextEdit->moveCursor(QTextCursor::End);
    recvTextEdit->insertPlainText(mySerial->getReadBuf().toHex());
    recvTextEdit->moveCursor(QTextCursor::End);
    recvTextEdit->insertPlainText(" ");
    mySerial->clearReadBuf();
}
