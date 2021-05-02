#include "orders_widget.h"
#include "ui_orders_widget.h"

orders_widget::orders_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::orders_widget)
{
    ui->setupUi(this);
}

orders_widget::~orders_widget()
{
    delete ui;
}

QTableWidget* orders_widget::get_stock_table(){
	return ui->orderStock;
}

QTableWidget* orders_widget::get_order_table(){
	return ui->orderItems;
}

QLineEdit* orders_widget::getOrderCurrent(){
	return ui->orderCurrent;
}

QPushButton* orders_widget::getAdd(){
	return ui->orderAddButton;
}

QPushButton* orders_widget::getDel(){
	return ui->orderDelButton;
}

QPushButton* orders_widget::getRem(){
	return ui->orderRemButton;
}

QPushButton* orders_widget::getNext(){
	return ui->orderNextButton;
}

QPushButton* orders_widget::getPrev(){
	return ui->orderPrevButton;
}

QLineEdit* orders_widget::getCustName(){
	return ui->orderCustomerName;
}
QLineEdit* orders_widget::getCustSurname(){
	return ui->orderCustomerSurname;
}
QLineEdit* orders_widget::getCustStreet(){
	return ui->orderCustomerStreet;
}
QLineEdit* orders_widget::getCustCity(){
	return ui->orderCustomerCity;
}
QLineEdit* orders_widget::getCustPSC(){
	return ui->orderCustomerPSC;
}
QLineEdit* orders_widget::getCustCountry(){
	return ui->orderCustomerCountry;
}
QLineEdit* orders_widget::getCustPhone(){
	return ui->orderCustomerPhone;
}
QLineEdit* orders_widget::getCustEmail(){
	return ui->orderCustomerEmail;
}
