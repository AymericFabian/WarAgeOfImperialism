#include "arrow.h"

#include <QtMath>

Arrow::Arrow(TechnologyFrame* startItem, TechnologyFrame* endItem, Position startPos, Position endPos)
    : myStartItem(startItem), myEndItem(endItem), startPos(startPos), endPos(endPos)
{
    mPen = QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
}

QRectF Arrow::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

QPointF Arrow::pixelPosition(TechnologyFrame* frame, Position pos)
{
    QPointF position = frame->pos();

    switch(pos)
    {
    case Position::TopLeft:
        break;
    case Position::TopLeftMid:
        position.setX(frame->pos().x() + frame->width()/4);
        break;
    case Position::Top:
        position.setX(frame->pos().x() + frame->width()/2);
        break;
    case Position::TopRightMid:
        position.setX(frame->pos().x() + 3*frame->width()/4);
        break;
    case Position::TopRight:
        position.setX(frame->pos().x() + frame->width());
        break;
    case Position::RightTopMid:
        position.setX(frame->pos().x() + frame->width());
        position.setY(frame->pos().y() + frame->height()/4);
        break;
    case Position::Right:
        position.setX(frame->pos().x() + frame->width());
        position.setY(frame->pos().y() + frame->height()/2);
        break;
    case Position::RightBotMid:
        position.setX(frame->pos().x() + frame->width());
        position.setY(frame->pos().y() + 3*frame->height()/4);
        break;
    case Position::BotRight:
        position.setX(frame->pos().x() + frame->width());
        position.setY(frame->pos().y() + frame->height());
        break;
    case Position::BotRightMid:
        position.setX(frame->pos().x() + 3*frame->width()/4);
        position.setY(frame->pos().y() + frame->height());
        break;
    case Position::Bot:
        position.setX(frame->pos().x() + frame->width()/2);
        position.setY(frame->pos().y() + frame->height());
        break;
    case Position::BotLeftMid:
        position.setX(frame->pos().x() + frame->width()/4);
        position.setY(frame->pos().y() + frame->height());
        break;
    case Position::BotLeft:
        position.setY(frame->pos().y() + frame->height());
        break;
    case Position::LeftBotMid:
        position.setY(frame->pos().y() + 3*frame->height()/4);
        break;
    case Position::Left:
        position.setY(frame->pos().y() + frame->height()/2);
        break;
    case Position::LeftTopMid:
        position.setY(frame->pos().y() + frame->height()/4);
        break;
    }

    return position;
}

void Arrow::paint(QPainter *painter, QWidget* /*target*/)
{
    QPen myPen = pen();
    myPen.setColor(myColor);
    qreal arrowSize = 15;
    painter->setPen(myPen);
    painter->setBrush(myColor);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::HighQualityAntialiasing);

    mLine = QLineF(pixelPosition(endItem(), endPos), pixelPosition(startItem(), startPos));
    double angle = atan2(-line().dy(), line().dx());

    QPointF arrowP1 = line().p1() + QPointF(sin(angle + M_PI / 2.5) * arrowSize,
                                            cos(angle + M_PI / 2.5) * arrowSize);
    QPointF arrowP2 = line().p1() + QPointF(sin(angle + M_PI - M_PI / 2.5) * arrowSize,
                                            cos(angle + M_PI - M_PI / 2.5) * arrowSize);

    arrowHead.clear();
    arrowHead << line().p1() << arrowP1 << arrowP2;
    painter->drawLine(line());
    painter->drawPolygon(arrowHead);
}
