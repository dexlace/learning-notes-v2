#include <QApplication>
#include <QDialog>
#include <QLabel>


/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 * 2-2 本工程演示以下几个要点
 * 1. 演示无ui文件下的工程
 * 2. 演示指定父窗口
 * 3. 演示一些其他设置
 */
int main(int argc, char *argv[])
{
    // 新建一个QApplication对象，用于管理应用程序资源，任何一个QT gui程序需要有
    // 一个QApplication对象 因为Qt程序可以接收命令行参数，所以它需要argc和argv两个参数
    // GUI 程序是 QApplication，非 GUI 程序是
//    QCoreApplication。QApplication 实际上是 QCoreApplication 的子类。）开始，后面才
//    是实际业务的代码。这个对象用于管理 Qt 程序的生命周期开启事件循环
    QApplication a(argc, argv);
    QDialog w;
    w.resize(400, 300);
    // 新建了一个QLabel对象，并将QDialog对象作为参数，表明了对话框是它的父窗口，也就是说这个标签放在对话框窗口中
    QLabel label(&w);
    label.move(120, 120);
    // 添加的QObject::tr()函数可以实现多语言支持，一般建议程序中所有要显示到界面上的字符串都使用tr()函数括起来
    label.setText(QObject::tr("Hello World! 你好Qt！！！"));
    // 默认可视部件对象都是不可见的，需要用show函数显示出来
    w.show();
    // 让QApplication对象进入事件循环，这样当Qt应用程序在运行时便可以接收产生的事件
    return a.exec();
}
