#include "gui.h"
#include "ui_gui.h"

DenRoze3::DenRoze3(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DenRoze3)
{
    ui->setupUi(this);
	this->activeWindow=0;
	this->lw = new login_widget{ui->login_widget};
	this->sw = new stock_widget{ui->stock_widget};
	this->bw = new bills_widget{ui->bills_widget};
	this->ow = new orders_widget{ui->orders_widget};
	connect(lw->getButton(), SIGNAL(clicked()), SLOT(login()));
	users.emplace_back("skrcka", "1337");
}

void DenRoze3::login(){
	std::string name = lw->getUsername();
	std::string password = lw->getPassword();
	for(auto& user : users){
		if(user.getUsername() == name){
			if(user.check_login(password)){
				this->activeWindow = 1;
				this->update_widgets();
				this->activeUser = user;
				return;
			}
		}
	}
}

DenRoze3::~DenRoze3()
{
    delete ui;
}

void DenRoze3::update_widgets(){
	ui->menu_widget->hide();
	ui->stock_widget->hide();
	ui->orders_widget->hide();
	ui->bills_widget->hide();
	ui->login_widget->hide();
	if(this->activeWindow == 0){
		ui->login_widget->show();
	} else if(this->activeWindow == 1){
		ui->stock_widget->show();
		ui->menu_widget->show();
	} else if(this->activeWindow == 2){
		ui->bills_widget->show();
		ui->menu_widget->show();
	} else if(this->activeWindow == 3){
		ui->orders_widget->show();
		ui->menu_widget->show();
	}
}
