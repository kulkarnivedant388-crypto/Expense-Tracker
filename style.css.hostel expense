#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <numeric>

struct Expense {
    double amount;
    std::string category;
    std::string date;
    std::string description;

    std::string toCSV() const {
        return std::to_string(amount) + "," + category + "," + date + "," + description;
    }

    static Expense fromCSV(const std::string& line) {
        std::stringstream ss(line);
        std::string amountStr, cat, dt, desc;
        
        std::getline(ss, amountStr, ',');
        std::getline(ss, cat, ',');
        std::getline(ss, dt, ',');
        std::getline(ss, desc, ',');

        double amt = 0.0;
        try {
            amt = std::stod(amountStr);
        } catch (...) {
            amt = 0.0;
        }

        return {amt, cat, dt, desc};
    }
};

class ExpenseTracker {
private:
    std::vector<Expense> expenses;
    const std::string filename = "expenses_data.csv";

    void loadFromFile() {
        std::ifstream file(filename);
        if (!file.is_open()) return;

        std::string line;
        expenses.clear();
        while (std::getline(file, line)) {
            if (!line.empty()) {
                expenses.push_back(Expense::fromCSV(line));
            }
        }
        file.close();
    }

    void saveToFile() const {
        std::ofstream file(filename);
        for (const auto& exp : expenses) {
            file << exp.toCSV() << "\n";
        }
        file.close();
    }

public:
    ExpenseTracker() {
        loadFromFile();
    }

    void addExpense(double amt, std::string cat, std::string dt, std::string desc) {
        expenses.push_back({amt, cat, dt, desc});
        saveToFile();
    }
};

int main() {
    std::cout << "Hostel Expense Tracker C++ Core Initialized.\n";
    return 0;
}
