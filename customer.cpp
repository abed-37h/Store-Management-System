#include "customer.h"
#include "fileio.h"

Customer::Customer(const unsigned int _id, const string _firstname, const string _lastname, const string _username, const string _email, const string _password, const Date _birthday, const double _balance) 
	: User(_id, _firstname, _lastname, _username, _email, _password, _birthday) {
	this->_balance = (_balance >= 0.0) ? _balance : 0.0;
}

Customer::Customer(const string _firstname, const string _lastname, const string _username, const string _email, const string _password, const Date _birthday, const double _balance)
	: User(_firstname, _lastname, _username, _email, _password, _birthday) {
	this->_balance = (_balance >= 0.0) ? _balance : 0.0;
}

Customer::Customer(const string _username, const string _password) : User(_username, _password) {
	this->_balance = 0.0;
}

Customer::~Customer() {
	//User::~User();
}

void Customer::balance(const double _balance) {
	if (_balance >= 0) this->_balance = _balance;
}

const double Customer::balance(void)const {
	return this->_balance;
}

const bool Customer::createAccount(void) {
	if (userio::exist<Customer>(this->username(), this->email())) return false;
	if (userio::exist<Employee>(this->username(), this->email())) return false;
	if (userio::exist<Dealer>(this->username(), this->email())) return false;
	insert(*this);
	return true;
}

const bool Customer::modifyAccount(void) {
	Customer _userRecord = select<Customer>(this->id());
	if (_userRecord == Customer()) return false;
	update(*this);
	return true;
}

const bool Customer::deleteAccount(void) {
	if (!userio::exist<Customer>(this->username(), this->email())) return false;
	delete1<Customer>(this->id());
	return true;
}

const bool Customer::login(void) {
	if (userio::authenticate<Customer>(this->username(), this->password())) {
		*this = userio::select<Customer>(this->username());
		this->_loggedIn = true;
		return true;
	}
	this->_loggedIn = false;
	return false;
}

const bool Customer::logout(void) {
	if (!this->_loggedIn) return false;
	this->_loggedIn = false;
	return true;
}

void Customer::showProfileInfo(void) const {
	User::showProfileInfo();
	cout << "Your Balance: " << '$' << this->_balance << endl;
}

const bool Customer::addProductToCart(const string _name, const unsigned int _quantity) {
	const Product _product = productio::select(_name);
	return this->_cart.addProduct(_product, _quantity);
}


const bool Customer::modifyProductQunatityInCart(const string _name, const unsigned int _quantity) {
	const Product _product = productio::select(_name);
	return this->_cart.modifyProductQuantity(_product, _quantity);
}

const bool Customer::removeProductFromCart(const string _name) {
	const Product _product = productio::select(_name);
	return this->_cart.removeProduct(_product);
}

void Customer::viewCart(void)const {
	this->_cart.display();
}

bool Customer::purchase(void) {
	if (this->_cart.totalPrice() > this->_balance) return false;
	this->_balance -= this->_cart.purchase();
	update(*this);
	return true;
}

bool Customer::operator==(const Customer& _customer) {
	return (User::operator==(_customer) && this->_balance == _customer._balance);
}

istream& operator>>(istream& in, Customer& _customer) {
	unsigned int _id;
	string _firstname, _lastname, _username, _email, _password;
	Date _birthday;
	in >> _id >> _firstname >> _lastname >> _username >> _email >> _password >> _birthday >> _customer._balance;
	_customer.id(_id);
	_customer.firstname(_firstname);
	_customer.lastname(_lastname);
	_customer.username(_username);
	_customer.email(_email);
	_customer.password(_password);
	_customer.birthday(_birthday);
	return in;
}

ostream& operator<<(ostream& out, const Customer& _customer) {
	const User* _user = &_customer;
	out << *_user << '\t' << _customer._balance;
	delete _user;
	return out;
}
