#include "login_widget.h"
#include "ui_login_widget.h"

login_widget::login_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login_widget)
{
    ui->setupUi(this);
}

std::string login_widget::getUsername(){
	return ui->username_edit->text().toUtf8().constData();
}
std::string login_widget::getPassword(){
	return ui->password_edit->text().toUtf8().constData();
}

login_widget::~login_widget()
{
    delete ui;
}

QPushButton* login_widget::getButton(){
	return ui->login_button;
}
