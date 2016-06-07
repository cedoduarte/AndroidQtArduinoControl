#include "Widget.h"
#include "ui_Widget.h"
#include <QTcpSocket>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mSocket = new QTcpSocket(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_connectPushButton_clicked()
{
    mSocket->connectToHost(ui->hostLineEdit->text(),
                           ui->portLineEdit->text().toInt());
}

void Widget::on_encenderPushButton_clicked()
{
    mSocket->write("1");
}

void Widget::on_apagarPushButton_clicked()
{
    mSocket->write("0");
}
