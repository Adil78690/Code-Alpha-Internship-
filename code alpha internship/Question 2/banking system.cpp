
#include <iostream>
#include <string>

using namespace std;

// Transaction Class
class Transaction {
private:
	string type;
	double amount;
	string date;

public:
	Transaction() : type(""), amount(0.0), date("") {}
	Transaction(string t, double a, string d) : type(t), amount(a), date(d) {}

	void displayTransaction() const {
		cout << "Type: " << type << ", Amount: $" << amount << ", Date: " << date << endl;
	}
};

// Account Class
class Account {
private:
	string accountNumber;
	double balance;
	Transaction transactions[100]; // Composition: Account "has" Transactions
	int transactionCount;

public:
	Account() : accountNumber(""), balance(0.0), transactionCount(0) {}
	Account(string accNum) : accountNumber(accNum), balance(0.0), transactionCount(0) {}

	void deposit(double amount, string date) {
		balance += amount;
		if (transactionCount < 100) {
			transactions[transactionCount++] = Transaction("Deposit", amount, date);
		}
		else {
			cout << "Transaction limit reached!" << endl;
		}
	}

	void withdraw(double amount, string date) {
		if (amount <= balance) {
			balance -= amount;
			if (transactionCount < 100) {
				transactions[transactionCount++] = Transaction("Withdrawal", amount, date);
			}
			else {
				cout << "Transaction limit reached!" << endl;
			}
		}
		else {
			cout << "Insufficient balance!" << endl;
		}
	}

	void transfer(Account &toAccount, double amount, string date) {
		if (amount <= balance) {
			withdraw(amount, date);
			toAccount.deposit(amount, date);
			cout << "Transfer successful!" << endl;
		}
		else {
			cout << "Insufficient balance!" << endl;
		}
	}

	void displayBalance() const {
		cout << "Account Number: " << accountNumber << ", Balance: $" << balance << endl;
	}

	void displayTransactions() const {
		for (int i = 0; i < transactionCount; i++) {
			transactions[i].displayTransaction();
		}
	}
};

// Customer Class (Base Class)
class Customer {
protected:
	string name;
	Account account; // Composition: Customer "has" an Account

public:
	Customer(string n, string accNum) : name(n), account(Account(accNum)) {}

	virtual void displayDetails() const {
		cout << "Customer Name: " << name << endl;
		account.displayBalance();
	}

	Account& getAccount() {
		return account;
	}
};

// BankingService Class (Derived Class)
class BankingService : public Customer {
public:
	BankingService(string n, string accNum) : Customer(n, accNum) {}

	void performDeposit(double amount, string date) {
		account.deposit(amount, date);
	}

	void performWithdrawal(double amount, string date) {
		account.withdraw(amount, date);
	}

	void performTransfer(Customer &toCustomer, double amount, string date) {
		account.transfer(toCustomer.getAccount(), amount, date);
	}

	void viewAccountDetails() const {
		displayDetails();
		account.displayTransactions();
	}
};

// Main Function with Menu
int main() {
	BankingService customer1("Hamza", "123456789");
	BankingService customer2("yusuf", "987654321");

	int choice;
	while (true) {
		cout << "\nBanking Menu:\n";
		cout << "1. Deposit\n";
		cout << "2. Withdraw\n";
		cout << "3. Transfer\n";
		cout << "4. View Account Details\n";
		cout << "5. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;

		double amount;
		string date;

		switch (choice) {
		case 1:
			cout << "Enter amount to deposit: ";
			cin >> amount;
			cout << "Enter date (YYYY-MM-DD): ";
			cin >> date;
			customer1.performDeposit(amount, date);
			break;

		case 2:
			cout << "Enter amount to withdraw: ";
			cin >> amount;
			cout << "Enter date (YYYY-MM-DD): ";
			cin >> date;
			customer1.performWithdrawal(amount, date);
			break;

		case 3:
			cout << "Enter amount to transfer: ";
			cin >> amount;
			cout << "Enter date (YYYY-MM-DD): ";
			cin >> date;
			customer1.performTransfer(customer2, amount, date);
			break;

		case 4:
			customer1.viewAccountDetails();
			break;

		case 5:
			cout << "Exiting the program." << endl;
			return 0;

		default:
			cout << "Invalid choice! Please try again." << endl;
			break;
		}
	}
}
