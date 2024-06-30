#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MyWidget; }
QT_END_NAMESPACE

class MyWidget : public QLabel
{
    Q_OBJECT
public:
    explicit MyWidget(QLabel *parent = nullptr);

signals:

};

#endif // MYWIDGET_H
