#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    llkwidget = new QWidget(this);
    game = new llkgame(llkwidget);

    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->setSpacing(10);
    hlayout->addWidget(game);
    llkwidget->setLayout(hlayout);

    this->setCentralWidget(llkwidget);
    this->resize(QSize(480,275));           //设置窗口大小
    this->setWindowFlags(Qt::SplashScreen); //设置窗口没标题栏

    this->setWindowOpacity(0.97);            //透明度

 /*
    QFrame *frame = new QFrame;
    frame->setObjectName("backgroup");
    frame->resize(480,275);
    frame->setStyleSheet("QFrame#backgroup{border-image:url(:/image/frame.png)}");
    frame->show();

    //QFrame *frame = new QFrame;
    //frame->resize(480,275);
    QPixmap backpixmap(":/imgae/backgroup.png");
    p.setBrush(this->backgroundRole(),QBrush(backpixmap));
    this->setPalette(p);
    //frame->setMask(backpixmap.mask());
    this->setAutoFillBackground(true);*/


    //frame->show();
    QPalette p;
    llkwidget->setAutoFillBackground(true);
    p.setColor(QPalette::Window,QColor(10,10,105));
    llkwidget->setPalette(p);

    startbutton =new QPushButton(tr("Sart"),this);
    startbutton->setGeometry(QRect(350,230,50,30));

    Hintbutton = new QPushButton(tr("Hint"),this);
    Hintbutton->setGeometry(QRect(410,230,50,30));

    Hintbutton->setEnabled(false);

    minute = 0;
    second = 0;

    timer1 = new QTimer(this);

    timerlabel = new QLabel(this);
    timerlabel->setText("<font color=red>game time:</font>");
    timerlabel->setGeometry(360,70,200,50);
    timerlabel1 = new QLabel(this);
    timerlabel2 = new QLabel(this);
    timerlabel1->setGeometry(430,70,20,50);
    timerlabel2->setGeometry(440,70,20,50);

    timerlabel1->setText("0:");
    timerlabel2->setText("0");

    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::yellow);
    timerlabel1->setPalette(pe);
    timerlabel2->setPalette(pe);


    QLabel *display = new QLabel(this);
    display->setText("<h2><font color=red>hello world !</font></h2>");

    QLabel *display1 = new QLabel(this);
    display1->setText("<h2><font color=red>LianLianKan</font></h2>");

    display->setGeometry(QRect(335,0,200,50));
    display1->setGeometry(QRect(352,25,100,50));

    connect(startbutton,SIGNAL(clicked()),
            game,SLOT(StartNewGame()));
    connect(startbutton,SIGNAL(clicked()),
            this,SLOT(setbuttonHint()));
    connect(Hintbutton,SIGNAL(clicked()),
            game,SLOT(Hint()));

    connect(timer1,SIGNAL(timeout()),
            this,SLOT(setgametimer()));
}

MainWindow::~MainWindow()
{
    delete game;
}

void MainWindow::setbuttonHint()
{
    second = 0 ;
    minute = 0 ;
    timer1->start(1000);
    Hintbutton->setEnabled(true);
}

void MainWindow::setgametimer()
{
    qDebug("timer out");
    if(minute == 59)
    {
        second++;
        minute = 0;
    }

    minute++;

    timerlabel1->setText(QString::number(second,10)+":");
    timerlabel2->setText(QString::number(minute,10));

}
