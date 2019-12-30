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

bool Serial::open(QString serialName, int baudRate) //open serial
{
    m_serialPort->setPortName(serialName);
    if(m_serialPort->open(QIODevice::ReadWrite))
    {
        m_serialPort->setBaudRate(baudRate);
        m_serialPort->setDataBits(QSerialPort::Data8);
        m_serialPort->setParity(QSerialPort::NoParity);
        m_serialPort->setStopBits(QSerialPort::OneStop);
        m_serialPort->setFlowControl(QSerialPort::NoFlowControl);

        connect(m_serialPort, SIGNAL(readyRead()), this, SLOT(readData()));
        connect(m_serialPort, SIGNAL(readyRead()), this, SIGNAL(readSignal()));

        return true;
    }

    return false;
}

void Serial::close() // 关闭串口
{
    m_serialPort->clear();
    m_serialPort->close();
}

void Serial::sendData(QByteArray &sendData) // 发送数据给下位机
{
    m_serialPort->write(sendData);
}

void Serial::readData()
{
    m_readBuf = m_serialPort->readAll();
}

QByteArray Serial::getReadBuf() // 获得读取数据缓冲区
{
    return m_readBuf;
}

void Serial::clearReadBuf() // 清除读取数据缓冲区
{
    m_readBuf.clear();
}

QByteArray Serial::hexStringToByteArray(QString HexString) // 将16进制字符串转换为对应的字节序列
{
    bool ok;
    QByteArray ret;
    HexString = HexString.trimmed();
    HexString = HexString.simplified();
    QStringList sl = HexString.split(" ");

    foreach (QString s, sl)
    {
        if(!s.isEmpty())
        {
            char c = static_cast<char>(s.toInt(&ok, 16) & 0xff);
            if(ok)
            {
                ret.append(c);
            }
            else
            {
                qDebug() << "Illegal hex chars: " << s;
                QMessageBox::warning(nullptr, tr("error:") ,tr("Illegal hex chars: \"%1\"").arg(s));
            }
        }
    }
    return ret;
}
