#pragma once
#include <string>
#include <vector>
#include "Billitem.h"

class Bill{
public:
	std::vector<Billitem> items;
	Bill(){}
};
