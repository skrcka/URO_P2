#include <string>

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
