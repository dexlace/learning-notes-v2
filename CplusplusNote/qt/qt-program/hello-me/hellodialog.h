#ifndef HELLODIALOG_H
#define HELLODIALOG_H

#include <QDialog>

namespace Ui {
class HelloDialog;
}

class HelloDialog : public QDialog
{
    // 定义了Q_OBJECT宏，扩展了普通C++类的功能，比如下一章要讲的信号和槽功能。必须在类定义的最开始处来定义这个宏
    // 注意继承自Qt的内部文件，一定在类中加上Q_OBJECT的宏定义，Qt会使用MOC将改文件重新编译成moc_mainwindow.cpp文件，这个才是原始的C++类的文件。
    // 所以Qt内置的类文件都不是原生态的C++类，需要Qt编译器再处理，所以继承子Qt的类一定要添加该宏定义，否则编译一定不通过

    Q_OBJECT

public:
    // 显式构造函数，参数是用来指定父窗口的，默认是没有父窗口的。
    explicit HelloDialog(QWidget *parent = 0);
    ~HelloDialog();

private:
    Ui::HelloDialog *ui;
};

#endif // HELLODIALOG_H
