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
