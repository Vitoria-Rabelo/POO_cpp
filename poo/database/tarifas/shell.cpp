#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <list>
using namespace std;

template<typename CONTAINER, typename FUNC>
string join(const CONTAINER& cont, FUNC func, const string& delim) {
    stringstream ss;
    for (auto it = cont.begin(); it != cont.end(); it++) {
        ss << (it == cont.begin() ? "" : delim) << func(*it);
    }
    return ss.str();
}


enum Label{
    DEPOSIT,
    FEE,
    OPENING,
    REVERSE,
    WITHDRAW,
    ERROR
};

class Operation{
    int index;
    Label label;
    int value;
    int balance;

public:
    Operation(int index, Label label, int value, int balance) : index(index), label(label), value(value), balance(balance){};

    int getIndex(){
        return index;
    }

    Label getLabel(){
        return label;
    }

    int getValue(){
        return value;
    }

    int getBalance(){
        return balance;
    }

    string str() const{
        stringstream ss;
        ss << index << ":";
        switch(label){
            case DEPOSIT:
                ss << "deposit:" << value;
                break;
            case FEE:
                ss << "fee:" << value;
                break;
            case OPENING:
                ss << "opening:" << value;
                break;
            case REVERSE:
                ss << "reverse:" << value;
                break;
            case WITHDRAW:
                ss << "withdraw:" << value;
                break;
            case ERROR:
                ss << "error:" << value;
                break;
        }
        return ss.str();
    }

};

class BalanceManager{
    int balance;
    int nextId;
    list<Operation> extract;

    public:
        BalanceManager(int balance = 0): balance(0), nextId(0){ addOperation(OPENING, balance);}
        
        int getBalance(){
            return balance;
        }
        void addOperation(Label label, int value){
            if(label == DEPOSIT){
                balance += value;
            }
            if(label == WITHDRAW){
                balance -= value;
            }
            if(label == FEE){
                balance -= value;
            }
            Operation op(nextId++, label, value, balance);
            extract.push_back(op);
        }

        void getOperation(int index){
            for(auto& op : extract){
                if(op.getIndex() == index){
                    cout << op.str() << endl;
                    return;
                }
            }
            cout << "fail: indice invalido" << endl;
        }

        void show() const{
            cout << "balance:" << balance << endl;
        }
};

class Account{
    int id;
    BalanceManager balanceManager;

    public:
        Account(int id = 0, int initBalance = 0): id(id){
            balanceManager = BalanceManager(initBalance);
        };

        void deposit(int value){
            if(value < 0){
                cout << "fail: invalid value" << endl;
                return;
            }
            balanceManager.addOperation(DEPOSIT, value);
        }

        void withdraw(int value){
            if(value > balanceManager.getBalance()){
                cout << "fail: insufficient balance" << endl;
                return;
            }
            balanceManager.addOperation(WITHDRAW, value);
        }

        void fee(int value){
            balanceManager.addOperation(FEE , value);
        }
        
        void extract(int qtd){
            
        }

        void show() const{
            cout << "account:" << id << " ";
             balanceManager.show();
            return;
        }

};

int main() {        
    Account account(0); 
    BalanceManager balanceManager(0);   
    while(true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        
        if (cmd == "end") {
            break;
        }
        else if (cmd == "init") {
            int number{};
            ss >> number;
            account = Account(number);
            
        }
        else if (cmd == "show") {
            account.show();
        }
        else if (cmd == "deposit") {
            float value{};
            ss >> value;
            account.deposit(value);
        }
        else if (cmd == "withdraw") {
            float value{};
            ss >> value;
            account.withdraw(value);
        }
        else if (cmd == "fee") {
            float value{};
            ss >> value;
            account.fee(value);
        }
        else if (cmd == "extract") {
            int qtd{};
            ss >> qtd;
            account.extract(qtd);
        }
        else if (cmd == "reverse") {
            // int index{};
            // while(ss >> index) {
            // }
        }
        else {
            cout << "fail: invalid command\n";
        }
    }
    return 0;
}
