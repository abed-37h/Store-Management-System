#pragma once
#include "date.h"
#include "product.h"
#include <string>
#include <iostream>
#include <sstream>

using std::string;
using std::istream;
using std::ostream;
using std::istringstream;
using std::cout;
using std::endl;

class User
{
protected:
	/*static unsigned int _lastUserId;
	static unsigned int _numberOfUsers;*/
	bool _loggedIn;
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
	virtual const bool createAccount(void);
	virtual const bool modifyAccount(void);
	virtual const bool deleteAccount(void);
	virtual const bool login(void);
	virtual const bool logout(void);
	void viewStocks(const string = "All")const;
	// Operators
	bool operator==(const User&);
	friend istream& operator>>(istream&, User&);
	friend ostream& operator<<(ostream&, const User&);
	friend istringstream& operator>>(istringstream&, User&);
};

