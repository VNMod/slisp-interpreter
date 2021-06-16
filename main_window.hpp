#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <string>

#include <QWidget>

#include "canvas_widget.hpp"
#include "message_widget.hpp"
#include "repl_widget.hpp"

#include "qt_interpreter.hpp"

class MainWindow : public QWidget
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  MainWindow(std::string filename, QWidget *parent = nullptr);

private:
  QtInterpreter interp;

  CanvasWidget *canvaswidget;
  MessageWidget *messagewidget;
  REPLWidget *replwidget;
  QtInterpreter *qtinterp;
};

#endif
