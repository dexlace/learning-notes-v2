#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "llkgame.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    llkgame *game;
    QWidget *llkwidget;

    QPushButton *Hintbutton;
    QPushButton *startbutton;

    QLabel *timerlabel;
    QLabel *timerlabel1;
    QLabel *timerlabel2;

    QTimer *timer1;

    int minute;
    int second;


private slots:
    void setbuttonHint();
    void setgametimer();
};

#endif // MAINWINDOW_H
