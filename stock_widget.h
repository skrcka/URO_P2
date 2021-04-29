#ifndef STOCK_WIDGET_H
#define STOCK_WIDGET_H

#include <QWidget>

namespace Ui {
class stock_widget;
}

class stock_widget : public QWidget
{
    Q_OBJECT

public:
    explicit stock_widget(QWidget *parent = nullptr);
    ~stock_widget();

private:
    Ui::stock_widget *ui;
};

#endif // FORM_H
