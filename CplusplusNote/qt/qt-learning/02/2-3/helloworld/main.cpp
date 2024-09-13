#include "ui_hellodialog.h"

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 * 2-3 本工程演示以下几个要点
 * 1. 演示使用UI的情况下的工程
 * 2. 在使用UI的情况下会生成ui_xxx.h文件，使用ui中的内容只需要#include "ui_xxx.h"即可
 * 3. 可以去查看"ui_xxx.h"中的内容
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDialog w;
    // 是ui_xxx.h中的定义
    Ui::HelloDialog ui;
    ui.setupUi(&w);
    w.show();
    return a.exec();
}


