#pragma once
#include <string>

class Customer{
public:
	std::string name;
	std::string surname;
	std::string street;
	std::string city;
	std::string psc;
	std::string country;
	std::string phone;
	std::string email;

	Customer() : name(""), surname(""), street(""), city(""), psc(""), country(""), phone(""), email("") {}
	Customer(std::string name, std::string surname, std::string street, std::string city, std::string psc, std::string country, std::string phone, std::string email)
		 : name(name), surname(surname), street(street), city(city), psc(psc), country(country), phone(phone), email(email) {}
};
