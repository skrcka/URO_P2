#include "gui.h"
#include "ui_gui.h"

DenRoze3::DenRoze3(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DenRoze3)
{
    ui->setupUi(this);
	this->activeWindow=1;
	

	// widgets
	this->lw = new login_widget{ui->login_widget};
	this->sw = new stock_widget{ui->stock_widget};
	this->bw = new bills_widget{ui->bills_widget};
	this->ow = new orders_widget{ui->orders_widget};
	/*
	this->ui->login_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->ui->stock_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->ui->bills_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->ui->orders_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->lw->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->sw->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->bw->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->ow->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	*/
	// menu buttons
	connect(lw->getButton(), SIGNAL(clicked()), SLOT(login()));
	connect(ui->stock_button, SIGNAL(clicked()), SLOT(stock()));
	connect(ui->bills_button, SIGNAL(clicked()), SLOT(bills()));
	connect(ui->orders_button, SIGNAL(clicked()), SLOT(orders()));

	users.emplace_back("skrcka", "1337");
	items.emplace_back("1", "test1", "test1", "1", "1", "1", "1");
	items.emplace_back("2", "test2", "test2", "2", "2", "2", "2");
	items.emplace_back("3", "test3", "test3", "3", "3", "3", "3");

	//stock
	this->sw->get_stock_table()->setRowCount(items.size());
	this->sw->get_stock_table()->setColumnCount(7);
	
	//QHeaderView* stock_header = new QHeaderView();
	QList<QString>* stock_header = new QList<QString>();
	stock_header->append(QString("id"));
	stock_header->append(QString("name"));
	stock_header->append(QString("code"));
	stock_header->append(QString("price"));
	stock_header->append(QString("dph"));
	stock_header->append(QString("count"));
	stock_header->append(QString("mincount"));
	this->sw->get_stock_table()->setHorizontalHeaderLabels(*stock_header);
	connect(sw->getAdd(), SIGNAL(clicked()), SLOT(addStock()));
	connect(sw->getRem(), SIGNAL(clicked()), SLOT(remStock()));
	refresh_stock();
}

void DenRoze3::refresh_stock(){
	this->sw->get_stock_table()->clear();
	this->sw->get_stock_table()->setRowCount(items.size());
	for(size_t i=0; i < items.size(); i++){
		this->sw->get_stock_table()->setItem(i, 0, new QTableWidgetItem(items[i].id.c_str()));
		this->sw->get_stock_table()->setItem(i, 1, new QTableWidgetItem(items[i].name.c_str()));
		this->sw->get_stock_table()->setItem(i, 2, new QTableWidgetItem(items[i].code.c_str()));
		this->sw->get_stock_table()->setItem(i, 3, new QTableWidgetItem(items[i].price.c_str()));
		this->sw->get_stock_table()->setItem(i, 4, new QTableWidgetItem(items[i].dph.c_str()));
		this->sw->get_stock_table()->setItem(i, 5, new QTableWidgetItem(items[i].count.c_str()));
		this->sw->get_stock_table()->setItem(i, 6, new QTableWidgetItem(items[i].mincount.c_str()));
	}
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
void DenRoze3::addStock(){
	items.emplace_back();
	refresh_stock();
}
void DenRoze3::remStock(){
	/*
	stock_select->hasSelection(); //check if has selection
	stock_select->selectedRows(); // return selected row(s)
	stock_select->selectedColumns(); // return selected column(s)
	*/
	if(this->sw->get_stock_table()->selectionModel()->hasSelection()){
		QModelIndexList selection = this->sw->get_stock_table()->selectionModel()->selectedRows();
		int row = selection.at(0).row();
		std::cout << row << std::endl;
		items.erase(items.begin() + row);
		refresh_stock();
	}
}

void DenRoze3::stock(){
	this->activeWindow = 1;
	this->update_widgets();
}
void DenRoze3::bills(){
	this->activeWindow = 2;
	this->update_widgets();
}
void DenRoze3::orders(){
	this->activeWindow = 3;
	this->update_widgets();
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
