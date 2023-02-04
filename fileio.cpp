#include "fileio.h"

// user
//bool userio::exist(const string& _username, const string& _email, const char _filename[]) {
//	ifstream fin;
//	fin.open(_filename, std::ios::binary);
//	if (fin.fail()) {
//		fin.close();
//		return false;
//	}
//	while (!fin.eof()) {
//		User _record;
//		if (_username == _record.username() || _email == _record.email()) return true;
//	}
//	return false;
//}
//
//bool userio::authenticate(const string& _username, const string& _password, const char _filename[]) {
//	ifstream fin;
//	fin.open(_filename, std::ios::binary);
//	if (fin.fail()) {
//		fin.close();
//		return false;
//	}
//	while (!fin.eof()) {
//		User _record;
//		fin >> _record;
//		if (_username == _record.username() && _password == _record.password()) return true;
//		if (_username == _record.username() && _password != _record.password()) return false;
//	}
//	return false;
//}

// product
bool productio::exist(const unsigned int& _id) {
	ifstream fin;
	fin.open(filenames::products, std::ios::binary);
	if (fin.fail()) {
		fin.close();
		return false;
	}
	while (!fin.eof()) {
		Product _record;
		fin >> _record;
		if (_id == _record.id()) {
			fin.close();
			return true;
		}
	}
	fin.close();
	return false;
}

bool productio::exist(const string& _name) {
	ifstream fin;
	fin.open(filenames::products, std::ios::binary);
	if (fin.fail()) {
		fin.close();
		return false;
	}
	while (!fin.eof()) {
		Product _record;
		fin >> _record;
		if (_name == _record.name()) {
			fin.close();
			return true;
		}
	}
	fin.close();
	return false;
}

Product productio::select(const string& _name) {
	ifstream fin;
	fin.open(filenames::products, std::ios::binary);
	if (fin.fail()) {
		fin.close();
		return Product();
	}
	while (!fin.eof()) {
		Product _record;
		fin >> _record;
		if (_record.name() == _name) {
			fin.close();
			return _record;
		}
	}
	fin.close();
	return Product();
}

vector<Product> productio::selectSet(const string& _category) {
	ifstream fin;
	fin.open(filenames::products, std::ios::binary);
	vector<Product> _records;
	if (fin.fail()) {
		fin.close();
		return _records;
	}
	while (!fin.eof()) {
		Product _record;
		if (_record.category() == _category) {
			_records.push_back(_record);
		}
	}
	fin.close();
	return _records;
}
