#include "user.h"
#include "dealer.h"
#include "employee.h"
#include "customer.h"
#include <iostream>
#include <Windows.h>

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

int main() {
	string welcome = "***************** WELCOME TO OUR STORE *****************";
	cout << welcome << endl << endl;
	char answer;
	prompt:
	cout << "Do you have an account? [y/n] ";
	cin >> answer;
	system("cls");
	bool success;
	User* user = NULL;
	enum userTypes {none = 0, dealer = 1, employee = 2, customer = 3};
	userTypes userType = none;
	switch (answer) {
	case 'n':
		cout << "Register" << endl;
		cout << "\tChoose your account type:" << endl
			<< "\t\t1.Dealer" << "\t\t2.Employee" << "\t\t3.Customer" << endl;
		int userTypeInput;
		cin >> userTypeInput;
		userType = static_cast<userTypes>(userTypeInput);
		do {
			string firstname = input<string>("\tFirstname: ");
			string lastname = input<string>("\tLastname: ");
			string username = input<string>("\tUsername: ");
			string email = input<string>("\tEmail: ");
			string password = input<string>("\tPassword: ");
			Date birthday = input<Date>("\tBirthDay (yyyy-mm-dd): ");

			if (userType == dealer) {
				delete user;
				user = new Dealer(firstname, lastname, username, email, password, birthday);
			}
			
			else if (userType == employee) {
				delete user;
				user = new Employee(firstname, lastname, username, email, password, birthday);
			}
			
			else if (userType == customer) {
				delete user;
				double balance = input<double>("\tYour Balance: ");
				user = new Customer(firstname, lastname, username, email, password, birthday, balance);
			}
			
			success = user->createAccount();
			system("cls");
			if (!success) {
				cout << "Username or email already exist!" << endl;
			}
		} while (!success);
		cout << "Congratulations! your acount was created successfully." << endl;
		cout << "Please login now." << endl;
		Sleep(5);
		system("cls");
	case 'y':
		cout << "Login" << endl;
		do {
			string username = input<string>("\tUsername: ");
			string password = input<string>("\tPassword: ");
			system("cls");

			// Try login as a customer
			user = new Customer(username, password);
			success = user->login();
			userType = customer;

			if (!success) { // If failed try as employee
				user = new Employee(username, password);
				success = user->login();
				userType = employee;
			}
			
			if (!success) { // If failed try as dealer
				user = new Dealer(username, password);
				success = user->login();
				userType = dealer;
			}
			
			if (!success) { // Otherwise it does not exist or password is incorrect
				userType = none;
				cout << "Incorrect username or password!" << endl;
			}
		} while (!success);
		
		cout << "Logging you in..." << endl;
		Sleep(5);
		system("cls");
		break;

	default:
		cout << "Please choose a valid character!" << endl;
		system("cls");
		goto prompt;
	}

	user->viewStocks();
	int action;
	if (userType == customer) {
		do {
			cout << "Choose an action to do:" << endl
				<< "\t1.Add product to card" << endl
				<< "\t2.Modify the quantity of an added product" << endl
				<< "\t3.Remove item from cart" << endl
				<< "\t4.View cart" << endl
				<< "\t5.Purchase Items" << endl
				<< "\t6.Logout";
			action = input<int>();
		} while (action != 6);
	}

	else if (userType == employee) {
		do {
			cout << "Choose an action to do:" << endl
				<< "\t1.Refill product" << endl
				<< "\t2.Logout";
			action = input<int>();
		} while (action != 2);
	}

	else if (userType == dealer) {
		do {
			cout << "Choose an action to do:" << endl
				<< "\t1.Add new product" << endl
				<< "\t2.Refill product" << endl
				<< "\t3.Remove a product" << endl
				<< "\t4.Logout";
			action = input<int>();
		} while (action != 3);
	}

	delete user;
}