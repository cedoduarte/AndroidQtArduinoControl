#ifndef DUARDUINO_H
#define DUARDUINO_H

#include <QObject>

class QSerialPort;

class DuArduino : public QObject
{
    Q_OBJECT
public:
    DuArduino(QObject *parent = nullptr);
    bool openArduino();
    bool closeArduino();
    void send(const QString &data);
signals:
    void messageArduino(QString);
    void errorArduino(QString, QString);
private:
    QSerialPort *mArduinoSerialPort;
    static const quint16 mArduinoUnoVendorId = 9025;
    static const quint16 mArduinoUnoProductId = 67;
    QString mArduinoPortName;
    bool mArduinoIsAvailable;
};

#endif // DUARDUINO_H
