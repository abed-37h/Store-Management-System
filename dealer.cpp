#include "dealer.h"
#include "fileio.h"

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
	if (userio::exist<Customer>(this->username(), this->email(), filenames::customers)) return false;
	if (userio::exist<Employee>(this->username(), this->email(), filenames::employees)) return false;
	if (userio::exist<Dealer>(this->username(), this->email(), filenames::dealers)) return false;
	insert(*this, filenames::customers);
	insert(*this, filenames::dealers);
	return true;
}

const bool Dealer::modifyAccount(void) {
	Dealer _userRecord = select<Dealer>(this->id(), filenames::dealers);
	if (_userRecord == Dealer()) return false;
	update(*this, filenames::dealers);
	return true;
}

const bool Dealer::deleteAccount(void) {
	if (!userio::exist<Dealer>(this->username(), this->email(), filenames::dealers)) return false;
	delete1(*this, filenames::dealers);
	return true;
}

const bool Dealer::login(void) {
	if (userio::authenticate<Dealer>(this->username(), this->password(), filenames::dealers)) {
		*this = userio::select<Dealer>(this->username(), filenames::dealers);
		return this->_loggedIn = true;
	}
	return this->_loggedIn = false;
}

const bool Dealer::logout(void) {
	if (!this->_loggedIn) return false;
	this->_loggedIn = false;
	return true;
}

const bool Dealer::addItem(const Product _product) {
	if (productio::exist(_product.name(), filenames::products)) return false;
	insert(_product, filenames::products);
	return true;
}

const bool Dealer::removeItem(const Product _product) {
	if (!productio::exist(_product.name(), filenames::products)) return false;
	delete1(_product, filenames::products);
	return true;
}

const bool Dealer::refill(Product _product, const unsigned int _quantity) {
	if (!productio::exist(_product.name(), filenames::products)) return false;
	_product += _quantity;
	update(_product, filenames::products);
	return true;
}

