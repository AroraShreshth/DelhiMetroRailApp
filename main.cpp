#include <iostream>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#elif __unix__
#include <unistd.h>
#endif

#define DATA 128

using namespace std;

void clrscr();
char getch();
char *gets(char *);
void sleep(int);

class app
{
protected:
public:
	char uid[DATA];
};

class menu : public app
{
private:
	char *title;
	char *options[10];
	unsigned short int selected_option;

public:
	menu(char *a = "", char *b = "", char *c = "",
		 char *d = "", char *e = "", char *f = "",
		 char *g = "", char *h = "", char *i = "",
		 char *j = "") : title(a)
	{
		options[0] = b;
		options[1] = c;
		options[2] = d;
		options[3] = e;
		options[4] = f;
		options[5] = g;
		options[6] = h;
		options[7] = i;
		options[8] = j;
	}
	void io();
	unsigned short int get_selected_option()
	{
		return selected_option;
	}
};
void menu::io()
{
	while (1)
	{
		int min_option = 1, max_option = 0;
		clrscr();
		cout << title << "\n\n";
		for (int i = 0; i < 9; i++)
		{
			if (strcmp(options[i], "") == 0)
			{
				break;
			}
			cout << i + 1 << ". " << options[i] << '\n';
			max_option = i + 1;
		}
		if (strcmp(title, "Welcome to Delhi Metro") != 0)
		{
			cout << "\n0. Back\n";
		}
		else
		{
			cout << "\n0. Exit\n";
		}
		min_option = 0;
		selected_option = ((int)getch()) - ((int)'0');
		if ((selected_option >= min_option) && (selected_option <= max_option))
		{
			break;
		}
		else
		{
			cout << "Invalid Option\n\n";
			sleep(2);
		}
	}
}

menu welcome_menu("Welcome to Delhi Metro", "Rider", "Admin");
menu rider_menu("Rider", "Use Metro Pass", "Buy New Metro Pass", "Cash");
menu uid_different_menu("Please enter a different username", "Enter");
menu uid_not_found_menu("Username doesn't exist", "Re-Enter Username", "Buy New Metro Pass");
menu uid_pass_not_match_menu("Incorrect Password", "Re-Enter Password", "Re-Enter Username", "Buy New Metro Pass");
menu admin_menu("Admin");

class user : public app
{
protected:
public:
	char passwd[DATA];
};

class rider : public user
{
public:
	unsigned short int buy_pass();
	unsigned short int validate_pass();
	static unsigned short int uid_exists(char[DATA]);
	static unsigned short int uid_passwd_match(char[DATA], char[DATA]);
};

unsigned short int rider::uid_exists(char a[DATA])
{
	ifstream riders_file("RIDERS.DAT", ios::in | ios::binary);
	rider read_rider;
	if (riders_file)
	{
		while (1)
		{
			riders_file.read((char *)&read_rider, sizeof(rider));
			if (riders_file.eof())
			{
				return 0;
			}
			if (strcmp(read_rider.uid, a) == 0)
			{
				return 1;
			}
		}
	}
	else
	{
		return 0;
	}
}

unsigned short int rider::uid_passwd_match(char a[DATA], char b[DATA])
{
	ifstream riders_file("RIDERS.DAT", ios::in | ios::binary);
	rider read_rider;
	if (riders_file)
	{
		while (1)
		{
			riders_file.read((char *)&read_rider, sizeof(rider));
			if (riders_file.eof())
			{
				return 0;
			}
			if (strcmp(read_rider.uid, a) == 0)
			{
				return (strcmp(read_rider.passwd, b) == 0);
			}
		}
	}
	else
	{
		return 0;
	}
}

unsigned short int rider ::buy_pass()
{
	while (1)
	{
		clrscr();
		cout << "Buy New Metro Pass\n\nNew Username: ";
		char a[DATA], b[DATA];
		gets(a);
		if (!rider::uid_exists(a))
		{
			strcpy(this->uid, a);
			cout << "New Password: ";
			gets(b);
			strcpy(this->passwd, b);
			ofstream riders_file("RIDERS.DAT", ios::out | ios::app | ios::binary);
			riders_file.write((char *)this, sizeof(rider));
			riders_file.close();
			cout << "\nPurchase Successful!\n\n";
			sleep(2);
			return 10;
		}
		else
		{
			uid_different_menu.io();
			int comm = uid_different_menu.get_selected_option();
			if (comm != 1)
			{
				return comm;
			}
		}
	}
}

unsigned short int rider::validate_pass()
{
	while (1)
	{
		clrscr();
		cout << "Use Metro Pass\n\n";
		char a[DATA], b[DATA];
		cout << "Username: ";
		if (!rider::uid_exists(a))
		{
			gets(a);
		}
		else
		{
			cout << a << '\n';
		}
		if (rider::uid_exists(a))
		{
			cout << "Password: ";
			gets(b);
			if (rider::uid_passwd_match(a, b))
			{
				strcpy(this->uid, a);
				strcpy(this->passwd, b);
				cout << "\nLogin and Usage Successful!\n";
				sleep(2);
				return 10;
			}
			else
			{
				cout << "\nLogin and Usage Unsuccessful!\n";
				sleep(2);
				uid_pass_not_match_menu.io();
				int comm = uid_pass_not_match_menu.get_selected_option();
				if (comm == 2)
				{
					strcpy(a, NULL);
				}
				else if (comm == 1)
				{
				}
				else
				{
					return comm;
				}
			}
		}
		else
		{
			uid_not_found_menu.io();
			int comm = uid_not_found_menu.get_selected_option();
			if (comm != 1)
			{
				return comm;
			}
		}
	}
}

int main()
{
	do
	{
		welcome_menu.io();
		switch (welcome_menu.get_selected_option())
		{
		case 1:
			do
			{
				rider_menu.io();
				switch (rider_menu.get_selected_option())
				{
					rider current_rider;
				case 1:
					switch (current_rider.validate_pass())
					{
					case 10:

						break;
					case 2:
						goto buy_pass;
						break;
					}
					break;
				case 2:
				buy_pass:
					if (current_rider.buy_pass())
					{
					}
					break;
				case 3:
					break;
				}
			} while (rider_menu.get_selected_option());
			break;
		case 2:
			do
			{
				admin_menu.io();
			} while (admin_menu.get_selected_option());
			break;
		}
	} while (welcome_menu.get_selected_option());

	return 0;
}

void clrscr()
{
#ifdef _WIN32
	system("cls");
#elif __unix__
	system("clear");
#endif
}

char getch()
{
	char t;
	cin >> t;
	return t;
}

char *gets(char *t)
{
	cin >> t;
	return t;
}

void sleep(int n)
{
#ifdef _WIN32
	Sleep(n * 1000);
#elif __unix__
	usleep(n * 1000000);
#endif
}