#include "gui.h"
#include "ui_gui.h"
#include <string>
#include <iostream>

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
	billvector.emplace_back();
	billvector[0].items.emplace_back(items[0], "5");
	billvector[0].items.emplace_back(items[1], "10");
	billvector[0].items.emplace_back(items[2], "4");
	billvector.emplace_back();
	billvector[1].items.emplace_back(items[1], "1");
	billvector[1].items.emplace_back(items[2], "2");
	activeBill = 0;

	//stock
	this->sw->get_stock_table()->setRowCount(items.size());
	this->sw->get_stock_table()->setColumnCount(7);
	
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

	//bills
	this->bw->get_stock_table()->setRowCount(items.size());
	this->bw->get_stock_table()->setColumnCount(4);
	QList<QString>* bill_stock_header = new QList<QString>();
	bill_stock_header->append(QString("name"));
	bill_stock_header->append(QString("code"));
	bill_stock_header->append(QString("price"));
	bill_stock_header->append(QString("dph"));
	this->bw->get_stock_table()->setHorizontalHeaderLabels(*bill_stock_header);

	this->bw->get_bill_table()->setRowCount(items.size());
	this->bw->get_bill_table()->setColumnCount(4);
	QList<QString>* bill_item_header = new QList<QString>();
	bill_item_header->append(QString("name"));
	bill_item_header->append(QString("price"));
	bill_item_header->append(QString("dph"));
	bill_item_header->append(QString("count"));
	this->bw->get_bill_table()->setHorizontalHeaderLabels(*bill_item_header);
	connect(bw->getNext(), SIGNAL(clicked()), SLOT(nextBill()));
	connect(bw->getPrev(), SIGNAL(clicked()), SLOT(prevBill()));
	connect(bw->getAdd(), SIGNAL(clicked()), SLOT(addBill()));
	connect(bw->getRem(), SIGNAL(clicked()), SLOT(remBill()));
	connect(bw->getDel(), SIGNAL(clicked()), SLOT(delBill()));

	refresh_stock();
	refresh_bill();
}

void DenRoze3::refresh_bill(){
	this->bw->getBillCurrent()->setText(std::to_string(activeBill).c_str());
	this->bw->get_bill_table()->clear();
	this->bw->get_bill_table()->setRowCount(billvector[activeBill].items.size());

	std::cout << billvector[activeBill].items.size() << std::endl;
	for(size_t i = 0; i < billvector[activeBill].items.size(); i++){
		std::cout << billvector[activeBill].items[i].item.name << std::endl;
		this->bw->get_bill_table()->setItem(i, 0, new QTableWidgetItem(billvector[activeBill].items[i].item.name.c_str()));
		this->bw->get_bill_table()->setItem(i, 1, new QTableWidgetItem(billvector[activeBill].items[i].item.price.c_str()));
		this->bw->get_bill_table()->setItem(i, 2, new QTableWidgetItem(billvector[activeBill].items[i].item.dph.c_str()));
		this->bw->get_bill_table()->setItem(i, 3, new QTableWidgetItem(billvector[activeBill].items[i].count.c_str()));
	}
}

void DenRoze3::refresh_stock(){
	this->sw->get_stock_table()->clear();
	this->sw->get_stock_table()->setRowCount(items.size());
	this->bw->get_stock_table()->clear();
	this->bw->get_stock_table()->setRowCount(items.size());
	for(size_t i=0; i < items.size(); i++){
		this->sw->get_stock_table()->setItem(i, 0, new QTableWidgetItem(items[i].id.c_str()));
		this->sw->get_stock_table()->setItem(i, 1, new QTableWidgetItem(items[i].name.c_str()));
		this->sw->get_stock_table()->setItem(i, 2, new QTableWidgetItem(items[i].code.c_str()));
		this->sw->get_stock_table()->setItem(i, 3, new QTableWidgetItem(items[i].price.c_str()));
		this->sw->get_stock_table()->setItem(i, 4, new QTableWidgetItem(items[i].dph.c_str()));
		this->sw->get_stock_table()->setItem(i, 5, new QTableWidgetItem(items[i].count.c_str()));
		this->sw->get_stock_table()->setItem(i, 6, new QTableWidgetItem(items[i].mincount.c_str()));

		this->bw->get_stock_table()->setItem(i, 0, new QTableWidgetItem(items[i].name.c_str()));
		this->bw->get_stock_table()->setItem(i, 1, new QTableWidgetItem(items[i].code.c_str()));
		this->bw->get_stock_table()->setItem(i, 2, new QTableWidgetItem(items[i].price.c_str()));
		this->bw->get_stock_table()->setItem(i, 3, new QTableWidgetItem(items[i].dph.c_str()));
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

void DenRoze3::nextBill(){
	activeBill++;
	if(activeBill >= billvector.size()){
		billvector.emplace_back();
	}
	refresh_bill();
}
void DenRoze3::prevBill(){
	if(activeBill-1 >= 0){
		activeBill--;
	}
	refresh_bill();
}
void DenRoze3::delBill(){
	billvector.erase(billvector.begin() + activeBill);
	if(activeBill != 0)
		activeBill--;
	if(activeBill <= billvector.size())
		billvector.emplace_back();
	refresh_bill();
}
void DenRoze3::addBill(){
	if(this->bw->get_stock_table()->selectionModel()->hasSelection()){
		for(auto s : this->bw->get_stock_table()->selectionModel()->selectedIndexes()){
			int row = s.row();
			billvector[activeBill].items.emplace_back(items[row], "1");
		}
		refresh_bill();
	}
}
void DenRoze3::remBill(){}

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
		for(auto s : this->sw->get_stock_table()->selectionModel()->selectedIndexes()){
			int row = s.row();
			items.erase(items.begin() + row);
		}
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
	delete sw;
	delete lw;
	delete bw;
	delete ow;
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
