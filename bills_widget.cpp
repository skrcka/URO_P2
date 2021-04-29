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
