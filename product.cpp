#include "product.h"
#include "fileio.h"

unsigned int Product::_availableId = getAvailableId<Product>();
//unsigned int Product::_avilableId = 0;

Product::Product(const unsigned int _id, const string _name, const string _brand, const string _category, const double _price, const unsigned int _quantity) {
	this->_id = _id;
	this->_name = _name;
	this->_brand = _brand;
	this->_category = _category;
	this->_price = _price;
	this->_quantity = _quantity;
}

Product::~Product(void) {
	//this->_totalQuantity--;
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

void Product::assignId(void) {
	this->_id = this->_availableId++;
}

void Product::display(const bool _asRowInTable) const {
	if (this->_id == 0) return;
	if (_asRowInTable) {
		vector<Product> _products = selectSet<Product>();
		size_t maxId = 8, maxName = 10, maxBrand = 10, maxCat = 10, maxPrice = 5, maxQuan = 8;
		for (Product _product : _products) {
			maxId = (std::to_string(_product.id()).length() > maxId) ? std::to_string(_product.id()).length() : maxId;
			maxName = (_product.name().length() > maxName) ? _product.name().length() : maxName;
			maxBrand = (_product.brand().length() > maxBrand) ? _product.brand().length() : maxBrand;
			maxCat = (_product.category().length() > maxCat) ? _product.category().length() : maxCat;
			maxPrice = (std::to_string(_product.price()).length() > maxPrice) ? std::to_string(_product.price()).length() : maxPrice;
			maxQuan = (std::to_string(_product.quantity()).length() > maxQuan) ? std::to_string(_product.quantity()).length() : maxQuan;
		}

		cout << std::setw(maxId) << this->_id << '|' << std::setw(maxName) << this->_name << '|' << std::setw(maxBrand) << this->_brand << '|' << std::setw(maxCat) << this->_category << '|' << std::setw(maxPrice) << this->_price << '|' << std::setw(maxQuan) << this->_quantity << endl;
	}
	else {
		cout << "Name: " << this->_name << endl
			<< "Brand: " << this->_brand << endl
			<< "Category: " << this->_category << endl
			<< "Price: " << this->_price << endl
			<< '\t' << this->_quantity << " stocks available" << endl
			<< 40 * (string)"_" << endl << endl;
	}
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
