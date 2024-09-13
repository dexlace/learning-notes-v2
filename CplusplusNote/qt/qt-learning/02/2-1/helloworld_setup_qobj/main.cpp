#include "hellodialog.h"
#include <QApplication>

/**
 * 2-1 本工程演示以下几个要点
 * 1. Q_OBJECT 注意继承自Qt的内部文件，一定在类中加上Q_OBJECT的宏定义
 * 2. 复习命名空间的使用
 * 3. exec()的使用 让QApplication对象进入事件循环，这样当Qt应用程序在运行时便可以接收产生的事件
 * 4. 理解setupUi()函数
 * 5. explicit的用法
 *
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    // 新建一个QApplication对象，用于管理应用程序资源，任何一个QT gui程序需要有
    // 一个QApplication对象 因为Qt程序可以接收命令行参数，所以它需要argc和argv两个参数
    QApplication a(argc, argv);
    HelloDialog w;
    w.show();

    return a.exec();
}
