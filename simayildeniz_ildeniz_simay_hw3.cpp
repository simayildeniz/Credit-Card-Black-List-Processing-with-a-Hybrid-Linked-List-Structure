# include <iostream>
# include <string>
# include <sstream>
# include <fstream>
# include "CardListHeader.h"

using namespace std;

void displayMenu ()
{
	cout << "1) Upload Card(s) from a File " << endl;
	cout << "2) Display List Chronological " << endl;
	cout << "3) Display List Reverse Chronological " << endl;
	cout << "4) Card Search " << endl;
	cout << "5) Bulk Delete " << endl;
	cout << "6) Exit " << endl;
	cout << "Please choose option from the menu: ";
}

//I took this function from my previous HW and updated it
bool isValidOption(string option)
{
	if (option == "1" || option == "2" || option == "3" || option == "4" || option == "5" || option == "6" )
	{
		return true;
	}
	return false;
}

//I took this function from my previous HW and updated it
bool monthChecker (string month)
{
	if (month.length()>2 )
	{
		return false;
	}
	else
	{
		if (month.length() == 1)
		{
			if (month[0] <= '9' && '1' <= month[0])
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (month.length() == 2)
		{
			if (month[0] <= '1' && (month[1] == '0' || month[1] == '1' || month[1] == '2'))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}

//I took this function from my previous HW and updated it
bool yearChecker (string year)
{
	if (year.length() < 4)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < year.length(); i++)
		{
			if (!(year[i] <= '9' && '0' <= year[i]))
			{
				return false;
			}
		}
	}
	return true;
}

//I took this function from my previous HW and updated it
bool isValidCardNo (string cardNo)
{
	int length = cardNo.length();
	if (length != 16)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < length; i++)
		{
			if (!(cardNo[i] <= '9' &&'0' <= cardNo[i] ))
			{
				return false;
			}
		}
	}
	return true;
}

int main()
{
	string cardNo;
	string month, year;
	string fileName;
	ifstream inFile;
	string option = "0";
	CardList myObject;

	displayMenu();
	cin.clear();
	cin >> option;

	while (option !=  "6")
	{
		while (isValidOption(option) == false)
		{
			cout << "Invalid operation! " << endl;
			cout << endl;
			displayMenu();
			cin.clear();
			cin >> option;
		}
		//inFile.clear();
		if (option == "1")
		{
			
			cout << "Please enter file name: ";
			cin >> fileName;
			inFile.open(fileName.c_str());

			if (inFile.fail())
			{
				cout << "Could not find a file named " << fileName << endl;
				cout << endl;
				displayMenu();
				cin >> option;
			}
			else
			{
				string line;
				while (!inFile.eof())
				{
					while (getline(inFile,line))
					{
						istringstream input(line);
						string creditCardNo;
						int month, year;
						input >> creditCardNo >> month >> year;
						myObject.insertCard(creditCardNo,month,year);
					}
				}
				cout << endl;
				inFile.close();
				displayMenu();
				cin.clear();
				cin >> option;
			}


		}
		else if (option == "2")
		{
			if (myObject.isEmpty() == true)
			{
				cout << "List is empty! " << endl;
				cout << endl;
				displayMenu();
				cin.clear();
				cin>> option;
			}
			else
			{
				myObject.displayListChronological();
				cout << endl;
				cout << endl;
				displayMenu();
				cin.clear();
				cin >> option;
			}
		}
		else if (option == "3")
		{
			if (myObject.isEmpty() == true)
			{
				cout << "List is empty! " << endl;
				cout << endl;
				displayMenu();
				cin.clear();
				cin>> option;
			}
			else
			{
				myObject.displayListReverseChronological();
				cout << endl;
				displayMenu();
				cin.clear();
				cin >> option;
			}
		}
		else if (option == "4") // credit card search
		{
			cout << "Please enter the credit card number: ";
			cin >> cardNo;
			if (isValidCardNo(cardNo) == false)
			{
				cout << "Invalid format! " << endl;
				cout << endl;
				displayMenu();
				cin.clear();
				cin >> option;
			}
			// card no is valid here:
			else
			{
				myObject.cardSearch(cardNo);
				cout << endl;
				displayMenu();
				cin.clear();
				cin >> option;
			}
			
		}
		else if (option == "5")
		{
			cout << "Please enter month and year: ";
			cin >> month >> year;
			if (monthChecker(month) == false || yearChecker(year) == false)
			{
				cout << "Invalid format! " << endl;
				cout << endl;
				displayMenu();
				cin.clear();
				cin  >> option;
			}
			else
			{
				int m = stoi(month);
				int y = stoi(year);
				myObject.bulkDelete(m,y);
				cout << endl;
				displayMenu();
				cin.clear();
				cin >> option;
			}
		}
	}
	if (option == "6")
	{
		cout << "All nodes have been deleted! " << endl;
		cout << "Terminating!!! " << endl;
		myObject.deleteAll();
	}
	return 0;
}