#include "message_widget.hpp"

#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <iostream>

MessageWidget::MessageWidget(QWidget *parent) : QWidget(parent)
{
  // TODO: your code here...

  QLabel *label = new QLabel("Message: ");
  lineEdit = new QLineEdit;
  lineEdit->setReadOnly(true);
  lineEdit->setFocus();

  // QWidget *window = new QWidget;

  QHBoxLayout *layout = new QHBoxLayout;
  layout->addWidget(label);
  layout->addWidget(lineEdit);

  setLayout(layout);
}

void MessageWidget::info(QString message)
{
  lineEdit->clear();
  QPalette *palette = new QPalette();
  palette->setColor(QPalette::Base, Qt::white);
  palette->setColor(QPalette::Text, Qt::black);
  lineEdit->setPalette(*palette);
  lineEdit->setText(message);
}

void MessageWidget::error(QString message)
{
  QPalette *palette = new QPalette();
  palette->setColor(QPalette::Text, Qt::black);
  lineEdit->setText(message);
  lineEdit->selectAll();
  palette->setColor(QPalette::Highlight, Qt::red);
  palette->setColor(QPalette::HighlightedText, Qt::white);
  lineEdit->setPalette(*palette);
}

// void MessageWidget::clear()
// {
//   // TODO: your code here...
// }
