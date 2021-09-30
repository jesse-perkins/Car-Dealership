#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <vector>
#include <cmath>
#include "Car.h"

using namespace std;

/*
Test Case 1
Input
-1
potato
8

Output
Invalid Input
Invalid Input
GOODBYE

Test Case 2
Input
1
2
3
Jaguar
Silver
100000
4
Jaguar
8

Output
Inventory Empty
Balance: 10000
Buy Car, Input Name
Input Color
Input Price
Insufficient Funds
Sell Car, input name
Car not found.
GOODBYE

Test Case 3
Input
5
Jaguar
6
boogabooga
7
boogabooga.txt
8

Output
Paint car, Input name
Error Car not found
Load File, Choose file name
Error, file not found
Save File, Choose file name
file saved
GOODBYE
*/

const double BEGINNING_BALANCE = 10000;

/*
checkIntIn takes the input and validates makes cure that it is a number. If the user tried to input a variable that is not 
a number, it clears cin and returns -1.

@param checkMe: passed integer to be checked for valid input 
@return: Passes back the int that was handed in or -1 if invalid input was fed to cin.
*/
int checkIntIn(int checkMe)
{
	while (cin.fail())
	{
		cin.clear();
		checkMe = -1;
	}
	cin.ignore(1000, '\n');
	return checkMe;
}

/*
showInventory calls the toString function in the Car object and iterates through all members of the passed 
vector. If there are no members in the vector, it tells the user that the inventory is empty.

@param inventory: the Car array containing the dealership's inventory
@return: VOID
*/
void showInventory(vector <Car> inventory)
{
	string output = "";
	for (int count = 0; count < inventory.size(); count++)
	{
		output = inventory[count].toString();
		cout << output << endl;
	}
	if (inventory.size() == 0)
	{
		cout << "Inventory is currently empty." << endl;
	}
	return;
}

/*
buyCar takes user input and checks to see if the car is already in the inventory and if the balance is too low to buy 
the car. If either case is true, an error message is given to the user and the function ends. Otherwise, the cost
of the car is subtracted from the balance and the car is added to the vector.

@param inventory: the Car array containing the dealership's inventory
@param balance: the balance of the car dealership
@return: VOID
*/
void buyCar(vector<Car>& inventory, double& balance)
{
	cout << "Name: ";
	string name;
	cin >> name;
	cout << "Color: ";
	string color;
	cin >> color;
	cout << "Price: $";
	int price;
	cin >> price;
	int carCheckLoc = -1;
	for (int count = 0; count < inventory.size(); count++)
	{
		if (inventory[count].getName() == name)
		{
			carCheckLoc = count;
		}
	}
	if (price > balance)
	{ 
		cout << "\n * * * ERROR * * * "
		<< "\nInsufficient Funds. Vehicle not added to inventory\n";
	}
	else if (carCheckLoc != -1)
	{
		cout << "\n * * * ERROR * * * "
		<< "\n" << name << " already in inventory. Pick a different name.\n";
	}
	else
	{
		inventory.push_back(Car(name, color, price));
		balance -= price;
		cout << "\n" << name << " Added to inventory\n";
	}
	return;
}

/*
sellCar takes user input and checks to see if the car is in the inventory. If it is not, an error message is given to 
the user and the function ends. Otherwise, the price of the car is added to the balance and the car is removed from the vector.

@param inventory: the Car array containing the dealership's inventory
@param balance: the balance of the car dealership
@return: VOID
*/
void sellCar(vector<Car>& inventory, double& balance)
{
	int carLoc = -1;
	cout << "Name of car to be sold: ";
	string carToSell;
	cin >> carToSell;
	for (int count = 0; count < inventory.size(); count++)
	{
		if (inventory[count].getName() == carToSell)
		{
			carLoc = count;
		}
	}
	if (carLoc == -1)
	{
		cout << "\n * * * ERROR * * * "
			<< "\n" << carToSell << " not found in inventory.\n";
	}
	else
	{
		balance += inventory[carLoc].getPrice();
		for (int count = carLoc; count < (inventory.size() - 1); count++)
		{
			inventory[count] = inventory[count + 1];
		}
		inventory.pop_back();

	}
	return;
}

/*
paintCar takes user input and checks to see if the car is in the inventory. If it is not, an error message is given to 
the user and the function ends. Otherwise, the paint function from the Car object is called, which changes the color 
of the car and increases its price.

@param inventory: the Car array containing the dealership's inventory
@return: VOID
*/
void paintCar(vector<Car>& inventory)
{
	int carLoc = -1;
	cout << "Name of car to be repainted: ";
	string carToPaint;
	cin >> carToPaint;
	for (int count = 0; count < inventory.size(); count++)
	{
		if (inventory[count].getName() == carToPaint)
		{
			carLoc = count;
		}
	}
	if (carLoc == -1)
	{
		cout << "\n * * * ERROR * * * "
			<< "\n" << carToPaint << " not found in inventory.\n";
	}
	else
	{
		cout << "Please enter the new color of the car: ";
		string color;
		cin >> color;
		inventory[carLoc].paint(color);
		cout << "\n" << carToPaint << " has been painted " << color << ".\n";
	}
	return;
}

/*
loadFile takes the current balance and the cars in the inventory and loads the balance and cars from a file to them.
It does NOT check for duplicate cars and ADDS the balance to the saved balance.

@param inventory: the Car array containing the dealership's inventory
@param balance: the balance of the car dealership
@return: VOID
*/
void loadFile(vector<Car>& inventory, double& balance)
{
	cout << "Filename to be loaded (including file extension): ";
	string fileName;
	cin >> fileName;
	ifstream inFile;
	inFile.open(fileName);
	double fileBalance;
	inFile >> fileBalance;
	if (inFile.fail())
	{
		inFile.clear();
		inFile.ignore(1000, '\n');
		cout << "\n * * * ERROR * * *"
			<< "\nFile not found. \n";
	}
	else
	{
		balance += fileBalance;
		bool looper = false;
		if (!inFile.fail()) { looper = true; }
		while (looper)
		{
			looper = false;
			string name;
			inFile >> name;
			string color;
			inFile >> color;
			double price;
			inFile >> price;
			if (!inFile.fail())
			{
				inventory.push_back(Car(name, color, price));
				looper = true;
			}
		}
		inFile.clear();
		inFile.ignore(1000, '\n');
	}
	return;
}

/*
saveFile takes the current balance and the cars in the inventory and saves them to a file. It must be saved to a NEW file,
otherwise it will overwrite the file.

@param inventory: the Car array containing the dealership's inventory
@param balance: the balance of the car dealership
@return: VOID
*/
void saveFile(vector<Car>& inventory, double& balance)
{
	cout << "Save file as (including file extension): ";
	string fileName;
	cin >> fileName;
	ofstream outFile;
	outFile.open(fileName);
	outFile << balance << endl;
	for (int count = 0; count < inventory.size(); count ++)
	{
		string name = inventory[count].getName();
		outFile << name << " ";
		string color = inventory[count].getColor();
		outFile << color << " ";;
		double price = inventory[count].getPrice();
		outFile << price << endl;
	}
	cout << "File Saved. \n";
	return;
}

/*
Displays the menu. 
*/
int main()
{	
	vector <Car> dealershipInventory;
	int input = 0;
	double carCost = 0;
	double currentBalance = BEGINNING_BALANCE;
	while (input != 8)
	{
		cout << "\n * * * MAIN MENU * * * \n"
			<< "\n1: Show Current Inventory"
			<< "\n2: Show Current Balance"
			<< "\n3: Buy a Car"
			<< "\n4: Sell a Car"
			<< "\n5: Paint a Car"
			<< "\n6: Load File"
			<< "\n7: Save File"
			<< "\n8: Quit Program"
			<< "\nPlease Select an Option [1-8]: ";
		cin >> input;
		cout << endl;
		input = checkIntIn(input);
		switch (input)
		{
		case 1:
			cout << "Show Current Inventory\n" << endl;
			showInventory(dealershipInventory);
			break;
		case 2:
			cout << "Show Current Balance\n" << endl;
			cout << "Current Balance: $" << fixed << setprecision(2) << currentBalance << endl;
			break;
		case 3:
			cout << "Buy a Car" << endl;
			buyCar(dealershipInventory, currentBalance);
			break;
		case 4:
			cout << "Sell a Car" << endl;
			sellCar(dealershipInventory, currentBalance);
			break;
		case 5:
			cout << "Paint a Car" << endl;
			paintCar(dealershipInventory);
			break;
		case 6:
			cout << "Load File" << endl;
			loadFile(dealershipInventory, currentBalance);
			break;
		case 7:
			cout << "Save File" << endl;
			saveFile(dealershipInventory, currentBalance);
			break;
		case 8:
			cout << "Quit Program" << endl;
			return;
		default:
			cout << "Invalid Input. Please try again." << endl;
			break;
		}
	}
	return 0;
}