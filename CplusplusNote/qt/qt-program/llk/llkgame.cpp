#include "llkgame.h"

llkgame::llkgame(QWidget *parent)
{
    //变量初始化
    map_row = ROWCOUNT+2;
    map_col = COLCOUNT+2;

    str_x = EMPTY;
    str_y = EMPTY;
    end_x = EMPTY;
    end_y = EMPTY;

    nfirst = 0 ;
    LinkFlag = 0;

    grade = 0;
    win = 0 ;
/*
    link_x1 = EMPTY;
    link_y1 = EMPTY;
    link_x2 = EMPTY;
    link_y1 = EMPTY;
  */
    hintflag = 0;
    hint_x1 = EMPTY;
    hint_y1 = EMPTY;
    hint_x2 = EMPTY;
    hint_y2 = EMPTY;


    QPainter px(this);

    //地图数组初始化
    for(int i = 0 ; i < map_row ; i++)
    {
        for(int j = 0 ; j < map_col ; j++)
        {
            arr_map[i][j] = EMPTY;
        }
    }
    gradelabel = new QLabel(this);
    gradelabel->setText("<font color=red>your score:</font>");

    gradelabel->setGeometry(350,90,200,50);

    gradelabel1=new QLabel(this);
    gradelabel1->setText(QString::number(grade,10));
    gradelabel1->setGeometry(420,90,30,50);

    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::yellow);
    gradelabel1->setPalette(pe);

}

llkgame::~llkgame()
{

}

//=====================================================================//

void llkgame::StartNewGame()
{
    int i , j;

    win = 1;

    //初始化地图数组
    for(i=0 ; i<map_row ; i++)
    {
        for(j=0 ; j<map_col ; j++)
        {
            arr_map[i][j] = EMPTY;
        }
    }

    str_x = EMPTY;
    str_y = EMPTY;
    end_x = EMPTY;
    end_y = EMPTY;

    hintflag = 0;
    hint_x1 = EMPTY;
    hint_y1 = EMPTY;
    hint_x2 = EMPTY;
    hint_y2 = EMPTY;

    grade = 0;

    //将图片存入容器
    int count ;
    count = 0 ;
    for(i=0 ; i<SUMPH ; i++)
    {
        QString phname = ":/image/"+QString::number(i,10)+".png";
        qDebug(phname.toLatin1());
        QPixmap pixmap(phname);
        ph_list.append(pixmap);

        for(j=0 ; j<PERPH ; j++)
        {
            count ++ ;
            tmplist.append(i);
            if( count >= 80 )
                break ;
        }
        if( count >= 80 )
            break ;
    }

//将图片随机存入地图数组
    for(i=1 ; i<map_row-1 ; i++)
    {
        for(j=1 ; j<map_col-1 ; j++)
        {
         //   int dex = (int(rand()*0.1+rand()*0.01+rand()))%tmplist.size();
               int dex = (int(rand()))%tmplist.size();
            //   int dex = 1 ;
            arr_map[i][j] = tmplist.at(dex);
            //arr_map[i][j] = 1;
            tmplist.removeAt(dex);
        }
    }
    update();
    qDebug("StartNewGame");
}

//=====================================================================//

void llkgame::DrawGameMap(QPainter *p)
{
    int i , j;
    //根据地图数组将容器中对应图片画出来
    for(i=1 ; i<map_row-1 ; i++)
    {
        for(j=1 ; j<map_col-1 ; j++)
        {
            if(arr_map[i][j] == EMPTY)
            {               
                continue;
            }

            p->drawPixmap((j-1)*(PHWIDTH),(i-1)*(PHHEIGHT),PHWIDTH,PHHEIGHT,ph_list.at(arr_map[i][j]));

        }
    }

    if(str_x != EMPTY && str_y != EMPTY && arr_map[str_x][str_y] != EMPTY && !hintflag)
    {
        QPen mypen;
        mypen.setColor(Qt::red);
        mypen.setWidth(2);
        p->setPen(mypen);
        p->drawLine((str_y-1)*PHWIDTH,(str_x-1)*PHHEIGHT,str_y*PHWIDTH,(str_x-1)*PHHEIGHT);
        p->drawLine(str_y*PHWIDTH,(str_x-1)*PHHEIGHT,str_y*PHWIDTH,str_x*PHHEIGHT);
        p->drawLine(str_y*PHWIDTH,str_x*PHHEIGHT,(str_y-1)*PHWIDTH,str_x*PHHEIGHT);
        p->drawLine((str_y-1)*PHWIDTH,str_x*PHHEIGHT,(str_y-1)*PHWIDTH,(str_x-1)*PHHEIGHT);
    }

    if(hintflag)
    {
        QPen HintPen;
        HintPen.setColor(Qt::green);
        HintPen.setWidth(2);
        p->setPen(HintPen);

        p->drawLine((hint_y1-1)*PHWIDTH,(hint_x1-1)*PHHEIGHT,hint_y1*PHWIDTH,(hint_x1-1)*PHHEIGHT);
        p->drawLine(hint_y1*PHWIDTH,(hint_x1-1)*PHHEIGHT,hint_y1*PHWIDTH,hint_x1*PHHEIGHT);
        p->drawLine(hint_y1*PHWIDTH,hint_x1*PHHEIGHT,(hint_y1-1)*PHWIDTH,hint_x1*PHHEIGHT);
        p->drawLine((hint_y1-1)*PHWIDTH,hint_x1*PHHEIGHT,(hint_y1-1)*PHWIDTH,(hint_x1-1)*PHHEIGHT);

        p->drawLine((hint_y2-1)*PHWIDTH,(hint_x2-1)*PHHEIGHT,hint_y2*PHWIDTH,(hint_x2-1)*PHHEIGHT);
        p->drawLine(hint_y2*PHWIDTH,(hint_x2-1)*PHHEIGHT,hint_y2*PHWIDTH,hint_x2*PHHEIGHT);
        p->drawLine(hint_y2*PHWIDTH,hint_x2*PHHEIGHT,(hint_y2-1)*PHWIDTH,hint_x2*PHHEIGHT);
        p->drawLine((hint_y2-1)*PHWIDTH,hint_x2*PHHEIGHT,(hint_y2-1)*PHWIDTH,(hint_x2-1)*PHHEIGHT);

        hint_x1 = EMPTY;
        hint_y1 = EMPTY;
        hint_x2 = EMPTY;
        hint_y2 = EMPTY;

        hintflag  = 0;

    }

    qDebug("DrawNewGame");
}

//=====================================================================//

//直连
int llkgame::Ilink(int sx, int sy, int ex, int ey)
{
    int max , min , i ;
    if( sx == ex )              //y方向直连
    {
        //找出y坐标大的点
        if( sy < ey )
        {
            max = ey ; min = sy ;
        }
        else
        {
            max = sy ; min = ey ;
        }
        for( i = min+1 ; i < max ; i ++ )
        {
            if( arr_map[sx][i] != EMPTY )
                return 0 ;
        }
        return 1 ;
    }
    if( sy == ey )
    {
        if( sx < ex )
        {
            max = ex ; min = sx ;
        }
        else
        {
            max = sx ; min = ex ;
        }
        for( i = min+1 ; i < max ; i ++ )
        {
            if( arr_map[i][sy] != EMPTY )
                return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}

//=====================================================================//

//一个拐点
int llkgame::Llink(int sx, int sy, int ex, int ey)
{
    int cx , cy , dx , dy ;
    cx = sx , cy = ey ;
    dx = ex , dy = sy ;
    if( Ilink(sx,sy,ex,ey) )
        return 1 ;
    if( (arr_map[cx][cy]==EMPTY&&Ilink(sx,sy,cx,cy)&&Ilink(cx,cy,ex,ey))
      ||(arr_map[dx][dy]==EMPTY&&Ilink(sx,sy,dx,dy)&&Ilink(dx,dy,ex,ey)))
        return 1 ;
    return 0 ;
}

//=====================================================================//

//两个拐点
int llkgame::Zlink(int sx, int sy, int ex, int ey)
{
    //map_row
    //map_col
    int i;
  /*  int maxx , maxy , minx , miny , i ;

    if( sx > ex )
    {
        maxx = sx ; minx = ex ;
    }
    else
    {
        maxx = ex ; minx = sx ;
    }
    if( sy > ey )
    {
        maxy = sy ; miny = ey ;
    }
    else
    {
        maxy = ey ; miny = sy ;
    }

    for( i = 0 ; i <= map_row ; i ++ )
    {
        if( (Llink(sx,sy,i,maxx)&&Llink(i,maxx,ex,ey))
          ||(Llink(sx,sy,i,minx)&&Llink(i,minx,ex,ey)))
            return 1 ;
    }
    for( i = 0 ; i <= map_col ; i ++ )
    {
        if( (Llink(sx,sy,maxy,i)&&Llink(maxy,i,ex,ey))
          ||(Llink(sx,sy,miny,i)&&Llink(miny,i,ex,ey)))
            return 1 ;
    }*/
    for(i = ey-1 ; i>=0 ; i--)
    {
        if(arr_map[ex][i] != EMPTY)
        {
            break;
        }
        if(arr_map[ex][i] == EMPTY && Llink(sx,sy,ex,i))
            return 1;
    }
    for(i=ey+1 ; i<=map_col ; i++)
    {
        if(arr_map[ex][i] != EMPTY)
            break;
        if(arr_map[ex][i] == EMPTY && Llink(sx,sy,ex,i))
            return 1;
    }
    for(i=ex+1 ; i>=0 ; i++)
    {
        if(arr_map[i][ey] != EMPTY)
            break;
        if(arr_map[i][ey] == EMPTY && Llink(sx,sy,i,ey))
            return 1;
    }
    for(i=ex-1 ; i<=map_row ; i--)
    {
        if(arr_map[i][ey] != EMPTY)
            break;
        if(arr_map[i][ey]== EMPTY && Llink(sx,sy,i,ey))
            return 1;
    }
    return 0 ;
}

//=====================================================================//

//判断连接函数
int llkgame::Link(int sx, int sy, int ex, int ey)
{
    if( Ilink(sx,sy,ex,ey) )
    {
        qDebug("Ilink");
        return 1;
    }
    else
    {
       if( Llink(sx,sy,ex,ey) )
        {
           qDebug("Llink");
           return 1 ;
       }
       else
       {
           if( Zlink(sx,sy,ex,ey) )
           {
               qDebug("Zlink");
               return 1 ;
           }
           else
           {
               return 0;
           }
       }
   }
}

//=====================================================================//

//判断输赢函数
bool llkgame::IsWin()
{
    qDebug("IsWin");
    int i , j;
    for(i=1 ; i<map_row-1 ; i++)
    {
        for(j=1 ; j<map_col-1 ; j++)
        {
            if(arr_map[i][j] != EMPTY)
            {
                qDebug("IsWin return false");
               return false;
            }

        }
    }
    return true;
    qDebug("IsWin return true");
}

//=====================================================================//

void llkgame::paintEvent(QPaintEvent *)
{
    //窗口事件
    QPainter p(this);
    DrawGameMap(&p);
    qDebug("paintEvent");
}

//=====================================================================//

void llkgame::mousePressEvent(QMouseEvent *event)
{
    //鼠标事件
//    qDebug("mousePressEvent");

    int y = (event->x()/PHWIDTH)+1;
    int x = (event->y()/PHHEIGHT)+1;

    qDebug("mousePressEvent %d %d", x , y );
    if((x <= (ROWCOUNT))&&(y <= (COLCOUNT)))
    {
     //   tx = x + 1 ; ty = y + 1 ;
        qDebug("nfirst = %d",nfirst);
        if( nfirst )
        {
            if( str_x == x && str_y == y )
            {
                ;
            }
            else
            {

                end_x = x ; end_y = y ;
            //    for( int i = 0 ; i <= 8 ; i ++)
            //        qDebug("%d %d %d %d %d %d %d %d %d %d",arr_map[i][0],arr_map[i][1],arr_map[i][2],arr_map[i][3],arr_map[i][4],arr_map[i][5],arr_map[i][6],arr_map[i][7],arr_map[i][8],arr_map[i][9],arr_map[i][10]);
                qDebug("Link str %d %d end %d %d", str_x , str_y , end_x , end_y );
                qDebug("%d %d",arr_map[str_x][str_y] , arr_map[end_x][end_y]);
                if( arr_map[str_x][str_y] == arr_map[end_x][end_y] && Link( str_x , str_y , end_x , end_y ))
                {
                    qDebug("link susses");
                    nfirst = 0 ;
                    arr_map[str_x][str_y] = EMPTY ;
                    arr_map[end_x][end_y] = EMPTY ;

                    if(win)
                    {
                        grade += 10;
                        gradelabel1->setText(QString::number(grade,10));
                    }
                    //update();
                }
                else
                {
                    str_x = end_x ; str_y = end_y ;
                    end_x = -1 ; end_y = -1 ;
                }
            }
        }
        else
        {
            str_x = x ; str_y = y ; nfirst = 1 ;
        }
    }
    //判断输赢
    if(win && IsWin())
    {
        QMessageBox::information(this,"YOU WIN",tr("YOU ARE WIN!"));
        StartNewGame();
    }
    update();
    qDebug("str_x=%d str_y=%d end_x = %d end_y = %d", str_x , str_y , end_x , end_y );

}

//=====================================================================//

bool llkgame::any(int &sx, int &sy, int &ex, int &ey)
{
    for( sx = 1 ; sx < map_row-1 ; sx ++ )
    {
        for( sy = 1 ; sy < map_col-1 ; sy ++ )
        {
            if( arr_map[sx][sy] != EMPTY )
            {
                for( ex = 1 ; ex < map_row-1 ; ex ++ )
                {
                    for( ey =  1 ; ey < map_col-1 ; ey ++ )
                    {
                        if( !(sx==ex&&sy==ey)&&arr_map[sx][sy] == arr_map[ex][ey] )
                        {
                            if( Link( sx , sy , ex , ey ) )
                            {
                                qDebug("any return 1") ;
                                return true ;
                            }
                        }
                    }
                }
            }
        }
    }
    qDebug("any return 0") ;
    return false ;
}
//=====================================================================//
int llkgame::reset()
{

    int i , j , size ;
    size = 0 ;
    for( i = 1 ; i < map_row-1 ; i ++ )
    {
        for( j = 1 ; j < map_col-1 ; j ++ )
        {
            if( arr_map[i][j] != EMPTY )
            {
                tmplist.append(arr_map[i][j]) ;
                size ++ ;
            }
        }
    }

    for( i = 1 ; i < map_row-1 ; i ++ )
    {
        for( j = 1 ; j < map_col-1 ; j ++ )
        {
            if( arr_map[i][j] != EMPTY )
            {
                int dex = (int(rand()))%size;
                arr_map[i][j] = tmplist.at(dex);
                tmplist.removeAt(dex);
                size -- ;
            }
        }
    }
    update();
    return 0 ;

}
//=====================================================================//
//提示
void llkgame::Hint()
{
    qDebug("Hint Running");
    if(any(hint_x1 ,hint_y1 , hint_x2 , hint_y2))
    {
        qDebug("hintflag return 1");
        hintflag = 1 ;
    }
    else
    {
        if(!IsWin())
        {
            qDebug("hintflag return 0");
            hintflag = 0;
            //QMessageBox::information(this,"OVER",tr("GAME OVER"));
            reset();
        }

    }
    update();
}

//=====================================================================//
