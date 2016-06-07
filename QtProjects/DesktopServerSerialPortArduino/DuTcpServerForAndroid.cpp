#include "DuTcpServerForAndroid.h"
#include <QTcpServer>
#include <QTcpSocket>

DuTcpServerForAndroid::DuTcpServerForAndroid(QObject *parent)
    : QTcpServer(parent)
{
    mAndroidSocket = nullptr;

    connect(this, &DuTcpServerForAndroid::newConnection, [&]() {
        mAndroidSocket = nextPendingConnection();

        connect(mAndroidSocket, &QTcpSocket::readyRead, [&]() {
            const int option = mAndroidSocket->readAll().toInt();
            emit selectedOption(option);
        });

        emit androidConnected();
    });
}

bool DuTcpServerForAndroid::openServerForAndroid(int port)
{
    if (!listen(QHostAddress::Any, port)) {
        emit errorMessage("Host for android is not open");
        return false;
    }
    emit errorMessage("Host for android is open...");
    return true;
}

bool DuTcpServerForAndroid::closeServerForAndroid()
{
    close();
    emit errorMessage("Host for android is closed");
    return true;
}
