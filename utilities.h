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
T input(const string& _s = "") {
	T temp;
	cout << _s;
	cin >> temp;
	return temp;
}

enum inputChar {
	BACKSPACE = 8,
	ENTER = 13
};

string getPassword(const string& _s = "") {
	cout << _s;
	string password = "";
	char ch = ' ';

	while (true) {
		ch = getch();
		if (ch == inputChar::ENTER) {
			cout << endl;
			return password;
		}

		else if (ch == inputChar::BACKSPACE && password.length() != 0) {
			password.pop_back();
			cout << "\b \b";
			continue;
		}

		else if (ch == inputChar::BACKSPACE && password.length() == 0) {
			continue;
		}

		else if (ch == 0 || ch == 224) {
			getch();
			continue;
		}

		password.push_back(ch);
		cout << '*';
	}
}
