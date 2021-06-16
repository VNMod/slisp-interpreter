#include "qt_interpreter.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <fstream>

#include <QBrush>
#include <QDebug>

#include "qgraphics_arc_item.hpp"
#include "expression.hpp"
#include "interpreter_semantic_error.hpp"

#define DEFAULT_POINT_RADIUS 2

QtInterpreter::QtInterpreter(QObject *parent) : QObject(parent)
{
}

void QtInterpreter::parseAndEvaluate(QString entry)
{
  interp.clearAST(); // re-clear the AST for the same interpreter

  std::istringstream incomingstream(entry.toStdString());

  bool ok = interp.parse(incomingstream);

  if (!ok)
  {
    emit error(QString::fromStdString("Error occured due to incorrect parse."));
  }
  else
  {
    try
    {
      Expression result = interp.eval();

      updatemessages(result);

      std::vector<Atom> graphics = interp.getGraphicsatoms();

      updatinggraphics(graphics);

      interp.clearGraphics(); // clears the vector of Graphics atoms
    }
    catch (const InterpreterSemanticError &e)
    {
      QString semanticerror = QString::fromStdString(e.what());
      emit error(semanticerror);
    }
  }
}

void QtInterpreter::parse(std::istream &fi)
{

  interp.clearAST(); // re-clear the AST for the same interpreter

  // Parse the incoming file stream
  bool ok = interp.parse(fi);

  if (!ok)
  {
    emit error(QString::fromStdString("Error occured due to incorrect parse."));
  }
  else
  {
    try
    {
      Expression result = interp.eval();

      updatemessages(result);

      std::vector<Atom> graphics = interp.getGraphicsatoms();

      updatinggraphics(graphics);

      interp.clearGraphics(); // clears the vector of Graphics atoms
    }
    catch (const InterpreterSemanticError &e)
    {
      QString semanticerror = QString::fromStdString(e.what());
      emit error(semanticerror);
    }
  }
}

void QtInterpreter::updatemessages(Expression result)
{
  if (result.head.type == NumberType)
  {
    std::string x;
    std::ostringstream oss;
    oss << result.head.value.num_value;
    x = "(" + oss.str() + ")";

    emit info(QString::fromStdString(x));
  }
  // else if (result.head.type == SymbolType)
  // {
  //   emit info(QString::fromStdString(("(" + result.head.value.sym_value + ")")));
  // }
  else if (result.head.type == BooleanType)
  {
    if (result.head.value.bool_value)
    {
      emit info(QString::fromStdString(("(True)")));
    }
    else if (!result.head.value.bool_value)
    {
      emit info(QString::fromStdString(("(False)")));
    }
  }
  else if (result.head.type == PointType)
  {
    QString x;
    x = "(" + QString::number(result.head.value.point_value.x) + "," + QString::number(result.head.value.point_value.y) + ")";
    emit info(x);
  }
  else if (result.head.type == LineType)
  {
    QString x;
    x = "((" + QString::number(result.head.value.line_value.first.x) + "," + QString::number(result.head.value.line_value.first.y) + ")(" + QString::number(result.head.value.line_value.second.x) + "," + QString::number(result.head.value.line_value.second.y) + "))";
    emit info(x);
  }
  else if (result.head.type == ArcType)
  {
    QString x;
    x = "((" + QString::number(result.head.value.arc_value.center.x) + "," + QString::number(result.head.value.arc_value.center.y) + ")(" + QString::number(result.head.value.arc_value.start.x) + "," + QString::number(result.head.value.arc_value.start.y) + ")(" + QString::number(result.head.value.arc_value.span) + "))";
    emit info(x);
  }
}

void QtInterpreter::updatinggraphics(std::vector<Atom> &graphics)
{
  for (int i = 0; i < graphics.size(); i++)
  {
    std::string x = "(None)";
    emit info(QString::fromStdString(x));
    if (graphics[i].type == PointType)
    {
      QGraphicsEllipseItem *item = new QGraphicsEllipseItem;
      // The rectangle is constructed with (x, y) as its top-left corner and a given width and height.
      // So, if you'd like to center your point at a coordinate (x,y) we must subtract the height and width
      // to get the specific point.
      item->setBrush(QBrush(Qt::black));
      item->setRect(graphics[i].value.point_value.x - DEFAULT_POINT_RADIUS, graphics[i].value.point_value.y - DEFAULT_POINT_RADIUS, 2 * DEFAULT_POINT_RADIUS, 2 * DEFAULT_POINT_RADIUS);
      emit drawGraphic(item);
    }
    else if (graphics[i].type == LineType)
    {
      Line l;
      QGraphicsLineItem *item = new QGraphicsLineItem;
      Point start = graphics[i].value.line_value.first;
      Point finish = graphics[i].value.line_value.second;
      item->setLine(start.x, start.y, finish.x, finish.y);
      emit drawGraphic(item);
    }
    else if (graphics[i].type == ArcType)
    {
      QGraphicsArcItem *item = new QGraphicsArcItem;
      item->setBrush(QBrush(Qt::black));
      Point center = graphics[i].value.arc_value.center;
      Point start = graphics[i].value.arc_value.start;
      double sp = graphics[i].value.arc_value.span;

      double radius = sqrt(pow((center.y - start.y), 2) + pow((center.x - start.x), 2));
      item->setRect(center.x - radius, center.y - radius, 2 * radius, 2 * radius);

      double sp_degrees = sp * 180 / atan2(0, -1);

      // central angle:
      double start_degrees = -(atan2((start.y - center.y), (start.x - center.x)) * 180 / atan2(0, -1));

      // Note: setStartAngle and setSpanAngle set an angle for an ellipse
      // segment to a number which is in 16ths of a degree. Hence, the resulting degree
      // is multiplied by 16.

      item->setStartAngle(16 * start_degrees);
      item->setSpanAngle(16 * sp_degrees);
      emit drawGraphic(item);
    }
  }
}