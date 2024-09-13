#include <QtWidgets>


/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 * 3-1 演示基础组件的用法 QWidget QLabel
 * 1. 默认parent参数是0时为顶级窗口
 * 2. 理解父窗口的概念
 * 3. 了解窗口类型的参数设置：Qt::FramelessWindowHint用来产生一个没有边框的窗口
 *    Qt::WindowStaysOnTopHint用来使该窗口停留在所有其它窗口上面
 * 4. 进一步理解exec()
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 新建QWidget类对象，默认parent参数是0，所以它是个窗口
    // Qt::FramelessWindowHint用来产生一个没有边框的窗口
    QWidget *widget = new QWidget(0, Qt::Dialog | Qt::FramelessWindowHint);
    // 设置窗口标题
    widget->setWindowTitle(QObject::tr("我是widget"));


    // 新建QLabel对象，默认parent参数是0，所以它是个窗口
    // Qt::WindowStaysOnTopHint用来使该窗口停留在所有其它窗口上面
    QLabel *label = new QLabel(0, Qt::SplashScreen | Qt::WindowStaysOnTopHint);
    label->setWindowTitle(QObject::tr("我是label"));
    // 设置要显示的信息
    label->setText(QObject::tr("label:我是个窗口"));
    // 改变部件大小，以便能显示出完整的内容
    label->resize(180, 20);


    // 窗口就是没有父部件的部件，所以又称为顶级部件（top-level widget）。与其相对的是非窗口部件，又称为子部件（child widget）

    // label2指定了父窗口为widget，所以不是窗口
    QLabel *label2 = new QLabel(widget);
    label2->setText(QObject::tr("label2:我不是独立窗口，只是widget的子部件"));
    label2->resize(250, 20);
    // 在屏幕上显示出来
    label->show();
    widget->show();

    int ret = a.exec();
    delete label;
    delete widget;
    return ret;
}




























