// Included required header files
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctime>
using namespace std;

// Declaration of Account class
class Account
{
    // Declarations of variable to store user data
protected:
    int accountNumber;
    char name[50];
    char address[50];
    char gmail[50];
    float balance;
    long long int phone;
    float monthinitialBalance;
    float monthtotalWithdraw;
    float monthtotalDeposit;
    int totalDeposit;
    int totalWithdraw;
    static float monthlyCharges;
    float interestRate;

public:
    //Prototype of Member functions of the Account class which perform their respective task
    void inputAccount();                //function to writes account details in file
    void showAccount();                 //function to display account information when clled
    int setAccountNumber();             //function to set accountNumber
    float setInterestRate(int balance); //function to set interest rate according to user balance;

    float calcInt(float balance, float interestRate); //function to calculate interest
    virtual void monthlyProc();                       //virtual function which adds interest,subtracts monthly charges accordingly etc.
    virtual void makeDeposit(int depositAmount);      //virtual function which add deposited amount
    virtual void makeWithdraw(int WithdrawAmount);    //virtual function which substracts withdrawn amount

    void displayAccounts();                           //function to read and display all account information
    void deleteAccount();                             //function to delete a given account
    void selectedAccount();                           //function to display information of selected account
    void updateAccount();                             //function to update account details
    friend istream &operator>>(istream &, Account &); //function to recieve and set  the account details
    void monthlystats();                              //function to display monthly statistics
};
float Account::monthlyCharges = 10; //initialization of monthlyCharges variable;
//Declaration of a global variable to store the input id and deposit Withdraw Amount;
int UserId;   //global variable which stores account number to be used in above functions
int WDamount; //global variable which store withdraw/deposit amount
static int AccountType = 0;
//Value of AccounrType will be set to 1 if the user chooses to work with saving account
//sinilary, value of AcconuntType will be 2 if user chooses checking account

//Defining all the member functions of all the classes starting with Account followed by CheckingAccount and SavingAccount class respectively

//function named setAccountNumber whoch set the account number to each newly created account.
int Account ::setAccountNumber()
{
    ifstream fin;
    Account temp;
    int acNo = 0;

    if (AccountType == 1)
        fin.open("saving.txt", ios::in | ios::binary);
    if (AccountType == 2)
        fin.open("checking.txt", ios::in | ios::binary);
    if (!fin)
        return 1;
    else
    {
        fin.read((char *)&temp, sizeof(temp));
        while (!fin.eof())
        {
            acNo = temp.accountNumber;
            fin.read((char *)&temp, sizeof(temp));
        }
        acNo++;
        return (acNo);
    }
}

//Overloading an extraction operator for account class which input the user details and call inputAccount function to write in the file
istream &operator>>(istream &input, Account &a)
{
    a.accountNumber = a.setAccountNumber();
    cout << "Enter the name : ";
    fflush(stdin);
    gets(a.name);
    cout << "Enter the address : ";
    fflush(stdin);
    gets(a.address);
    cout << "Enter the gmail : ";
    fflush(stdin);
    gets(a.gmail);
    cout << "Enter the phone number : ";
    fflush(stdin);
    cin >> a.phone;
startingBalance:
    cout << "Enter the starting balance : ";
    fflush(stdin);
    input >> a.balance;
    if (a.balance < 25)
    {
        cout << "Sorry your balance should be above $25 to create an account." << endl;
        cout << "Please try again." << endl;
        goto startingBalance;
    }
    a.interestRate = a.setInterestRate(a.balance);
    a.totalDeposit = 1;
    a.totalWithdraw = 0;
    a.monthinitialBalance = a.balance;
    a.monthtotalDeposit = 0;
    a.monthtotalWithdraw = 0;
    a.inputAccount();
    cout << endl;
    return input;
}
//function named setInterestRate which sets the interest rate according to the balance in the account
float Account::setInterestRate(int balance)
{
    if (balance < 100)
        interestRate = 0.5;
    else if (balance >= 100 && balance < 500)
        interestRate = 0.7;
    else if (balance >= 500 && balance < 1000)
        interestRate = 0.9;
    else if (balance >= 1000 && balance < 10000)
        interestRate = 0.11;
    else
        interestRate = 0.13;

    return interestRate;
}
//function name inputAccount which write the account details in file
void Account ::inputAccount()
{
    if (AccountType == 1)
    {
        ofstream fout;
        fout.open("saving.txt", ios::app | ios::binary);
        if (!fout)
            cout << "File cannot open.";
        else
            fout.write((char *)this, sizeof(*this));
        fout.close();
    }
    if (AccountType == 2)
    {
        ofstream fout;
        fout.open("checking.txt", ios::app | ios::binary);
        if (!fout)
            cout << "File cannot open.";
        else
            fout.write((char *)this, sizeof(*this));
        fout.close();
    }
}

//function named showAccount which displayed the account details when called.
void Account ::showAccount()
{
    cout << endl;
    cout << left;
    cout << "Account Number : " << accountNumber << endl;
    cout << "Name : " << name << endl;
    cout << "Address : " << address << endl;
    cout << "Email : " << gmail << endl;
    cout << "Phone Number : " << phone << endl;
    cout << "Remaining Balance : " << balance << endl;
    cout << "Total Deposit : " << totalDeposit << endl;
    cout << "Total Withdraw : " << totalWithdraw << endl;
    cout << "Interest Rate : " << interestRate << endl;
    cout << "Monthly charges : " << monthlyCharges << endl
         << endl;
}
//function name displayAccounts which displays the information of all the accounts
void Account ::displayAccounts()
{
    ifstream fin;
    if (AccountType == 1)
        fin.open("saving.txt", ios::in | ios::binary);
    if (AccountType == 2)
        fin.open("checking.txt", ios::in | ios::binary);
    if (!fin)
        cout << "File not found" << endl;
    else
    {
        fin.read((char *)this, sizeof(*this));
        while (!fin.eof())
        {
            showAccount();
            fin.read((char *)this, sizeof(*this));
        }
        if (fin.eof())
            cout << "All files displayed." << endl;
    }
    fin.close();
}

//function named selectedAccount which displays the information of particular account
void Account ::selectedAccount()
{
    int id;
    ifstream fin;
    if (AccountType == 1)
        fin.open("saving.txt", ios::in | ios::binary);
    if (AccountType == 2)
        fin.open("checking.txt", ios::in | ios::binary);
    if (!fin)
        cout << "File not found." << endl;
    else
    {
        cout << "Enter account number to display : ";
        cin >> id;
        fin.read((char *)this, sizeof(*this));
        while (!fin.eof())
        {
            if (accountNumber == id)
            {
                showAccount();
                break;
            }
            fin.read((char *)this, sizeof(*this));
        }
    }
    if (fin.eof())
        cout << "Account not found." << endl;
}
//function named deleteAccount which deletes particular account
void Account ::deleteAccount()
{
    if (AccountType == 1)
    {
        ifstream fin("saving.txt", ios::in | ios::binary);
        ofstream fout("temp.txt", ios::out | ios::binary);
        if (!fin)
            cout << "File not found" << endl;
        else
        {
            int id;
            cout << "Enter account number to delete : ";
            cin >> id;
            fin.read((char *)this, sizeof(*this));
            while (!fin.eof())
            {
                if (id != accountNumber)
                    fout.write((char *)this, sizeof(*this));
                fin.read((char *)this, sizeof(*this));
            }
        }
        fout.close();
        fin.close();
        remove("saving.txt");
        rename("temp.txt", "saving.txt");
        cout << "The account is deleted." << endl;
    }

    if (AccountType == 2)
    {
        ifstream fin("checking.txt", ios::in | ios::binary);
        ofstream fout("temp.txt", ios::out | ios::binary);
        if (!fin)
            cout << "File not found" << endl;
        else
        {
            int id;
            cout << "Enter account number to delete : ";
            cin >> id;
            fin.read((char *)this, sizeof(*this));
            while (!fin.eof())
            {
                if (id != accountNumber)
                    fout.write((char *)this, sizeof(*this));
                fin.read((char *)this, sizeof(*this));
            }
        }
        fout.close();
        fin.close();
        remove("checking.txt");
        rename("temp.txt", "checking.txt");
        cout << "The account is deleted." << endl;
    }
}
//function name updateAccount which is used to update the details of the account/user
void Account ::updateAccount()
{
    int id;
    int count = 0;
    fstream file;
    if (AccountType == 1)
        file.open("saving.txt", ios::in | ios::out | ios::ate | ios::binary);
    if (AccountType == 2)
        file.open("checking.txt", ios::in | ios::out | ios::ate | ios::binary);
    cout << "\nEnter account number to update: ";
    cin >> id;
    file.seekg(0);
    if (!file)
        cout << "File not found." << endl;
    else
    {
        file.read((char *)this, sizeof(*this));
        while (!file.eof())
        {
            count++;
            if (accountNumber == id)
            {
                //type here anything needed to modify
                cout << "Enter the name : ";
                fflush(stdin);
                gets(name);
                cout << "Enter the address : ";
                fflush(stdin);
                gets(address);
                cout << "Enter the gmail : ";
                fflush(stdin);
                gets(gmail);
                cout<<"Enter the phone number : ";
                fflush(stdin);
                cin>>phone;
                //Placing the write pointer at the starting of the object
                file.seekp((count - 1) * sizeof(Account), ios::beg);
                file.write((char *)this, sizeof(*this));
                break;
            }
            file.read((char *)this, sizeof(*this));
        }
        if (file.eof())
            cout << "Account not found. " << endl;
    }
    file.close();
}
//function named makeDeposit which deposit the given amount to its respective account
void Account::makeDeposit(int depositAmount)
{
    int count = 0;
    fstream file;
    if (AccountType == 1)
        file.open("saving.txt", ios::in | ios::out | ios::ate | ios::binary);
    if (AccountType == 2)
        file.open("checking.txt", ios::in | ios::out | ios::ate | ios::binary);
    file.seekg(0);
    file.read((char *)this, sizeof(*this));
    while (!file.eof())
    {
        count++;
        if (accountNumber == UserId)
        {
            balance += depositAmount;
            totalDeposit++;
            interestRate = setInterestRate(balance);
            monthtotalDeposit += depositAmount;
            file.seekp((count - 1) * sizeof(Account), ios::beg);
            file.write((char *)this, sizeof(*this));
            cout << "The account details after deposit : ";
            showAccount();
            break;
        }
        file.read((char *)this, sizeof(*this));
    }
    file.close();
}
//function name makewithdraw which withdraws the given amount from its respective account
void Account::makeWithdraw(int withdrawAmount)
{
    int count = 0;
    fstream file;
    if (AccountType == 1)
        file.open("saving.txt", ios::in | ios::out | ios::ate | ios::binary);
    if (AccountType == 2)
        file.open("checking.txt", ios::in | ios::out | ios::ate | ios::binary);
    file.seekg(0);
    file.read((char *)this, sizeof(*this));
    while (!file.eof())
    {
        count++;
        if (accountNumber == UserId)
        {
            balance -= withdrawAmount;
            totalWithdraw++;
            interestRate = setInterestRate(balance);
            monthtotalWithdraw += withdrawAmount;
            file.seekp((count - 1) * sizeof(Account), ios::beg);
            file.write((char *)this, sizeof(*this));
            cout << "The account details after withdraw : " << endl;
            showAccount();
            break;
        }
        file.read((char *)this, sizeof(*this));
    }
    file.close();
}
//function named calcInt which calculate the interest amount of the account using its balance and interest Rate
float Account::calcInt(float balance, float interestRate)
{
    float MonthlyInterestrate = interestRate / 12;
    float monthlyInterest = balance * MonthlyInterestrate;
    return monthlyInterest;
}

//function named monthlyProc which add interest, substracts monthly charges and resets total deposit and withdraw to 0
void Account::monthlyProc()
{
    float storebalance;
    int count = 0;
    fstream file;
    if (AccountType == 1)
        file.open("saving.txt", ios::in | ios::out | ios::ate | ios::binary);
    if (AccountType == 2)
        file.open("checking.txt", ios::in | ios::out | ios::ate | ios::binary);
    file.seekg(0);
    if (!file)
        cout << "File not found." << endl;
    else
    {
        file.read((char *)this, sizeof(*this));
        while (!file.eof())
        {
            count++;
            if (accountNumber == UserId)
            {
                storebalance = calcInt(balance, interestRate);
                balance = balance - monthlyCharges + storebalance;
                totalWithdraw = 0;
                totalDeposit = 0;
                monthlyCharges = 10;
                monthinitialBalance = balance;
                monthtotalWithdraw = 0;
                monthtotalDeposit = 0;
                file.seekp((count - 1) * sizeof(Account), ios::beg);
                file.write((char *)this, sizeof(*this));
                break;
            }
            file.read((char *)this, sizeof(*this));
        }
        if (file.eof())
            cout << "Account not found. " << endl;
    }
    file.close();
}
void Account::monthlystats()
{
    int id;
    ifstream fin;
    if (AccountType == 1)
        fin.open("saving.txt", ios::in | ios::binary);
    if (AccountType == 2)
        fin.open("checking.txt", ios::in | ios::binary);
    if (!fin)
        cout << "File not found." << endl;
    else
    {
        cout << "Enter account number to display : ";
        cin >> id;
        fin.read((char *)this, sizeof(*this));
        while (!fin.eof())
        {
            if (accountNumber == id)
            {
                showAccount();
                cout << "Month's initial balance : " << monthinitialBalance << endl;
                cout << "Month's final balance : " << balance << endl;
                cout << "Month's total deposit amount : " << monthtotalDeposit << endl;
                cout << "Month's total withdraw amount : " << monthtotalWithdraw << endl
                     << endl;
                break;
            }
            fin.read((char *)this, sizeof(*this));
        }
    }
    if (fin.eof())
        cout << "Account not found." << endl;
}
// Declaration of CheckingAccount class
class CheckingAccount : public Account
{
public:
    void monthlyProc();
    void makeDeposit(int depositAmount);   //function to add the monthly fee and perwithdrawal charge before calling base class function
    void makeWithdraw(int withdrawAmount); //function to determine if withdrawal will cause the balance to go below 0
};

void CheckingAccount ::makeWithdraw(int withdrawAmount)
{
    int checkBalance;

    checkBalance = balance - withdrawAmount;
    if (checkBalance < 0)
    {
        cout << "You do not have enough balance to withdraw. You are charged $15" << endl;
        int count = 0;
        fstream file;
        file.open("checking.txt", ios::in | ios::out | ios::ate | ios::binary);
        file.seekg(0);
        file.read((char *)this, sizeof(*this));
        while (!file.eof())
        {
            count++;
            if (accountNumber == UserId)
            {
                balance -= 15;
                monthtotalWithdraw += 15;
                file.seekp((count - 1) * sizeof(Account), ios::beg);
                file.write((char *)this, sizeof(*this));
                break;
            }
            file.read((char *)this, sizeof(*this));
        }
        file.close();
    }
    else
        Account::makeWithdraw(withdrawAmount);
}

void CheckingAccount::makeDeposit(int depositAmount)
{
    Account::makeDeposit(depositAmount);
}

void CheckingAccount::monthlyProc()
{
    float monthlyfee = 5;
    int count = 0;
    fstream file("checking.txt", ios::in | ios::out | ios::ate | ios::binary);
    file.seekg(0);
    if (!file)
        cout << "File not found." << endl;
    else
    {
        file.read((char *)this, sizeof(this));
        while (!file.eof())
        {
            count++;
            if (accountNumber == UserId)
            {
                monthlyCharges += monthlyfee + (0.1 * totalWithdraw);
                Account::monthlyProc();
            }
            file.read((char *)this, sizeof(*this));
        }
    }
    file.close();
}

//Declaration of SavingAccount class
class SavingAccount : public Account
{
public:
    bool status(int remainingBalance);     //function to determine if account is active
    void monthlyProc();                    //function to check number of withdrawal
    void makeDeposit(int depositAmount);   //function to check if account will be acitve with deposit
    void makeWithdraw(int withdrawAmount); //function to check if account is inactive to withdraw
};
// SavingAccount class functions

bool SavingAccount ::status(int remainingBalance)
{
    bool flag = 0;
    if (remainingBalance > 25)
    {
        flag = 1;
    }
    return flag;
}

void SavingAccount ::makeDeposit(int depositAmount)
{
    float storeBalance;
    int count = 0;
    fstream file;
    file.open("saving.txt", ios::in | ios::ate | ios::binary | ios::out);
    file.seekg(0);
    if (!file)
        cout << "File not found." << endl;
    else
    {
        file.read((char *)this, sizeof(*this));
        while (!file.eof())
        {
            if (accountNumber == UserId)
            {
                storeBalance = balance + depositAmount;
                if (status(storeBalance) == 1)
                {
                    Account::makeDeposit(depositAmount);
                }
                else
                {
                    cout << "Your deposit does not bring you balance above $25. Your process is terminated." << endl;
                }
                file.seekp((count - 1) * sizeof(Account), ios::beg);
                file.write((char *)this, sizeof(*this));
                break;
            }
            file.read((char *)this, sizeof(*this));
        }
        if (file.eof())
            cout << "Account not found. " << endl;
    }
    file.close();
}

void SavingAccount ::makeWithdraw(int withdrawAmount)
{
    int count = 0;
    fstream file;
    file.open("saving.txt", ios::in | ios::ate | ios::binary | ios::out);
    file.seekg(0);
    if (!file)
        cout << "File not found." << endl;
    else
    {
        file.read((char *)this, sizeof(*this));
        while (!file.eof())
        {
            if (accountNumber == UserId)
            {
                if (status(balance) == 1)
                {
                    Account::makeWithdraw(WDamount);
                }
                else
                {
                    cout << "You do not have an active account.Your process is terminated" << endl;
                }
                file.seekp((count - 1) * sizeof(Account), ios::beg);
                file.write((char *)this, sizeof(*this));
                break;
            }
            file.read((char *)this, sizeof(*this));
        }
        if (file.eof())
            cout << "Account not found. " << endl;
    }
    file.close();
}

void SavingAccount::monthlyProc()
{
    int count = 0;
    ifstream file("saving.txt", ios::in | ios::out | ios::ate | ios::binary);
    file.seekg(0);
    if (!file)
        cout << "File not found." << endl;
    else
    {
        file.read((char *)this, sizeof(*this));
        while (!file.eof())
        {
            count++;
            showAccount();
            UserId = accountNumber;
            if (totalWithdraw > 4)
            {
                monthlyCharges += (0.4) + (totalWithdraw - 4);
                Account::monthlyProc();
            }
            else
            {
                monthlyCharges += (0.1 * totalWithdraw);
                Account::monthlyProc();
            }
            file.read((char *)this, sizeof(*this));
        }
    }
    file.close();
}

// Declaration of function named accountChoice which displays the operational menu
int accountChoice()
{
    cout << "Operational Menu." << endl;
    cout << "1.Saving Account." << endl;
    cout << "2.Checking Account." << endl;
    cout << "3.Exit." << endl;
    cout << "Enter your choice : ";
    int choice;
    cin >> choice;
    cout << endl;
    return (choice);
}
int menu()
{
    cout << "1.Create an account." << endl;
    cout << "2.Display all accounts." << endl;
    cout << "3.Display single account." << endl;
    cout << "4.Delete an account." << endl;
    cout << "5.Update an account." << endl;
    cout << "6.Display Monthly stats." << endl;
    cout << "7.Deposit." << endl;
    cout << "8.Withdraw." << endl;
    cout << "9.Back to Operational Menu." << endl;
    cout << "Enter your choice : ";
    int choice;
    cin >> choice;
    cout << endl;
    return (choice);
}
//Declaration of function name setIDAmt which inputs the userID and WD amount for future use
int setIdAmt()
{
    cout << "Enter the User Id : ";
    cin >> UserId;
    cout << "Enter the amount : ";
    cin >> WDamount;
    cout << endl;
    return WDamount;
}
int main()
{
    time_t t;
    struct tm tLocal;
    t = time(NULL);
    tLocal = *localtime(&t);
    cout << "Today's Date is :  " << tLocal.tm_mday << endl;

    SavingAccount s;
    CheckingAccount c;

    if (tLocal.tm_mday == 1)
    {
        s.monthlyProc();
        c.monthlyProc();
    }
    int ch;
    int ch2;
    while (1)
    {
        system("pause");
        system("cls");
        ch = accountChoice();
        switch (ch)
        {
        case 1:
            AccountType = 1;
            ch2 = menu();
            switch (ch2)
            {
            case 1:
                cin >> s;
                break;
            case 2:
                s.displayAccounts();
                break;
            case 3:
                s.selectedAccount();
                break;
            case 4:
                s.deleteAccount();
                break;
            case 5:
                s.updateAccount();
                break;
            case 6:
                s.monthlystats();
                break;
            case 7:
                s.makeDeposit(setIdAmt());
                break;
            case 8:
                s.makeWithdraw(setIdAmt());
                break;
            case 9:
                break;
            default:
                cout << "Wrong choice : ";
                break;
            }
            break;

        case 2:
            AccountType = 2;
            ch2 = menu();
            switch (ch2)
            {
            case 1:
                cin >> c;
                break;
            case 2:
                c.displayAccounts();
                break;
            case 3:
                c.selectedAccount();
                break;
            case 4:
                c.deleteAccount();
                break;
            case 5:
                c.updateAccount();
                break;
            case 6:
                s.monthlystats();
                break;
            case 7:
                c.makeDeposit(setIdAmt());
                break;
            case 8:
                c.makeWithdraw(setIdAmt());
                break;
            case 9:
                break;
            default:
                cout << "Wrong choice : ";
                break;
            }
            break;
        case 3:
            exit(0);
        default:
            cout << "Wrong choice try again." << endl;
        }
    }

    return 0;
}
