#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <string>

class AccountsDatabase;

class UserInterface {
public:
    explicit UserInterface(AccountsDatabase& db);

    void run();

private:
    AccountsDatabase& db_;
    int currentUserId_;
    bool loggedIn_;

    void showWelcome();
    void showMainMenu();
    void showLoggedInMenu();

    int getChoice(int min, int max);
    std::string getLine(const std::string& prompt);
    double getMoney(const std::string& prompt);

    void createAccountFlow();
    void loginFlow();
    void logoutFlow();

    void checkingMenu();
    void savingsMenu();

    void depositFlow(bool isChecking);
    void withdrawFlow(bool isChecking);
    void transferFlow(bool fromChecking);
    void viewBalanceFlow(bool isChecking);
};

#endif
