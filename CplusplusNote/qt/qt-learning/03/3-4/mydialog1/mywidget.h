#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();

private:
    Ui::MyWidget *ui;

    // 槽函数声明 槽一般使用slots关键字进行修饰（Qt 4中必须使用，Qt 5使用新connect语法时可以不用，为了与一般函数进行区别，建议使用），
    // 这里使用了public slots，表明这个槽可以在类外被调用
public slots:
    void showChildDialog();

};

#endif // MYWIDGET_H
