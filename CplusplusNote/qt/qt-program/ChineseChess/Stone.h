#ifndef STONE_H
#define STONE_H
#include <QString>

class Stone
{
public:
    Stone();


    enum TYPE{JIANG,CHE,PAO,MA,BING,SHI,XIANG};

    // 棋子的x坐标
    int row;

    // 棋子的y坐标
    int col;

    // 棋子的类型
    TYPE type;

    // 棋子的id
    int id;

    // 棋子是否已经死亡
    bool dead;

    // 棋子是否是红色的
    bool red;



    // 根据类型来返回
    QString getText()
    {
        switch(this->type)
        {   case CHE:
            return "车";
        case MA:
            return "马";
        case PAO:
            return "炮";
        case BING:
            return "兵";
        case SHI:
            return "士";
        case JIANG:
            return "将";
        case XIANG:
            return "象";
        }
        return "错误";

    }

    // 该棋子的初始化函数
    void init(int id);


};

#endif // STONE_H
