#include "repl_widget.hpp"

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QLayout>
#include <QKeyEvent>
#include <QDebug>

REPLWidget::REPLWidget(QWidget *parent) : QWidget(parent)
{
  QLabel *label = new QLabel("slisp> ");
  lineEdit = new QLineEdit;

  index = history.size();

  // We must set focus in order to receive a key press event
  lineEdit->setFocus();

  QWidget *window = new QWidget;

  QHBoxLayout *layout = new QHBoxLayout(window);
  layout->addWidget(label);
  layout->addWidget(lineEdit);

  setLayout(layout);

  // connect the line entered (signal) and the changed slot
  QObject::connect(this, SIGNAL(lineEntered(QString)), this, SLOT(changed()));
}

void REPLWidget::changed()
{
  lineEdit->clear();
}

void REPLWidget::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
  {
    QString line;
    line = lineEdit->text();
    emit lineEntered(line);
    history.push_back(line); // for history mechanism
    index = history.size();  // index must be the latest index value (i.e. size - 1)
  }
  else if (event->key() == Qt::Key_Down)
  {
    if (!history.empty())
    {
      if (index + 1 < history.size())
      {
        // qDebug() << "key down";

        lineEdit->clear();
        index++;
        lineEdit->setText(history[index]);
      }
      else if (index != history.size())
      {
        // qDebug() << "Else if";

        index = history.size();
        lineEdit->clear();
      }
    }
  }
  else if (event->key() == Qt::Key_Up)
  {
    if (!history.empty())
    {
      if (index - 1 > -1)
      {
        // qDebug() << "key up";
        lineEdit->clear();
        index--;
        lineEdit->setText(history[index]);
      }
    }
  }
}