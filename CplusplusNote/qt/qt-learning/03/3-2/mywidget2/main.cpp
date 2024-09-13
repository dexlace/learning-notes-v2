#include <QApplication>
#include <QWidget>
#include <QDebug>


/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 * 3-2 演示窗口的几何布局
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget widget;
    widget.resize(400, 300);       // 设置窗口大小
    widget.move(200, 100);         // 设置窗口位置
    widget.show();

    int x = widget.x();
    qDebug("x: %d", x);            // 输出x的值
    int y = widget.y();
    qDebug("y: %d", y);
    QRect geometry = widget.geometry();
    QRect frame = widget.frameGeometry();
    // geometry()和frameGeometry()函数分别返回没有边框和包含边框的窗口框架矩形的值，
    // 其返回值是QRect类型的，就是一个矩形，它的形式是（位置坐标，大小信息），也就是（x，y，宽，高）。
    qDebug() << "geometry: " << geometry << "frame: " << frame;

    // 成为模态框  调用exec函数
    return a.exec();
}
