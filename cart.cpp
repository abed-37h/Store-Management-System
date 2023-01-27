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
	// TODO: format output
	cout << "Product Name\t|\tPrice\t|\tQuantity" << endl;
	for (auto pair : this->_products) {
		cout << pair.first.name() << "\t|\t" << pair.first.price() << "\t|\t" << pair.second << endl;
	}
	cout << endl << "Total Price: " << this->_totalPrice << endl;
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
