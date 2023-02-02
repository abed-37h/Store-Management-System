#pragma once
#include "utilities.h"
#include <fstream>
#include <vector>
#include <cstring>

using std::ifstream;
using std::ofstream;
using std::vector;
using std::getline;
using std::endl;

namespace filenames {
	// directories
	const string usersdir = "users/";
	const string productsdir = "products/";
	// filenames
	const string users = "users.txt";
	const string customers = "customers.txt";
	const string employees = "employees.txt";
	const string dealers = "dealers.txt";
	const string products = "products.txt";
	const string temp = "temp.txt";

	template <class T>
	string chooseFilename(T& _object) {
		if (instanceof<Customer>(_object)) return customers;
		if (instanceof<Employee>(_object)) return employees;
		if (instanceof<Dealer>(_object)) return dealers;
		if (instanceof<Product>(_object)) return products;
		return ""; // Nothing of the above;
	}
}

// General
template <class T>
void insert(const T&);

template <class T>
T select(const unsigned int&);

template <class T>
vector<T> selectSet(void);

template <class T>
void update(const T&);

template <class T>
void delete1(const unsigned int&);

// User namespace
namespace userio {
	template <class T>
	bool exist(const string&, const string&);
	template <class T>
	bool authenticate(const string&, const string&);
	template <class T = User>
	T select(const string&);
}

// Product namespace
namespace productio {
	bool exist(const unsigned int&);
	bool exist(const string&);
	Product select(const string&);
	vector<Product> selectSet(const string&);
}

// general
template <class T>
void insert(const T& _object) {
	ofstream fout;
	const string _filename = filenames::chooseFilename(_object);
	fout.open(_filename, std::ios::binary | std::ios::app);
	// TODO: give an id
	fout << _object << endl;
	fout.close();
}

template <class T>
T select(const unsigned int& _id) {
	T _object;
	ifstream fin;
	const string _filename = filenames::chooseFilename(_object);
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
vector<T> selectSet(void) {
	T _object;
	ifstream fin;
	const string _filename = filenames::chooseFilename(_object);
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
void update(const T& _object) {
	ifstream fin;
	ofstream nout;
	const string _filename = filenames::chooseFilename(_object);
	fin.open(_filename, std::ios::binary);
	if (fin.fail()) {
		fin.close();
		return;
	}
	nout.open(filenames::temp, std::ios::binary | std::ios::app);
	while (!fin.eof()) {
		T _record;
		fin >> _record;
		if (_record == T()) continue;
		if (_record.id() == _object.id()) _record = _object;
		nout << _record << endl;
	}
	fin.close();
	nout.close();
	
	char* filename = new char[_filename.length() + 1];
	char* temp = new char[filenames::temp.length() + 1];
	strcpy_s(filename, _filename.length() + 1, _filename.c_str());
	strcpy_s(temp, filenames::temp.length() + 1, filenames::temp.c_str());

	remove(filename);
	rename(temp, filename);

	delete[] filename;
	delete[] temp;
	filename = temp = nullptr;
}

template <class T>
void delete1(const unsigned int& _id) {
	ifstream fin;
	ofstream nout;
	T _object;
	const string _filename = filenames::chooseFilename(_object);
	fin.open(_filename, std::ios::binary);
	if (fin.fail()) {
		fin.close();
		return;
	}
	nout.open(filenames::temp, std::ios::binary | std::ios::app);
	while (!fin.eof()) {
		T _record;
		fin >> _record;
		if (_record == T()) continue;
		if (_record.id() != _id) nout << _record << endl;
	}
	fin.close();
	nout.close();

	char* filename = new char[_filename.length()];
	char* temp = new char[filenames::temp.length()];
	strcpy_s(filename, _filename.length(), _filename.c_str());
	strcpy_s(temp, filenames::temp.length(), filenames::temp.c_str());

	remove(filename);
	rename(temp, filename);

	delete[] filename;
	delete[] temp;
	filename = temp = nullptr;
}

// user
template <class T>
bool userio::exist(const string& _username, const string& _email) {
	static_assert(std::is_base_of<User, T>::value, "T must inherit from User"); // Check if T inherits User class
	T _user;
	ifstream fin;
	const string _filename = filenames::chooseFilename(_user);
	fin.open(_filename, std::ios::binary);
	if (fin.fail()) {
		fin.close();
		return false;
	}
	while (!fin.eof()) {
		T _record;
		fin >> _record;
		if (_username == _record.username() || _email == _record.email()) return true;
	}
	return false;
}

template <class T>
bool userio::authenticate(const string& _username, const string& _password) {
	static_assert(std::is_base_of<User, T>::value, "T must inherit from User");
	T _user;
	ifstream fin;
	const string _filename = filenames::chooseFilename(_user);
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
T userio::select(const string& _username) {
	static_assert(std::is_base_of<User, T>::value, "T must inherit from User");
	T _user;
	ifstream fin;
	const string _filename = filenames::chooseFilename(_user);
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
