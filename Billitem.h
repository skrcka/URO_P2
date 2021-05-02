#pragma once
#include <string>
#include "Item.h"

class Billitem{
public:
	Item item;
	std::string count;
    Billitem() : item(Item()), count("0") {}
	Billitem(Item item, std::string count) : item(item), count(count){}
};
