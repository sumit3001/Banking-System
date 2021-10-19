#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<map>
using namespace std;

class InsufficientAmount{};

class Account
{ 
    private:
        long accountNo;
        string firstName;
        string lastName;
        float balance;
        static long acNo;
    public:
        Account(){}
        Account(string firstName,string lastName,float balance);

        string getfName(){return firstName;}
        string getlName(){return lastName;}
        int getBalance(){return balance;}
        long getaccountNo(){return accountNo;}

        void withdrawn(float amount);
        void deposit(float amount);
        static long setacNo(int no);
        friend ifstream & operator>>(ifstream &ifs, Account &acc);
        friend ofstream & operator<<(ofstream &ofs, Account &acc);
        friend ostream & operator<<(ostream &os, Account &acc);
};
long Account::acNo=0;

class Bank
{
    private:
        map<long,Account> accounts;
    public:
        Bank();
        Account openAccount(string firstName,string lastName,float balance);
        Account balanceEnquiry(long acNo);
        Account withdraw(long acNo,float amount);
        Account deposit(long acNo,float amount);
        void closeAccount(long acNo);
        void showAllAccount();
        ~Bank();
};

int main()
{
    Account acc;
    Bank b;
    int select;
    
    string firstname,lastname;
    float balance,withdrawn,deposit;
    int acNo;
    cout<<"\n*******Banking System*******\n";
    do
    { 
        cout<<"Select One Option Below\n";
        cout<<"1 Open an Account\n";
        cout<<"2 Balance Enquiry\n";
        cout<<"3 Deposit Amount\n";
        cout<<"4 Withdraw Amount\n";
        cout<<"5 Close an Account\n";
        cout<<"6 Show all Account\n";
        cout<<"7 Quit\n";
        cin>>select;
        switch (select)
        {
            case 1:
            {
                cout<<"Enter First Name: ";
                cin>>firstname;
                cout<<"Enter Last Name: ";
                cin>>lastname;
                cout<<"Enter Inial Balance: ";
                cin>>balance;
                acc=b.openAccount(firstname,lastname,balance);
                cout<<acc;
                break;
            }
            case 2:
            {
                cout<<"Enter Account Number: ";
                cin>>acNo;
                acc=b.balanceEnquiry(acNo);
                cout<<acc;
                break;
            } 
            case 3:
            {
                cout<<"Enter Account Number: ";
                cin>>acNo;
                cout<<"Enter Deposit Amount: ";
                cin>>deposit;
                acc=b.deposit(acNo,deposit);
                cout<<acc;
                break;
            }
            case 4:
            {
                cout<<"Enter Account Number: ";
                cin>>acNo;
                cout<<"Enter Widrawn Amount: ";
                cin>>withdrawn;
                acc=b.withdraw(acNo,withdrawn);
                cout<<acc;
                break;
            }
            case 5:
            {
                cout<<"Enter Account Number: ";
                cin>>acNo;
                b.closeAccount(acNo);
                break;
            }
            case 6:
            {
                b.showAllAccount();
                break;
            }
            case 7: break;
        }
    }while(select!=7);
    return 0;
}

long Account::setacNo(int no)
{
    acNo=no;
    return 0;
}

Account::Account(string firstName,string lastName,float balance)
{
    acNo++;
    accountNo=acNo;
    this->firstName=firstName;
    this->lastName=lastName;
    this->acNo=acNo;
    this->balance=balance;
}

void Account::withdrawn(float amount)
{
    if (amount<500)
        throw InsufficientAmount();
    else
        balance-=amount;
}

void Account::deposit(float amount)
{
    balance+=amount;
}

ifstream & operator>>(ifstream &ifs, Account &acc)
{
    ifs>>acc.accountNo;
    ifs>>acc.firstName;
    ifs>>acc.lastName;
    ifs>>acc.balance;
    return ifs;
}

ofstream & operator<<(ofstream &ofs, Account &acc)
{
    ofs<<acc.accountNo<<endl;
    ofs<<acc.firstName<<endl;
    ofs<<acc.lastName<<endl;
    ofs<<acc.balance<<endl;
    return ofs;
}

ostream & operator<<(ostream &os, Account &acc)
{
    os<<"Account Number: "<<acc.accountNo<<endl;
    os<<"First Name: "<<acc.firstName<<endl;
    os<<"Last Name: "<<acc.lastName<<endl;
    os<<"Balance: "<<acc.balance<<endl;
    return os;
}

Account Bank::openAccount(string firstName,string lastName,float balance)
{
    ofstream ofs;
    Account acc(firstName,lastName,balance);
    accounts.insert(pair<long,Account>(acc.getaccountNo(),acc));
    ofs.open("Bank.data",ios::trunc);
    map<long,Account>::iterator itr;
    for(itr=accounts.begin(); itr!=accounts.end(); itr++)
    {
        ofs<<itr->second;
    }
    ofs.close();
    return acc; 
}

Account Bank::balanceEnquiry(long acNo)
{
    Account a;
    map<long,Account>::iterator itr=accounts.find(acNo);
    return itr->second;
}

Account Bank::withdraw(long acNo,float amount)
{
    map<long,Account>::iterator itr=accounts.find(acNo);
    itr->second.withdrawn(amount);
    return itr->second;
}

Account Bank::deposit(long acNo,float amount)
{
    map<long,Account>::iterator itr=accounts.find(acNo);
    itr->second.deposit(amount);
    return itr->second;
}

void Bank::closeAccount(long acNo)
{
    map<long,Account>::iterator itr=accounts.find(acNo);
    cout<<"Acount Closed"<<itr->second;
    accounts.erase(acNo);
}

void Bank::showAllAccount()
{
    map<long,Account>::iterator itr;
    for(itr=accounts.begin(); itr!=accounts.end(); itr++)
        cout<<itr->second<<endl;
}

Bank::Bank()
{
    ifstream ifs;
    ifs.open("Bank.data");
    Account account;
    if(!ifs)
		return;
    while (!ifs.eof())
    {
        ifs>>account;
        accounts.insert(pair<long,Account>(account.getaccountNo(),account));
    }
    Account::setacNo(account.getaccountNo());
    ifs.close();
}

Bank::~Bank()
{
    ofstream ofs;
    ofs.open("Bank.data",ios::trunc);
    map<long,Account>::iterator itr;
    for(itr=accounts.begin(); itr!=accounts.end(); itr++)
    {
        ofs<<itr->second;
    }
    ofs.close();
}