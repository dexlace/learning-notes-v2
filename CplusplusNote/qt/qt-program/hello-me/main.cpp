#include <QApplication>
#include "hellodialog.h"

int main(int argc, char *argv[])
{
    // 新建一个QApplication对象，用于管理应用程序资源，任何一个QT gui程序需要有
    // 一个QApplication对象 因为Qt程序可以接收命令行参数，所以它需要argc和argv两个参数
    QApplication a(argc, argv);
    HelloDialog w;
    w.show();

    return a.exec();
}
