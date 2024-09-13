#include "mywidget.h"
#include <QApplication>


/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 * 3.5 演示信号与槽之ui使用转到槽
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWidget w;
    w.show();

    return a.exec();
}
