#include <iostream>
#include <cassert>
#include <windows.h>

using namespace std;

class bankAccount{
private:
    string accountNum;
    string name;
    double balance;
public:
    bankAccount(string n,string num,double bala){
        setName(n);
        setAccountNum(num);
        setBalance(bala);
    }
    void setName(string n){
        name = n;
    }
    void setAccountNum(string num){
        accountNum = num;
    }
    void setBalance(double bala){
        balance = bala;
    }
    string getAccountNum(){
        return accountNum;
    }
    string getName(){
        return name;
    }
    double getBalance(){
        return balance;
    }
    virtual void makeDeposits(int dep) = 0;
    virtual void withdrawMoney(int withdraw) = 0;
    virtual void monthlyStatement() = 0;
};

class checkingAcount : public bankAccount{
public:
    checkingAcount(string n,string num,double bala) : bankAccount(n,num,bala) {

    }
    virtual void writeChek(int m) = 0;

};

class serviceChargeChecking : public checkingAcount{
private:
    int limitNumberOfChecks;
public:
    serviceChargeChecking(string n,string num,double bala,int limits) : checkingAcount(n,num,bala){
        setLimitNumberOfChecks(limits);
    }
    void setLimitNumberOfChecks(int l){
        limitNumberOfChecks = l;
    }
    int getLimitNumberOfChecks(){
        return limitNumberOfChecks;
    }
    void makeDeposits(int dep){
        setBalance(getBalance() + dep);
    }
    void withdrawMoney (int withdraw){
        if(withdraw <= getBalance()){
            setBalance(getBalance() - withdraw);
        }
        else {
            assert(false);
        }
    }
    void monthlyStatement () {
        cout << "************************\n";
        cout << "Your name : " << getName() << endl;
        cout << "Account number : " << getAccountNum() << endl;
        cout << "Your balance : " << getBalance() << endl;
        cout << "The remaining checks that you can write is : " << getLimitNumberOfChecks() << endl;
        cout << "*************************\n";
    }
    void writeChek(int money){
        if(money <= getBalance() and getLimitNumberOfChecks() > 0){
            setBalance(getBalance() - money);
            setLimitNumberOfChecks(limitNumberOfChecks - 1);
        }
        else {
            assert(false);
        }
    }
};

class noServiceChargeChecking : public checkingAcount{
private:
    double interest;
    int minimumBalance;
public:
    noServiceChargeChecking(string n,string num,double bala,double in,int m) : checkingAcount(n,num,bala){
        setInterest(in);
        setMinimumBalance(m);
    }
    void setInterest(double in){
        interest = in;
    }
    void setMinimumBalance(int m){
        minimumBalance = m;
    }
    double getInterest(){
        return interest;
    }
    int getMinimumBalance(){
        return minimumBalance;
    }
    void makeDeposits(int dep){
        setBalance(getBalance() + dep);
    }
    void withdrawMoney (int withdraw){
        if(getBalance() - withdraw >= minimumBalance){
            setBalance(getBalance() - withdraw);
        }
        else {
            assert(false);
        }
    }
    void monthlyStatement () {
        cout << "************************\n";
        cout << "Your name : " << getName() << endl;
        cout << "Account number : " << getAccountNum() << endl;
        cout << "Your balance : " << getBalance() << endl;
        cout << "Interest : " << getInterest() << endl;
        cout << "*************************\n";

    }
    void writeChek(int money){
        if(getBalance() - money >= minimumBalance){
            setBalance(getBalance() - money);
            int Interest = interest * money;
            setBalance(getBalance() + Interest);
        }
        else {
            assert(false);
        }
    }
};

class highInterestChecking : public noServiceChargeChecking{
public:
    highInterestChecking(string n,string num,double bala,double in,int mini) : noServiceChargeChecking(n,num,bala,in,mini){

    }
};

class savingAcount : public bankAccount{
private:
    double interest;
public:
    savingAcount(string n,string num,double bala,double in) : bankAccount(n,num,bala){
        interest = in;
    }
    void setInterest(double in){
        interest = in;
    }
    double getInterest(){
        return interest;
    }
    void makeDeposits(int dep){
        int X = dep * getInterest();
        setBalance(getBalance() + X + dep)  ;
    }
    void withdrawMoney(int withdraw){
        if(getBalance() >= withdraw){
            setBalance(getBalance() - withdraw);
        }
        else {
            assert(false);
        }
    }
    void monthlyStatement(){
        cout << "************************\n";
        cout << "Your name : " << getName() << endl;
        cout << "Account number : " << getAccountNum() << endl;
        cout << "Your balance : " << getBalance() << endl;
        cout << "Interest : " << getInterest() << endl;
        cout << "*************************\n";
    }

};

class hightInterestSavings : public savingAcount{
public:
    hightInterestSavings(string n,string num,double bala,double in) : savingAcount(n,num,bala,in){

    }
};

class certificateOfDeposit : public bankAccount{
private:
    int numberOfMonths;
    double interestRate;
    int currentCDMonth;
    int balance2;
public:
    certificateOfDeposit(string n,string num,double bala,int numOFmaturity,double in,int currCDMonth) : bankAccount(n,num,bala){
        setNumberOfMonths(numOFmaturity);
        setInterestRate(in);
        setCurretnCDMonth(currCDMonth);
        balance2 = bala;
    }

    void makeDeposits(int dep = 0){
        assert(false);
    }
    void withdrawMoney (int withdraw  = 0){
        setBalance(0);
    }
    double AmountOfMoney(){
        if(numberOfMonths == currentCDMonth){
            double res = balance2;
            for(int  i = 0;i < numberOfMonths;i++){
                res += interestRate * res;
            }
            return res;
        }
        else if(currentCDMonth < numberOfMonths){
            return (getBalance() - (interestRate * getBalance()));
        }
    }
    void monthlyStatement(){
        cout << "****************************************\n";
        cout << "Your name : " << getName() << endl;
        cout << "Account number : " << getAccountNum() << endl;
        getCurretnAmountOfMoney();
        cout << "Your balance : " << getBalance() << endl;
        cout << "The number of CD maturity months : " << numberOfMonths << endl;
        cout << "The current CD month : " << currentCDMonth << endl;
        cout << "The money that you withdraw it : " << AmountOfMoney() << endl;
        cout << "****************************************\n";
    }
    void setNumberOfMonths(int m){
        numberOfMonths = m;
    }
    void setInterestRate(double r){
        interestRate = r;
    }
    void setCurretnCDMonth(int m){
        currentCDMonth = m;
    }
    int getNumberOfMonths(){
        return numberOfMonths;
    }
    double getInterestRate(){
        return interestRate ;
    }
    int getCurretnCDMonth(){
        return currentCDMonth;
    }
    void getCurretnAmountOfMoney(){
        double res = balance2;
        for(int  i = 0;i < currentCDMonth;i++){
            res += interestRate * res;
        }
        setBalance(res);
    }
};

void account(){
    cout << "*******************\n";
    cout << "Types of accounts : " << endl;
    cout << "1. Checking account." << endl;
    cout << "2. Saving account." << endl;
    cout << "3. Certificate of deposit." << endl;
    cout << "*******************\n";
}

void check(){
    cout << "*******************\n";
    cout << "Types of Checking accoutn : " << endl;
    cout << "1. Service charge." << endl;
    cout << "2. No service charge." << endl;
    cout << "*******************\n";
}

void noService(){
    cout << "*******************\n";
    cout << "Types of No service checking account : " << endl;
    cout << "1. Normal interest." << endl;
    cout << "2. high interest." << endl;
    cout << "*******************\n";
}

void saving(){
    cout << "*******************\n";
    cout << "Types of saving account : " << endl;
    cout << "1. Normal interest." << endl;
    cout << "2. high interest." << endl;
    cout << "*******************\n";
}

int main(){
    int x;
    account();
    cin >> x;
    system("cls");
    if(x == 1){
        check();
        int c;
        cin >> c;
        system("cls");
        if(c == 1){
            serviceChargeChecking per("Sarat" , "22311322" , 4000, 3);
            per.makeDeposits(1000);
            per.withdrawMoney(1500);
            per.writeChek(1200);
            per.monthlyStatement();
        }
        else if(c == 2){
            noService();
            int b;
            cin >> b;
            system("cls");
            if(b == 1){
                noServiceChargeChecking per("Sarat" , "22311322" , 4000, .05,2000);
                per.makeDeposits(1000);
                per.withdrawMoney(1500);
                per.writeChek(1200);
                per.monthlyStatement();
            }
            else if(b == 2){
                highInterestChecking per("Sarat" , "22311322" , 5000, .1,3000);
                per.makeDeposits(1000);
                per.withdrawMoney(1500);
                per.writeChek(1200);
                per.monthlyStatement();
            }
        }
        else assert(false);
    }
    else if(x == 2){
        saving();
        int d;
        cin >> d;
        system("cls");
        if(d == 1){
            savingAcount per("Sarat", "22311322", 4000, .05);
            per.makeDeposits(500);
            per.monthlyStatement();
        }
        if(d == 2){
            hightInterestSavings per("Sarat", "22311322", 4000, .1);
            per.makeDeposits(500);
            per.monthlyStatement();
        }
    }
    else if(x == 3){
        certificateOfDeposit per("Sarat" , "22311322" , 5000, 5 ,.05, 4);
        per.monthlyStatement();

    }
    else assert(false);
    return 0;
}
