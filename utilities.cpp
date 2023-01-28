#include "utilities.h"


string getPassword(const string& _s) {
	enum inputChar {
		BACKSPACE = 8,
		ENTER = 13
	};

	cout << _s;
	string password = "";
	char ch = ' ';

	while (true) {
		ch = _getch();
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
			_getch();
			continue;
		}

		password.push_back(ch);
		cout << '*';
	}
}

bool startsWith(const string& _string, const string& _substring) {
	return _string.rfind(_substring, 0) == 0;
}

string strip(const string& _string) {
	auto start_it = _string.begin();
	auto end_it = _string.rbegin();
	while (std::isspace(*start_it))
		++start_it;
	while (std::isspace(*end_it))
		++end_it;
	return std::string(start_it, end_it.base());
}
