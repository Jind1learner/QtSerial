#ifndef MYSERIAL_H
#define MYSERIAL_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QDebug>

class Serial:public QSerialPort
{
    Q_OBJECT

public:
    Serial();
    QStringList scanSerial();  //scanf serial

    //打开串口的参数分别为: 串口名称，波特率，数据位，校验位，停止位
    bool opened(QString serialName, int baudRate, int Data, int Parity, int Stop);
    void closed(); // 关闭串口
    void sendData(QByteArray &sendData); // 发送数据给下位机
    QString getReadBuf(); // 获得读取数据缓冲区
    void clearReadBuf(); // 清除读取数据缓冲区
    QByteArray hexStringToByteArray(QString HexString); // 将16进制字符串转换为对应的字节序列

signals:
    void readSignal(); // 当下位机中有数据发送过来时就会触发这个信号，以提示其它类对象

public slots:
    void readDataFrom(); // 读取下位机发来数据

private:
    QSerialPort *m_serialPort; // 实例化一个指向串口的指针，可以用于访问串口
    QString m_readBuf; // 存储下位机发来数据的缓冲区

};

#endif // MYSERIAL_H

