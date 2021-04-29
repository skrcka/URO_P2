#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "login_widget.h"
#include "stock_widget.h"
#include "bills_widget.h"
#include "orders_widget.h"
#include "User.h"
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class DenRoze3; }
QT_END_NAMESPACE

class DenRoze3 : public QMainWindow
{
    Q_OBJECT

public:
    DenRoze3(QWidget *parent = nullptr);
    ~DenRoze3();
	login_widget *lw;
	stock_widget *sw;
	bills_widget *bw;
	orders_widget *ow;
	std::vector<User> users;
	User activeUser;
	int activeWindow;

	void update_widgets();

private slots:
	void login();
	void stock();
	void bills();
	void orders();

private:
    Ui::DenRoze3 *ui;
};
#endif // MAINWINDOW_H
