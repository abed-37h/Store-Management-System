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
bool productio::exist(const string& _name, const char _filename[]) {
	ifstream fin;
	fin.open(_filename, std::ios::binary);
	if (fin.fail()) {
		fin.close();
		return false;
	}
	while (!fin.eof()) {
		Product _record;
		fin >> _record;
		if (_name == _record.name()) return true;
	}
	return false;
}

vector<Product> productio::select(const string& _category, const char _filename[]) {
	ifstream fin;
	fin.open(_filename, std::ios::binary);
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
