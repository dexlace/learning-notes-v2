#ifndef LLKGAME_H
#define LLKGAME_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QPaintEvent>
#include <QPainter>
#include <QPalette>
#include <QList>
#include <QMouseEvent>
#include <QMessageBox>
#include <QFrame>
#include <QLabel>
#include <QTimer>


#define ROWCOUNT 8          //行数
#define COLCOUNT 10         //列数

//图片宽和高
#define PHWIDTH 32
#define PHHEIGHT 32

#define SUMPH 20            //图片种数
#define PERPH 4             //每种图片张数
#define EMPTY -1            //清空图片标志

class llkgame: public QWidget
{
    Q_OBJECT
public:
    llkgame(QWidget *parent=0);
    ~llkgame();

    /////////////////
   void paintEvent(QPaintEvent *);
   void mousePressEvent(QMouseEvent *event);

   void DrawGameMap(QPainter *p);


protected slots:
    void StartNewGame();
    void Hint();

private:
    int arr_map[ROWCOUNT+2][COLCOUNT+2];    //地图数组

    //地图行、列数
    int map_row;
    int map_col;

    QList<QPixmap> ph_list;            //存放图片容器
    QList<int> tmplist;

    //记录鼠标位置
    int str_x;
    int str_y;
    int end_x;
    int end_y;

    int nfirst ;        //记录是否第一次点击

    int win ;

    bool IsWin();           //赢否标志
    int LinkFlag;

    int grade;
    QLabel *gradelabel;
    QLabel *gradelabel1;

    /*
    int link_x1;
    int link_y1;
    int link_x2;
    int link_y2;
    */
    int hintflag;
    int hint_x1;
    int hint_y1;
    int hint_x2;
    int hint_y2;


    int Ilink( int sx , int sy , int ex , int ey );
    int Llink( int sx , int sy , int ex , int ey );
    int Zlink( int sx , int sy , int ex , int ey );
    int Link( int sx , int sy , int ex , int ey );

    bool any( int &sx , int &sy , int &ex , int &ey ) ;

    int reset( ) ;

};

#endif // LLKGAME_H
