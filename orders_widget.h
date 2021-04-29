#ifndef ORDERS_WIDGET_H
#define ORDERS_WIDGET_H

#include <QWidget>

namespace Ui {
class orders_widget;
}

class orders_widget : public QWidget
{
    Q_OBJECT

public:
    explicit orders_widget(QWidget *parent = nullptr);
    ~orders_widget();

private:
    Ui::orders_widget *ui;
};

#endif // FORM_H
