#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include "course.h"


using namespace std;


int main() {
	int input; //menu option
	bool dataReady = false;
	vector <Course> courses;//creating new vector
	
	cout << "Welcome to the course planner" << endl; // display welcome message
	cout<< endl;
		
	input = 0;
	while (true) {
		while (input != 4) { //as long as the input is not 4
			cout << "1. Load Data Structure." << endl; // display menu
			cout << "2. Print Course List." << endl;
			cout << "3. Print Course." << endl;
			cout << "4. Exit" << endl;
			cout << endl;
			cout << " What would you like to do? "; // prompt user for input
			cin >> input;// get user input

			switch (input) {
			case 1: {
				ifstream file("academicCatalog.csv"); //opening course catalog
				if (!file.is_open()) { //if read file does not open
					cout << "Could not open file academicCatalog.csv" << endl; // print error message
					dataReady = false;
				}
				else {
					string line;
					while (getline(file, line)) {//parse through csv file 
						istringstream iss(line);
						string courseNum;
						string courseTitle;
						string preReq;

						getline(iss, courseNum, ','); 
						getline(iss, courseTitle, ',');
						getline(iss, preReq, ',');

						courses.push_back(Course(courseNum, courseTitle, preReq));
					}
					dataReady = true;
				}
				break;
			}

			case 2: {
				if (dataReady) {
					vector <Course> cSCourses;// creating new vector of courses

					for (const auto& course : courses) {
						if (course.getCourseNum().substr(0, 2) == "CS" || course.getCourseNum().substr(0, 2) == "MATH") {
							cSCourses.push_back(course);//cSCourses only stores  CS and MATH courses from the original vector
						}
					}
					sort(cSCourses.begin(), cSCourses.end(), [](const Course& A, const Course& B) {
						return A.getCourseNum() < B.getCourseNum();
						}
						
				);
					cout << "Here is a sample schedule:" << endl;//output header before sample schedule
					cout << endl;
					for (const auto& course : cSCourses) {
						cout << course.getCourseNum() << ", " << course.getCourseTitle() << endl; //prints course number and title 
						
					}
					cout << endl;
				}
				else {
					cout << "No data is loaded to access!" << endl; //print error message if data is not loaded
				}
				break;
			}

			case 3: {
				string courseNumber;
				if (dataReady) {
					cout << "what course do you want to know about? ";// prompt user for input
					cin >> courseNumber;//store input
					transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);//change user input string to  all capital letters to abide with the csv file
						
					
					auto in = std::find_if(courses.begin(), courses.end(), [courseNumber](const Course& course) {//searches the vector for matching course title
						return course.getCourseNum() == courseNumber;//return course number if found
					}
					);

					if (in !=courses.end()){ // if the course is not at the lists end
						cout << in->getCourseNum() << ", "<< in->getCourseTitle() << endl;//prints course number and title
						cout << "Prerequisites: " << in->getPreReq() << endl;//prints list of preReqs
					}
					else {
						cout << courseNumber << " not found!" << endl;//print the course was not found
					}
				}
				else {
					cout << "No data is loaded to access!" << endl;//print if data was not loaded into structure
				}
				break;
			}
			case 4: {
				cout << "Thank you for using the course planner!" << endl;//print goodbye message
				return 0;
			default:
				cout << input << " is not a valid option." << endl;//if not a menue option print  error message
				cout << endl;
				break;
			}


			}
		}
	}
	return 0;
}
