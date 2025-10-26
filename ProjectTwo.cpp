// Alejandro Martinez
// 10/18/2025
// CS-300 Project Two

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// Define a structure to hold course information
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Function to load course data from a file
vector<Course> LoadCourseData(const string& fileName) {
    vector<Course> courses;
    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Error: Could not open file '" << fileName << "'." << endl;
        return courses;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string number, title, prereq;
        getline(ss, number, ',');
        getline(ss, title, ',');

        Course course;
        course.courseNumber = number;
        course.courseTitle = title;

        while (getline(ss, prereq, ',')) {
            course.prerequisites.push_back(prereq);
        }

        courses.push_back(course);
    }

    file.close();
    return courses;
}

// Function to print the sorted course list
void PrintCourseList(const vector<Course>& courses) {
    // Copy and sort the course list by courseNumber
    vector<Course> sortedCourses = courses;
    sort(sortedCourses.begin(), sortedCourses.end(), [](const Course& a, const Course& b) {
        return a.courseNumber < b.courseNumber;
        });

    for (const Course& course : sortedCourses) {
        cout << course.courseNumber << ", " << course.courseTitle << endl;
    }
}

// Function to display information for a specific course
void PrintCourseInfo(const vector<Course>& courses, const string& courseNumber) {
    for (const Course& course : courses) {
        if (course.courseNumber == courseNumber) {
            cout << course.courseNumber << ", " << course.courseTitle << endl;

            if (!course.prerequisites.empty()) {
                cout << "Prerequisites: ";
                for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                    cout << course.prerequisites[i];
                    if (i < course.prerequisites.size() - 1) {
                        cout << ", ";
                    }
                }
                cout << endl;
            }
            else {
                cout << "Prerequisites: None" << endl;
            }
            return;
        }
    }

    cout << "Course not found: " << courseNumber << endl;
}

int main() {
    vector<Course> courses;
    int choice = 0;

    cout << "Advising Assistance Program Initialized." << endl;

    while (choice != 9) {
        cout << "\n===== Main Menu =====" << endl;
        cout << "1. Load Data Structure" << endl;
        cout << "2. Print Course List (Sorted)" << endl;
        cout << "3. Print Course Information" << endl;
        cout << "9. Exit" << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string fileName;
            cout << "Enter file name to load courses (e.g., course.txt): ";
            cin >> fileName;
            courses = LoadCourseData(fileName);
            if (!courses.empty()) {
                cout << "Courses successfully loaded!" << endl;
            }
        }
        else if (choice == 2) {
            if (courses.empty()) {
                cout << "No course data loaded. Please load data first." << endl;
            }
            else {
                PrintCourseList(courses);
            }
        }
        else if (choice == 3) {
            if (courses.empty()) {
                cout << "No course data loaded. Please load data first." << endl;
            }
            else {
                string inputCourse;
                cout << "Enter course number (e.g., CSCI101): ";
                cin >> inputCourse;
                PrintCourseInfo(courses, inputCourse);
            }
        }
        else if (choice == 9) {
            cout << "Thank you for using the course planner!" << endl;
        }
        else {
            cout << "Invalid option. Please try again.\n" << endl;
        }
    }

    return 0;
}