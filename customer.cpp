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
	if (userio::exist(this->username(), this->email(), filenames::customers)) return false;
	if (userio::exist(this->username(), this->email(), filenames::dealers)) return false;
	if (userio::exist(this->username(), this->email(), filenames::employees)) return false;
	insert(*this, filenames::customers);
	return true;
}

const bool Customer::modifyAccount(void) {
	Customer _userRecord = select<Customer>(this->id(), filenames::customers);
	if (_userRecord == Customer()) return false;
	update(*this, filenames::customers);
	return true;
}

const bool Customer::deleteAccount(void) {
	if (!userio::exist(this->username(), this->email(), filenames::customers)) return false;
	delete1(*this, filenames::customers);
	return true;
}

const bool Customer::login(void) {
	if (userio::authenticate(this->username(), this->password(), filenames::customers)) {
		*this = userio::select<Customer>(this->username(), filenames::customers);
		return this->_loggedIn = true;
	}
	return this->_loggedIn = false;
}

const bool Customer::logout(void) {
	if (!this->_loggedIn) return false;
	this->_loggedIn = false;
	return true;
}

const bool Customer::addProductToCart(const Product _product, const unsigned int _quantity) {
	return this->_cart.addProduct(_product, _quantity);
}

const bool Customer::modifyProductQunatityInCart(const Product _product, const unsigned int _quantity) {
	return this->_cart.modifyProductQuantity(_product, _quantity);
}

const bool Customer::removeProductFromCart(const Product _product) {
	return this->_cart.removeProduct(_product);
}

void Customer::viewCart(void)const {
	this->_cart.display();
}

bool Customer::purchase(void) {
	if (this->_cart.totalPrice() > _balance) return false;
	_balance -= _cart.purchase();
	return true;
}

bool Customer::operator==(const Customer& _customer) {
	if (this->firstname() == _customer.firstname() && this->lastname() == _customer.lastname() && this->username() == _customer.username() && this->email() == _customer.email() && this->password() == _customer.password() && this->_balance == _customer._balance)
		return true;
	return false;
}

