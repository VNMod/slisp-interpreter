#include "canvas_widget.hpp"

#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLayout>

CanvasWidget::CanvasWidget(QWidget *parent) : QWidget(parent)
{
  // TODO: your code here...
  scene = new QGraphicsScene(this);

  QGraphicsView *view = new QGraphicsView(scene);

  QWidget *window = new QWidget;

  QVBoxLayout *layout = new QVBoxLayout(window);
  layout->addWidget(view);

  setLayout(layout);
}

void CanvasWidget::addGraphic(QGraphicsItem *item)
{
  // TODO: your code here...
  // QPainter *painter = new QPainter;
  // item->paint(painter, this, view);
  scene->addItem(item);
}
