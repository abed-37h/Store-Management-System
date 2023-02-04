#pragma once
#include "date.h"
#include "product.h"
#include <string>
#include <iostream>
#include <sstream>

using std::string;
using std::istream;
using std::ostream;
using std::cout;
using std::endl;

class User
{
private:
	//string _role;
	unsigned int _id;
	string _firstname;
	string _lastname;
	string _username;
	string _email;
	string _password;
	Date _birthday;
	//unsigned int _age;
protected:
	/*static unsigned int _lastUserId;
	static unsigned int _numberOfUsers;*/
	bool _loggedIn;
	virtual istream& input(istream&);
	virtual ostream& output(ostream&) const;
public:
	User(const unsigned int = 0, const string = "", const string = "", const string = "", const string = "", const string = "", const Date = Date());
	User(const string, const string, const string, const string, const string, const Date = Date());
	User(const string, const string);
	~User(void);
	// Setters:
	void id(const unsigned int);
	void firstname(const string);
	void lastname(const string);
	void fullname(const string, const string);
	void username(const string);
	void email(const string);
	void password(const string);
	void birthday(const string);
	void birthday(const Date);
	// Getters:
	const unsigned int id(void)const;
	const string firstname(void)const;
	const string lastname(void)const;
	const string fullname(void)const;
	const string username(void)const;
	const string email(void)const;
	const string password(void)const;
	const Date birthday(void)const;
	const unsigned int age(void)const;
	// 
	//const unsigned int calculateAge(void)const;
	virtual const bool createAccount(void) = 0;
	virtual const bool modifyAccount(void) = 0;
	virtual const bool deleteAccount(void) = 0;
	virtual const bool login(void) = 0;
	virtual const bool logout(void) = 0;
	virtual void showProfileInfo(void)const;
	void viewStocks(const string = "All")const;
	// Operators
	bool operator==(const User&);
	friend istream& operator>>(istream&, User&);
	friend ostream& operator<<(ostream&, const User&);
};

