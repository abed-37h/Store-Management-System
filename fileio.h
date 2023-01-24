#pragma once
#include "user.h"
#include "customer.h"
#include "employee.h"
#include "dealer.h"
#include "product.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;
using std::getline;
using std::endl;

namespace filenames {
// directory
const string usersdir = "users/";
const string productsdir = "products/";
// filenames
const string users = "users.dat";
const string customers = "customers.dat";
const string employees = "employees.dat";
const string dealers = "dealers.dat";
const string products = "products.dat";
}

// General
template <class T>
void insert(const T&, const string&);

template <class T>
T select(const unsigned int&, const string&);

template <class T>
vector<T> select(const string&);

template <class T>
void update(const T&, const string&);

template <class T>
void delete1(const T&, const string&);

namespace userio {
	bool exist(const string&, const string&, const string&);
	bool authenticate(const string&, const string&, const string&);
	template <class T = User>
	T select(const string&, const string&);
}

namespace productio {
	bool exist(const string&, const string&);
	vector<Product> select(const string&, const string&);
}

// general
template <class T>
void insert(const T& _object, const string& _filename) {
	ofstream fout;
	fout.open(_filename, std::ios::binary | std::ios::app);
	// TODO: give an id
	fout << _object << endl;
	fout.close();
}

template <class T>
T select(const unsigned int& _id, const string& _filename) {
	ifstream fin;
	fin.open(_filename, std::ios::binary);
	if (fin.fail()) {
		fin.close();
		return T();
	}
	while (!fin.eof()) {
		T _record;
		fin >> _record;
		if (_record.id() == _id) {
			fin.close();
			return _record;
		}
	}
	fin.close();
	return T();
}

template <class T>
vector<T> select(const string& _filename) {
	ifstream fin;
	fin.open(_filename, std::ios::binary);
	vector<T> _records;
	if (fin.fail()) {
		fin.close();
		return _records;
	}
	while (!fin.eof()) {
		T _record;
		fin >> _record;
		_records.push_back(_record);
	}
	fin.close();
	return _records;
}

template <class T>
void update(const T& _object, const string& _filename) {
	ifstream fin;
	ofstream nout;
	fin.open(_filename, std::ios::binary);
	if (fin.fail()) {
		fin.close();
		return;
	}
	nout.open("temp.dat", std::ios::binary | std::ios::app);
	while (!fin.eof()) {
		T _record;
		fin >> _record;
		if (_record.id() == _object.id()) _record = _object;
		nout << _record << endl;
	}
	fin.close();
	nout.close();
	remove(_filename);
	rename("temp.dat", _filename);
}

template <class T>
void delete1(const T& _object, const string& _filename) {
	ifstream fin;
	ofstream nout;
	fin.open(_filename, std::ios::binary);
	if (fin.fail()) {
		fin.close();
		return;
	}
	nout.open("temp.dat", std::ios::binary | std::ios::app);
	while (!fin.eof()) {
		T _record;
		fin >> _record;
		if (_record.id() == _object.id()) nout << _record << endl;
	}
	fin.close();
	nout.close();
	remove(_filename);
	rename("temp.dat", _filename);
}

// user
template <class T>
T userio::select(const string& _username, const string& _filename) {
	ifstream fin;
	fin.open(_filename, std::ios::binary);
	if (fin.fail()) {
		fin.close();
		return T();
	}
	while (!fin.eof()) {
		T _record;
		fin >> _record;
		if (_record.username() == _username) {
			fin.close();
			return _record;
		}
	}
	fin.close();
	return T();
}
