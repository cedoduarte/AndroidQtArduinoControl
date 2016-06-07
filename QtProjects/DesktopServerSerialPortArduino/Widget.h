#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui
{
class Widget;
}

class DuArduino;
class DuTcpServerForAndroid;

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
private slots:
    void on_abrirArduinoPushButton_clicked();
    void on_cerrarArduinoPushButton_clicked();
    void on_abrirServidorPushButton_clicked();
    void on_cerrarServidorPushButton_clicked();
    void on_encenderPushButton_clicked();
    void on_apagarPushButton_clicked();
private:
    void createObjects();
    void configureGUI();
    void connectSlots();
    void printIpAddresses();

    Ui::Widget *ui;
    DuArduino *mArduino;
    DuTcpServerForAndroid *mTcpServerForAndroid;
};

#endif // WIDGET_H
