/*
	Name: Miguel Juarez
	Date: 11/22/2022
	Class: CIS 160 Fundamentals of Computer Science I
	Project Name: Caswell Catering & Convention Services Billing
	Description: Bill that displays customer order information and the total amount due
*/

//Preprocessor directives needed for program
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cctype>

using namespace std;

//TIPS is amount charged to total amount, CHILD is 60% charged to the price of an adult's meal
const float TIPS = 0.2, CHILD = 0.6;

//Function prototypes to take user input, display menus, perform calculations, and display output
void Input(int&, int&, string&, char&, char&, char&, float&, float&, float&);
void Process(int, int, char, char, float, float, float, float&, float&, float&, float&, float&, float&, float&, float&, float&);
void Output(int, int, string, char, char, float, float, float, float, float, float, float, float, float, float, float, float);
float mealMenu(string&);
float hallMenu(char&);

//Template functions for addition, subtraction, and multiplication operations
//add function contains 3 default parameters to allow the addition of 2 numbers, and up to 5 number if necessary
template<class T> 
float add(T, T, T num3 = 0, T num4 = 0, T num5 = 0);

template<class T>
float subtract(T, T, T);

template<class T1, class T2>
float multiply(T1, T2);

int main()
{
	int numAdult; //number of adults
	int numChild; //number of children
	string mealType; //standard or deluxe meal
	char weekend; //yes or no for weekend services
	char hall; //which hall the customer designates by inputting letter
	char speedy; //yes or no for speedy payment
	float fee; //hall or room fee
	float meal; //price of adult meal
	float deposit; //amount paid when reservation was made
	float costA; //total cost for all adults
	float costC; //total cost for all children
	float food; //total cost of food oredered
	float tips; //tips added to the total amount of food ordered
	float weekendCost; //surcharge added to total cost of food if there is weekend catering
	float tax; //taxed amount for total cost of food
	float bill; //total cost of food with tax, tips, hall or room fee, and weekend surcharge
	float speedyCost; //discount to be applied based on speedy payment and total cost of the bill
	float balance; //total cost after reducing it with the deposit amount

	Input(numAdult, numChild, mealType, weekend, hall, speedy, meal, fee, deposit);
	Process(numAdult, numChild, weekend, speedy, meal, fee, deposit, costA, costC, food, tips, weekendCost, tax, bill, speedyCost, balance);
	Output(numAdult, numChild, mealType, weekend, hall, meal, costA, costC, food, tips, weekendCost, tax, fee, bill, deposit, speedyCost, balance);
}

//Prompts user to input customer information to be stored for calculations and output
//Parameters are defined variables that will be passed by reference to store user input
void Input(int& numAdult, int& numChild, string& mealType, char& weekend, char& hall, char& speedy, float& meal, float& fee, float& deposit)
{
	cout << "\nNumber of Adults: ";
	cin >> numAdult;
	cout << "\nNumber of Children: ";
	cin >> numChild;
	cout << endl;
	fee = hallMenu(hall);
	cout << "\nWeekend Catering? (Y/N): ";
	cin >> weekend;
	weekend = toupper(weekend);
	cout << endl;
	meal = mealMenu(mealType);
	cout << "\nSpeedy Payment? (Y/N): ";
	cin >> speedy;
	speedy = toupper(speedy);
	cout << "\nDeposit: ";
	cin >> deposit;
}

/* Calculations to find the cost of all the food ordered, including tax, tips, fees, and reservation deposit
Some parameters will be stored user input that will be passed by value
Some parameters will be passed by reference to store calculations done and results to be used later
Functions used to perform simple arthmetic operations
Certain calculations will only be performed based on user input and if they meet specific conditions*/
void Process(int numAdult, int numChild, char weekend, char speedy, float meal, float fee, float deposit, float& costA, float& costC, float& food, float& tips, float& weekendCost, float& tax, float& bill, float& speedyCost, float& balance)
{
	//TAX is amount charged to total amount 
	//DISCOUNT(1-5) are all discount rates to reduce the cost of the bill, dependent on total of bill
	const float TAX = 0.07, DISCOUNT1 = 0.01, DISCOUNT2 = 0.02, DISCOUNT3 = 0.04, DISCOUNT4 = 0.05, DISCOUNT5 = 0.07;

	costA = multiply(numAdult, meal);
	costC = numChild * (meal * CHILD);
	food = add(costA, costC);
	tips = multiply(food, TIPS);
	if (weekend == 'Y')
		weekendCost = multiply(food, 0.1);
	else if (weekend == 'N')
		weekendCost = 0;
	tax = multiply(food, TAX);
	bill = add(food, tax, tips, fee, weekendCost);
	if (speedy == 'Y')
	{
		if (bill < 500)
			speedyCost = multiply(bill, DISCOUNT1);
		else if (bill >= 500 && bill < 1000)
			speedyCost = multiply(bill, DISCOUNT2);
		else if (bill >= 1000 && bill < 5000)
			speedyCost = multiply(bill, DISCOUNT3);
		else if (bill >= 5000 && bill < 10000)
			speedyCost = multiply(bill, DISCOUNT4);
		else if (bill >= 10000)
			speedyCost = multiply(bill, DISCOUNT5);
	}
	else if (speedy == 'N')
		speedyCost = 0;
	balance = subtract(bill, deposit, speedyCost);
}

//Displays the output of the customer's information and bill in a separate text file
//Parameters are all user input and results from calculations that will be passed by value for displaying output
void Output(int numAdult, int numChild, string mealType, char weekend, char hall, float meal, float costA, float costC, float food, float tips, float weekendCost, float tax, float fee, float bill, float deposit, float speedyCost, float balance)
{
	//Used to print output out into a separate text file
	ofstream fout("Output.txt");

	string line;
	line.assign(55, '_');
	fout << "/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/" << endl;
	fout << "\t\tCaswell Catering & Concention Services" << endl;
	fout << "\t\t\t\tFinal Bill" << endl;
	fout << "/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/" << endl;
	fout << "\n     Number of Adults : \t\t\t" << numAdult << endl;
	fout << "     Number of Children:\t\t\t" << numChild << endl;
	fout << "     Gratuity:\t\t\t\t\t" << multiply(TIPS, 100) << "%" << endl;
	fout << "     Weekend:\t\t\t\t\t";
	if (weekend == 'Y')
		fout << "Yes" << endl;
	else if (weekend == 'N')
		fout << "No" << endl;
	fout << fixed << showpoint << setprecision(2); //displays all prices with only 2 digits after the decimal
	fout << "     Cost per " << mealType << " Meal for Adult: \t\t$" << meal << endl;
	fout << "     Cost per " << mealType << " Meal for Child: \t\t$" << multiply(meal, CHILD) << endl;
	fout << "     " << line << endl;
	fout << "     Total Cost for Adult Meals:\t\t$" << costA << endl;
	fout << "     Total Cost for Child Meals:\t\t$" << costC << endl;
	fout << "\n     Total food cost:\t\t\t\t$" << food << endl;
	fout << "     " << line << endl;
	fout << "     Gratuity:\t\t\t\t\t$" << tips << endl;
	fout << "     Hall " << hall << " - Room fee:\t\t\t\t$" << fee << endl;
	fout << "     Weekend Charge:\t\t\t\t$" << weekendCost << endl;
	fout << "     Taxes:\t\t\t\t\t$" << tax << endl;
	fout << "     " << line << endl;
	fout << "     Subtotal:\t\t\t\t\t$" << bill << endl;
	fout << "\n     Less Deposit:\t\t\t\t$" << deposit << endl;
	fout << "     Less Speedy Payment:\t\t\t$" << speedyCost << endl;
	fout << "\n     Balance Due:\t\t\t\t$" << balance << endl;
	fout << "/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/" << endl;
	fout.close();
}

/*Menu to allow user to choose between standard or deluxe meals
Price of meal is returned depending on which option is chosen 
string variable will either hold standard or deluxed when passed by reference
Any other input besides what is allowed by the menu will terminate the program with a message*/
float mealMenu(string& mealType)
{
	const float STANDARD = 25.75, DELUXE = 29.95;

	char choice;
	cout << "Select choice of meal from menu below:" << endl;
	cout << "\n\tS - Standard Meal" << endl;
	cout << "\tD - Deluxe Meal" << endl;
	cout << "\nMeal: ";
	cin >> choice;
	choice = toupper(choice);
	if (choice == 'S')
	{
		mealType = "Standard";
		return STANDARD;
	}
	else if (choice == 'D')
	{
		mealType = "Deluxe";
		return DELUXE;
	}
	else
	{
		cout << "\nInvalid Input" << endl;
		exit(0);
	}
}

/*Menu to allow user to choose which hall to have the catering service at
The fee for the hall is returned depending on which option is chosen
char variable will hold the letter of the hall (or H if at home) when passed by reference
Any other input besides what is allowed by the menu will terminate the program with a message*/
float hallMenu(char& hall)
{
	const float A = 100.00, B = 85.00, C = 75.00, D = 65.00, H = 0.00;

	char choice;
	cout << "Select choice of hall from menu below:" << endl;
	cout << "\n\tA - Hall A" << endl;
	cout << "\tB - Hall B" << endl;
	cout << "\tC - Hall C" << endl;
	cout << "\tD - Hall D" << endl;
	cout << "\tH - Home" << endl;
	cout << "\nHall: ";
	cin >> choice;
	hall = toupper(choice);
	switch (hall)
	{
		case 'A':
			return A;
			break;
		case 'B':
			return B;
			break;
		case 'C':
			return C;
			break;
		case 'D':
			return D;
			break;
		case 'H':
			return H;
			break;
		default:
			cout << "Invalid Input" << endl;
			exit(0);
	}
}

//Template function to perform addition with up to five different values and return a float result
//Last three parameters contains default values to allow the addition of two numbers
template<class T>
float add(T num1, T num2, T num3, T num4, T num5)
{
	return num1 + num2 + num3 + num4 + num5;
}

//Template function to perform subtraction and return a float result
//First parameter will be subtracted by the second and third parameters
template<class T>
float subtract(T num1, T num2, T num3)
{
	return num1 - num2 - num3;
}


//Template function to perform multiplication of up to two different types of variables and return a float result
//Planned to allow multiplication between int and float variables, planned
template<class T1, class T2>
float multiply(T1 num1, T2 num2)
{
		return num1 * num2;
}