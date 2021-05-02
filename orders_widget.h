#ifndef ORDERS_WIDGET_H
#define ORDERS_WIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class orders_widget;
}

class orders_widget : public QWidget
{
    Q_OBJECT

public:
    explicit orders_widget(QWidget *parent = nullptr);
    ~orders_widget();
	QTableWidget* get_stock_table();
    QTableWidget* get_order_table();
    QLineEdit* getOrderCurrent();
	QPushButton* getNext();
	QPushButton* getPrev();
	QPushButton* getAdd();
	QPushButton* getRem();
	QPushButton* getDel();

	QLineEdit* getCustName();
	QLineEdit* getCustSurname();
	QLineEdit* getCustStreet();
	QLineEdit* getCustCity();
	QLineEdit* getCustPSC();
	QLineEdit* getCustCountry();
	QLineEdit* getCustPhone();
	QLineEdit* getCustEmail();

private:
    Ui::orders_widget *ui;
};

#endif // FORM_H
