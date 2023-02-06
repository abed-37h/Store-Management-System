#include "dealer.h"
#include "fileio.h"

unsigned int Dealer::_validId = getValidId<Dealer>();

Dealer::Dealer(const unsigned int _id, const string _firstname, const string _lastname, const string _username, const string _email, const string _password, const Date _birthday)
	: User(_id, _firstname, _lastname, _username, _email, _password, _birthday) {

}

Dealer::Dealer(const string _firstname, const string _lastname, const string _username, const string _email, const string _password, const Date _birthday)
	: User(_firstname, _lastname, _username, _email, _password, _birthday) {

}

Dealer::Dealer(const string _username, const string _password) : User(_username, _password) {

}

Dealer::~Dealer() {
	//User::~User();
}

const bool Dealer::createAccount(void) {
	if (userio::exist<Customer>(this->username(), this->email())) return false;
	if (userio::exist<Employee>(this->username(), this->email())) return false;
	if (userio::exist<Dealer>(this->username(), this->email())) return false;
	this->id(this->_validId++);
	insert(*this);
	return true;
}

const bool Dealer::modifyAccount(void) {
	Dealer _userRecord = select<Dealer>(this->id());
	if (_userRecord == Dealer()) return false;
	update(*this);
	return true;
}

const bool Dealer::deleteAccount(void) {
	if (!userio::exist<Dealer>(this->username(), this->email())) return false;
	delete1<Dealer>(this->id());
	return true;
}

const bool Dealer::login(void) {
	if (userio::authenticate<Dealer>(this->username(), this->password())) {
		*this = userio::select<Dealer>(this->username());
		this->_loggedIn = true;
		return true;
	}
	this->_loggedIn = false;
	return false;
}

const bool Dealer::logout(void) {
	if (!this->_loggedIn) return false;
	this->_loggedIn = false;
	return true;
}

const bool Dealer::addItem(Product _product) {
	if (productio::exist(_product.name())) return false;
	_product.assignId();
	insert(_product);
	return true;
}

const bool Dealer::removeItem(const unsigned int _id) {
	if (!productio::exist(_id)) return false;
	delete1<Product>(_id);
	return true;
}

const bool Dealer::refill(const unsigned int _id, const unsigned int _quantity) {
	if (!productio::exist(_id)) return false;
	Product _product = select<Product>(_id);
	_product += _quantity;
	update(_product);
	return true;
}

