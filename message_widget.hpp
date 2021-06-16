#ifndef MESSAGE_WINDOW_HPP
#define MESSAGE_WINDOW_HPP

#include <QString>
#include <QWidget>

#include "qt_interpreter.hpp"

class QLineEdit;

class MessageWidget : public QWidget
{
  Q_OBJECT

private:
  QLineEdit *lineEdit;

public:
  MessageWidget(QWidget *parent = nullptr);

public slots:

  void info(QString message);

  void error(QString message);

  // void clear();
};

#endif
