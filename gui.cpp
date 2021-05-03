#include "gui.h"
#include "ui_gui.h"
#include <string>
#include <iostream>

DenRoze3::DenRoze3(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DenRoze3)
{
    ui->setupUi(this);
	this->activeWindow=0;
	
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->ui->login_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->ui->stock_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->ui->bills_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->ui->orders_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	// widgets
	this->lw = new login_widget{ui->login_widget};
	this->sw = new stock_widget{ui->stock_widget};
	this->bw = new bills_widget{ui->bills_widget};
	this->ow = new orders_widget{ui->orders_widget};

	this->lw->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->sw->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->bw->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->ow->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	
	// menu buttons
	connect(lw->getButton(), SIGNAL(clicked()), SLOT(login()));
	connect(ui->stock_button, SIGNAL(clicked()), SLOT(stock()));
	connect(ui->bills_button, SIGNAL(clicked()), SLOT(bills()));
	connect(ui->orders_button, SIGNAL(clicked()), SLOT(orders()));

	customers.emplace_back("Adam", "Skkr", "Venkovni", "Opava", "42020", "CZ", "900900900", "mail@mail.cz");
	customers.emplace_back("Petr", "Mol", "Prajzska", "Ostrava", "69699", "CZ", "666666666", "email@email.cz");
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
	activeOrder = 0;
	ordervector.emplace_back();
	ordervector[0].customer = customers[0];
	ordervector[0].items.emplace_back(items[0], "5");
	ordervector[0].items.emplace_back(items[1], "10");
	ordervector[0].items.emplace_back(items[2], "4");
	ordervector.emplace_back();
	ordervector[1].customer = customers[1];
	ordervector[1].items.emplace_back(items[1], "1");
	ordervector[1].items.emplace_back(items[2], "2");

	//stock
	this->sw->get_stock_table()->setRowCount(items.size());
	this->sw->get_stock_table()->setColumnCount(7);
	
	stock_header = new QList<QString>();
	stock_header->append(QString("id"));
	stock_header->append(QString("name"));
	stock_header->append(QString("code"));
	stock_header->append(QString("price"));
	stock_header->append(QString("dph"));
	stock_header->append(QString("count"));
	stock_header->append(QString("mincount"));
	connect(sw->getAdd(), SIGNAL(clicked()), SLOT(addStock()));
	connect(sw->getRem(), SIGNAL(clicked()), SLOT(remStock()));

	//bills
	this->bw->get_stock_table()->setRowCount(items.size());
	this->bw->get_stock_table()->setColumnCount(4);
	bill_stock_header = new QList<QString>();
	bill_stock_header->append(QString("name"));
	bill_stock_header->append(QString("code"));
	bill_stock_header->append(QString("price"));
	bill_stock_header->append(QString("dph"));

	this->bw->get_bill_table()->setColumnCount(4);
	bill_item_header = new QList<QString>();
	bill_item_header->append(QString("name"));
	bill_item_header->append(QString("price"));
	bill_item_header->append(QString("dph"));
	bill_item_header->append(QString("count"));
	connect(bw->getNext(), SIGNAL(clicked()), SLOT(nextBill()));
	connect(bw->getPrev(), SIGNAL(clicked()), SLOT(prevBill()));
	connect(bw->getAdd(), SIGNAL(clicked()), SLOT(addBill()));
	connect(bw->getRem(), SIGNAL(clicked()), SLOT(remBill()));
	connect(bw->getDel(), SIGNAL(clicked()), SLOT(delBill()));

	//orders
	this->ow->get_stock_table()->setRowCount(items.size());
	this->ow->get_stock_table()->setColumnCount(4);
	order_stock_header = new QList<QString>();
	order_stock_header->append(QString("name"));
	order_stock_header->append(QString("code"));
	order_stock_header->append(QString("price"));
	order_stock_header->append(QString("dph"));

	this->ow->get_order_table()->setColumnCount(4);
	order_item_header = new QList<QString>();
	order_item_header->append(QString("name"));
	order_item_header->append(QString("price"));
	order_item_header->append(QString("dph"));
	order_item_header->append(QString("count"));
	connect(ow->getNext(), SIGNAL(clicked()), SLOT(nextOrder()));
	connect(ow->getPrev(), SIGNAL(clicked()), SLOT(prevOrder()));
	connect(ow->getAdd(), SIGNAL(clicked()), SLOT(addOrder()));
	connect(ow->getRem(), SIGNAL(clicked()), SLOT(remOrder()));
	connect(ow->getDel(), SIGNAL(clicked()), SLOT(delOrder()));

	refresh_stock();
	refresh_bill();
	refresh_order();
}

void DenRoze3::refresh_bill(){
	this->bw->getBillCurrent()->setText(std::to_string(activeBill).c_str());
	this->bw->get_bill_table()->clear();
	this->bw->get_bill_table()->setRowCount(billvector[activeBill].items.size());

	this->bw->get_bill_table()->setHorizontalHeaderLabels(*bill_item_header);
	this->bw->get_bill_table()->verticalHeader()->hide();

	for(size_t i = 0; i < billvector[activeBill].items.size(); i++){
		this->bw->get_bill_table()->setItem(i, 0, new QTableWidgetItem(billvector[activeBill].items[i].item.name.c_str()));
		this->bw->get_bill_table()->setItem(i, 1, new QTableWidgetItem(billvector[activeBill].items[i].item.price.c_str()));
		this->bw->get_bill_table()->setItem(i, 2, new QTableWidgetItem(billvector[activeBill].items[i].item.dph.c_str()));
		this->bw->get_bill_table()->setItem(i, 3, new QTableWidgetItem(billvector[activeBill].items[i].count.c_str()));
	}
}

void DenRoze3::refresh_order(){
	this->ow->getOrderCurrent()->setText(std::to_string(activeOrder).c_str());

	this->ow->getCustName()->setText(ordervector[activeOrder].customer.name.c_str());
	this->ow->getCustSurname()->setText(ordervector[activeOrder].customer.surname.c_str());
	this->ow->getCustStreet()->setText(ordervector[activeOrder].customer.street.c_str());
	this->ow->getCustCity()->setText(ordervector[activeOrder].customer.city.c_str());
	this->ow->getCustPSC()->setText(ordervector[activeOrder].customer.psc.c_str());
	this->ow->getCustCountry()->setText(ordervector[activeOrder].customer.country.c_str());
	this->ow->getCustPhone()->setText(ordervector[activeOrder].customer.phone.c_str());
	this->ow->getCustEmail()->setText(ordervector[activeOrder].customer.email.c_str());

	this->ow->get_order_table()->clear();
	this->ow->get_order_table()->setRowCount(ordervector[activeOrder].items.size());

	this->ow->get_order_table()->setHorizontalHeaderLabels(*order_item_header);
	this->ow->get_order_table()->verticalHeader()->hide();

	for(size_t i = 0; i < ordervector[activeOrder].items.size(); i++){
		this->ow->get_order_table()->setItem(i, 0, new QTableWidgetItem(ordervector[activeOrder].items[i].item.name.c_str()));
		this->ow->get_order_table()->setItem(i, 1, new QTableWidgetItem(ordervector[activeOrder].items[i].item.price.c_str()));
		this->ow->get_order_table()->setItem(i, 2, new QTableWidgetItem(ordervector[activeOrder].items[i].item.dph.c_str()));
		this->ow->get_order_table()->setItem(i, 3, new QTableWidgetItem(ordervector[activeOrder].items[i].count.c_str()));
	}
}

void DenRoze3::refresh_stock(){
	this->sw->get_stock_table()->clear();
	this->sw->get_stock_table()->setRowCount(items.size());
	this->bw->get_stock_table()->clear();
	this->bw->get_stock_table()->setRowCount(items.size());
	this->ow->get_stock_table()->clear();
	this->ow->get_stock_table()->setRowCount(items.size());

	this->sw->get_stock_table()->setHorizontalHeaderLabels(*stock_header);
	this->sw->get_stock_table()->verticalHeader()->hide();

	this->bw->get_stock_table()->setHorizontalHeaderLabels(*bill_stock_header);
	this->bw->get_stock_table()->verticalHeader()->hide();

	this->ow->get_stock_table()->setHorizontalHeaderLabels(*order_stock_header);
	this->ow->get_stock_table()->verticalHeader()->hide();

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
		
		this->ow->get_stock_table()->setItem(i, 0, new QTableWidgetItem(items[i].name.c_str()));
		this->ow->get_stock_table()->setItem(i, 1, new QTableWidgetItem(items[i].code.c_str()));
		this->ow->get_stock_table()->setItem(i, 2, new QTableWidgetItem(items[i].price.c_str()));
		this->ow->get_stock_table()->setItem(i, 3, new QTableWidgetItem(items[i].dph.c_str()));
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
void DenRoze3::nextOrder(){
	activeOrder++;
	if(activeOrder >= ordervector.size()){
		ordervector.emplace_back();
	}
	refresh_order();
}
void DenRoze3::prevBill(){
	if(activeBill-1 >= 0){
		activeBill--;
	}
	refresh_bill();
}
void DenRoze3::prevOrder(){
	if(activeOrder-1 >= 0){
		activeOrder--;
	}
	refresh_order();
}
void DenRoze3::delBill(){
	billvector.erase(billvector.begin() + activeBill);
	if(activeBill != 0)
		activeBill--;
	if(activeBill <= billvector.size())
		billvector.emplace_back();
	refresh_bill();
}
void DenRoze3::delOrder(){
	ordervector.erase(ordervector.begin() + activeOrder);
	if(activeOrder != 0)
		activeOrder--;
	if(activeOrder <= ordervector.size())
		ordervector.emplace_back();
	refresh_order();
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
void DenRoze3::addOrder(){
	if(this->ow->get_stock_table()->selectionModel()->hasSelection()){
		for(auto s : this->ow->get_stock_table()->selectionModel()->selectedIndexes()){
			int row = s.row();
			ordervector[activeOrder].items.emplace_back(items[row], "1");
		}
		refresh_order();
	}
}
void DenRoze3::remBill(){
	if(this->bw->get_bill_table()->selectionModel()->hasSelection()){
		for(auto s : this->bw->get_bill_table()->selectionModel()->selectedIndexes()){
			int row = s.row();
			billvector[activeBill].items.erase(billvector[activeBill].items.begin() + row);
		}
		refresh_bill();
	}
}
void DenRoze3::remOrder(){
	if(this->ow->get_order_table()->selectionModel()->hasSelection()){
		for(auto s : this->ow->get_order_table()->selectionModel()->selectedIndexes()){
			int row = s.row();
			ordervector[activeOrder].items.erase(ordervector[activeOrder].items.begin() + row);
		}
		refresh_order();
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
