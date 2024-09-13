#include "mywidget.h"
#include "ui_mywidget.h"
#include <QDialog>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    // clicked()信号在QPushButton类中进行了定义，而connect()是QObject类中的函数，因为我们的类继承自QObject，所以可以直接使用它
    // connect()函数中的四个参数分别是：发送信号的对象、发送的信号、接收信号的对象和要执行的槽
    connect(ui->showChildButton, &QPushButton::clicked,
            this, &MyWidget::showChildDialog);
}

MyWidget::~MyWidget()
{
    delete ui;
}

/**
 * @brief MyWidget::showChildDialog
 * 槽函数的实现  创建并显示一个对话框
 */
void MyWidget::showChildDialog()
{
    QDialog *dialog = new QDialog(this);
    dialog->show();
}
