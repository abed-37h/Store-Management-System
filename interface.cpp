#include "utilities.h"


int main() {
	prompt:
	const string welcome = "***************** WELCOME TO OUR STORE *****************";
	cout << welcome << endl << endl;

	cout << "Do you have an account? [y/n] ";
	char answer = _getch();
	system("cls");

	bool success = false;
	User* user = nullptr;
	enum class userTypes {
		none = 0,
		dealer = 1,
		employee = 2,
		customer = 3
	};
	userTypes userType = userTypes::none;
	switch (answer) {
	case 'n':
		do {
			try {
				cout << "Register" << endl;
				cout << "\tChoose your account type:" << endl
					<< "\t\t1.Dealer" << "\t\t2.Employee" << "\t\t3.Customer" << endl;
				userType = static_cast<userTypes>(input<int>());
				if (userType != userTypes::dealer && userType != userTypes::employee && userType != userTypes::customer) {
					cerr << "The number must be 1, 2 or 3." << endl;
					continue;
				}

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
			}
			catch (const int&) {
				cin.clear();
				cin.ignore();
				cerr << "Please, enter an integer number." << endl;
			}
			catch (const string& str) {
				cerr << str << endl;
			}
			catch (const std::exception& e) {
				cerr << e.what() << endl;
			}
			catch (...) {
				cerr << "Some exceptions occurred!" << endl;
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
		string category = "*";
		string command;
		do {
			cout << "Choose an action to do:" << endl
				<< "\t1. Profile < show-profile >" << endl
				<< "\t2. Add product to card < add {product-name} [quantity] >" << endl
				<< "\t3. Modify the quantity of an added product < modify|edit {product-name} {quantity} >" << endl
				<< "\t4. Remove item from cart < remove {product-name} >" << endl
				<< "\t5. View cart < view-cart >" << endl
				<< "\t6. Exit < exit >" << endl;
			cout << customer->username() << '>';
			cin >> command;
			if (command == "show-profile") {
				system("cls");
				do {
					customer->showProfileInfo();
					cout << endl;
					cout << "Choose an action to do:" << endl
						<< "\t1. Edit profile info < edit >" << endl
						<< "\t2. Logout < logout >" << endl
						<< "\t3. Delete account < delete >" << endl
						<< "\t4. Go back < back >" << endl;
					cout << customer->username() << '>';
					cin >> command;
					if (command == "edit") {
						cout << "\tFirstname: ";
						cin.ignore();
						if (cin.peek() != inputChar::ENTER) {
							string firstname = input<string>();
							customer->firstname(firstname);
						}

						cout << "\tLastname: ";
						cin.ignore();
						if (cin.peek() != inputChar::ENTER) {
							string lastname = input<string>();
							customer->lastname(lastname);
						}

						cout << "\tUsername: ";
						cin.ignore();
						if (cin.peek() != inputChar::ENTER) {
							string username = input<string>();
							customer->username(username);
						}

						cout << "\tEmail: ";
						cin.ignore();
						if (cin.peek() != inputChar::ENTER) {
							string email = input<string>();
							customer->email(email);
						}

						cout << "\tPassword: ";
						cin.ignore();
						if (cin.peek() != inputChar::ENTER) {
							string password = getPassword();
							customer->password(password);
						}

						cout << "\tBirthDay (yyyy-mm-dd): ";
						cin.ignore();
						if (cin.peek() != inputChar::ENTER) {
							Date birthday = input<Date>();
							customer->birthday(birthday);
						}

						cout << "\tYour Balance: ";
						cin.ignore();
						if (cin.peek() != inputChar::ENTER) {
							double balance = input<double>();
							customer->balance(balance);
						}

						customer->modifyAccount();
					}
					else if (command == "logout") {
						success = customer->logout();
						if (success) {
							delete customer;
							delete user;
							customer = nullptr;
							user = nullptr;
							cout << "Logging out..." << endl;
							Sleep(5);
							system("cls");
							goto prompt;
						}
						else cout << "Something went wrong! Try again later." << endl;
					}
					else if (command == "delete") {
						confirmDeletionCustomer:
						cout << "Are you sure you want to delete your account? [y/n]" << endl
							<< "Your information will be lost and can't be restored again." << endl;
						char confirm = _getch();
						switch (confirm) {
						case 'y':
							success = customer->logout() && customer->deleteAccount();
							if (success) {
								delete customer;
								delete user;
								customer = nullptr;
								user = nullptr;
								cout << "We are sad to see leave :(" << endl;
								Sleep(5);
								system("cls");
								goto prompt;
							}
							else cout << "Something went wrong! Try again later." << endl;
							break;
						case 'n':
							cout << "Bravo! You made a good decision." << endl
								<< "\tPress any key to continue..." << endl;
							_getch();
							break;
						default: goto confirmDeletionCustomer;
						}
					}
					system("cls");
				} while (command != "back");
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
				do {
					cout << "Choose an action to do:" << endl
						<< "\t1. Purchase items < purchase >" << endl
						<< "\t2. Back < back >" << endl;
					cout << customer->username() << '>';
					cin >> command;
					if (command == "purchase") {
						customer->purchase();
					}
				} while (command != "back");
			}
			system("cls");
			customer->viewStocks(category);
		} while (command != "exit");

		delete customer;
		customer = nullptr;
	}

	else if (userType == userTypes::employee) {
		Employee* employee = static_cast<Employee*>(user);
		string category = "*";
		string command;
		do {
			cout << "Choose an action to do:" << endl
				<< "\t1.Profile < show-profile >" << endl
				<< "\t2.Refill product < refill {id} {quantity} >" << endl
				<< "\t3.Exit < exit >" << endl;
			cin >> command;
			if (command == "show-profile") {
				system("cls");
				do {
					employee->showProfileInfo();
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
							employee->firstname(firstname);
						}

						cout << "\tLastname: ";
						if (cin.peek() != inputChar::ENTER) {
							string lastname = input<string>();
							employee->lastname(lastname);
						}

						cout << "\tUsername: ";
						if (cin.peek() != inputChar::ENTER) {
							string username = input<string>();
							employee->username(username);
						}

						cout << "\tEmail: ";
						if (cin.peek() != inputChar::ENTER) {
							string email = input<string>();
							employee->email(email);
						}

						cout << "\tPassword: ";
						if (cin.peek() != inputChar::ENTER) {
							string password = getPassword();
							employee->password(password);
						}

						cout << "\tBirthDay (yyyy-mm-dd): ";
						if (cin.peek() != inputChar::ENTER) {
							Date birthday = input<Date>();
							employee->birthday(birthday);
						}

						employee->modifyAccount();
					}
					else if (command == "logout") {
						success = employee->logout();
						if (success) {
							delete employee;
							delete user;
							employee = nullptr;
							user = nullptr;
							cout << "Logging out..." << endl;
							Sleep(5);
							system("cls");
							goto prompt;
						}
						else cout << "Something went wrong! Try again later." << endl;
					}
					else if (command == "delete") {
					confirmDeletionEmployee:
						cout << "Are you sure you want to delete your account? [y/n]" << endl
							<< "Your information will be lost and can't be restored again." << endl;
						char confirm = _getch();
						switch (confirm) {
						case 'y':
							success = employee->logout() && employee->deleteAccount();
							if (success) {
								delete employee;
								delete user;
								employee = nullptr;
								user = nullptr;
								cout << "We are sad to see leave :(" << endl;
								Sleep(5);
								system("cls");
								goto prompt;
							}
							else cout << "Something went wrong! Try again later." << endl;
							break;
						case 'n':
							cout << "Bravo! You made a good decision." << endl
								<< "\tPress any key to continue..." << endl;
							_getch();
							break;
						default: goto confirmDeletionEmployee;
						}
					}
					system("cls");
				} while (command != "back");
			}
			else if (command == "refill") {
				unsigned int id;
				unsigned int quantity;
				cin >> id >> quantity;
				employee->refill(id, quantity);
			}
			system("cls");
			employee->viewStocks(category);
		} while (command != "exit");

		delete employee;
		employee = nullptr;
	}

	else if (userType == userTypes::dealer) {
		Dealer* dealer = static_cast<Dealer*>(user);
		string category = "*";
		string command;
		do {
			cout << "Choose an action to do:" << endl
				<< "\t1. Profile < show-profile >" << endl
				<< "\t2. Add new product < add {name} {brand} {category} {price} {quanity} >" << endl
				<< "\t3. Refill product < refill {id} {quantity} >" << endl
				<< "\t4. Remove a product < remove {product-id} >" << endl
				<< "\t5. Exit < exit >" << endl;
			cin >> command;
			if (command == "show-profile") {
				system("cls");
				do {
					dealer->showProfileInfo();
					cout << endl;
					cout << "Choose an action to do:" << endl
						<< "\t1. Edit profile info < edit >" << endl
						<< "\t2. Logout < logout >" << endl
						<< "\t3. Delete account < delete >" << endl
						<< "\t4. Go back < back >" << endl;
					cin >> command;
					if (command == "edit") {
						cout << "\tFirstname: ";
						cin.ignore();
						if (cin.peek() != inputChar::ENTER) {
							string firstname = input<string>();
							dealer->firstname(firstname);
						}

						cout << "\tLastname: ";
						cin.ignore();
						if (cin.peek() != inputChar::ENTER) {
							string lastname = input<string>();
							dealer->lastname(lastname);
						}

						cout << "\tUsername: ";
						cin.ignore();
						if (cin.peek() != inputChar::ENTER) {
							string username = input<string>();
							dealer->username(username);
						}

						cout << "\tEmail: ";
						cin.ignore();
						if (cin.peek() != inputChar::ENTER) {
							string email = input<string>();
							dealer->email(email);
						}

						cout << "\tPassword: ";
						cin.ignore();
						if (cin.peek() != inputChar::ENTER) {
							string password = getPassword();
							dealer->password(password);
						}

						cout << "\tBirthDay (yyyy-mm-dd): ";
						cin.ignore();
						if (cin.peek() != inputChar::ENTER) {
							Date birthday = input<Date>();
							dealer->birthday(birthday);
						}

						dealer->modifyAccount();
					}
					else if (command == "logout") {
						success = dealer->logout();
						if (success) {
							delete dealer;
							delete user;
							dealer = nullptr;
							user = nullptr;
							cout << "Logging out..." << endl;
							Sleep(5);
							system("cls");
							goto prompt;
						}
						else cout << "Something went wrong! Try again later." << endl;
					}
					else if (command == "delete") {
					confirmDeletionDealer:
						cout << "Are you sure you want to delete your account? [y/n]" << endl
							<< "Your information will be lost and can't be restored again." << endl;
						char confirm = _getch();
						switch (confirm) {
						case 'y':
							success = dealer->logout() && dealer->deleteAccount();
							if (success) {
								delete dealer;
								delete user;
								dealer = nullptr;
								user = nullptr;
								cout << "We are sad to see leave :(" << endl;
								Sleep(5);
								system("cls");
								goto prompt;
							}
							else cout << "Something went wrong! Try again later." << endl;
							break;
						case 'n':
							cout << "Bravo! You made a good decision." << endl
								<< "\tPress any key to continue..." << endl;
							_getch();
							break;
						default: goto confirmDeletionDealer;
						}
					}
					system("cls");
				} while (command != "back");
			}
			else if (command == "add") {
				string name;
				string brand;
				string category;
				double price;
				unsigned int quantity;
				cin >> name >> brand >> category >> price >> quantity;
				Product product(0, name, brand, category, price, quantity);
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
				dealer->removeItem(id);
			}
			system("cls");
			dealer->viewStocks(category);
		} while (command != "exit");

		delete dealer;
		dealer = nullptr;
	}

	delete user;
	user = nullptr;

	return 0;
}