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

	template <typename T>
	inline string chooseFilename(T& _object) {
		if (instanceof<Customer>(_object)) return customers;
		if (instanceof<Employee>(_object)) return employees;
		if (instanceof<Dealer>(_object)) return dealers;
		if (instanceof<Product>(_object)) return products;
		return ""; // Nothing of the above;
	}
}

// General
template <typename T>
unsigned int getAvailableId(void);

template <typename T>
void insert(const T&);

template <typename T>
T select(const unsigned int&);

template <typename T>
vector<T> selectSet(void);

template <typename T>
void update(const T&);

template <typename T>
void delete1(const unsigned int&);

// User namespace
namespace userio {
	template <typename T>
	bool exist(const string&, const string&);
	template <typename T>
	bool authenticate(const string&, const string&);
	template <typename T = User>
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
template<typename T>
inline unsigned int getAvailableId(void) {
	T _object;
	ifstream fin;
	const string _filename = filenames::chooseFilename(_object);
	fin.open(_filename, std::ios::binary);
	if (fin.fail()) {
		return 1;
	}
	unsigned int _id = 0;
	while (!fin.eof()) {
		//if (fin.peek() != '\n') _id = fin.peek();
		string _line;
		getline(fin, _line);
		if (!_line.empty()) {
			istringstream lin(_line);
			lin >> _id;
		}
	}
	fin.close();
	return _id + 1;
}

template<typename T>
inline void insert(const T& _object) {
	ofstream fout;
	const string _filename = filenames::chooseFilename(_object);
	fout.open(_filename, std::ios::binary | std::ios::app);
	// TODO: give an id
	fout << _object << endl;
	fout.close();
}

template<typename T>
inline T select(const unsigned int& _id) {
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

template<typename T>
inline vector<T> selectSet(void) {
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

template<typename T>
inline void update(const T& _object) {
	ifstream fin;
	ofstream fout;
	const string _filename = filenames::chooseFilename(_object);
	fin.open(_filename, std::ios::binary);
	if (fin.fail()) {
		fin.close();
		return;
	}
	fout.open(filenames::temp, std::ios::binary);
	while (!fin.eof()) {
		T _record;
		fin >> _record;
		if (_record == T()) continue;
		if (_record.id() == _object.id()) _record = _object;
		fout << _record << endl;
	}
	fin.close();
	fout.close();
	
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

template<typename T>
inline void delete1(const unsigned int& _id) {
	ifstream fin;
	ofstream fout;
	T _object;
	const string _filename = filenames::chooseFilename(_object);
	fin.open(_filename, std::ios::binary);
	if (fin.fail()) {
		fin.close();
		return;
	}
	fout.open(filenames::temp, std::ios::binary);
	while (!fin.eof()) {
		T _record;
		fin >> _record;
		if (_record == T()) continue;
		if (_record.id() != _id) fout << _record << endl;
	}
	fin.close();
	fout.close();

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

// user
template<typename T>
inline bool userio::exist(const string& _username, const string& _email) {
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
		if (_username == _record.username() || _email == _record.email()) {
			fin.close();
			return true;
		}
	}
	fin.close();
	return false;
}

template<typename T>
inline bool userio::authenticate(const string& _username, const string& _password) {
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
		if (_username == _record.username() && _password == _record.password()) {
			fin.close();
			return true;
		}
		if (_username == _record.username() && _password != _record.password()) {
			fin.close();
			return false;
		}
	}
	fin.close();
	return false;
}

template<typename T>
inline T userio::select(const string& _username) {
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
