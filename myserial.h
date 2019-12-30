#ifndef MYSERIAL_H
#define MYSERIAL_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QDebug>

class Serial:public QObject
{
    Q_OBJECT

public:
    Serial();
    QStringList scanSerial();  //scanf serial
    bool open(QString serialName, int baudRate); //open serial
    void close(); // 关闭串口
    void sendData(QByteArray &sendData); // 发送数据给下位机
    QByteArray getReadBuf(); // 获得读取数据缓冲区
    void clearReadBuf(); // 清除读取数据缓冲区
    QByteArray hexStringToByteArray(QString HexString); // 将16进制字符串转换为对应的字节序列

signals:
    void readSignal(); // 当下位机中有数据发送过来时就会触发这个信号，以提示其它类对象

public slots:
    void readData(); // 读取下位机发来数据

private:
    QSerialPort *m_serialPort; // 实例化一个指向串口的指针，可以用于访问串口
    QByteArray m_readBuf; // 存储下位机发来数据的缓冲区

};

#endif // MYSERIAL_H

