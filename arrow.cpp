#include "arrow.h"

#include <QtMath>

Arrow::Arrow(TechnologyFrame* startItem, TechnologyFrame* endItem)
    : myStartItem(startItem), myEndItem(endItem)
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

void Arrow::paint(QPainter *painter, QWidget* target)
{
    QPen myPen = pen();
    myPen.setColor(myColor);
    qreal arrowSize = 20;
    painter->setPen(myPen);
    painter->setBrush(myColor);
    QLineF centerLine(myStartItem->pos(), myEndItem->pos());

    QPointF topleft = QPointF(myEndItem->pos().x() - myEndItem->size().width()/2, myEndItem->pos().y() - myEndItem->size().height()/2);
    QPointF topright = QPointF(myEndItem->pos().x() + myEndItem->size().width()/2, myEndItem->pos().y() - myEndItem->size().height()/2);
    QPointF botleft = QPointF(myEndItem->pos().x() - myEndItem->size().width()/2, myEndItem->pos().y() + myEndItem->size().height()/2);
    QPointF botright = QPointF(myEndItem->pos().x() + myEndItem->size().width()/2, myEndItem->pos().y() + myEndItem->size().height()/2);
    QPolygonF endPolygon({topleft, topright, botleft, botright});

    QPointF p1 = endPolygon.first() + myEndItem->pos();
    QPointF intersectPoint;
    for (int i = 1; i < endPolygon.count(); ++i) {
        QPointF p2 = endPolygon.at(i) + myEndItem->pos();
        QLineF polyLine = QLineF(p1, p2);
        QLineF::IntersectionType intersectionType =
            polyLine.intersects(centerLine, &intersectPoint);
        if (intersectionType == QLineF::BoundedIntersection)
            break;
        p1 = p2;
    }

    mLine = QLineF(intersectPoint, myStartItem->pos());
    double angle = atan2(-line().dy(), line().dx());

   QPointF arrowP1 = line().p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                   cos(angle + M_PI / 3) * arrowSize);
   QPointF arrowP2 = line().p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                   cos(angle + M_PI - M_PI / 3) * arrowSize);

   arrowHead.clear();
   arrowHead << line().p1() << arrowP1 << arrowP2;
   painter->drawLine(line());
   painter->drawPolygon(arrowHead);
}
