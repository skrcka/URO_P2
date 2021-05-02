#pragma once
#include <string>
#include <vector>
#include "Billitem.h"
#include "Customer.h"

class Order{
public:
	std::vector<Billitem> items;
	Customer customer;
	Order(){}
};
