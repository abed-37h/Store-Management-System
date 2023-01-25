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
	// directories
	const char usersdir[] = "users/";
	const char productsdir[] = "products/";
	// filenames
	const char users[] = "users.dat";
	const char customers[] = "customers.dat";
	const char employees[] = "employees.dat";
	const char dealers[] = "dealers.dat";
	const char products[] = "products.dat";
	const char temp[] = "temp.dat";
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
void delete1(const T&, const char _filename[]);

namespace userio {
	template <class T>
	bool exist(const string&, const string&, const char _filename[]);
	template <class T>
	bool authenticate(const string&, const string&, const char _filename[]);
	template <class T = User>
	T select(const string&, const char _filename[]);
}

namespace productio {
	bool exist(const string&, const char _filename[]);
	vector<Product> select(const string&, const char _filename[]);
}

// general
template <class T>
void insert(const T& _object, const char _filename[]) {
	ofstream fout;
	fout.open(_filename, std::ios::binary | std::ios::app);
	// TODO: give an id
	fout << _object << endl;
	fout.close();
}

template <class T>
T select(const unsigned int& _id, const char _filename[]) {
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
void update(const T& _object, const char _filename[]) {
	ifstream fin;
	ofstream nout;
	fin.open(_filename, std::ios::binary);
	if (fin.fail()) {
		fin.close();
		return;
	}
	nout.open(filenames::temp, std::ios::binary | std::ios::app);
	while (!fin.eof()) {
		T _record;
		fin >> _record;
		if (_record.id() == _object.id()) _record = _object;
		nout << _record << endl;
	}
	fin.close();
	nout.close();
	remove(_filename);
	rename(filenames::temp, _filename);
}

template <class T>
void delete1(const T& _object, const char _filename[]) {
	ifstream fin;
	ofstream nout;
	fin.open(_filename, std::ios::binary);
	if (fin.fail()) {
		fin.close();
		return;
	}
	nout.open(filenames::temp, std::ios::binary | std::ios::app);
	while (!fin.eof()) {
		T _record;
		fin >> _record;
		if (_record.id() == _object.id()) nout << _record << endl;
	}
	fin.close();
	nout.close();
	remove(_filename);
	rename(filenames::temp, _filename);
}

// user
template <class T>
bool userio::exist(const string& _username, const string& _email, const char _filename[]) {
	static_assert(std::is_base_of<User, T>::value, "T must inherit from User"); // Check if T inherits User class
	ifstream fin;
	fin.open(_filename, std::ios::binary);
	if (fin.fail()) {
		fin.close();
		return false;
	}
	while (!fin.eof()) {
		T _record;
		if (_username == _record.username() || _email == _record.email()) return true;
	}
	return false;
}

template <class T>
bool userio::authenticate(const string& _username, const string& _password, const char _filename[]) {
	static_assert(std::is_base_of<User, T>::value, "T must inherit from User");
	ifstream fin;
	fin.open(_filename, std::ios::binary);
	if (fin.fail()) {
		fin.close();
		return false;
	}
	while (!fin.eof()) {
		T _record;
		fin >> _record;
		if (_username == _record.username() && _password == _record.password()) return true;
		if (_username == _record.username() && _password != _record.password()) return false;
	}
	return false;
}


template <class T>
T userio::select(const string& _username, const char _filename[]) {
	static_assert(std::is_base_of<User, T>::value, "T must inherit from User");
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
