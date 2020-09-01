#include "star.h"

star::star(QWidget *parent,int type):
    QLabel(parent)
{
    this->setFixedSize(50,50);//设置大小
    this->setFrameShape(QFrame::Box);//设置边框
    //设置图片
    if(type==0)
    {
        this->setStyleSheet("background-image: url(:/star/images/blue_blank.png);");
    }
    else if(type==1)
    {
        this->setStyleSheet("background-image: url(:/star/images/purple_blank.png);");
    }
    else if(type==2)
    {
        this->setStyleSheet("background-image: url(:/star/images/yellow_blank.png);");
    }
    else if(type==3)
    {
        this->setStyleSheet("background-image: url(:/star/images/pink_blank.png);");
    }
    else if(type==4)
    {
        this->setStyleSheet("background-image: url(:/star/images/green_blank.png);");
    }
    else
    {
        this->setStyleSheet("background-image: url(:/star/images/orange_blank.png);");
    }
}
