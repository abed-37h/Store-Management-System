#include "employee.h"
#include "fileio.h"

Employee::Employee(const unsigned int _id, const string _firstname, const string _lastname, const string _username, const string _email, const string _password, const Date _birthday, const double _wage)
	: User(_id, _firstname, _lastname, _username, _email, _password, _birthday) {
	this->_wage = _wage;
}

Employee::Employee(const string _firstname, const string _lastname, const string _username, const string _email, const string _password, const Date _birthday)
	: User(_firstname, _lastname, _username, _email, _password, _birthday) {

}

Employee::Employee(const string _username, const string _password) :User(_username, _password) {

}

Employee::~Employee() {
	//User::~User();
}

void Employee::wage(const double) {
	this->_wage = _wage;
}

const double Employee::wage(void)const {
	return this->_wage;
}

const bool Employee::createAccount(void) {
	if (userio::exist(this->username(), this->email(), filenames::employees)) return false;
	insert(*this, filenames::employees);
	return true;
}

const bool Employee::modifyAccount(void) {
	Employee _userRecord = select<Employee>(this->id(), filenames::employees);
	if (_userRecord == Employee()) return false;
	update(*this, filenames::employees);
	return true;
}

const bool Employee::deleteAccount(void) {
	if (!userio::exist(this->username(), this->email(), filenames::employees)) return false;
	delete1(*this, filenames::employees);
	return true;
}

const bool Employee::login(void) {
	if (userio::authenticate(this->username(), this->password(), filenames::employees)) {
		*this = userio::select<Employee>(this->username(), filenames::employees);
		return this->_loggedIn = true;
	}
	return this->_loggedIn = false;
}

const bool Employee::logout(void) {
	if (!this->_loggedIn) return false;
	this->_loggedIn = false;
	return true;
}

const bool Employee::refill(Product _product, const unsigned int _quantity) {
	if (!productio::exist(_product.name(), filenames::products)) return false;
	_product += _quantity;
	update(_product, filenames::products);
	return true;
}

bool Employee::operator==(const Employee& _employee) {
	if (this->firstname() == _employee.firstname() && this->lastname() == _employee.lastname() && this->username() == _employee.username() && this->email() == _employee.email() && this->password() == _employee.password() && this->_wage == _employee._wage)
		return true;
	return false;
}
