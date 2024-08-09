#include <iostream>
#include <string>

using namespace std;

class Student {
private:
	string name;
	int numCourses;
	double totalPoints;
public:
	double getGradePoints(string grade) {
		if (grade == "A+" || grade == "A") return 4.0;
		else if (grade == "A-") return 3.67;
		else if (grade == "B+") return 3.33;
		else if (grade == "B") return 3.0;
		else if (grade == "B-") return 2.67;
		else if (grade == "C+") return 2.34;
		else if (grade == "C") return 2.0;
		else if (grade == "C-") return 1.67;
		else if (grade == "D+") return 1.33;
		else if (grade == "D") return 1.0;
		else if (grade == "F") return 0.0;
		else {
			cout << "Invalid grade entered. Please enter a valid grade (A+, A, A-, B+, etc.)" << endl;
			return -1;
		}
	}


	void inputStudentDetails() {
		cout << "Enter student's name: ";
		getline(cin, name);

		cout << "Enter the number of courses taken: ";
		cin >> numCourses;
		cin.ignore();

		totalPoints = 0.0;
		string courseName, grade;

		for (int i = 0; i < numCourses; i++) {
			cout << "Enter name of course " << i + 1 << ": ";
			getline(cin, courseName);

			cout << "Enter grade for " << courseName << ": ";
			cin >> grade;
			cin.ignore();

			double points = getGradePoints(grade);
			while (points == -1) { // Loop until a valid grade is entered
				cout << "Enter grade for " << courseName << ": ";
				cin >> grade;
				cin.ignore();
				points = getGradePoints(grade);
			}

			totalPoints += points;
		}
	}

	double calculateCGPA() {
		if (numCourses == 0) return 0.0;
		return totalPoints / numCourses;
	}

	void displayCGPA() {
		cout << "Student Name: " << name << endl;
		cout << "CGPA: " << calculateCGPA() << endl;
	}
};

int main() {
	Student student;
	student.inputStudentDetails();
	student.displayCGPA();

	return 0;
}