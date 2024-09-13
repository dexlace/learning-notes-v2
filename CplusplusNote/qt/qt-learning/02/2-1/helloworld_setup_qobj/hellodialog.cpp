#include "hellodialog.h"
// 工程中的hellodialog.ui文件会被UIC编译生成ui_hellodialog.h
#include "ui_hellodialog.h"


// 继承的时候构造函数直接实例化对象成员函数列表
HelloDialog::HelloDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelloDialog)
{
    // HelloDialog自身已经有了一个对象
    // 为指定的widget设置一个ui界面
    // setupUi(this)是由.ui文件生成的类的构造函数，这个函数的作用是对界面进行初始化，
    // 它按照我们在Qt设计器里设计的样子把窗体画出来，把我们在Qt设计器里面定义的信号和槽建立起来。也可以说，setupUi 是我们画界面和写程序之间的桥梁
    ui->setupUi(this);
}


//HelloDialog::HelloDialog(QWidget *parent) :
//    QDialog(parent)
//{
//    ui=new Ui::HelloDialog;
//    ui->setupUi(this);
//}

HelloDialog::~HelloDialog()
{
    delete ui;
}
