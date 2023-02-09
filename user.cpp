#include "user.h"
#include "fileio.h"

//unsigned int User::_lastUserId = 0;
//unsigned User::_numberOfUsers = 0;

istream& User::input(istream& in) {
	return in >> this->_id >> this->_firstname >> this->_lastname >> this->_username >> this->_email >> this->_password >> this->_birthday;
}

ostream& User::output(ostream& out) const {
	return out << this->_id << '\t' << this->_firstname << '\t' << this->_lastname << '\t' << this->_username << '\t' << this->_email << '\t' << this->_password << '\t' << this->_birthday;
}

User::User(const unsigned int _id, const string _firstname, const string _lastname, const string _username, const string _email, const string _password, const Date _birthday) {
	// Check Validity
	/*if (_firstname != "" && !std::regex_match(_firstname, std::regex("[A-Z]{1,1}[a-z]+")))
		throw string("Firstname must be a sequence of alphabetic letters (a-z) staring with a capital letter.");

	if (_lastname != "" && !std::regex_match(_lastname, std::regex("[A-Z]{1,1}[a-z]+")))
		throw string("Lastname must be a sequence of alphabetic letters (a-z) staring with a capital letter.");

	if (_username != "" && !std::regex_match(_username, std::regex("[a-z][a-z0-9_\\.\\-]+")))
		throw string("Invalid username: It must start with a letter, and can only include lower-case letters, numbers, underscore, dash and/or period.");
	
	if (_email != "" && !std::regex_match(_email, std::regex("[a-z][a-z0-9_\\.]+@[a-z]+\\.[a-z]+")))
		throw string("Invalid email address: must be of the form 'something@example.example'. Can include lower-case letters, numbers and dot.");
	
	if (_password != "" && !std::regex_match(_password, std::regex("[a-zA-z0-9_@$#!&\\*\\-\\.\\?]+")))
		throw string("Invalid password: allowed characters are lower and upper-case letters, numbers, and these special characters '_@$#!&*-.?'.");
	
	if ((Date() - _birthday).year() > 100) throw InvalidDate("Logical age exceeded!");
	if ((Date() - _birthday).year() < 14) throw InvalidDate("Illegal age (must be > 13).");*/

	// Assign values if valid
	this->_id = _id;
	this->_firstname = _firstname;
	this->_lastname = _lastname;
	this->_username = _username;
	this->_email = _email;
	this->_password = _password;
	this->_birthday = _birthday;
}

User::User(const string _firstname, const string _lastname, const string _username, const string _email, const string _password, const Date _birthday) {
	// Check Validity
	if (!std::regex_match(_firstname, std::regex("[A-Z]{1,1}[a-z]+")))
		throw string("Firstname must be a sequence of alphabetic letters (a-z) staring with a capital letter.");

	if (!std::regex_match(_lastname, std::regex("[A-Z]{1,1}[a-z]+")))
		throw string("Lastname must be a sequence of alphabetic letters (a-z) staring with a capital letter.");

	if (!std::regex_match(_username, std::regex("[a-z][a-z0-9_\\.\\-]+")))
		throw string("Invalid username: It must start with a letter, and can only include lower-case letters, numbers, underscore, dash and/or period.");

	if (!std::regex_match(_email, std::regex("[a-z][a-z0-9_\\.]+@[a-z]+\\.[a-z]+")))
		throw string("Invalid email address: must be of the form 'something@example.example'. Can include lower-case letters, numbers and dot.");

	if (!std::regex_match(_password, std::regex("[a-zA-z0-9_@$#!&\\*\\-\\.\\?]+")))
		throw string("Invalid password: allowed characters are lower and upper-case letters, numbers, and these special characters '_@$#!&*-.?'.");

	if ((Date() - _birthday).year() > 100) throw InvalidDate("Invalid date: Logical age exceeded!");
	if ((Date() - _birthday).year() < 14) throw InvalidDate("Invalid date: Illegal age (must be > 13).");

	// Assign values if valid
	this->_firstname = _firstname;
	this->_lastname = _lastname;
	this->_username = _username;
	this->_email = _email;
	this->_password = _password;
	this->_birthday = _birthday;
}

User::User(const string _username, const string _password) {
	// Check Validity
	if (!std::regex_match(_username, std::regex("[a-z][a-z0-9_\\.\\-]+")))
		throw string("Invalid username: It must start with a letter, and can only include lower-case letters, numbers, underscore, dash and/or period.");

	if (!std::regex_match(_password, std::regex("[a-zA-z0-9_@$#!&\\*\\-\\.\\?]+")))
		throw string("Invalid password: allowed characters are lower and upper-case letters, numbers, and these special characters '_@$#!&*-.?'.");

	// Assign values if valid
	this->_username = _username;
	this->_password = _password;
}

User::~User(void) {
	//this->_numberOfUsers--;
}

// Setters:
void User::id(const unsigned int _id) {
	this->_id = _id;
}

void User::firstname(const string _firstname) {
	// Check if alphabetic and capitalize
	if (!std::regex_match(_firstname, std::regex("[A-Z]{1,1}[a-z]+")))
		throw string("Firstname must be a sequence of alphabetic letters (a-z) staring with a capital letter.");
	this->_firstname = _firstname;
}

void User::lastname(const string _lastname) {
	// Check if alphabetic and capitalize
	if (!std::regex_match(_lastname, std::regex("[A-Z]{1,1}[a-z]+")))
		throw string("Lastname must be a sequence of alphabetic letters (a-z) staring with a capital letter.");
	this->_lastname = _lastname;
}

void User::fullname(const string _firstname, const string _lastname) {
	// Check if alphabetic and capitalize
	if (!std::regex_match(_firstname, std::regex("[A-Z]{1,1}[a-z]+")) || !std::regex_match(_lastname, std::regex("[A-Z]{1,1}[a-z]+")))
		throw string("Firstname and Lastname must be a sequence of alphabetic letters (a-z) staring with a capital letter.");

	this->_firstname = _firstname;
	this->_lastname = _lastname;
}

void User::username(const string _username) {
	// Check validity
	if (!std::regex_match(_username, std::regex("[a-z][a-z0-9_\\.\\-]+")))
		throw string("Invalid username: It must start with a letter, and can only include lower-case letters, numbers, underscore, dash and/or period.");
	this->_username = _username;
}

void User::email(const string _email) {
	// Check validity
	if (!std::regex_match(_email, std::regex("[a-z][a-z0-9_\\.]+@[a-z]+\\.[a-z]+")))
		throw string("Invalid email address: must be of the form 'something@example.example'. Can include lower-case letters, numbers and dot.");
	this->_email = _email;
}

void User::password(const string _password) {
	// Check validity
	if (!std::regex_match(_password, std::regex("[a-zA-z0-9_@$#!&\\*\\-\\.\\?]+")))
		throw string("Invalid password: allowed characters are lower and upper-case letters, numbers, and these special characters '_@$#!&*-.?'.");
	this->_password = _password;
}

void User::birthday(const string _birthday) {
	Date temp(_birthday);
	if ((Date() - temp).year() > 100) throw InvalidDate("Logical age exceeded!");
	if ((Date() - temp).year() < 14) throw InvalidDate("Illegal age (must be > 13).");
	this->_birthday = temp;
}

void User::birthday(const Date _birthday) {
	if ((Date() - _birthday).year() > 100) throw InvalidDate("Logical age exceeded!");
	if ((Date() - _birthday).year() < 14) throw InvalidDate("Illegal age (must be > 13).");
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

void User::showProfileInfo(void) const {
	cout << "Firstname: " << this->_firstname << endl
		<< "Lastname: " << this->_lastname << endl
		<< "Username: " << this->_username << endl
		<< "Email: " << this->_email << endl
		<< "Birthday: " << this->_birthday << endl;
}

//
/*const bool User::createAccount(void) {
	if (userio::exist(this->_username, this->_email, filenames::users)) return false;
	insert(*this, filenames::users);
	return true;
}
const bool User::modifyAccount(void) {
	User _userRecord = select<User>(this->_id, filenames::users);
	if (_userRecord == User()) return false;
	update(*this, filenames::users);
	return true;
}
const bool User::deleteAccount(void) {
	if (!userio::exist(this->_username, this->_email, filenames::users)) return false;
	delete1(*this, filenames::users);
	return true;
}
const bool User::login(void) {
	if (userio::authenticate(this->_username, this->_password, filenames::users)) {
		*this = userio::select(this->_username, filenames::users);
		this->_loggedIn = true;
		return true;
	}
	this->_loggedIn = false;
	return false;
}
const bool User::logout(void) {
	if (!this->_loggedIn) return false;
	this->_loggedIn = false;
	return true;
}*/
void User::viewStocks(const string _category)const {
	vector<Product> _products;
	if (_category == "*") _products = selectSet<Product>();
	else _products = productio::selectSet(_category);

	// TODO: modify
	size_t maxId = 8, maxName = 10, maxBrand = 10, maxCat = 10, maxPrice = 5, maxQuan = 8;
	for (Product _product : _products) {
		maxId = (std::to_string(_product.id()).length() > maxId) ? std::to_string(_product.id()).length() : maxId;
		maxName = (_product.name().length() > maxName) ? _product.name().length() : maxName;
		maxBrand = (_product.brand().length() > maxBrand) ? _product.brand().length() : maxBrand;
		maxCat = (_product.category().length() > maxCat) ? _product.category().length() : maxCat;
		maxPrice = (std::to_string(_product.price()).length() > maxPrice) ? std::to_string(_product.price()).length() : maxPrice;
		maxQuan = (std::to_string(_product.quantity()).length() > maxQuan) ? std::to_string(_product.quantity()).length() : maxQuan;
	}

	cout << std::left;
	cout << std::setw(maxId) << "ID" << '|' << std::setw(maxName) << "Name" << '|' << std::setw(maxBrand) << "Brand" << '|' << std::setw(maxCat) << "Category" << '|' << std::setw(maxPrice) << "Price" << '|' << std::setw(maxQuan) << "Quantity" << endl;
	size_t times = maxId + maxName + maxBrand + maxCat + maxPrice + maxQuan + 5;
	cout << times * (string)"-" << endl;

	for (Product _product : _products)
		_product.display();

	cout << endl;
}
bool User::operator==(const User& _user) {
	return (this->_firstname == _user._firstname && this->_lastname == _user._lastname &&
		this->_username == _user._username && this->_email == _user._email && this->_password == _user._password && this->_birthday == _user._birthday);
}
istream& operator>>(istream& in, User& _user) {
	return _user.input(in);
}
ostream& operator<<(ostream& out, const User& _user) {
	return _user.output(out);
}
