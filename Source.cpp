#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


class id
{
public:
	string username;
	string password;
	bool operator==(id&);
	id(string &a, string &b) :
		username(a), password(b){}
	id() :
		username(""), password("") {}

	bool get_username();
	bool get_password();

};


void Menu();
void Register();
void Login();
bool Check_Database(string&);
ifstream& operator>>(ifstream& ist, id& temp);
void PutInDatabase(id);
bool Check_strength(string&);
bool correct(id);


void Menu()
{
	string choice;
	cout << "Do you want to register or login?\n";
	cin >> ws;
	getline(cin,choice);
	if (choice == "register" || choice == "Register")
		Register();
	else if (choice == "login" || choice == "Login")
		Login();
	else
	{
		cout << "Please input correct command.\n";
		Menu();
	}
}

void Register()
{
	string uname,pword;
	cout << "Please enter username: ";
	cin >> uname;
	cin.clear();
	if (Check_Database(uname))
	{
		cout << "Username already exists, Please try again.\n";
		Menu();
	}
	else
	{
		cout << "Please enter new password: ";
		cin>> pword;
		cin.clear();
		if (!Check_strength(pword))
		{
			cout << "password too weak, Please try again.\n";
			Menu();
		}
		ofstream ost;
		ost.open(uname + ".txt");
		PutInDatabase(id(uname, pword));
		ost.close();
	}
}

void Login()
{
	string uname,pword;
	cout << "Please enter username: ";
	cin >> uname;
	if (!Check_Database(uname))
	{
		cout << "Username Doesn't exists.\n";
		Menu();
	}
	else
	{
		cout << "Please Enter the password: ";
		cin >> pword;
		cin.clear();
		if (correct(id(uname, pword)))
		{
			cout << "Successfully Logged in.";
			string file1 = "notepad.exe " + uname ;
			char* file = new char[file1.size()];
			for (int i = 0; i <= file1.size(); i++)
			{
				file[i] = file1[i];
			}
			system(file);
				throw 2;
		}
		else
		{
			cout << "Wrong Username or Password: ";
			Menu();
		}
	}
}


bool id::get_username()
{
	ifstream ist("database.txt");
	char ch;
	ist.get(ch);
	if (ch == 'u')
	{
		string temp;
		ist >> temp;
		username = temp;
		return true;
	}
	else if (ch == 'p')
	{
		return true;
	}
	return false;
}

bool id::get_password()
{
	ifstream ist("database.txt");
	char ch;
	ist.get(ch);
	if (ch == 'p')
	{
		string temp;
		ist >> temp;
		password = temp;
		return true;
	}
	else if (ch == 'u')
	{
		return true;
	}
	return false;
}

bool Check_Database(string &uname)
{
	ifstream ist("databse.txt");
	for (id temp;temp.get_username();)
	{
		if (temp.username == uname)return true;
	}
	return false;
}



ifstream& operator>>(ifstream& ist, id& temp)
{
	char ch;
	ist.get(ch);
	ist >>temp.username;
	ist.get(ch);
	ist.get(ch);
	ist >>temp.password;
	ist.get(ch);
	return ist;
}

void PutInDatabase(id temp)
{
	ofstream ost;
	ost.open("database.txt", ios::app);
	ost << "u" << temp.username << " " << "p" << temp.password << '\n';
	ost.close();
}

bool Check_strength(string& pword)
{
	if (pword.size() <= 8)
		return false;
	return true;
}

bool correct(id temp)
{
	ifstream ist("database.txt");
	for (id uname;ist>>uname;)
	{
		if (uname.username == temp.username && uname.password == temp.password)return true;
	}
	return false;
}


int main()
{
	try
	{
		while (true)
		{
			Menu();
		}
	}
	catch (...)
	{
		char ch;
		cout << "\nPress a key and enter to exit terminal";
		cin >> ch;
	}
}

bool id::operator==(id &temp)
{
	return temp.username == username && temp.password == password;
}