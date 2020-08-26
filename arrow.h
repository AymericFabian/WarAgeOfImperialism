#ifndef ARROW_H
#define ARROW_H

#include "technologyframe.h"

#include <QPainter>
#include <QLine>

class Arrow
{
public:
    Arrow(TechnologyFrame* startItem, TechnologyFrame* endItem);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    //void setColor(const QColor &color) { myColor = color; }
    TechnologyFrame *startItem() const { return myStartItem; }
    TechnologyFrame *endItem() const { return myEndItem; }

    QLineF line() const {return mLine;}
    QPen pen() const {return mPen;}

    void paint(QPainter *painter, QWidget *target = nullptr);

private:
    TechnologyFrame *myStartItem;
    TechnologyFrame *myEndItem;
    QPolygonF arrowHead;
    QColor myColor = Qt::black;

    QPen mPen;
    QLineF mLine;
};

#endif // ARROW_H
