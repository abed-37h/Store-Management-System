#include "product.h"

unsigned int Product::_totalQuantity = 0;

Product::Product(const unsigned int _id, const string _name, const string _brand, const string _category, const double _price, const unsigned int _quantity) {
	this->_id = _id;
	this->_name = _name;
	this->_brand = _brand;
	this->_category = _category;
	this->_price = _price;
	this->_quantity = _quantity;
	this->_totalQuantity++;
}

Product::~Product(void) {
	this->_totalQuantity--;
}

// Setters:
void Product::id(const unsigned int _id) {
	this->_id = _id;
}

void Product::name(const string _name) {
	this->_name = _name;
}

void Product::brand(const string _brand) {
	this->_brand = _brand;
}

void Product::category(const string _category) {
	this->_category = _category;
}

void Product::price(const double _price) {
	this->_price = _price;
}

void Product::quantity(const unsigned int _quantity) {
	this->_quantity = _quantity;
}

// Getters:
const unsigned int Product::id(void)const {
	return this->_id;
}

const string Product::name(void)const {
	return this->_name;
}

const string Product::brand(void)const {
	return this->_brand;
}

const string Product::category(void)const {
	return this->_category;
}

const double Product::price(void)const {
	return this->_price;
}

const unsigned int Product::quantity(void)const {
	return this->_quantity;
}

void Product::display(void)const {
	if (this->_id == 0) return;
	cout << "Name: " << this->_name << endl;
	cout << "Brand: " << this->_brand << endl;
	cout << "Category: " << this->_category << endl;
	cout << "Price: " << this->_price << endl;
	cout << '\t' << this->_quantity << " stocks available" << endl;
}

istream& operator>>(istream& in, Product& _product) {
	in >> _product._id >> _product._name >> _product._brand >> _product._category >> _product._price >> _product._quantity;
	return in;
}

ostream& operator<<(ostream& out, const Product& _product) {
	out << _product._id << '\t' << _product._name << '\t' << _product._brand << "\t" << _product._category << "\t" << _product._price << "\t" << _product._quantity;
	return out;
}

bool Product::operator==(const Product& _product) {
	return (this->_id == _product._id && this->_name == _product._name && this->_brand == _product._brand && this->_category == _product._category && this->_price == _product._price && this->_quantity == _product._quantity);
}

Product Product::operator++(void) {
	this->_quantity++;
	return *this;
}

Product Product::operator++(int dummy) {
	Product temp = *this;
	this->_quantity++;
	return temp;
}

Product Product::operator--(void) {
	this->_quantity--;
	return *this;
}

Product Product::operator--(int dummy) {
	Product temp = *this;
	this->_quantity--;
	return temp;
}

Product Product::operator+=(const unsigned int _addedQuantity) {
	this->_quantity += _addedQuantity;
	return *this;
}

Product Product::operator-=(const unsigned int _addedQuantity) {
	this->_quantity -= _addedQuantity;
	return *this;
}

bool Product::operator<(const Product& _product) const {
	if (this->_id < _product._id) return true;
	return false;
}
