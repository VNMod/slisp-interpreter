#ifndef REPL_WIDGET_HPP
#define REPL_WIDGET_HPP

#include <QWidget>
#include <QLineEdit>
#include <QString>
#include <QVector>

class REPLWidget : public QWidget
{
  Q_OBJECT

private:
  QLineEdit *lineEdit;

  int index;

  QVector<QString> history;

public:
  REPLWidget(QWidget *parent = nullptr);
  void keyPressEvent(QKeyEvent *event);

signals:
  void lineEntered(QString entry);

private slots:
  void changed();
};

#endif
