#include "mywidget.h"
#include <QApplication>

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 * 3.3 演示模态对话框和非模态对话框
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWidget w;
    w.show();

    // 要使一个对话框成为非模态对话框，我们就可以使用new操作来创建，然后使用show()函数来显示
    // 要想使一个对话框成为模态对话框，只需要调用它的exec()函数

    // 使用show()函数也可以建立模态对话框，只需在其前面使用setModal()函数即可。例如：

    /*QDialog *dialog = new QDialog(this);
    dialog->setModal(true);
    dialog->show();

        现在运行程序，可以看到生成的对话框是模态的。
        但是，它与用exec()函数时的效果是不一样的。
        这是因为调用完show()函数后会立即将控制权交给调用者，那么程序可以继续往下执行。
        而调用exec()函数却不是这样，它只有当对话框被关闭时才会返回。*/

    return a.exec();
}
