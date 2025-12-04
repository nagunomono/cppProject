#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

// checks if string contains only numbers from 0 to 9
bool isDigits(const string &s) {
    if (s.empty()) return false; // if empty, false
    for (char c : s) { // range-based loop. every char in string
        if (!isdigit((unsigned char)c)) return false; // checks if char is digit
    }
    return true; // if loop is w/o false, function is true
}

// validates if a string is a valid number (integer or decimal)
// used for deposit and withdrawal amount input
bool isValidAmount(const string &s) {
    if (s.empty()) return false; // if string has no characters, not valid number
    bool dotSeen = false; // tracks if decimal point already appeared
    int digitCount = 0; // counts digit. ensures if it has atleast one digit

    for (char c : s) {
        if (c == '.') {
            // only allow ONE decimal point
            if (dotSeen) return false;	// more than one dot, invalid
            dotSeen = true;
        }
        else if (!isdigit((unsigned char)c)) {
            return false; // character not digit, invalid
        }
        else {
            digitCount++; // count digits
        }
    }
    return digitCount > 0; // returns true if there is atleast one digit
}

// converts string to double using stringstream
double strToDouble(const string &s) {
    stringstream ss(s); // read numeric value from string
    double v;
    ss >> v; // ex., from s="123" to v=123
    return v;
}

// input must not contain digits
// must be only y or n (uppercase or lowercase)
char getYesNo() {
    string inp;

    while (true) {
        cin >> inp;

        // check if input contains any digit, invalid
        for (char c : inp) {
            if (isdigit((unsigned char)c)) {
                cout << "Error input\n\n";
                cout << "Do you want another transaction (Y/N)? ";
                goto askAgain;
            }
        }

        // accept only single character Y/y/N/n
        if (inp.size() == 1) {
            char c = inp[0];
            if (c == 'Y' || c == 'y' || c == 'N' || c == 'n')
                return c;
        }

        cout << "Error input\n\n";
        cout << "Do you want another transaction (Y/N)? ";

        askAgain: ;
    }
}

// validates proceed or exit input (must be 1 or 2 only)
int getProceedOrExit() {
    string s;

    while (true) {
        cin >> s;

        if (!isDigits(s)) { //uses function isDigits to check
            cout << "Error input\n";
            cout << "Press [1] to PROCEED or [2] to EXIT: ";
            continue;
        }

        int v = stoi(s); // converts string to integer
        if (v == 1 || v == 2) return v;

        cout << "Invalid selection\n";
        cout << "Press [1] to PROCEED or [2] to EXIT: ";
    }
}

int main() {
    string createdAccount;
    double balance = 100000.00; 

    // create an account number (digits only)
    while (true) {
        cout << "************************************\n";
        cout << "       WELCOME TO PaBB BANK\n";
        cout << "************************************\n\n";

        cout << "Create Account Number: ";
        string inpt;
        cin >> inpt;

        if (!isDigits(inpt)) {
            cout << "Error input. Account number must be digits only.\n\n";
            continue;
        }

        createdAccount = inpt;
        cout << "\nAccount " << createdAccount << " created successfully.\n\n";
        break;
    }

// main loop
start:
    cout << "************************************\n";
    cout << "       WELCOME TO PaBB BANK\n";
    cout << "************************************\n\n";

    cout << "[1] BALANCE\n";
    cout << "[2] DEPOSIT\n";
    cout << "[3] WITHDRAW\n";
    cout << "[4] CANCEL\n\n";

    // validate account number input
    cout << "Enter Account Number: ";
    string enteredAcc;
    cin >> enteredAcc;

    if (!isDigits(enteredAcc) || enteredAcc != createdAccount) {
        cout << "Error input or invalid account number.\n\n";
        goto start;
    }

    // validate transaction selection
    cout << "Select Transaction: ";
    string trans;
    cin >> trans;
    cout << "\n";

    if (!isDigits(trans)) {
        cout << "Error input\n\n";
        goto start;
    }

    int choice = stoi(trans);
    if (choice < 1 || choice > 4) {
        cout << "Error input\n\n";
        goto start;
    }

    // process transactions
    switch (choice) {

        // balance section
        case 1: {
            cout << "************************************\n";
            cout << "       WELCOME TO PaBB BANK\n";
            cout << "************************************\n\n";

            cout << fixed << setprecision(2); // fixed= ensures no scientific notation
            								  // setprecision(2)= number is rounded to two decimal places
            cout << "AVAILABLE BALANCE: " << balance << "\n\n";

            cout << "Do you want another transaction (Y/N)? ";
            char yn = getYesNo();

            if (yn == 'Y' || yn == 'y') {
                cout << "Press [1] to PROCEED or [2] to EXIT: ";
                int p = getProceedOrExit();
                cout << "\n";
                if (p == 1) goto start;
                else return 0;
            }
            return 0;
        }

        // deposit section
        case 2: {
            cout << "************************************\n";
            cout << "       WELCOME TO PaBB BANK\n";
            cout << "************************************\n\n";

            cout << "Enter Deposit Amount: ";
            string amtStr;
            cin >> amtStr;

            // amount validation
            if (!isValidAmount(amtStr)) {
                cout << "Error input\n\n";
                goto start;
            }

            double amt = strToDouble(amtStr);
            if (amt <= 0) {
                cout << "Error input: amount must be positive.\n\n";
                goto start;
            }

            balance += amt;

            cout << fixed << setprecision(2);
            cout << amt << "\n\n";

            cout << "Do you want another transaction (Y/N)? ";
            char yn = getYesNo();

            if (yn == 'Y' || yn == 'y') {
                cout << "Press [1] to PROCEED or [2] to EXIT: ";
                int p = getProceedOrExit();
                cout << "\n";
                if (p == 1) goto start;
                else return 0;
            }
            return 0;
        }

        // withdraw section
        case 3: {
            cout << "************************************\n";
            cout << "       WELCOME TO PaBB BANK\n";
            cout << "************************************\n\n";

            cout << "Enter Withdraw Amount: ";
            string wStr;
            cin >> wStr;

            if (!isValidAmount(wStr)) {
                cout << "Error input\n\n";
                goto start;
            }

            double w = strToDouble(wStr);
            if (w <= 0) {
                cout << "Error input: amount must be positive.\n\n";
                goto start;
            }
            if (w > balance) {
                cout << "Insufficient funds.\n\n";
                goto start;
            }

            balance -= w;

            cout << "\nYour transaction is complete! Please take your cash.\n";
            cout << "Thank you!\n\n";

            cout << "Do you want another transaction (Y/N)? ";
            char yn = getYesNo();

            if (yn == 'Y' || yn == 'y') {
                cout << "Press [1] to PROCEED or [2] to EXIT: ";
                int p = getProceedOrExit();
                cout << "\n";
                if (p == 1) goto start;
                else return 0;
            }
            return 0;
        }

        // cancel
        case 4:
            return 0;
    }

    return 0;
    
}

