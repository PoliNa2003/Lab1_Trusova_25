#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>

using namespace std;

struct manufacture {
	char* firma;
	char* adr2;
	int type;
	double balance;
};

void menu() {
	cout << "Add a new element - 1\n";
	cout << "Print the database - 2\n";
	cout << "Search for a provider - 3\n";
	cout << "Sort by type of provider - 4\n";
	cout << "Sort the database(in redusing balance) - 5\n";
	cout << "Close the program - 6\n";
}

void new_firma(manufacture* new_firm) {
	cout << "Enter the name of a new firm(max 20 chars)\n";
	char buff[30];
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	gets_s(buff);
	new_firm->firma = new char[strlen(buff) + 1];
	strcpy(new_firm->firma, buff);

	cout << "Enter the address(max 20 chars)\n";
	gets_s(buff);
	new_firm->adr2 = new char[strlen(buff) + 1];
	strcpy(new_firm->adr2, buff);

	cout << "Enter the type(1 or 2)\n";
	cin >> new_firm->type;
	while (cin.fail() or new_firm->type > 2 or new_firm->type < 1) {
		cout << "Error!\n";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Enter the type(1 or 2)\n";
		cin >> new_firm->type;
	}

	cout << "Enter the balance\n";
	cin >> new_firm->balance;
	while (cin.fail()) {
		cout << "Error!\n";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Enter the balance\n";
		cin >> new_firm->balance;
	}
}

void print_data(manufacture* firm) {
	cout << firm->firma;
	for (int i = 20; i > strlen(firm->firma); i--) cout << " ";
	cout << '|';
	cout << firm->adr2;
	for (int i = 20; i > strlen(firm->adr2); i--) cout << " ";
	cout << '|';
	cout << firm->type;
	cout << "    |";
	cout << firm->balance << '\n';
}


int main() {
	int amount_of_data = 0;
	manufacture* base_manufacture = new manufacture[100];
	ifstream fin;
	fin.open("1.txt");
	fin >> amount_of_data;
	for (int i = 0; i < amount_of_data; ++i) {
		char buff[21];
		fin.getline(buff, 20, '|');
		base_manufacture[i].firma = new char[strlen(buff) + 1];
		strcpy(base_manufacture[i].firma, buff);
		fin.getline(buff, 20, '|');
		base_manufacture[i].adr2 = new char[strlen(buff) + 1];
		strcpy(base_manufacture[i].adr2, buff);

		fin >> base_manufacture[i].type;
		fin >> base_manufacture[i].balance;
	}
	fin.close();

	int menu_option = 1;
	while (menu_option != 6) {
		menu();
		cout << "Enter the command number\n";
		cin >> menu_option;
		while (cin.fail() or menu_option > 6 or menu_option < 1) {
			cout << "Error!\n";
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << "Enter the command number\n";
			cin >> menu_option;
		}

		if (menu_option == 1) {
			new_firma(&base_manufacture[amount_of_data]);
			amount_of_data++;
			cout << "Successfully!\n";
		}

		else if (menu_option == 2) {
			cout << "Name                |Address             |Type |Balance\n";
			for (int i = 0; i < amount_of_data; ++i)
				print_data(&base_manufacture[i]);
		}

		else if (menu_option == 3) {
			cout << "Enter the name of the firm\n";
			char name_firm[21];
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			gets_s(name_firm);
			cout << "Name                |Address             |Type |Balance\n";
			for (int i = 0; i < amount_of_data; ++i)
				if (strcmp(name_firm, base_manufacture[i].firma) == 0) print_data(&base_manufacture[i]);
		}

		else if (menu_option == 4) {
			int type;
			cout << "Enter the type of provider(1 or 2)\n";
			cin >> type;
			while (cin.fail() or type > 2 or type < 1) {
				cout << "Error!\n";
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cout << "Enter the type of provider(1 or 2)\n";
				cin >> menu_option;
			}
			cout << "Name                |Address             |Type |Balance\n";
			for (int i = 0; i < amount_of_data; ++i) {
				if (base_manufacture[i].type == type)
					print_data(&base_manufacture[i]);
			}
		}

		else if (menu_option == 5) {
			int* sort_data = new int[amount_of_data];
			for (int i = 0; i < amount_of_data; ++i) sort_data[i] = i;
			for (int i = 0; i < amount_of_data; ++i) {
				for (int j = 1; j < amount_of_data; ++j) {
					if (base_manufacture[sort_data[j]].balance < base_manufacture[sort_data[j - 1]].balance) {
						sort_data[j] += sort_data[j - 1];
						sort_data[j - 1] = sort_data[j] - sort_data[j - 1];
						sort_data[j] = sort_data[j] - sort_data[j - 1];
					}
				}
			}
			cout << "Name                |Address             |Type |Balance\n";
			for (int i = 0; i < amount_of_data; ++i) print_data(&base_manufacture[sort_data[i]]);
			delete[] sort_data;
		}

		else break;
	}

	ofstream fout;
	fout.open("1.txt");
	fout << amount_of_data;
	for (int i = 0; i < amount_of_data; ++i) {
		fout << base_manufacture[i].firma << '|';
		fout << base_manufacture[i].adr2 << '|';
		fout << base_manufacture[i].type << '\n';
		fout << base_manufacture[i].balance;
	}
	fout.close();

	for (int i = 0; i < amount_of_data; ++i) {
		delete[] base_manufacture[i].adr2;
		delete[] base_manufacture[i].firma;
	}
	delete[] base_manufacture;

	cout << "Goodbye\n";

	return 0;
}