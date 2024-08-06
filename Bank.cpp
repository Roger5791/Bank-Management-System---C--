#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct Account
{
    string accountNumber;
    string name;
    string password;
    double balance;
    Account *next;
};

class BankManagementSystem
{
private:
    Account *head;
    string dataFile;

public:
    BankManagementSystem() : head(NULL), dataFile("accounts.txt") {}

    void addAccount()
    {
        Account *newAccount = new Account;
        cout << "Enter Account Number: ";
        cin >> newAccount->accountNumber;

        if (isAccountNumberUnique(newAccount->accountNumber))
        {
            cout << "Enter Name: ";
            cin >> newAccount->name;
            getline(cin, newAccount->password);
            cout << "Enter Password: ";
            cin >> newAccount->password;
            cout << "Enter Opening Balance: ";
            cin >> newAccount->balance;

            newAccount->next = NULL;

            if (head == NULL)
            {
                head = newAccount;
            }
            else
            {
                Account *current = head;
                while (current->next != NULL)
                {
                    current = current->next;
                }
                current->next = newAccount;
            }
            cout << "\nAccount Added Successfully!" << endl;
            saveAccountsTofile();
        }
        else
        {
            cout << "\nAccount Number is Already Used. Please try another Number..." << endl;
            delete newAccount;
        }
    }

    bool isAccountNumberUnique(const string &accountNumber)
    {
        Account *current = head;
        while (current != NULL)
        {
            if (current->accountNumber == accountNumber)
            {
                return false;
            }
            current = current->next;
        }
        return true;
    }

    Account *findAccount(const string &accountNumber, const string &password)
    {
        Account *current = head;
        while (current != NULL)
        {
            if (current->accountNumber == accountNumber && current->password == password)
            {
                return current;
            }
            current = current->next;
        }
        return NULL;
    }

    void searchAccount()
    {
        string accountNumber;
        cout << "Enter Account Number: ";
        cin >> accountNumber;

        string password;
        cout << "Enter Password: ";
        cin >> password;

        Account *account = findAccount(accountNumber, password);
        if (account != NULL)
        {
            cout << "\nAccount Number: " << account->accountNumber << endl;
            cout << "\nName: " << account->name << endl;
            cout << "\nBalance: " << account->balance << endl;
        }
        else
        {
            cout << "\nAccount not Found or Invalid Password" << endl;
        }
    }

    void depositFunds()
    {
        string accountNumber;
        cout << "Enter Account Number: ";
        cin >> accountNumber;

        string password;
        cout << "Enter Password: ";
        cin >> password;

        Account *account = findAccount(accountNumber, password);
        if (account != NULL)
        {
            double amount;
            cout << "Enter Deposit Amount: ";
            cin >> amount;

            account->balance += amount;
            cout << "\nDeposit Successful" << endl;
            cout << "Balance: " << account->balance << endl;

            saveAccountsTofile();
        }
        else
        {
            cout << "\nAccount Not Found or Invalid Password" << endl;
        }
    }

    void withdrawFunds()
    {
        string accountNumber;
        cout << "Enter Account Number: ";
        cin >> accountNumber;

        string password;
        cout << "Enter Password: ";
        cin >> password;

        Account *account = findAccount(accountNumber, password);
        if (account != NULL)
        {
            double amount;
            cout << "Enter Withdrawal Amount: ";
            cin >> amount;

            if (account->balance >= amount)
            {
                account->balance -= amount;
                cout << "\nWithdrawal Successful" << endl;
                cout << "Balance: " << account->balance << endl;

                saveAccountsTofile();
            }
            else
            {
                cout << "\nInsufficient Funds!" << endl;
            }
        }
        else
        {
            cout << "\nAccount Not Found or Invalid Password" << endl;
        }
    }

    void displayAccounts()
    {
        cout << "\n---- All Acccounts ----" << endl;

        Account *current = head;
        while (current != NULL)
        {
            cout << "\n--------------------";
            cout << "\nAccount Number: " << current->accountNumber << endl;
            cout << "Name: " << current->name << endl;
            cout << "Balance: " << current->balance << endl;
            current = current->next;
        }
        cout << endl;
    }

    void saveAccountsTofile()
    {
        ofstream outputFile(dataFile.c_str());

        if (outputFile.is_open())
        {
            Account *current = head;
            while (current != NULL)
            {
                outputFile << current->accountNumber << "," << current->name << ',' << current->password << "," << current->balance << endl;
                current = current->next;
            }
            outputFile.close();
            cout << "\nAccounts Saved to Directory: " << dataFile << endl;
        }
        else
        {
            cout << "\nError: Unable to open File!" << endl;
        }
    }

    void loadAccountsFromFile()
    {
        ifstream inputFile(dataFile.c_str());

        if (inputFile.is_open())
        {
            string line;
            while (getline(inputFile, line))
            {
                stringstream ss(line);
                string accountNumber, name, password;
                double balance;

                getline(ss, accountNumber, ',');
                getline(ss, name, ',');
                getline(ss, password, ',');
                ss >> balance;

                Account *newAccount = new Account;
                newAccount->accountNumber = accountNumber;
                newAccount->name = name;
                newAccount->password = password;
                newAccount->balance = balance;
                newAccount->next = NULL;

                if (head == NULL)
                {
                    head = newAccount;
                }
                else
                {
                    Account *current = head;
                    while (current->next != NULL)
                    {
                        current = current->next;
                    }
                    current->next = newAccount;
                }
            }
            inputFile.close();
            cout << "\nAccounts loaded from Directory: " << dataFile << endl;
        }
        else
        {
            cout << "\nError: Unable to open File!" << endl;
        }
    }

    void menu()
    {
        loadAccountsFromFile();
        int choice;

        while (true)
        {
            cout << "\n----- Bank Management System -----" << endl;
            cout << "\n1. Add Account" << endl;
            cout << "2. Search Account" << endl;
            cout << "3. Deposit Funds" << endl;
            cout << "4. Withdraw Funds" << endl;
            cout << "5. Display All Accounts" << endl;
            cout << "6. Exit" << endl;
            cout << "Enter your Choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                addAccount();
                break;
            case 2:
                searchAccount();
                break;
            case 3:
                depositFunds();
                break;
            case 4:
                withdrawFunds();
                break;
            case 5:
                displayAccounts();
                break;
            case 6:
                return;

            default:
                cout << "Inavalid Choice! " << endl;
            }
        }
    }
};

int main()
{
    BankManagementSystem bankManagementSystem;
    bankManagementSystem.menu();
    return 0;
}
