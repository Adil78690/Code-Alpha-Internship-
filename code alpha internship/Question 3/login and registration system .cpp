#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class User {
private:
	string username;
	string password;

public:
	void registerUser() {
		cout << "Enter username: ";
		cin >> username;
		cout << "Enter password: ";
		cin >> password;

		ofstream outfile("data.txt", ios::app);
		if (outfile.is_open()) {
			outfile << username << " " << password << endl;
			outfile.close();
			cout << "Registration successful!" << endl;
		}
		else {
			cout << "Error in opening file for writing!" << endl;
		}
	}

	bool checkRegistration() {
		ifstream infile("data.txt");
		string user, pass;
		bool registered = false;

		if (infile.is_open()) {
			while (infile >> user >> pass) {
				if (user == username && pass == password) {
					registered = true;
					break;
				}
			}
			infile.close();
		}
		else {
			cout << "Error in opening file for reading!" << endl;
		}
		return registered;
	}
};

int main() {
	User newUser;
	newUser.registerUser();

	if (newUser.checkRegistration()) {
		cout << "User registration verified successfully!" << endl;
	}
	else {
		cout << "User registration verification failed!" << endl;
	}

	return 0;
}
