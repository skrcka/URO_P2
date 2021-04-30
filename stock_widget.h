#ifndef STOCK_WIDGET_H
#define STOCK_WIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>

namespace Ui {
class stock_widget;
}

class stock_widget : public QWidget
{
    Q_OBJECT

public:
    explicit stock_widget(QWidget *parent = nullptr);
    ~stock_widget();
	QTableWidget* get_stock_table();
	QPushButton* getAdd();
	QPushButton* getRem();

private:
    Ui::stock_widget *ui;
};

#endif // FORM_H
