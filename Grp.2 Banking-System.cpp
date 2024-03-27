#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <limits>

using namespace std;

class Account {
private:
    string first_name;
    string last_name;
    string middle_name;
    string address;
    string birthday;
    char gender;
    string account_type;
    double balance;
    int account_number;
    int pin;
    bool account_exists;

public:
    Account() {
        account_exists = false;
    }

    Account(string first, string last, string middle, string addr, string dob, char gen, string type, double initial_deposit, int pin) {
        first_name = first;
        last_name = last;
        middle_name = middle;
        address = addr;
        birthday = dob;
        gender = gen;
        account_type = type;
        balance = initial_deposit;
        account_number = generate_account_number();
        this->pin = pin;
        account_exists = true;
    }

    int generate_account_number() {
        srand(time(0));
        return rand() % 900000 + 100000; // Generate a random 6-digit number
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit successful. New balance: $" << balance << endl;
        } else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful. New balance: $" << balance << endl;
        } else {
            cout << "Invalid withdrawal amount." << endl;
        }
    }

    void display_account_info() {
        cout << "Account Information:" << endl;
        cout << "Account Number: " << account_number << endl;
        cout << "Name: " << first_name << " " << middle_name << " " << last_name << endl;
        cout << "Address: " << address << endl;
        cout << "Birthday: " << birthday << endl;
        cout << "Gender: " << gender << endl;
        cout << "Account Type: " << account_type << endl;
        cout << "Balance: $" << balance << endl;
    }

    double get_balance() {
        return balance;
    }

    int get_account_number() {
        return account_number;
    }

    bool validate_pin(int input_pin) {
        return pin == input_pin;
    }

    void set_pin(int new_pin) {
        pin = new_pin;
    }

    bool exists() {
        return account_exists;
    }
};

bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int get_days_in_month(int month, int year) {
    switch (month) {
        case 2:
            return is_leap_year(year) ? 29 : 28;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        default:
            return 31;
    }
}

int main() {
    string first_name, last_name, middle_name, address, birthday, account_type;
    char gender;
    double initial_deposit;
    int pin;

    Account new_account;

    cout << "Welcome to Our Bank!" << endl;

    int choice;
    double amount;
    int input_pin;
    while (true) {
        // Display menu
        cout << "\nMenu:" << endl;
        cout << "1. Open a New Account" << endl;
        cout << "2. Balance Inquiry" << endl;
        cout << "3. Deposit" << endl;
        cout << "4. Withdraw" << endl;
        cout << "5. View Account Information" << endl;
        cout << "6. Close Account" << endl;
        cout << "7. Exit Program" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
    if (cin.fail()) {
            cout << "Invalid input. Please enter an integer." << endl;
            cin.clear(); // Clear the failbit
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the input buffer
        } else {
            switch (choice) {
            case 1: {
                // Open a new account
                if (new_account.exists()) {
                    cout << "An account already exists. You cannot open a new one." << endl;
                } else {
                    // Prompt user for account details
                    cout << "Enter first name: ";
                    cin >> first_name;
                    cout << "Enter middle name: ";
                    cin >> middle_name;
                    cout << "Enter last name: ";
                    cin >> last_name;
                    cout << "Enter address: ";
                    cin.ignore();
                    getline(cin, address);
                    // Validate and set birthday (mm/dd/yyyy)
                    bool valid_birthday = false;
                    while (!valid_birthday) {
                        cout << "Enter birthday (mm/dd/yyyy): ";
                        cin >> birthday;
                        // Extract month, day, and year from input string
                        string mm_str = birthday.substr(0, 2);
                        string dd_str = birthday.substr(3, 2);
                        string yyyy_str = birthday.substr(6, 4);
                        int mm = stoi(mm_str);
                        int dd = stoi(dd_str);
                        int yyyy = stoi(yyyy_str);
                        // Validate month, day, and year
                        if (mm >= 1 && mm <= 12 && dd >= 1 && dd <= 31 && yyyy >= 1900 && yyyy <= 2100) {
                            // Check for valid number of days in month
                            int days_in_month = get_days_in_month(mm, yyyy);
                            if (dd <= days_in_month) {
                                // Check if user is at least 18 years old
                                time_t now = time(0);
                                tm* today = localtime(&now);
                                int current_year = today->tm_year + 1900;
                                int current_month = today->tm_mon + 1;
                                int current_day = today->tm_mday;
                                if (current_year - yyyy > 18 || (current_year - yyyy == 18 && current_month > mm) || (current_year - yyyy == 18 && current_month == mm && current_day >= dd)) {
                                    valid_birthday = true;
                                } else {
                                    cout << "You must be at least 18 years old to open an account." << endl;
                                }
                            } else {
                                cout << "Invalid day for the given month." << endl;
                            }
                        } else {
                            cout << "Invalid birthday. Please enter a valid date (mm/dd/yyyy)." << endl;
                        }
                    }
                    cout << "Enter gender (M/F): ";
                    cin >> gender;
                    // Validate gender
                    while (gender != 'M' && gender != 'F') {
                        cout << "Invalid gender. Please enter 'M' or 'F'." << endl;
                        cout << "Enter gender (M/F): ";
                        cin >> gender;
                    }
                    cout << "Enter account type (Savings/Current): ";
                    cin >> account_type;

                    // Validate account type
                    while (account_type != "Savings" && account_type != "Current") {
                        cout << "Invalid account type. Please enter 'Savings' or 'Current'." << endl;
                        cout << "Enter account type (Savings/Current): ";
                        cin >> account_type;
                    }
                    cout << "Enter initial deposit amount: $";
                    cin >> initial_deposit;
                    cout << "Enter PIN number (4 digits): ";
                    cin >> pin;

                    // Create the account
                    new_account = Account(first_name, last_name, middle_name, address, birthday, gender, account_type, initial_deposit, pin);
                    cout << "Account created successfully." << endl;
                    cout << "Your account number is: " << new_account.get_account_number() << endl;
                }
                break;
            }
            case 2: {
                // Balance Inquiry
                if (!new_account.exists()) {
                    cout << "No account exists. Please open an account first." << endl;
                } else {
                    cout << "Current balance: $" << new_account.get_balance() << endl;
                }
                break;
            }
            case 3: {
                // Deposit
                if (!new_account.exists()) {
                    cout << "No account exists. Please open an account first." << endl;
                } else {
                    cout << "Enter deposit amount: $";
                    cin >> amount;
                    new_account.deposit(amount);
                }
                break;
            }
            case 4: {
                // Withdraw
                if (!new_account.exists()) {
                    cout << "No account exists. Please open an account first." << endl;
                } else {
                    cout << "Enter withdrawal amount: $";
                    cin >> amount;
                    new_account.withdraw(amount);
                }
                break;
            }
            case 5: {
                // View Account Information
                if (!new_account.exists()) {
                    cout << "No account exists. Please open an account first." << endl;
                } else {
                    new_account.display_account_info();
                }
                break;
            }
            case 6: {
                // Close Account
                if (!new_account.exists()) {
                    cout << "No account exists. Please open an account first." << endl;
                } else {
                    cout << "Account closed successfully." << endl;
                    new_account = Account(); // Reset account
                }
                break;
            }
            case 7: {
                // Exit Program
                cout << "Exiting program. Thank you!" << endl;
                return 0;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
            } 
       } 
    

    return 0;
}
        
    }


