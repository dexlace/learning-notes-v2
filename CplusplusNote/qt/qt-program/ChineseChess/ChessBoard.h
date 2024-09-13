#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include "Stone.h"
#include<QMouseEvent>

class ChessBoard : public QWidget
{
    Q_OBJECT
public:
    explicit ChessBoard(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

//    // 点击释放事件
    void mouseReleaseEvent(QMouseEvent * ev);

//    // 根据像素值计算坐标
    bool getRowCol(QPoint pt,int& row,int& col);
    // 棋子
    Stone s[32];

    // 棋子的半径
    int r;

    // 当前棋盘选中的id
    int selectId;

    // 获取棋子的行和列坐标
    QPoint getStonePoint(int rowIndex, int colIndex);

    // 根据id拿到棋子的行和列坐标
    QPoint getStonePoint(int id);

    // 画棋子
    void drawStone(QPainter& painter,int id);


signals:

};

#endif // CHESSBOARD_H
