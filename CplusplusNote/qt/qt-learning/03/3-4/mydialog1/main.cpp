#include "mywidget.h"
#include <QApplication>

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 * 3.4 演示信号与槽之通过connect()关联
 *  clicked()信号在QPushButton类中进行了定义，而connect()是QObject类中的函数，因为我们的类继承自QObject，所以可以直接使用它
 *  connect()函数中的四个参数分别是：发送信号的对象、发送的信号、接收信号的对象和要执行的槽
 *  ui下有一个showChildButton  发出了click信号 this对象接收  接收后执行槽函数showChildDialog
 *  connect(ui->showChildButton, &QPushButton::clicked,
            this, &MyWidget::showChildDialog);
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWidget w;
    w.show();

    return a.exec();
}
