#include "Stone.h"

Stone::Stone()
{

}

void Stone::init(int id)
{
    void init(int id);
    {
        // 初始化 一个对应关系  用结构体数组定义
        struct {
                int row, col;
                Stone::TYPE type;
        } pos[16] = {
            {0, 0, Stone::CHE},   {0, 1, Stone::MA},    {0, 2, Stone::XIANG},
            {0, 3, Stone::SHI},   {0, 4, Stone::JIANG}, {0, 5, Stone::SHI},
            {0, 6, Stone::XIANG}, {0, 7, Stone::MA},    {0, 8, Stone::CHE},

            {2, 1, Stone::PAO},   {2, 7, Stone::PAO},   {3, 0, Stone::BING},
            {3, 2, Stone::BING},  {3, 4, Stone::BING},  {3, 6, Stone::BING},
            {3, 8, Stone::BING},
        };

        this->id=id;
        dead=false;
        red=id<16;

        // command+;格式化
        if (id < 16){
            row=pos[id].row;
            col=pos[id].col;
            type=pos[id].type;
        }else{
            row=9-pos[id-16].row;
            col=8-pos[id-16].col;
            type=pos[id-16].type;
        }
    }

}
