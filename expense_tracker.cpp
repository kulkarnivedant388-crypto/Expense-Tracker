#include <iostream>   // for printing on the screen (cout)
#include <vector>     // idk why this library is used
#include <string>     // idk why this library is used
#include <fstream>    // idk why this library is used
#include <sstream>    // idk why this library is used
#include <iomanip>    // idk why this library is used
#include <numeric>    

// A struct groups related variables together.
// Expense = one entry like "35 rupees, bhel, 16-11-2026, snack"
struct Expense {
    double amount;            // money spent
    std::string category;     // type of expense (Food, Travel, etc.)
    std::string date;         // date of the expense
    std::string description;  // small note about the expense

    // Turns this expense into one line of text so it can be saved in the file.
    // Values are separated by commas, like: 35,Food,16-11-2026,Snack aka CSV
    std::string toCSV() const {
        return std::to_string(amount) + "," + category + "," + date + "," + description;
    }

    // Does the opposite of toCSV: takes one line from the file
    // and turns it back into an Expense.
    static Expense fromCSV(const std::string& line) {
        std::stringstream ss(line);
        std::string amountStr, cat, dt, desc;

        // Pick out each value from the line, stopping at every comma
        std::getline(ss, amountStr, ',');
        std::getline(ss, cat, ',');
        std::getline(ss, dt, ',');
        std::getline(ss, desc, ',');

        // Convert the amount from text to a number.
        // If that fails (bad data in the file), use 0 instead of crashing.
        double amt = 0.0;
        try {
            amt = std::stod(amountStr);
        } catch (...) {
            amt = 0.0;
        }

        // Make an Expense from the values and give it back
        return {amt, cat, dt, desc};
    }
};

// A class bundles data and the functions that work on that data.
// ExpenseTracker holds all the expenses and handles saving/loading them.
class ExpenseTracker {
private:  // private = only usable inside this class
    std::vector<Expense> expenses;                     // the list of all expenses
    const std::string filename = "expenses_data.csv";  // name of the file where data is saved

    // Reads the saved file and puts every expense back into the list
    void loadFromFile() {
        std::ifstream file(filename);   // open the file for reading
        if (!file.is_open()) return;    // no file yet (first run), so nothing to load

        std::string line;
        expenses.clear();               // empty the list first
        while (std::getline(file, line)) {   // read the file one line at a time
            if (!line.empty()) {             // ignore empty lines
                expenses.push_back(Expense::fromCSV(line));  // convert the line and add it to the list
            }
        }
        file.close();
    }

    // Writes the whole list of expenses into the file
    void saveToFile() const {
        std::ofstream file(filename);   // open the file for writing (replaces old content)
        for (const auto& exp : expenses) {   // go through every expense in the list
            file << exp.toCSV() << "\n";     // write it as one line
        }
        file.close();
    }

public:  // public = can be used from outside the class
    // Constructor: runs automatically when an ExpenseTracker is created.
    // It loads any previously saved expenses
    ExpenseTracker() {
        loadFromFile();
    }

    // Adds a new expense to the list and saves it to the file
    void addExpense(double amt, std::string cat, std::string dt, std::string desc) {
        expenses.push_back({amt, cat, dt, desc});  // add to the end of the list
        saveToFile();                              // update the file
    }
};

int main() {
    std::cout << "Hostel Expense Tracker C++ Core Initialized.\n";
    return 0;
}
