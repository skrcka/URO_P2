#include "stock_widget.h"
#include "ui_stock_widget.h"

stock_widget::stock_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::stock_widget)
{
    ui->setupUi(this);
}

stock_widget::~stock_widget()
{
    delete ui;
}

QTableWidget* stock_widget::get_stock_table(){
	return ui->stock_list;
}

QPushButton* stock_widget::getAdd(){
	return ui->stock_add_button;
}

QPushButton* stock_widget::getRem(){
	return ui->stock_delete_button;
}
