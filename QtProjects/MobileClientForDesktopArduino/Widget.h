#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui
{
class Widget;
}

class QTcpSocket;

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
private slots:
    void on_connectPushButton_clicked();
    void on_encenderPushButton_clicked();
    void on_apagarPushButton_clicked();
private:
    Ui::Widget *ui;
    QTcpSocket *mSocket;
};

#endif // WIDGET_H
