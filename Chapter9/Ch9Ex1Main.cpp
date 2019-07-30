#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

struct Account {
	string first_name;
	string last_name;
	string password;
	string email;
};

const string accounts_file = "accounts.txt";

vector<Account> read_accounts_from_file() {
	vector<Account> accounts;
	ifstream input_file(accounts_file);
	if (input_file) {
		Account account;
		while (input_file >> account.first_name >> account.last_name
			>> account.password >> account.email) {
			accounts.push_back(account);
		}
		input_file.close();
	}
	return accounts;
}

void display_accounts(vector<Account> accounts) {
		int col_width = 10;
		cout << left
			<< setw(col_width * 3) << "Name"
			<< setw(col_width * 4) << "Email" << endl;
		for(Account account : accounts) {
			cout << setw(col_width * 3) << account.first_name + ' ' + account.last_name
				<< setw(col_width * 4) << account.email << endl;
		}
	cout << endl;
}

void write_account_to_file(const string first, const string last, const string password, const string email) {
	ofstream output_file(accounts_file, ios::app);
	if (output_file) {
		output_file << first << '\t'
			<< last << '\t'
			<< password << '\t'
			<< email << '\n';
		output_file.close();
	}
}

void write_accounts_to_file(vector<Account> accounts) {
	ofstream output_file(accounts_file);
	if (output_file) {
		for (Account account : accounts) {
			output_file << account.first_name << '\t'
				<< account.last_name << '\t'
				<< account.password << '\t'
				<< account.email << '\n';
		}
		output_file.close();
	}
}
Account get_account() {
	Account account;
	cout << "First name: ";
	getline(cin, account.first_name);
	cout << "Last name: ";
	getline(cin, account.last_name);
	cout << "Password: ";
	getline(cin, account.password);
	cout << "Email: ";
	getline(cin, account.email);
	return account;
}

int main()
{
	cout << "Create Account List\n\n";

	//string first_name;
	//string last_name;
	//string password;
	//string email;

	vector<Account> accounts = read_accounts_from_file();
	display_accounts(accounts);

	char another = 'y';
	while (tolower(another) == 'y') {
		accounts.push_back(get_account());

		write_accounts_to_file(accounts);

		//write_account_to_file(first_name, last_name, password, email);
		//cout << endl << email << " was added for "
		//	<< first_name + ' ' + last_name << endl << endl;

		cout << "Enter another account? (y/n): ";
		cin >> another;
		cin.ignore();
		cout << endl;
	}

	display_accounts(accounts);
}
