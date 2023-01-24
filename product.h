#pragma once
#include <string>
#include <iostream>

using std::string;
using std::istream;
using std::ostream;
using std::cout;
using std::endl;

class Product
{
	static unsigned int _totalQuantity;
private:
	unsigned int _id;
	string _name;
	string _brand;
	string _category;
	double _price;
	unsigned int _quantity;
public:
	Product(const unsigned int = 0, const string = "", const string = "", const string = "", const double = 0.0, const unsigned int = 0);
	~Product(void);
	// Setters:
	void id(const unsigned int);
	void name(const string);
	void brand(const string);
	void category(const string);
	void price(const double);
	void quantity(const unsigned int);
	// Getters:
	const unsigned int id(void)const;
	const string name(void)const;
	const string brand(void)const;
	const string category(void)const;
	const double price(void)const;
	const unsigned int quantity(void)const;
	// 
	void display(void)const;
	friend istream& operator>>(istream&, Product&);
	friend ostream& operator<<(ostream&, const Product&);
	Product operator++(void);
	Product operator++(int);
	Product operator--(void);
	Product operator--(int);
	Product operator+=(const unsigned int);
	Product operator-=(const unsigned int);
	bool operator<(const Product&)const; // NOTE: We don't use it actually, but just to avoid the error when used as key in map
};

