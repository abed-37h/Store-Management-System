#include "utilities.h"


string operator*(unsigned int _times, string _str) {
	string temp;
	while (_times--) temp += _str;
	return temp;
}

string operator*(string _str, unsigned int _times) {
	string temp;
	while (_times--) temp += _str;
	return temp;
}

string getPassword(const string& _s) {
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

// To be modified, partitionned or cancelled
void showProfile(User* _user) {
	system("cls");
	string command;
	bool success = false;
	do {
		_user->showProfileInfo();
		cout << endl;
		cout << "Choose an action to do:" << endl
			<< "\t1. Edit profile info < edit >" << endl
			<< "\t2. Logout < logout >" << endl
			<< "\t3. Delete account < delete >" << endl
			<< "\t4. Go back < back >" << endl;
		cin >> command;
		if (command == "edit") {
			cout << "\tFirstname: ";
			if (cin.peek() != inputChar::ENTER) {
				string firstname = input<string>();
				_user->firstname(firstname);
			}

			cout << "\tLastname: ";
			if (cin.peek() != inputChar::ENTER) {
				string lastname = input<string>();
				_user->lastname(lastname);
			}

			cout << "\tUsername: ";
			if (cin.peek() != inputChar::ENTER) {
				string username = input<string>();
				_user->username(username);
			}

			cout << "\tEmail: ";
			if (cin.peek() != inputChar::ENTER) {
				string email = input<string>();
				_user->email(email);
			}

			cout << "\tPassword: ";
			if (cin.peek() != inputChar::ENTER) {
				string password = getPassword();
				_user->password(password);
			}

			cout << "\tBirthDay (yyyy-mm-dd): ";
			if (cin.peek() != inputChar::ENTER) {
				Date birthday = input<Date>();
				_user->birthday(birthday);
			}

			/*cout << "\tYour Balance: ";
			if (cin.peek() != inputChar::ENTER) {
				double balance = input<double>();
				_user->balance(balance);
			}*/

			_user->modifyAccount();
		}
		else if (command == "logout") {
			success = _user->logout();
			if (success) {
				delete _user;
				//delete user;
				_user = nullptr;
				//user = nullptr;
				cout << "Logging out..." << endl;
				Sleep(5);
				system("cls");
				//goto prompt;
			}
			else cout << "Something went wrong! Try again later." << endl;
		}
		else if (command == "delete") {
		confirmDeletion:
			cout << "Are you sure you want to delete your account? [y/n]" << endl
				<< "Your information will be lost and can't be restored again." << endl;
			char confirm = _getch();
			switch (confirm) {
			case 'y':
				success = _user->logout() && _user->deleteAccount();
				if (success) {
					delete _user;
					//delete user;
					_user = nullptr;
					//user = nullptr;
					cout << "We are sad to see leave :(" << endl;
					Sleep(5);
					system("cls");
					//goto prompt;
				}
				else cout << "Something went wrong! Try again later." << endl;
				break;
			case 'n':
				cout << "Bravo! You made a good decision." << endl
					<< "\tPress any key to continue..." << endl;
				_getch();
				break;
			default: goto confirmDeletion;
			}
		}
		system("cls");
	} while (command != "back");
}
