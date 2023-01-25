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
