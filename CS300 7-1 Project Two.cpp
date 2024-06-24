// CS300 7-1 Project Two
// Ahmed Sharairi
// Implements a hash table to store and interact with data

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

// Creates class to hold course information.
class Course {
public:
	string courseNumber;
	string name;
	vector<string> prerequisites;
};

// Reads from file
void fileRead(const string& fileName, unordered_map<string, Course>& courses) {
	ifstream file(fileName);

	// Checks if valid
	if (!file) {
		cerr << "File not found: " << fileName << endl;
		return;
	}

	// Reads each line and appends information into vector
	string line;
	while (getline(file, line)) {
		vector<string> items;
		string item;
		stringstream ss(line);

		// Appends each item to the vector
		while (getline(ss, item, ',')) {
			items.push_back(item);
		}

		// Error handling if format is wrong
		if (items.size() < 2) {
			cerr << "Invalid formatting!" << line << endl;
		}

		// Initializes course class, makes the first item the course number
		Course course;
		course.courseNumber = items[0];

		// Second item becomes name
		course.name = items[1];

		// Inserts n amount of prerequisites
		for (int i = 2; i < items.size(); i++) {
			course.prerequisites.push_back(items[i]);
		}
	
		// Creates key in map
		courses[course.courseNumber] = course;

	}
	file.close();
}

// Function to find the course
void findCourse(const unordered_map<string, Course>& courses, const string& courseNumber) {
	// Looks for course number in map
	auto courseNum = courses.find(courseNumber);

	// If found, print information, if not, error
	if (courseNum != courses.end()) {
		const Course& course = courseNum->second;
		cout << "Course Number: " << course.courseNumber << endl;
		cout << "Course Name: " << course.name << endl;
		cout << "Prerequisites: " << endl;
		for (const string& prereq : course.prerequisites) {
			cout << prereq << endl;
		}
	}
	else {
		cout << "Course not found!" << endl;
	}
}

// Function to sort and print the courses
void sortPrintList(const unordered_map<string, Course>& courses) {
	vector<string> list;

	// Interate through each element in map, then appends to vector
	for (const auto& pair : courses) {
		list.push_back(pair.first);
	}
	
	// Sorts vector
	sort(list.begin(), list.end());

	// Output data
	cout << "Sorted course list:" << endl;
	for (const string& courseNumber : list) {
		cout << courseNumber << endl;
	}
}

// Main function creates a console menu and puts everything together
int main() {
	unordered_map<string, Course> courses;
	string filename;
	int option;

	cout << "Menu:" << endl;
	cout << "1. Load data" << endl;
	cout << "2. Sort and print courses" << endl;
	cout << "3. Find a course" << endl;
	cout << "9. Exit" << endl;

	do {
		cout << "Enter option: ";
		cin >> option;

		// Clears input buffer in order to avoid error
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (option) {
		case 1:
			cout << "Enter file name: ";
			getline(cin, filename);
			fileRead(filename, courses);
			break;
		case 2:
			sortPrintList(courses);
			break;
		case 3:
		{
			string courseNumber;
			cout << "Enter course number: ";
			cin >> courseNumber;
			findCourse(courses, courseNumber);
		}
		break;
		case 9:
			cout << "Exiting program." << endl;
			break;
		default:
			cout << "Invalid option. Please try again." << endl;
		}
	} while (option != 9);

	return 0;
}