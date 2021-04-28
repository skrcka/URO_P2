#include <QApplication>
#include <QInputDialog>
#include <QMessageBox>
#include "ui_gui.h"
#include "ui_login_widget.h"
#include "ui_stock_widget.h"
#include "ui_bills_widget.h"
#include "ui_orders_widget.h"
#include <string>
#include <vector>

class User{
private:
	std::string username;
	std::string password;
public:
	User() : username(""), password("") {}
	User(std::string username, std::string password) : username(username), password(password) {}
	std::string getUsername(){
		return this->username;
	}
	bool check_login(std::string password){
		return this->password == password ? true : false;
	}
};

Ui::DenRoze3 ui;
int activeWidget = 0;
std::vector<User> users;
User activeUser;

void update_widgets(){
	ui.menu_widget->hide();
	ui.stock_widget->hide();
	ui.orders_widget->hide();
	ui.bills_widget->hide();
	ui.login_widget->hide();
	if(activeWidget == 0){
		ui.login_widget->show();
	} else if(activeWidget == 1){
		ui.stock_widget->show();
		ui.menu_widget->show();
	} else if(activeWidget == 2){
		ui.bills_widget->show();
		ui.menu_widget->show();
	} else if(activeWidget == 3){
		ui.orders_widget->show();
		ui.menu_widget->show();
	}
}

void login(){
	std::string name = dynamic_cast<Ui_login_widget*>(ui.login_widget)->username_edit->text().toUtf8().constData();;
	std::string password = dynamic_cast<Ui_login_widget*>(ui.login_widget)->username_edit->text().toUtf8().constData();;
	for(auto& user : users){
		if(user.getUsername() == name){
			if(user.check_login(password)){
				activeWidget = 1;
				update_widgets();
				activeUser = user;
				return;
			}
		}
	}
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow widget;
    ui.setupUi(&widget);
	Ui::bills_widget bw;
	Ui::orders_widget ow;
	Ui::stock_widget sw;
	Ui::login_widget lw;
	bw.setupUi(ui.bills_widget);
	ow.setupUi(ui.orders_widget);
	lw.setupUi(ui.login_widget);
	sw.setupUi(ui.stock_widget);

	users.emplace_back("skrcka", "1337");
	update_widgets();

    widget.show();
    return app.exec();
}
