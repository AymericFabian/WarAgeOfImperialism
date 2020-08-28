#ifndef ARROW_H
#define ARROW_H

#include "technologyframe.h"

#include <QPainter>
#include <QLine>

class Arrow
{
public:
    enum class Position { TopLeft, TopLeftMid, Top, TopRightMid, TopRight,
                          RightTopMid, Right, RightBotMid,
                          BotRight, BotRightMid, Bot, BotLeftMid, BotLeft,
                          LeftBotMid, Left, LeftTopMid };

    Arrow(TechnologyFrame* startItem, TechnologyFrame* endItem, Position startPos, Position endPos);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    //void setColor(const QColor &color) { myColor = color; }
    TechnologyFrame *startItem() const { return myStartItem; }
    TechnologyFrame *endItem() const { return myEndItem; }

    QLineF line() const {return mLine;}
    QPen pen() const {return mPen;}

    void paint(QPainter *painter, QWidget *);

private:
    TechnologyFrame *myStartItem;
    TechnologyFrame *myEndItem;
    Position startPos;
    Position endPos;

    QPolygonF arrowHead;
    QColor myColor = Qt::black;

    QPen mPen;
    QLineF mLine;
    QPointF pixelPosition(TechnologyFrame *frame, Position pos);
};

#endif // ARROW_H
