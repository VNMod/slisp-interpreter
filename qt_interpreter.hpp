#ifndef QT_INTERPRETER_HPP
#define QT_INTERPRETER_HPP

#include <string>

#include <QObject>
#include <QString>
#include <QGraphicsItem>

#include "interpreter.hpp"

class QtInterpreter : public QObject, private Interpreter
{
  Q_OBJECT

private:
  Interpreter interp; // creating the interpreter

public:
  QtInterpreter(QObject *parent = nullptr);

  void parse(std::istream &fi);

  void updatemessages(Expression result);

  void updatinggraphics(std::vector<Atom> &graphics);

signals:

  void drawGraphic(QGraphicsItem *item);

  void info(QString message);

  void error(QString message);

public slots:

  void parseAndEvaluate(QString entry);
};

#endif
