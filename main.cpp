#include "accountsDatabase.h"
#include "userInterface.h"

int main()
{
	AccountsDatabase db;
	UserInterface ui(db);
	ui.run();
	return 0;
}
