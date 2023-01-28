#include "utilities.h"
#include <Windows.h>
#include <sstream>

using std::istringstream;
using std::getline;
using std::count;

int main() {
	const string welcome = "***************** WELCOME TO OUR STORE *****************";
	cout << welcome << endl << endl;

	prompt:
	cout << "Do you have an account? [y/n] ";
	char answer = _getch();
	system("cls");

	bool success;
	User* user = NULL;
	enum class userTypes {
		none = 0,
		dealer = 1,
		employee = 2,
		customer = 3
	};
	userTypes userType = userTypes::none;
	switch (answer) {
	case 'n':
		cout << "Register" << endl;
		cout << "\tChoose your account type:" << endl
			<< "\t\t1.Dealer" << "\t\t2.Employee" << "\t\t3.Customer" << endl;
		/*int userTypeInput;
		cin >> userTypeInput;*/
		userType = static_cast<userTypes>(input<int>());
		do {
			string firstname = input<string>("\tFirstname: ");
			string lastname = input<string>("\tLastname: ");
			string username = input<string>("\tUsername: ");
			string email = input<string>("\tEmail: ");
			string password = getPassword("\tPassword: ");
			Date birthday = input<Date>("\tBirthDay (yyyy-mm-dd): ");

			if (userType == userTypes::dealer) {
				//delete user;
				user = new Dealer(firstname, lastname, username, email, password, birthday);
			}
			
			else if (userType == userTypes::employee) {
				//delete user;
				user = new Employee(firstname, lastname, username, email, password, birthday);
			}
			
			else if (userType == userTypes::customer) {
				//delete user;
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
			string password = getPassword("\tPassword: ");
			system("cls");

			// Try login as a customer
			user = new Customer(username, password);
			success = user->login();
			userType = userTypes::customer;

			if (!success) { // If failed try as employee
				user = new Employee(username, password);
				success = user->login();
				userType = userTypes::employee;
			}
			
			if (!success) { // If failed try as dealer
				user = new Dealer(username, password);
				success = user->login();
				userType = userTypes::dealer;
			}
			
			if (!success) { // Otherwise it does not exist or password is incorrect
				userType = userTypes::none;
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
	string action;
	if (userType == userTypes::customer) {
		Customer* customer = static_cast<Customer*>(user);
		string command;
		do {
			cout << "Choose an action to do:" << endl
				<< "\t1.Profile < show-profile >" << endl
				<< "\t2.Add product to card < add {product-name} [quantity] >" << endl
				<< "\t3.Modify the quantity of an added product < modify|edit {product-name} {quantity} >" << endl
				<< "\t4.Remove item from cart < remove {product-name} >" << endl
				<< "\t5.View cart < view-cart >" << endl
				<< "\t6.Purchase Items < purchase >" << endl
				<< "\t7.Exit < exit >" << endl;
			cin >> command;
			if (command == "show-profile") {
				// TODO: implement
			}
			else if (command == "add") {
				Product product;
				string name;
				cin >> name;
				product.name(name);
				if (!cin) {
					customer->addProductToCart(name);
				}
				else {
					unsigned int quantity;
					cin >> quantity;
					customer->addProductToCart(name, quantity);
				}
			}
			else if (command == "modify" || command == "edit") {
				string name;
				unsigned int quantity;
				cin >> name >> quantity;
				customer->modifyProductQunatityInCart(name, quantity);
			}
			else if (command == "remove") {
				string name;
				cin >> name;
				customer->removeProductFromCart(name);
			}
			else if (command == "view-cart") {
				customer->viewCart();
			}
			else if (command == "purchase") {
				customer->purchase();
			}
			system("cls");
		} while (command != "exit");

		delete customer;
	}

	else if (userType == userTypes::employee) {
		Employee* employee = static_cast<Employee*>(user);
		string command;
		do {
			cout << "Choose an action to do:" << endl
				<< "\t1.Profile < show-profile >" << endl
				<< "\t2.Refill product < refill {id} {quantity} >" << endl
				<< "\t3.Exit < exit >" << endl;
			cin >> command;
			if (command == "show-profile") {
				// TODO: implement
			}
			else if (command == "refill") {
				unsigned int id;
				unsigned int quantity;
				cin >> id >> quantity;
				employee->refill(id, quantity);
			}
			system("cls");
		} while (command != "exit");

		delete employee;
	}

	else if (userType == userTypes::dealer) {
		Dealer* dealer = static_cast<Dealer*>(user);
		string command;
		do {
			cout << "Choose an action to do:" << endl
				<< "\t1.Profile < show-profile >" << endl
				<< "\t2.Add new product < add {name} {brand} {category} {price} {quanity} >" << endl
				<< "\t3.Refill product < refill {id} {quantity} >" << endl
				<< "\t4.Remove a product < remove {product-id} >" << endl
				<< "\t5.Exit < exit >" << endl;
			//action = _getch();
			/*getline(cin, action);
			action = strip(action);
			istringstream sin(action);*/
			
			cin >> command;
			if (command == "show-profile") {
				// TODO: implement
			}
			else if (command == "add") {
				//int spaces = count(action.begin(), action.end(), ' ');
				string name;
				string brand;
				string category;
				double price;
				unsigned int quantity;
				cin >> name >> brand >> category >> price >> quantity;
				Product product(0, name, brand, category, price, quantity);
				/*Product product;
				cin.putback(0);
				cin >> product;*/
				dealer->addItem(product);
			}
			else if (command == "refill") {
				unsigned int id;
				unsigned int quantity;
				cin >> id >> quantity;
				dealer->refill(id, quantity);
			}
			else if (command == "remove") {
				unsigned int id;
				cin >> id;
				dealer->removeItem(id); // TODO: edit
			}
			system("cls");
		} while (command != "exit");

		delete dealer;
	}

	delete user;

	return 0;
}