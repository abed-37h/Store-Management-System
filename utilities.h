#pragma once
#include "user.h"
#include "dealer.h"
#include "employee.h"
#include "customer.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <type_traits>

using std::cout;
using std::cin;
using std::string;

template<typename Base, typename T>
inline bool instanceof(const T&);

template <typename T>
T input(const string& = "");

string getPassword(const string& = "");

// Definitions
template<typename Base, typename T>
inline bool instanceof(const T& var) {
	//return dynamic_cast<const Base*>(&var) != nullptr;
	return std::is_base_of<Base, T>::value;
}

template <typename T>
T input(const string& _s) {
	T temp;
	cout << _s;
	cin >> temp;
	return temp;
}
