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
