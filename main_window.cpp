#include "main_window.hpp"

#include <iostream>
#include <fstream>

#include <QLayout>

#include "message_widget.hpp"
#include "canvas_widget.hpp"
#include "repl_widget.hpp"
#include "interpreter_semantic_error.hpp"

MainWindow::MainWindow(QWidget *parent) : MainWindow("", parent)
{
}

MainWindow::MainWindow(std::string filename, QWidget *parent) : QWidget(parent)
{
  // TODO: your code here...

  messagewidget = new MessageWidget;
  canvaswidget = new CanvasWidget;
  replwidget = new REPLWidget;
  qtinterp = new QtInterpreter;

  QWidget *window = new QWidget;

  // Grid Layout:
  QVBoxLayout *layout = new QVBoxLayout(window);
  layout->addWidget(messagewidget);
  layout->addWidget(canvaswidget);
  layout->addWidget(replwidget);

  setLayout(layout);
  setWindowTitle("Slisp Interpreter");

  std::ifstream fi;

  if (!filename.empty())
  {
    fi.open(filename); // opening the file to be read
  }

  // connect the line entered from the REPLWidget (signal) and the parseAndEvaluate slot
  QObject::connect(replwidget, SIGNAL(lineEntered(QString)), qtinterp, SLOT(parseAndEvaluate(QString)));

  // connect the info (signal) from QtInterpreter and the message widget's info slot
  QObject::connect(qtinterp, SIGNAL(info(QString)), messagewidget, SLOT(info(QString)));

  // connect the error (signal) from QtInterpreter and the message widget's error slot
  QObject::connect(qtinterp, SIGNAL(error(QString)), messagewidget, SLOT(error(QString)));

  // connect the (signal) from the QtInterpreter for the QGraphicsItem and the canvas widget's addGraphic slot
  QObject::connect(qtinterp, SIGNAL(drawGraphic(QGraphicsItem *)), canvaswidget, SLOT(addGraphic(QGraphicsItem *)));

  // parsing the file:

  if (!filename.empty())
  {
    qtinterp->parse(fi);
  }
}