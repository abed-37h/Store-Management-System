#include "user.h"
#include "fileio.h"

//unsigned int User::_lastUserId = 0;
//unsigned User::_numberOfUsers = 0;

User::User(const unsigned int _id, const string _firstname, const string _lastname, const string _username, const string _email, const string _password, const Date _birthday) {
	//this->_id = this->_lastUserId++;
	this->_id = _id;
	this->_firstname = _firstname;
	this->_lastname = _lastname;
	this->_username = _username;
	this->_email = _email;
	this->_password = _password; // TODO: cipher the password
	this->_birthday = _birthday;
	//this->_numberOfUsers++;
}

User::User(const string _firstname, const string _lastname, const string _username, const string _email, const string _password, const Date _birthday) {
	this->_firstname = _firstname;
	this->_lastname = _lastname;
	this->_username = _username;
	this->_email = _email;
	this->_password = _password; // TODO: cipher the password
	this->_birthday = _birthday;
}

User::User(const string _username, const string _password) {
	this->_username = _username;
	this->_password = _password; // TODO: cipher the password
}

User::~User(void) {
	//this->_numberOfUsers--;
}

// Setters:
void User::id(const unsigned int _id) {
	this->_id = _id;
}

void User::firstname(const string _firstname) {
	// TODO: Check if alphabetic and capitalize
	this->_firstname = _firstname;
}

void User::lastname(const string _lastname) {
	// TODO: Check if alphabetic and capitalize
	this->_lastname = _lastname;
}

void User::fullname(const string _firstname, const string _lastname) {
	// TODO: Check if alphabetic and capitalize
	this->_firstname = _firstname;
	this->_lastname = _lastname;
}

void User::username(const string _username) {
	// TODO: Check validity
	this->_username = _username;
}

void User::email(const string _email) {
	// TODO: Check validity
	this->_email = _email;
}

void User::password(const string _password) {
	// TODO: Check validity and cipher the password
	this->_password = _password;
}

void User::birthday(const string _birthday) {
	Date temp(_birthday);
	this->_birthday = temp;
}

void User::birthday(const Date _birthday) {
	this->_birthday = _birthday;
}

// Getters:
const unsigned int User::id(void)const {
	return this->_id;
}

const string User::firstname(void)const {
	return this->_firstname;
}

const string User::lastname(void)const {
	return this->_lastname;
}

const string User::fullname(void)const {
	return this->_firstname + " " + this->_lastname;
}

const string User::username(void)const {
	return this->_username;
}

const string User::email(void)const {
	return this->_email;
}

const string User::password(void)const {
	return this->_password; // TODO: decipher the password
}

const Date User::birthday(void)const {
	return this->_birthday;
}

const unsigned int User::age(void)const {
	Date diff = Date() - this->_birthday;
	return (diff.month() < 6) ? diff.year() : diff.year() + 1;
}

//
//const bool User::createAccount(void) {
//	if (userio::exist(this->_username, this->_email, filenames::users)) return false;
//	insert(*this, filenames::users);
//	return true;
//}
//const bool User::modifyAccount(void) {
//	User _userRecord = select<User>(this->_id, filenames::users);
//	if (_userRecord == User()) return false;
//	update(*this, filenames::users);
//	return true;
//}
//const bool User::deleteAccount(void) {
//	if (!userio::exist(this->_username, this->_email, filenames::users)) return false;
//	delete1(*this, filenames::users);
//	return true;
//}
//const bool User::login(void) {
//	if (userio::authenticate(this->_username, this->_password, filenames::users)) {
//		*this = userio::select(this->_username, filenames::users);
//		this->_loggedIn = true;
//		return true;
//	}
//	this->_loggedIn = false;
//	return false;
//}
//const bool User::logout(void) {
//	if (!this->_loggedIn) return false;
//	this->_loggedIn = false;
//	return true;
//}
void User::viewStocks(const string _category)const {
	vector<Product> _products;
	if (_category == "All") _products = select<Product>(filenames::products);
	else _products = productio::select(_category, filenames::products);
	for (unsigned int i = 0; i < _products.size(); i++)
		_products[i].display();
}
bool User::operator==(const User& _user) {
	return (this->_firstname == _user._firstname && this->_lastname == _user._lastname &&
		this->_username == _user._username && this->_email == _user._email && this->_password == _user._password && this->_birthday == _user._birthday);
}
istream& operator>>(istream& in, User& _user) {
	in >> _user._id >> _user._firstname >> _user._lastname >> _user._username
		>> _user._email >> _user._password >> _user._birthday;
	return in;
}
ostream& operator<<(ostream& out, const User& _user) {
	out << _user._id << '\t' << _user._firstname << '\t' << _user._lastname << '\t' << _user._username
		<< '\t' << _user._email << '\t' << _user._password << '\t' << _user._birthday;
	return out;
}
