#include "Widget.h"
#include "ui_Widget.h"
#include "DuArduino.h"
#include "DuTcpServerForAndroid.h"
#include <QMessageBox>
#include <QNetworkInterface>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    createObjects();
    configureGUI();
    printIpAddresses();
    connectSlots();
}

Widget::~Widget()
{
    mArduino->closeArduino();
    delete ui;
}

void Widget::on_abrirArduinoPushButton_clicked()
{
    mArduino->openArduino();
}

void Widget::on_cerrarArduinoPushButton_clicked()
{
    mArduino->closeArduino();
}

void Widget::on_abrirServidorPushButton_clicked()
{
    mTcpServerForAndroid->openServerForAndroid(ui->portSpinBox->value());
}

void Widget::on_cerrarServidorPushButton_clicked()
{
    mTcpServerForAndroid->closeServerForAndroid();
}

void Widget::connectSlots()
{
    connect(mTcpServerForAndroid,&DuTcpServerForAndroid::androidConnected,[&]()
    {
        ui->errorAndroidMessageLabel->setText("Android connected...");
    });

    connect(mTcpServerForAndroid,&DuTcpServerForAndroid::selectedOption,
            [&](int option)
    {
        switch (option) {
        case DuTcpServerForAndroid::ON: {
            mArduino->send("1");
            break;
        }
        case DuTcpServerForAndroid::OFF: {
            mArduino->send("0");
            break;
        }
        }
    });

    connect(mTcpServerForAndroid,&DuTcpServerForAndroid::errorMessage,
            [&](const QString &message)
    {
        ui->errorAndroidMessageLabel->setText(message);
    });

    connect(mArduino, &DuArduino::errorArduino, [&](const QString &title,
            const QString &errorMessage)
    {
        ui->errorArduinoMessageLabel->setText("Error message: " + title
                                       + ", " + errorMessage);
    });

    connect(mArduino, &DuArduino::messageArduino, [&](const QString &message)
    {
        ui->arduinoTextBrowser->append(message);
    });
}

void Widget::printIpAddresses()
{
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address
                != QHostAddress(QHostAddress::LocalHost))
        {
            ui->androidTextBrowser->append(address.toString());
        }
    }
}

void Widget::on_encenderPushButton_clicked()
{
    mArduino->send("1");
}

void Widget::on_apagarPushButton_clicked()
{
    mArduino->send("0");
}

void Widget::createObjects()
{
    mArduino = new DuArduino(this);
    mTcpServerForAndroid = new DuTcpServerForAndroid(this);
}

void Widget::configureGUI()
{
    ui->portSpinBox->setMinimum(0);
    ui->portSpinBox->setMaximum(INT_MAX);
    ui->portSpinBox->setValue(5555);
}
