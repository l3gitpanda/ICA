#include "userInterface.h"
#include "accountsDatabase.h"

#include <iostream>
#include <limits>
#include <iomanip>

UserInterface::UserInterface(AccountsDatabase& db)
    : db_(db), currentUserId_(-1), loggedIn_(false) {}

void UserInterface::run() {
    showWelcome();
    while (true) {
        if (!loggedIn_) {
            showMainMenu();
            int c = getChoice(1, 3);
            if (c == 1) createAccountFlow();
            else if (c == 2) loginFlow();
            else break;
        } else {
            showLoggedInMenu();
            int c = getChoice(1, 4);
            if (c == 1) checkingMenu();
            else if (c == 2) savingsMenu();
            else if (c == 3) logoutFlow();
            else break;
        }
    }
    std::cout << "Bye.\n";
}

void UserInterface::showWelcome() {
    std::cout << "=============================\n";
    std::cout << "        Simple Bank\n";
    std::cout << "=============================\n";
}

void UserInterface::showMainMenu() {
    std::cout << "\nMain Menu\n";
    std::cout << "1) Create account\n";
    std::cout << "2) Log in\n";
    std::cout << "3) Exit\n";
}

void UserInterface::showLoggedInMenu() {
    std::cout << "\nHome Screen (User ID: " << currentUserId_ << ")\n";

    if (db_.hasChecking(currentUserId_)) {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Checking balance: $" << db_.getCheckingBalance(currentUserId_) << "\n";
    } else {
        std::cout << "Checking balance: N/A\n";
    }

    if (db_.hasSavings(currentUserId_)) {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Savings balance: $" << db_.getSavingsBalance(currentUserId_) << "\n";
    } else {
        std::cout << "Savings balance: N/A\n";
    }

    std::cout << "1) Checking details\n";
    std::cout << "2) Savings details\n";
    std::cout << "3) Log out\n";
    std::cout << "4) Exit\n";
}

int UserInterface::getChoice(int min, int max) {
    while (true) {
        std::cout << "Choice (" << min << "-" << max << "): ";
        int x;
        if (std::cin >> x && x >= min && x <= max) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return x;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input.\n";
    }
}

std::string UserInterface::getLine(const std::string& prompt) {
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

double UserInterface::getMoney(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        double amt;
        if (std::cin >> amt && amt > 0) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return amt;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter a positive number.\n";
    }
}

void UserInterface::createAccountFlow() {
    std::string email = getLine("Email: ");
    std::string pass  = getLine("Password: ");

    int newId = db_.createUser(email, pass);   // TODO_CALL_DB
    if (newId < 0) {
        std::cout << "Could not create account.\n";
        return;
    }

    currentUserId_ = newId;
    loggedIn_ = true;

    std::cout << "Account created. Your user id is " << currentUserId_ << ".\n";

    if (!db_.hasChecking(currentUserId_)) db_.createChecking(currentUserId_); // TODO_CALL_DB
    if (!db_.hasSavings(currentUserId_))  db_.createSavings(currentUserId_);  // TODO_CALL_DB
}

void UserInterface::loginFlow() {
    std::string email = getLine("Email: ");
    std::string pass  = getLine("Password: ");

    int id = db_.authenticate(email, pass);    // TODO_CALL_DB
    if (id < 0) {
        std::cout << "Login failed.\n";
        return;
    }

    currentUserId_ = id;
    loggedIn_ = true;
    std::cout << "Logged in.\n";

    if (!db_.hasChecking(currentUserId_)) db_.createChecking(currentUserId_);
    if (!db_.hasSavings(currentUserId_)) db_.createSavings(currentUserId_);
}

void UserInterface::logoutFlow() {
    loggedIn_ = false;
    currentUserId_ = -1;
    std::cout << "Logged out.\n";
}

void UserInterface::checkingMenu() {
    while (true) {
        std::cout << "\nChecking Menu\n";
        std::cout << "1) View balance\n";
        std::cout << "2) Deposit\n";
        std::cout << "3) Withdraw\n";
        std::cout << "4) Withdraw to savings\n";
        std::cout << "5) Back\n";

        int c = getChoice(1, 5);
        if (c == 1) viewBalanceFlow(true);
        else if (c == 2) depositFlow(true);
        else if (c == 3) withdrawFlow(true);
        else if (c == 4) transferFlow(true);
        else break;
    }
}

void UserInterface::savingsMenu() {
    while (true) {
        std::cout << "\nSavings Menu\n";
        std::cout << "1) View balance\n";
        std::cout << "2) Deposit\n";
        std::cout << "3) Withdraw\n";
        std::cout << "4) Withdraw to checking\n";
        std::cout << "5) Back\n";

        int c = getChoice(1, 5);
        if (c == 1) viewBalanceFlow(false);
        else if (c == 2) depositFlow(false);
        else if (c == 3) withdrawFlow(false);
        else if (c == 4) transferFlow(false);
        else break;
    }
}

void UserInterface::viewBalanceFlow(bool isChecking) {
    double bal = isChecking
        ? db_.getCheckingBalance(currentUserId_)   // TODO_CALL_DB
        : db_.getSavingsBalance(currentUserId_);   // TODO_CALL_DB

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Balance: $" << bal << "\n";
}

void UserInterface::depositFlow(bool isChecking) {
    double amt = getMoney("Deposit amount: $");

    bool ok = isChecking
        ? db_.depositChecking(currentUserId_, amt) // TODO_CALL_DB
        : db_.depositSavings(currentUserId_, amt); // TODO_CALL_DB

    if (!ok) std::cout << "Deposit failed.\n";
    else std::cout << "Deposit successful.\n";
}

void UserInterface::withdrawFlow(bool isChecking) {
    double amt = getMoney("Withdraw amount: $");

    bool ok = isChecking
        ? db_.withdrawChecking(currentUserId_, amt) // TODO_CALL_DB
        : db_.withdrawSavings(currentUserId_, amt); // TODO_CALL_DB

    if (!ok) std::cout << "Withdraw failed.\n";
    else std::cout << "Withdraw successful.\n";
}

void UserInterface::transferFlow(bool fromChecking) {
    std::string targetName = fromChecking ? "savings" : "checkings";
    double amt = getMoney("Transfer amount to " + targetName + ": $");

    bool ok = fromChecking 
            ? db_.transferCheckingToSavings(currentUserId_, amt)
            : db_.transferSavingsToChecking(currentUserId_, amt);

    if (ok) {
        std::cout << "Transfer successful.\n";
    } else {
        std::cout << "Transfer failed.\n"; 
    }
}
