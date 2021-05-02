#pragma once
#include <string>

class Item{
public:
	std::string id;
	std::string name;
	std::string code;
	std::string price;
	std::string dph;
	std::string count;
	std::string mincount;
	Item() : id(""), name(""), code(""), price(""), dph(""), count(""), mincount("") {}
	Item(std::string id, std::string name, std::string code, std::string price, std::string dph, std::string count, std::string mincount)
			 : id(id), name(name), code(code), price(price), dph(dph), count(count), mincount(mincount) {}
};
