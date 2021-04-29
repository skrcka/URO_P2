#include "login_widget.h"
#include "ui_login_widget.h"

login_widget::login_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login_widget)
{
    ui->setupUi(this);
}

login_widget::~login_widget()
{
    delete ui;
}
