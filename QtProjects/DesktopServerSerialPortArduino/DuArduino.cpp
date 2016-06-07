#include "DuArduino.h"
#include <QSerialPort>
#include <QSerialPortInfo>

DuArduino::DuArduino(QObject *parent)
    : QObject(parent)
{
    mArduinoIsAvailable = false;
    mArduinoPortName = "";
    mArduinoSerialPort = new QSerialPort(this);
}

bool DuArduino::openArduino()
{
    emit messageArduino(QString("Number of available ports: %1")
                        .arg(QSerialPortInfo::availablePorts().length()));
    foreach (const QSerialPortInfo &serialPortInfo,
             QSerialPortInfo::availablePorts())
    {
        emit messageArduino(QString("Has vendor ID: %1")
                            .arg(serialPortInfo.hasVendorIdentifier()));
        if (serialPortInfo.hasVendorIdentifier()) {
            emit messageArduino(QString("Vendor ID: %1")
                                .arg(serialPortInfo.vendorIdentifier()));
        }
        emit messageArduino(QString("Has Product ID: %1")
                            .arg(serialPortInfo.hasProductIdentifier()));
        if (serialPortInfo.hasProductIdentifier()) {
            emit messageArduino(QString("Product ID: %1")
                                .arg(serialPortInfo.productIdentifier()));
        }
    }


    foreach (const QSerialPortInfo &serialPortInfo,
            QSerialPortInfo::availablePorts())
    {
        if(serialPortInfo.hasVendorIdentifier()
                && serialPortInfo.hasProductIdentifier())
        {
            if(serialPortInfo.vendorIdentifier() == mArduinoUnoVendorId) {
                if(serialPortInfo.productIdentifier()
                        == mArduinoUnoProductId)
                {
                    mArduinoPortName = serialPortInfo.portName();
                    mArduinoIsAvailable = true;
                }
            }
        }
    }

    if (mArduinoIsAvailable) {
        // open and configure the serialport
        mArduinoSerialPort->setPortName(mArduinoPortName);
        if (!mArduinoSerialPort->open(QSerialPort::WriteOnly)) {
            emit errorArduino("Port error", "Couldn't open the Arduino!");
            return false;
        }
        mArduinoSerialPort->setBaudRate(QSerialPort::Baud9600);
        mArduinoSerialPort->setDataBits(QSerialPort::Data8);
        mArduinoSerialPort->setParity(QSerialPort::NoParity);
        mArduinoSerialPort->setStopBits(QSerialPort::OneStop);
        mArduinoSerialPort->setFlowControl(QSerialPort::NoFlowControl);
    } else {
        // give error message if not available
        emit errorArduino("Port error", "Couldn't find the Arduino!");
        return false;
    }
    emit errorArduino("Port connected", "Arduino is connected...");
    return true;
}

bool DuArduino::closeArduino()
{
    if (mArduinoSerialPort->isOpen()) {
        mArduinoSerialPort->close();
        emit errorArduino("Port disconnected", "Arduino is disconnected!!!");
        return true;
    }
    return false;
}

void DuArduino::send(const QString &data)
{
    if (mArduinoSerialPort->isWritable()) {
        mArduinoSerialPort->write(data.toLatin1());
    }
}
