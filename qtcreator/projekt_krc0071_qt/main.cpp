#include "mainwindow.h"
#include "ui_gui.h"
#include "ui_login_widget.h"
#include "ui_stock_widget.h"
#include "ui_bills_widget.h"
#include "ui_orders_widget.h"

#include <QApplication>

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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow widget;
    Ui::bills_widget bw;
    Ui::orders_widget ow;
    Ui::stock_widget sw;
    Ui::login_widget lw;
    Ui::DenRoze3 w;
    widget.show();
    return a.exec();
}
