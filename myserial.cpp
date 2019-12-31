#include "myserial.h"

Serial::Serial()
{
    m_serialPort = new QSerialPort;
}

QStringList Serial::scanSerial()
{
    QStringList serialStrList;
    foreach (QSerialPortInfo info, QSerialPortInfo::availablePorts())
    {
        m_serialPort->setPort(info);
        if(m_serialPort->open(QIODevice::ReadWrite))
        {
            serialStrList.append(m_serialPort->portName());
            m_serialPort->close();
        }
    }
    return serialStrList;
}

//打开串口的参数分别为: 串口名称，波特率，数据位，校验位，停止位
bool Serial::opened(QString serialName, int baudRate, int Data, int Parity, int Stop)
{
    m_serialPort->setPortName(serialName);
    if(m_serialPort->open(QIODevice::ReadWrite))
    {
        //波特率
        m_serialPort->setBaudRate(baudRate);

        //数据位
        switch(Data)
        {
        case 8:
            m_serialPort->setDataBits(QSerialPort::Data8);
            break;
        case 7:
            m_serialPort->setDataBits(QSerialPort::Data7);
            break;
        case 6:
            m_serialPort->setDataBits(QSerialPort::Data6);
            break;
        case 5:
            m_serialPort->setDataBits(QSerialPort::Data5);
            break;

        default:
            break;
        }

        //校验位
        switch(Parity)
        {
        case 0:
            m_serialPort->setParity(QSerialPort::OddParity);
            break;
        case 1:
            m_serialPort->setParity(QSerialPort::EvenParity);
            break;
        case 2:
            m_serialPort->setParity(QSerialPort::NoParity);
            break;

        default:
            break;
        }

        //停止位
        switch(Stop)
        {
        case 0:
            m_serialPort->setStopBits(QSerialPort::OneStop);
            break;
        case 1:
            m_serialPort->setStopBits(QSerialPort::OneAndHalfStop);
            break;
        case 2:
            m_serialPort->setStopBits(QSerialPort::TwoStop);
            break;

        default:
            break;
        }
        //流控制
        m_serialPort->setFlowControl(QSerialPort::NoFlowControl);

        connect(m_serialPort, SIGNAL(readyRead()), this, SLOT(readDataFrom()));
        connect(m_serialPort, SIGNAL(readyRead()), this, SIGNAL(readSignal()));

        return true;
    }

    return false;
}

void Serial::closed() // 关闭串口
{
    m_serialPort->clear();
    m_serialPort->close();
}

void Serial::sendData(QByteArray &sendData) // 发送数据给下位机
{
    m_serialPort->write(sendData);
}

void Serial::readDataFrom()
{
    m_readBuf = m_serialPort->readAll();
}

QString Serial::getReadBuf() // 获得读取数据缓冲区
{
    return m_readBuf;
}

void Serial::readDataFrom()
{
    m_readBuf = m_serialPort->readAll();
}

QString Serial::getReadBuf() // 获得读取数据缓冲区
{
    return m_readBuf;
}

QByteArray Serial::hexStringToByteArray(QString HexString) // 将16进制字符串转换为对应的字节序列
{
    //bool ok;
    QByteArray ret;
    HexString = HexString.trimmed();
    HexString = HexString.simplified();
    QStringList sl = HexString.split(" ");
    foreach (QString s, sl)
    {
        for(int i=0; i<s.size(); i++)
        {
            ret.append(s.at(i));
        }
        ret.append('\r');
        ret.append('\n');
    }
    return ret;
}
