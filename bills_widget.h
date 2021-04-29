#ifndef BILLS_WIDGET_H
#define BILLS_WIDGET_H

#include <QWidget>

namespace Ui {
class bills_widget;
}

class bills_widget : public QWidget
{
    Q_OBJECT

public:
    explicit bills_widget(QWidget *parent = nullptr);
    ~bills_widget();

private:
    Ui::bills_widget *ui;
};

#endif // FORM_H
