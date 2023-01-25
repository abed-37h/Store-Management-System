#include "employee.h"
#include "fileio.h"

Employee::Employee(const unsigned int _id, const string _firstname, const string _lastname, const string _username, const string _email, const string _password, const Date _birthday, const double _wage)
	: User(_id, _firstname, _lastname, _username, _email, _password, _birthday) {
	this->_wage = _wage;
}

Employee::Employee(const string _firstname, const string _lastname, const string _username, const string _email, const string _password, const Date _birthday)
	: User(_firstname, _lastname, _username, _email, _password, _birthday) {
	this->_wage = 0.0;
}

Employee::Employee(const string _username, const string _password) :User(_username, _password) {
	this->_wage = 0.0;
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
	if (userio::exist<Customer>(this->username(), this->email(), filenames::customers)) return false;
	if (userio::exist<Employee>(this->username(), this->email(), filenames::employees)) return false;
	if (userio::exist<Dealer>(this->username(), this->email(), filenames::dealers)) return false;
	insert(*this, filenames::customers);
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
	if (!userio::exist<Employee>(this->username(), this->email(), filenames::employees)) return false;
	delete1(*this, filenames::employees);
	return true;
}

const bool Employee::login(void) {
	if (userio::authenticate<Employee>(this->username(), this->password(), filenames::employees)) {
		*this = userio::select<Employee>(this->username(), filenames::employees);
		this->_loggedIn = true;
		return true;
	}
	this->_loggedIn = false;
	return false;
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
	return (User::operator==(_employee) && this->_wage == _employee._wage);
}

istream& operator>>(istream& in, Employee& _employee) {
	unsigned int _id;
	string _firstname, _lastname, _username, _email, _password;
	Date _birthday;
	in >> _id >> _firstname >> _lastname >> _username >> _email >> _password >> _birthday >> _employee._wage;
	_employee.id(_id);
	_employee.firstname(_firstname);
	_employee.lastname(_lastname);
	_employee.username(_username);
	_employee.email(_email);
	_employee.password(_password);
	_employee.birthday(_birthday);
	return in;
}

ostream& operator<<(ostream& out, const Employee& _employee) {
	const User* _user = &_employee;
	out << *_user << '\t' << _employee._wage;
	delete _user;
	return out;
}
