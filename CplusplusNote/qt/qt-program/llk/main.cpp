#include <QApplication>
#include "mainwindow.h"
#include <time.h>
//#include <QTextCodec>


// 注意用gb2312 或者gbk编码
int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
    QApplication a(argc, argv);

//    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
    MainWindow w;
    w.show();

    return a.exec();
}
