#include "cart.h"
#include "fileio.h"

Cart::Cart() {
	this->_totalPrice = 0;
}

const double Cart::totalPrice() const {
	return this->_totalPrice;
}

const bool Cart::addProduct(const Product _product, const unsigned int _quantity) {
	if (!(_quantity > 0)) return false;
	if (this->_products.count(_product) == 0 && _quantity <= _product.quantity()) {
		this->_products.insert({ _product, _quantity });
		_totalPrice += _quantity * _product.price();
		return true;
	}
	if (this->_products.count(_product) != 0 && this->_products[_product] + _quantity <= _product.quantity()) {
		this->_products[_product] += _quantity;
		_totalPrice += _quantity * _product.price();
		return true;
	}
	return false;
}

const bool Cart::modifyProductQuantity(const Product _product, const unsigned int _quantity) {
	if (!(_quantity > 0) || _quantity > _product.quantity() || this->_products.count(_product) == 0)
		return false;
	_totalPrice -= _products[_product] * _product.price();
	this->_products[_product] = _quantity;
	_totalPrice += _quantity * _product.price();
	return true;
}

const bool Cart::removeProduct(const Product _product) {
	if (this->_products.count(_product) == 0) return false;
	_totalPrice -= _products[_product] * _product.price();
	this->_products.erase(_product);
	return true;
}

void Cart::display(void) const {
	size_t maxName = 12, maxPrice = 5, maxQuan = 8;
	for (auto pair : _products) {
		Product _product = pair.first;
		maxName = (_product.name().length() > maxName) ? _product.name().length() : maxName;
		maxPrice = (std::to_string(_product.price()).length() > maxPrice) ? std::to_string(_product.price()).length() : maxPrice;
		maxQuan = (std::to_string(pair.second).length() > maxQuan) ? std::to_string(pair.second).length() : maxQuan;
	}

	cout << std::left;
	cout << std::setw(maxName) << "Product Name" << "|" << std::setw(maxPrice) << "Price" << "|" << std::setw(maxQuan) << "Quantity" << endl;
	
	cout << maxName * (string)"-" << '|' << maxPrice * (string)"-" << '|' << maxQuan*(string)"-" << endl;

	for (auto pair : this->_products) {
		cout << std::setw(maxName) << pair.first.name() << "|" << std::setw(maxPrice) << pair.first.price() << "|" << std::setw(maxQuan) << pair.second << endl;
	}
	cout << endl << "\tTotal Price: " << this->_totalPrice << endl << endl;
}

const double Cart::purchase(void) {
	for (auto pair : this->_products) {
		Product _product = pair.first;
		_product -= pair.second;
		update(_product);
	}
	const double temp = this->_totalPrice;
	this->clear();
	return temp;
}

void Cart::clear(void) {
	this->_totalPrice = 0;
	this->_products.clear();
}
