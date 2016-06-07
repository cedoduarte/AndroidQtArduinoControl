#ifndef DUTCPSERVER_H
#define DUTCPSERVER_H

#include <QTcpSocket>
#include <QTcpServer>

class DuTcpServerForAndroid : public QTcpServer
{
    Q_OBJECT
public:
    enum Option
    {
        ON = 1, OFF = 0
    };

    DuTcpServerForAndroid(QObject *parent = nullptr);
    bool openServerForAndroid(int port);
    bool closeServerForAndroid();
signals:
    void errorMessage(QString);
    void androidConnected();
    void selectedOption(int);
private:
    QTcpSocket *mAndroidSocket;
};

#endif // DUTCPSERVER_H
