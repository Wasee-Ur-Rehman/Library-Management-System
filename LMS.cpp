#include <iostream>
#include <cstdio>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;
struct Lib
{
	int ISBN, dop, quantity;
	char title[30];
	char authorname[50];
	int total_quantity;
};
struct LentBook {
	int ISBN;
	char title[30];
	char lent_to[20];
	int date;
};
Lib books[10000];
int record = 0;

int currentLogin = -1;
void addbook()
{

	fstream fileofbooks;
	while (1)
	{
		Lib book;
		cin.ignore();
		cout << "\n------------------------------------------------";
		cout << "\nEnter the Book Title : ";
		cin.getline(book.title, 50);
		cout << "\n------------------------------------------------";
		cout << "\nEnter the Author Name : ";
		cin.getline(book.authorname,50);
		cout << "\n------------------------------------------------";
		cin.ignore();
		cout << "\nEnter the Quantity : ";
		cin >> book.quantity;
		cout << "\n------------------------------------------------";
		cout << "\nEnter the ISBN NUMBER  : ";
		cin >> book.ISBN;
		cout << "\n------------------------------------------------";
		cin.ignore();
		cout << "\nEnter the Year Book Published  : ";
		cin >> book.dop;
		cout << "\n------------------------------------------------";

		string convert = "dataof";
		convert += to_string(book.ISBN);
		bool exist = false;
		// if the book is already present in the library then we will just add the quantity of the book
		for (int j = 0; j < record; j++)
		{
			if (books[j].ISBN == book.ISBN)
			{
				exist = true;
				books[j].quantity += book.quantity;
				cout << "\n-----(Book is already present in the library so we have just added the quantity of the book)-----" << endl;
				cout << "----(Quantity of the book is : " << books[j].quantity <<"  )----" << endl;
			}
		}
		if (!exist) {
			// append the book file name to the meta
			fileofbooks.open("meta.txt", ios::app);
			fileofbooks << convert << endl;
			fileofbooks.close();

			books[record] = book;
			record++;
		}

		fileofbooks.open(convert + ".txt", ios::out);
		fileofbooks << book.title << endl;
		fileofbooks << book.authorname << endl;
		fileofbooks << book.quantity << endl;
		fileofbooks << book.ISBN << endl;
		fileofbooks << book.dop << endl;
		fileofbooks.close();

		cout << "\n------------------------------------   ";
		cout << "\nDo You want to Enter more Books ?\n(1) to Enter more books\n(0) If u don't wanna Add More books\n";
		cout << "\n------------------------------------   ";
		int option;
		cin >> option;
		if (option != 1)
		{
			break;
		}
	}
}
void delete_book()
{
	int del_ISBN;
	cout << "\n--------------------------------------------------------";
	cout << "\nEnter The ISBN of the book for DELETETION  :      ";
	cin >> del_ISBN;
	cout << "\n--------------------------------------------------------";
	string change = "del dataof";
	change += to_string(del_ISBN);
	change += ".txt";
	int k = ::record;
	bool found = false;
	for (int i = 0; i < ::record; i++)
	{

		if (books[i].ISBN == int(del_ISBN))
		{
			for (int j = i; j < k - 1; j++)
			{
				books[j] = books[j + 1];
			}
			break;
		}
	}
	if (!found)
	{
		cout << "----(Book Deleted Successfully )----";
	}
	else 
			cout << "----(Book Deleted )----";
	char filename[100];
	
	strcpy_s(filename, change.c_str());
	system(filename);
	// delete the file from meta
	fstream meta("meta.txt");
	string line;
	string newmeta = "";
	while (getline(meta, line))
	{
		if (("del " + line + ".txt") != change)
		{
			newmeta += line;
			newmeta += "\n";
		}
	}
	meta.close();
	ofstream meta1("meta.txt");
	meta1 << newmeta;
	meta1.close();
	record--;
	//remove(filesofbooks);
}
Lib searchBook_byTITLE(string title = "")
{
	Lib book;
	book.ISBN = -1;
	ifstream meta("meta.txt");
	string check;
	while (!meta.eof())
	{
		getline(meta, check);
		ifstream fileofbooks;
		fileofbooks.open(check + ".txt");
		string scan;
		getline(fileofbooks, scan);
		if (scan == title)
		{
			strcpy_s(book.title, scan.c_str());
			getline(fileofbooks, scan);
			strcpy_s(book.authorname, scan.c_str());
			getline(fileofbooks, scan);
			book.quantity = stoi(scan);
			getline(fileofbooks, scan);
			book.ISBN = stoi(scan);
			getline(fileofbooks, scan);
			book.dop = stoi(scan);
			cout << "\n-------------------------\n";
			cout << "Title: " << book.title << endl;
			cout << "Author : " << book.authorname << endl;
			cout << "Quantity : " << book.quantity << endl;
			cout << "ISBN : " << book.ISBN << endl;
			cout << "Year : " << book.dop << endl;
			cout << "\n-------------------------\n";
			break;
		}
		fileofbooks.close();
	}
	meta.close();
	return book;
}
Lib searchBook_byISBN(int ISBN = 0)
{
	Lib book{};
	book.ISBN = -1;
	ifstream meta("meta.txt");
	string check;
	while (!meta.eof())
	{
		getline(meta, check);
		ifstream fileofbooks;
		if (check == ("dataof" + to_string(ISBN)))
		{
			// convert scan to chararray
			fileofbooks.open(check + ".txt");
			string scan;
			getline(fileofbooks, scan);
			strcpy_s(book.title, scan.c_str());
			getline(fileofbooks, scan);
			strcpy_s(book.authorname, scan.c_str());
			getline(fileofbooks, scan);
			book.quantity = stoi(scan);
			getline(fileofbooks, scan);
			book.ISBN = stoi(scan);
			getline(fileofbooks, scan);
			book.dop = stoi(scan);
			cout << "\n-------------------------\n";
			cout << "Title: " << book.title << endl;
			cout << "Author : " << book.authorname << endl;
			cout << "Quantity : " << book.quantity << endl;
			cout << "ISBN : " << book.ISBN << endl;
			cout << "Year : " << book.dop << endl;
			cout << "\n-------------------------\n";
			break;
		}
		fileofbooks.close();
	}
	meta.close();
	return book;

}
void LendBook()
{
	int ISBN;
	cout << "\n-------------------------------------------------------";
	cout << "\nEnter the ISBN of the book For LENDING :  ";
	cin >> ISBN;
	cout << "\n-------------------------------------------------------";
	Lib book = searchBook_byISBN(ISBN);
	if (book.ISBN == ISBN)
	{
		if (book.quantity > 0)
		{
			book.quantity--;
			string convert = "dataof";
			convert += to_string(book.ISBN);
			ofstream fileofbooks;
			fileofbooks.open(convert + ".txt", ios::out);
			fileofbooks << book.title << endl;
			fileofbooks << book.authorname << endl;
			fileofbooks << book.quantity << endl;
			fileofbooks << book.ISBN << endl;
			fileofbooks << book.dop << endl;
			fileofbooks.close();
			
			ofstream userfile;
			userfile.open("./assets/users/" + to_string(currentLogin) + ".txt", ios::app);
			userfile << book.ISBN << " " << time(0) << endl;
			userfile.close();

			cout << "\n----(Book Lended Successfully)----";
		}
		else
		{
			cout << "\n----(Book is not available)----";
		}
	}
	else
	{
		cout << "\n----(Book does not exist)----";
	}
}

void ReturnBook()
{
	int ISBN;

	cout << "\n-------------------------------------------------------";
	cout << "\nEnter the ISBN of the book which u want to return : ";
	cin >> ISBN;
	cout << "\n-------------------------------------------------------";
	Lib book = searchBook_byISBN(ISBN);
	if (book.ISBN == ISBN)
	{


		ifstream userfile;
		userfile.open("./assets/users/" + to_string(currentLogin) + ".txt");
		string line;
		string data;
		bool found = false;
		string date;
		getline(userfile, line); // user id
		data += line + "\n";
		getline(userfile, line); // user password
		data += line + "\n";
		while (!userfile.eof())
		{
			getline(userfile, line);
			if (line == "" || line == " " || line == "\n")
				break;
			int i = 0;
			string ISBN;

			while (line[i] != ' ')
			{
				ISBN += line[i];
				i++;
			}
			while (line[i] != '\0')
			{
				date += line[i];
				i++;
			}
			if (stoi(ISBN) != book.ISBN)
			{
				data += line + "\n";
				if (!found)date = "";
			}
			else
			{
				found = true;
			}
		}
		userfile.close();
		if (found)
		{
			book.quantity++;
			string convert = "dataof";
			convert += to_string(book.ISBN);
			ofstream fileofbooks;
			fileofbooks.open(convert + ".txt", ios::out);
			fileofbooks << book.title << endl;
			fileofbooks << book.authorname << endl;
			fileofbooks << book.quantity << endl;
			fileofbooks << book.ISBN << endl;
			fileofbooks << book.dop << endl;
			fileofbooks.close();
			int currentTimestamp = time(0); // I used this becasue it will check for fine if the 7 days end it will automatically add 10 rupee per day 
			bool late = false;
			int fine = 0;
			if (currentTimestamp - stoi(date) > 7 * 24 * 60 * 60)
			{
				late = true;
				fine = (currentTimestamp - stoi(date)) / (24 * 60 * 60) * 10;
			}
			if (fine != 0) {
				cout << "You have been charged a fine of " << fine << " rupees" << endl;
				cout << "Press enter to pay the fine";
				system("pause >nul");
			}
			ofstream userfile;
			userfile.open("./assets/users/" + to_string(currentLogin) + ".txt", ios::out);
			userfile << data;
			userfile.close();
			cout << "Book Returned Successfully" << endl;
		}
		else
		{
			cout << "Book not found in your account" << endl;
		}

	}
	else
	{
		cout << "Book does not exist";
	}
}

void display_books()
{

	ifstream meta("meta.txt");
	string check;
	while (!meta.eof())
	{
		getline(meta, check);
		if (check == "" || check == " " || check == "\n")
			break;
		ifstream fileofbooks;
		fileofbooks.open(check + ".txt");
		string scan;
		string one, two, three,four,five;
		getline(fileofbooks, scan);
		one = scan;
		getline(fileofbooks, scan);
		two = scan;
		getline(fileofbooks, scan);
		three=scan;
		getline(fileofbooks, scan);
		four = scan;
		getline(fileofbooks, scan);
		five = scan;
		if (stoi(three) > 0)
		{
			cout << "\n-------------------------------" << endl;
			cout << "Title : " << one<< endl;
			cout << "Author Name :" << two << endl;
			cout << "Quantity : " << three << endl;
			cout << "ISBN  : " << four << endl;
			cout << "Publication Year : " << five << endl;
			cout << "-------------------------------" << endl;
		}
		fileofbooks.close();

	}
	meta.close();
}

void load_books()
{
	ifstream meta("meta.txt");
	string check;
	while (!meta.eof())
	{
		getline(meta, check);
		//check if file is empty
		if (check == "" || check == " " || check == "\n")
			break;
		ifstream fileofbooks;
		fileofbooks.open(check + ".txt");
		if (!fileofbooks.is_open()) {
			cout << "Error opening file " << check << endl;
			fileofbooks.close();
			continue;
		}
		cout << "Loading " << check << endl;
		string scan;
		getline(fileofbooks, scan);
		// convert scan to chararray
		strcpy_s(books[record].title, scan.c_str());
		getline(fileofbooks, scan);
		strcpy_s(books[record].authorname, scan.c_str());
		getline(fileofbooks, scan);
		books[record].quantity = stoi(scan);
		getline(fileofbooks, scan);
		books[record].ISBN = stoi(scan);
		getline(fileofbooks, scan);
		books[record].dop = stoi(scan);
		record++;
		fileofbooks.close();
	}
	meta.close();
}
void login()
{
	int id;
	cout << "\n-------------------------";
	cout << "\nEnter your ID : ";
	cin >> id;
	ifstream userfile;
	userfile.open("./assets/users/" + to_string(id) + ".txt");
	if (userfile.is_open())
	{
		string password;
		getline(userfile, password);
		getline(userfile, password);
		string input;
		cout << "\n-------------------------";
		cout << "\nEnter your password : ";
		cin >> input;
		if (input == password)
		{
			currentLogin = id;
			cout << "\n----(Login Successful)----" << endl;
		}
		else
		{
			cout << "\n----(Wrong Password)----" << endl;
		}
		userfile.close();
	}
	else
	{
		cout << "\n----(User does not exist)----" << endl;
	}
}
void register_user() {
	int id;
	cout << "\n------------------------";
	cout << "\nEnter your ID : ";
	cin >> id;
	ifstream userfile;
	userfile.open("./assets/users/" + to_string(id) + ".txt");
	if (userfile.is_open())
	{
		cout << "----(User already exists)----" << endl;
		userfile.close();
	}
	else
	{
		string password;
		cout << "\n------------------------";
		cout << "\nEnter your password : ";
		cin >> password;
		ofstream userfile;
		userfile.open("./assets/users/" + to_string(id) + ".txt");
		userfile << id << endl;
		userfile << password << endl;
		userfile.close();
		cout << "\n\n----(User created successfully)----" << endl;
	}
}

int main()
{
	load_books();
	while (true) 
	{
		system("cls");
		if (currentLogin == -1) 
		{
			system("cls");
			cout << setw(70) << "*-----------------------------------*\n";
			cout << setw(70) << "* Wasee's Library Management System *\n";
			cout << setw(70) << "*-----------------------------------*\n";

			cout << setw(70) << "\n\n***************";
			cout << setw(70) <<"\n(1) Login" << endl;
			cout << setw(70) << "\n***************";
			cout << setw(70) << "\n(2) Register" << endl;
			cout << setw(70) << "\n***************";
			cout << setw(70) << "\n(3) Exit" << endl;
			cout << setw(70) << "\n***************\n\n";
			char choice;
			cout << "Select Option :            ";
			cin >> choice;
			if (choice == '1')
			{
				system("cls");

				cout <<"\n*********************";
				cout << "\n* In LoGin Function *";
				cout <<"\n*********************\n\n";

				login();
				system("pause");
			}
			else if (choice == '2')
			{
				system("cls");
				register_user();
				system("pause");
			}
			else if (choice == '3')
			{
				cout << "----(Thanks For Coming)----\n";
				break;
			}
			else
			{
				cout << "\n***********************************";
				cout << "\nPlease Enter The Option From Menu" << endl;
				system("pause");
				continue;
			}
		}
		else if (currentLogin != -1) {
			cout << setw(70) << "*-----------------------------------*\n";
			cout << setw(70) << "* Wasee's Library Management System *\n";
			cout << setw(70) << "*-----------------------------------*\n";

			cout << setw(26) << "Home Page\n";
			cout << setw(49) << "Please Enter the Option Given Below\n";

			cout << setw(25) << "(A) Add Books\n";
			cout << setw(28) << "(S) Search Book \n";
			cout << setw(27) << "(D) Delete Book\n";
			cout << setw(28) << "(E) Display Book\n";
			cout << setw(26) << "(L) Lend Book \n";
			cout << setw(27) << "(R) Return Book\n";
			cout << setw(23) << "(Q) Log Out\n";

			cout << setw(50) << "\nPlease Select Option from The Menu" << endl;

			char option;
			cin >> option;
			if (option == 'a' || option == 'A')
			{
				system("cls");
				cout << "\n**************************";
				cout << "\n*  In Add Book Function  *";
				cout << "\n**************************";
				addbook();
				system("pause");
			}
			else if (option == 's' || option == 'S')
			{
				a:
				system("cls");
				cout << "\n*****************************";
				cout << "\n*  In Search Book Function  *";
				cout << "\n*****************************";
				char choice;
				cout << "\n ---------------------------";
				cout << "\n(1) Search By ISBN\n        ";
				cout << "\n ---------------------------";
				cout << "\n(2) Search By Book Title\n   ";
				cout << "\n ----------------------------";
				cin >> choice;
				Lib book;
				if (choice == '1')
				{
					system("cls");
					cout << "\n-------------------------";
					cout << "\nEnter the Book ISBN    ";
					int ISBN;
					cin >> ISBN;
					cout << "\n-------------------------";
					book = searchBook_byISBN(ISBN);
				}
				else if (choice == '2')
				{
					system("cls");
					cout << "\n-------------------------";
					cout << "\nEnter the Book Title     ";
					string title;
					cin >> title;
					cout << "\n-------------------------\n";
					book = searchBook_byTITLE(title);
				}
				else
				{
					cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~";
					cout << "Invalid INPUT";
					cout << "Enter the Option Again";
					cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~";
					goto a;
				}

				if (book.ISBN == -1) {
					cout << "\n----(Book not found)----" << endl;
				}
				cout << "\n";
				system("pause");
			}
			else if (option == 'd' || option == 'D')
			{
				system("cls");
				cout << "\n*****************************";
				cout << "\n*  In Delete Book Function  *";
				cout << "\n*****************************";
				delete_book();
				system("pause");
			}
			else if (option == 'e' || option == 'E')
			{
				system("cls");
				cout << "\n******************************";
				cout << "\n*  In DISPLAY Book Function  *";
				cout << "\n******************************";
				display_books();
				cout << "\nPress enter to continue...";
				system("pause >nul");
			}
			else if (option == 'l' || option == 'L')
			{
				system("cls");
				cout << "\n******************************";
				cout << "\n*  In LENDING Book Function  *";
				cout << "\n******************************";
				LendBook();
				system("pause");
			}
			if (option == 'r' || option == 'R')
			{
				system("cls");
				cout << "\n******************************";
				cout << "\n*  In RETURN  Book Function  *";
				cout << "\n******************************";
				ReturnBook();
				system("pause");
			}
			else if (option == 'q' || option == 'Q')
			{
				currentLogin = -1;
			}
			else
			{
				puts("\n\n \t\tSelect only from the given menu.....\n \t\tpress enter to to go to main menu......");
			}
		}

	}
	system("pause");
	return 0;
}