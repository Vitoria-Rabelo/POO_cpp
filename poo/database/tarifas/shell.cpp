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

enum Label {
    DEPOSIT,
    FEE,
    OPENING,
    REVERSE,
    WITHDRAW,
    ERROR
};

class Operation {
    int index;
    Label label;
    int value;
    int balance;

public:
    Operation(int index, Label label, int value, int balance) 
        : index(index), label(label), value(value), balance(balance) {};

    int getIndex() const {
        return index;
    }

    Label getLabel() const {
        return label;
    }

    int getValue() const {
        return value;
    }

    int getBalance() const {
        return balance;
    }

    string str() const {
        stringstream ss;
        ss << setw(2) << index << ": ";
        switch (label) {
            case DEPOSIT:
                ss << " deposit:" << setw(5) << value;
                break;
            case FEE: 
                if(value > 9) {
                    ss << "     fee:" << setw(3) << "-" << value;
                } else
                ss << "     fee:" << setw(4) << "-" << value;
                break;
            case OPENING: 
                ss << " opening:" << setw(5) << value;
                break;
            case REVERSE: 
                ss << " reverse:" << setw(5) << value; 
                break;
            case WITHDRAW: 
                ss << "withdraw:" << setw(3) << "-" << value ; 
                break;
            case ERROR: 
                ss << "   error:" << setw(5) << value; 
                break;
        }


        ss << ": " << setw(4) << balance;
        return ss.str();
    }
};

class BalanceManager {
    int balance;
    int nextId;
    list<Operation> extract;

public:
    BalanceManager(int balance = 0) : balance(balance), nextId(0) {
        addOperation(OPENING, balance);
    }

    int getBalance() const {
        return balance;
    }

    void addOperation(Label label, int value) {
        if (label == DEPOSIT) {
            balance += value;
        } else if (label == WITHDRAW || label == FEE) {
            balance -= value;
        } else if(label == REVERSE){
            balance += value;
        }
        Operation op(nextId++, label, value, balance);
        extract.push_back(op);
    }

    void extractBalance(int qtd) const {
        int count = 0;
        if(qtd == 0){
            for (const auto& op : extract) {
                if (count >= qtd && qtd != 0) break;
                cout << op.str() << endl; 
                count++;
            }
        }
        else{
            vector<Operation> lastOps;
        size_t limit = static_cast<size_t>(qtd); 

        for (auto rit = extract.rbegin(); rit != extract.rend() && lastOps.size() < limit; ++rit) {
            lastOps.push_back(*rit);
        }
        for (auto it = lastOps.rbegin(); it != lastOps.rend(); ++it) {
            cout << it->str() << endl;
        }
        }
        
    }

    const list<Operation>& getExtract() const {
        return extract;
    }

    void show() const {
        cout << "balance:" << balance << endl;
    }
};

class Account {
    int id;
    BalanceManager balanceManager;

public:
    Account(int id = 0, int initBalance = 0) : id(id), balanceManager(initBalance) {}

    void deposit(int value) {
        if (value < 0) {
            cout << "fail: invalid value" << endl;
            return;
        }
        balanceManager.addOperation(DEPOSIT, value);
    }

    void withdraw(int value) {
        if (value > balanceManager.getBalance()) {
            cout << "fail: insufficient balance" << endl;
            return;
        }
        balanceManager.addOperation(WITHDRAW, value);
    }

    void fee(int value) {
        balanceManager.addOperation(FEE, value);
    }

    void extract(int qtd) {
        balanceManager.extractBalance(qtd);
    }

    void reverse(const vector<int>& values) {
        const list<Operation>& operations = balanceManager.getExtract();
    
        for (int value : values) {
            auto it = operations.end();
            while (it != operations.begin()) {
                --it; 
                if (it->getIndex() == value) {
                    if (it->getLabel() != FEE) {
                        cout << "fail: index " << value << " is not a fee" << endl;
                    } else {
                        balanceManager.addOperation(REVERSE, it->getValue());
                        balanceManager.addOperation(DEPOSIT, it->getValue());
                    }
                    goto next_value;
                }
            }
            cout << "fail: index " << value << " invalid" << endl;
        next_value:;
        }
    }

    void show() const {
        cout << "account:" << id << " ";
        balanceManager.show();
    }
};

int main() {
    Account account(0);
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        } else if (cmd == "init") {
            int number;
            ss >> number;
            account = Account(number);
        } else if (cmd == "show") {
            account.show();
        } else if (cmd == "deposit") {
            int value;
            ss >> value;
            account.deposit(value);
        } else if (cmd == "withdraw") {
            int value;
            ss >> value;
            account.withdraw(value);
        } else if (cmd == "fee") {
            int value;
            ss >> value;
            account.fee(value);
        } else if (cmd == "extract") {
            int qtd;
            ss >> qtd;
            account.extract(qtd);
        } else if(cmd == "reverse"){
            vector<int> values;
            int value;
            while (ss >> value) { 
                values.push_back(value);
            }
            account.reverse(values);
        }else {
            cout << "fail: invalid command\n";
        }
    }
    return 0;
}