#include "ChessBoard.h"
#include <QPainter>
/**
 * @brief ChessBoard::ChessBoard
 * @param parent
 * 1.  构造函数 初始化  生成每个棋子的位置
 */
ChessBoard::ChessBoard(QWidget *parent) : QWidget{parent} {
  // 要知道32颗棋子的初始化坐标 在构造函数中初始化
  for (int i = 0; i < 32; i++) {
    s[i].init(i);
  }
  selectId = -1;
}

/**
 * @brief ChessBoard::paintEvent
 * 2. 重绘棋子
 */
void ChessBoard::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  int d = 40;

  // 1. 棋子的半径
  r = d / 2;

  // 2. 要画象棋的十条横线
  // 第一条线起点是(d,d) 终点是(d+8*d,d)
  // 第二条线是(d,2*d)  终点是(d+8*d,2*d)
  for (int i = 1; i <= 10; i++) {
    painter.drawLine(QPoint(d, i * d), QPoint(9 * d, i * d));
  }

  // 3. 画象棋的九条竖线
  for (int i = 1; i <= 9; i++) {
    // (d,d) (d,10d)
    // (2d,d) (2d,10d)
    if (i == 1 || i == 9) {
      painter.drawLine(QPoint(i * d, d), QPoint(i * d, 10 * d));
    } else {
      painter.drawLine(QPoint(i * d, d), QPoint(i * d, 5 * d));
      painter.drawLine(QPoint(i * d, 6 * d), QPoint(i * d, 10 * d));
    }
  }
  // 快捷键 option+commond+上 复制到上一行
  // 快捷键 option+commond+下 复制到下一行

  // 画九宫格
  painter.drawLine(QPoint(4 * d, d), QPoint(6 * d, 3 * d));
  painter.drawLine(QPoint(4 * d, 3 * d), QPoint(6 * d, d));
  painter.drawLine(QPoint(4 * d, 10 * d), QPoint(6 * d, 8 * d));
  painter.drawLine(QPoint(4 * d, 8 * d), QPoint(6 * d, 10 * d));

  // 4. 初始化  绘制32颗棋子
  for (int i = 0; i < 32; i++) {
    drawStone(painter, i);
  }
}

/**
 * @brief ChessBoard::mouseReleaseEvent
 * @param ev
 * 3. 鼠标释放事件
 */
void ChessBoard::mouseReleaseEvent(QMouseEvent *ev) {
  QPoint pt = ev->pos();
  // 将pt转化成象棋的行列值
  // 判断这个行列值上面有没有棋子
  int row, col;

  int clickedId = -1;
  // 1. 判断点的区域是否合法 并拿到点击区域的坐标
  bool bRet = getRowCol(pt, row, col);
  if (!bRet) {
    return;
  }

  // 2. 找到被点的位置的棋子id
  for (int i = 0; i < 32; i++) {
    if (s[i].row == row && s[i].col == col && s[i].dead == false) {
      clickedId = i;
      break;
    }
  }

  // 3. 第一次选中棋子
  if (selectId == -1) {
    // 将会重绘
    if (clickedId != -1) {
      selectId = clickedId;
      update();
    }
  } else {
    // 移动棋子 更新棋子的坐标
    s[selectId].row = row;
    s[selectId].col = col;
    // 如果被点的地方有棋子的话 那么该棋子将会死亡
    if (clickedId != -1) {
      s[clickedId].dead = true;
    }
    selectId = -1;
    update();
  }
}



/**
 * @brief ChessBoard::getRowCol
 * @param pt
 * @param row
 * @param col
 * @return
 * 4. 根据鼠标像素值得到坐标  效率不高 应该改进
 */
bool ChessBoard::getRowCol(QPoint pt, int &row, int &col) {
  for (row = 0; row <= 9; row++) {
    for (col = 0; col <= 8; col++) {
      QPoint c = getStonePoint(row, col);
      int dx = c.x() - pt.x();
      int dy = c.y() - pt.y();
      int dist = dx * dx + dy * dy;
      if (dist < r * r) {
        return true;
      }
    }
  }
  return false;
}

/**
 * @brief ChessBoard::drawStone
 * @param painter
 * @param id
 * 5. 画棋子
 */
void ChessBoard::drawStone(QPainter &painter, int id) {
  if (s[id].dead) {
    return;
  }
  QPoint center = getStonePoint(id);

  // 如果是选中的 那么置灰色 否则置黄色
  if (id == selectId) {
    painter.setBrush(QBrush(Qt::gray));
  } else {
    painter.setBrush(QBrush(Qt::yellow));
  }
  // 黑色画笔画椭圆
  painter.setPen(Qt::black);
  painter.drawEllipse(center, r, r);
  // 矩形左上角的坐标  长宽都是2r
  QRect rec = QRect(center.x() - r, center.y() - r, r * 2, r * 2);
  // 如果是红色的  字符串给绘制成红色的
  if (s[id].red) {
    painter.setPen(Qt::red);
  }

  painter.setFont(QFont("system", r, 700));
  // 绘制字符串 居中对齐
  painter.drawText(rec, s[id].getText(), QTextOption(Qt::AlignCenter));
}


/**
 * @brief ChessBoard::getStonePoint
 * @param rowIndex
 * @param colIndex
 * @return
 * 6. 获取棋子的行和列坐标的像素值
 */
QPoint ChessBoard::getStonePoint(int rowIndex, int colIndex) {

  QPoint res;

  // 坐标00的坐标是rr 01的坐标是2rr=(1+1)rr
  // 坐标10的坐标是r2r=r(1+1)r
  res.rx() = ((colIndex + 1) * r * 2);
  res.ry() = ((rowIndex + 1) * r * 2);

  return res;
}

// 根据id拿到棋子的行和列坐标
QPoint ChessBoard::getStonePoint(int id) {
  return getStonePoint(s[id].row, s[id].col);
}
