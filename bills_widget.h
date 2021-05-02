#ifndef BILLS_WIDGET_H
#define BILLS_WIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class bills_widget;
}

class bills_widget : public QWidget
{
    Q_OBJECT

public:
    explicit bills_widget(QWidget *parent = nullptr);
    ~bills_widget();
    QTableWidget* get_stock_table();
    QTableWidget* get_bill_table();
    QLineEdit* getBillCurrent();
	QPushButton* getNext();
	QPushButton* getPrev();
	QPushButton* getAdd();
	QPushButton* getRem();
	QPushButton* getDel();

private:
    Ui::bills_widget *ui;
};

#endif // FORM_H
