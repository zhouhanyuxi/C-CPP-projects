#ifndef STAR_H
#define STAR_H

#include <QPushButton>
#include <QLabel>

class star : public QLabel
{
public:
    star(QWidget *parent = 0,int type=0);
};

#endif // STAR_H
