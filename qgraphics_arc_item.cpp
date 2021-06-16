#include "qgraphics_arc_item.hpp"

#include <cmath>

#include <QDebug>
#include <QPainter>

QGraphicsArcItem::QGraphicsArcItem()
{
}

// QGraphicsArcItem::QGraphicsArcItem(qreal x, qreal y, qreal width, qreal height,
//                                    QGraphicsItem *parent)
// {
//   // TODO: your code here ...
// }
void QGraphicsArcItem::paint(QPainter *painter,
                             const QStyleOptionGraphicsItem *option,
                             QWidget *widget)
{
  // TODO: your code here ...
  painter->setBrush(Qt::black);
  painter->drawArc(rect(), startAngle(), spanAngle());
}
