// COMSC-210 | Lab 28 | Vevaan Verma
using namespace std;
#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <numeric>
#include "Goat.h"

/* FUNCTION PROTOTYPES */
int main_menu();
int select_goat(list<Goat> trip);
void delete_goat(list<Goat>& trip);
void add_goat(list<Goat>& trip, string[], string[]);
void find_youngest(list<Goat> trip);
void find_oldest(list<Goat> trip);
double find_avg_age(list<Goat> trip);
void duplicate_goat(list<Goat>& trip);
void apply_age_limit(list<Goat>& trip);
void apply_age_limit(list<Goat>& trp);
void display_trip(list<Goat> trip);
int getValidatedAge();

/* CONSTANTS */
const int SZ_NAMES = 200, SZ_COLORS = 25;

// main() is the entry point of the program and drives the program
// arguments: none
// returns: int - the exit code of the program
int main() {

	srand(time(0));

	// read & populate arrays for names and colors
	ifstream fin("names.txt");
	string names[SZ_NAMES];
	int i = 0;

	while (fin >> names[i++]);

	fin.close();

	ifstream fin1("colors.txt");
	string colors[SZ_COLORS];

	i = 0;

	while (fin1 >> colors[i++]);

	fin1.close();

	// create & populate a trip of Goats using std::list of random size 8-15
	int tripSize = rand() % 8 + 8;
	list<Goat> trip;
	int age;
	string name, color;

	for (int i = 0; i < tripSize; i++) {

		age = rand() % MAX_AGE;  // defined in Goat.h
		name = names[rand() % SZ_NAMES];
		color = colors[rand() % SZ_COLORS];
		Goat tmp(name, age, color);
		trip.push_back(tmp);

	}

	// Goat Manager 3001 Engine
	int sel = main_menu();

	while (sel != 12) {

		switch (sel) {

		case 1:
			cout << endl << "Adding a goat.\n";
			add_goat(trip, names, colors);
			break;

		case 2:
			cout << endl << "Removing a goat.\n";
			delete_goat(trip);
			break;

		case 3:
			cout << endl << "Displaying goat data.\n";
			display_trip(trip);
			break;

		case 4:
			cout << endl << "Finding the youngest goat.\n";
			find_youngest(trip);
			break;

		case 5:
			cout << endl << "Finding the oldest goat.\n";
			find_oldest(trip);
			break;

		case 6:
			cout << endl << "Finding the average age of the goats.\n";
			cout << "Average age: " << find_avg_age(trip) << endl;
			break;

		case 7:
			cout << endl << "Duplicating a goat.\n";
			duplicate_goat(trip);
			break;

		case 8:
			cout << endl << "Sorting goats by name.\n";
			trip.sort([](Goat a, Goat b) { return a.get_name() < b.get_name(); }); // sort by name (ascending)
			break;

		case 9:
			cout << endl << "Sorting goats by age.\n";
			trip.sort([](Goat a, Goat b) { return a.get_age() < b.get_age(); }); // sort by age (ascending)
			break;

		case 10:
			cout << endl << "Reversing the trip.\n";
			trip.reverse();
			break;

		case 11:
			cout << endl << "Applying age limit.\n";
			apply_age_limit(trip);
			break;

		default:
			cout << endl << "Invalid selection.\n";
			break;

		}

		cout << endl; // output blank line for formatting purposes
		sel = main_menu();

	}

	return 0;

}

// main_menu() displays the main menu and gets the user's choice
// arguments: none
// returns: int - the user's choice
int main_menu() {

	cout << "*** GOAT MANAGER 3001 ***\n";
	cout << "[1] Add a goat\n";
	cout << "[2] Delete a goat\n";
	cout << "[3] List goats\n";
	cout << "[4] List youngest goat\n";
	cout << "[5] List oldest goat\n";
	cout << "[6] List average age\n";
	cout << "[7] Duplicate goat\n";
	cout << "[8] Sort goats by name\n";
	cout << "[9] Sort goats by age\n";
	cout << "[10] Reverse trip\n";
	cout << "[11] Apply age limit\n";
	cout << "[12] Quit\n";
	cout << "Choice --> ";

	int choice;
	cin >> choice;

	while (choice < 1 || choice > 12) {

		cout << "Invalid, again --> ";
		cin >> choice;

	}

	return choice;

}

// select_goat() displays the goats in the trip and gets the user's choice
// arguments: list<Goat> trip - the list of goats
// returns: int - the user's choice
int select_goat(list<Goat> trp) {

	int input;
	cout << "Make a selection:\n";
	display_trip(trp);
	cout << "Choice --> ";
	cin >> input;

	while (input < 1 || input > trp.size()) {

		cout << "Invalid choice, again --> ";
		cin >> input;

	}

	return input;

}

// add_goat() adds a goat to the trip
// arguments: list<Goat> trip - the list of goats, string names[] - the array of names, string colors[] - the array of colors
// returns: none
void add_goat(list<Goat>& trip, string nms[], string cls[]) {

	cout << "ADD A GOAT\n";

	int age = rand() % MAX_AGE;
	string nm = nms[rand() % SZ_NAMES];
	string cl = cls[rand() % SZ_COLORS];

	Goat tmp(nm, age, cl);
	trip.push_back(tmp);

	cout << "Goat added. New trip size: " << trip.size() << endl;

}

// delete_goat() deletes a goat from the trip
// arguments: list<Goat> trip - the list of goats
// returns: none
void delete_goat(list<Goat>& trip) {

	cout << "DELETE A GOAT\n";

	int index = select_goat(trip);
	auto it = trip.begin();

	advance(it, index - 1);
	trip.erase(it);

	cout << "Goat deleted. New trip size: " << trip.size() << endl;

}

// find_youngest() finds the youngest goat in the trip
// arguments: list<Goat> trip - the list of goats
// returns: none
void find_youngest(list<Goat> trp) {

	Goat youngest = *min_element(trp.begin(), trp.end(), [](Goat a, Goat b) { return a.get_age() < b.get_age(); }); // lambda function to compare ages and find youngest
	cout << "Youngest Goat: " << youngest.get_name() << " (" << youngest.get_age() << ", " << youngest.get_color() << ")\n";

}

// find_oldest() finds the oldest goat in the trip
// arguments: list<Goat> trip - the list of goats
// returns: none
void find_oldest(list<Goat> trp) {

	Goat oldest = *max_element(trp.begin(), trp.end(), [](Goat a, Goat b) { return a.get_age() < b.get_age(); }); // lambda function to compare ages and find oldest
	cout << "Oldest Goat: " << oldest.get_name() << " (" << oldest.get_age() << ", " << oldest.get_color() << ")\n";

}

// find_avg_age() finds the average age of the goats in the trip
// arguments: list<Goat> trip - the list of goats
// returns: double - the average age
double find_avg_age(list<Goat> trp) {

	double sum = std::accumulate(trp.begin(), trp.end(), 0, [](double a, Goat b) { return a + b.get_age(); }); // sum of ages
	return sum / trp.size();

}

// duplicate_goat() duplicates a goat in the trip
// arguments: list<Goat> trip - the list of goats
// returns: none
void duplicate_goat(list<Goat>& trp) {

	int copyIndex = select_goat(trp);
	copy(next(trp.begin(), copyIndex - 1), next(trp.begin(), copyIndex), back_inserter(trp)); // copy selected goat to end of list
	cout << "Goat duplicated. New trip size: " << trp.size() << endl;

}

// apply_age_limit() removes goats older than 10 years from the trip
// arguments: list<Goat> trip - the list of goats
// returns: none
void apply_age_limit(list<Goat>& trp) {

	cout << "Enter the age limit: ";
	int ageLimit = getValidatedAge();

	trp.remove_if([ageLimit](const Goat& goat) { return goat.get_age() > ageLimit; }); // remove goats older than input age
	cout << "Goats older than " << ageLimit << " removed. New trip size: " << trp.size() << endl;

}

// display_trip() outputs all the goats in the trip
// arguments: list<Goat> trip - the list of goats
// returns: none
void display_trip(list<Goat> trp) {

	int i = 1;

	for (auto gt : trp)
		cout << "\t" << "[" << i++ << "] " << gt.get_name() << " (" << gt.get_age() << ", " << gt.get_color() << ")" << endl;

}

// getValidatedAge() gets a valid age from the user
// arguments: none
// returns: int - the valid age
int getValidatedAge() {

	int inputAge; // variable to store the input (of type int)

	while (!(cin >> inputAge) || inputAge < 0) { // while the input is not an integer or is less than 0

		cin.clear(); // clear the input stream
		cin.ignore(INT_MAX, '\n'); // ignore the invalid input
		cout << "Invalid input. Please enter a valid age: "; // prompt the user to enter a valid age

	}

	return inputAge;

}