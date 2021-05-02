#include "bills_widget.h"
#include "ui_bills_widget.h"

bills_widget::bills_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bills_widget)
{
    ui->setupUi(this);
}

bills_widget::~bills_widget()
{
    delete ui;
}

QTableWidget* bills_widget::get_stock_table(){
	return ui->billStock;
}

QTableWidget* bills_widget::get_bill_table(){
	return ui->billItems;
}

QLineEdit* bills_widget::getBillCurrent(){
	return ui->billCurrent;
}

QPushButton* bills_widget::getAdd(){
	return ui->billAddButton;
}

QPushButton* bills_widget::getDel(){
	return ui->billDelButton;
}

QPushButton* bills_widget::getRem(){
	return ui->billRemButton;
}

QPushButton* bills_widget::getNext(){
	return ui->billNextButton;
}

QPushButton* bills_widget::getPrev(){
	return ui->billPrevButton;
}
