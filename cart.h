#pragma once
#include "product.h"
#include <vector>
#include <map>

using std::vector;
using std::map;

class Cart
{
private:
	map<Product, unsigned int> _products;
	double _totalPrice;
public:
	Cart();
	const double totalPrice(void) const;
	const bool addProduct(const Product, const unsigned int = 1);
	const bool modifyProductQuantity(const Product, const unsigned int);
	const bool removeProduct(const Product);
	void display(void) const;
	const double purchase(void);
	void clear(void);
};

