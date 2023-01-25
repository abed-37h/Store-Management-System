#pragma once
#include "user.h"
#include "dealer.h"
#include "employee.h"
#include "customer.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

using std::cout;
using std::cin;
using std::string;

template <typename T>
T input(const string& = "");

string getPassword(const string& = "");

// Definitions
template <typename T>
T input(const string& _s) {
	T temp;
	cout << _s;
	cin >> temp;
	return temp;
}
