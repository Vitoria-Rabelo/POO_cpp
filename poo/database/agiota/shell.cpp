#include <sstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
using namespace std;

template <typename CONTAINER, typename FN>
string map_join(const CONTAINER& container, FN fn, string sep = ", ") {
    stringstream ss;
    for (auto it = container.begin(); it != container.end(); ++it) {
        ss << (it != container.begin() ? sep : "") << fn(*it);
    }
    return ss.str();
}

enum class Label {
    GIVE , TAKE, PLUS
};

string labelToString(Label label){
    switch (label){
    case Label::GIVE: return "give";
    case Label::PLUS: return "plus";
    case Label::TAKE: return "take";
    }
}

class Operation{
    int id;
    string name;
    Label label;
    int value;

 public:

    Operation(int id, string name, Label label, int value): id(id), name(name), 
    label(label), value(value){}

    int getId(){
        return id;
    }

    string getName(){
        return name;
    }

    int getValue(){
        return value;
    }

    Label getLabel(){
        return label;
    }

    string str(){
        stringstream ss;

        ss << "id:" << this->id << " " << labelToString(label) << ":" << this->name << " " 
        << this->value;
        return ss.str();
    }

};

class Client{
    string name;
    int limite;
    list<shared_ptr<Operation>> operations;
 public:

    Client(string name, int limite): name(name), limite(limite){}
    
    string getName(){
        return name;
    }

    int getLimite(){
        return limite;
    }

    
    void addOperation(shared_ptr<Operation> op){
         operations.push_back(op);
    }

    int getBalance() const {
        int balance = 0;
        for (const auto& op : operations) {
            if (op->getLabel() == Label::GIVE) {
                balance += op->getValue();
            } else {
                balance -= op->getValue();
            }
        }
        return balance;
    }
    

    bool isAlive() const{
        return getBalance() >= -limite;
    }

    string str() const{
        stringstream ss;
        ss << name << " " <<getBalance() << "/" << this->limite <<  " [" << map_join(operations, [](shared_ptr<Operation> op) { return op->str(); }) << "]";
        return ss.str();
    }
};

class Agiota{
    map<string, shared_ptr<Client>> alive;
    map<string, shared_ptr<Client>> dead;
    list<shared_ptr<Operation>> operations;
    int nextOpId = 0;

 public:
    void addClient(string name, int limite) {
        if (alive.count(name) || dead.count(name)) {
            cout << "fail: cliente ja existe\n";
            return;
        }
        alive[name] = make_shared<Client>(name, limite);
    }

    void show() {
        for (auto& [name, client] : alive) {
            cout << ":) " << client->getName() << " " << client->getBalance() << "/" << client->getLimite() << endl;
        }
        for (auto& op : operations) {
            cout << "+ " << op->str() << endl;
        }
    }
    
    

    void showClient(string name) {
        if (alive.count(name)) {
            auto client = alive[name];
            cout << client->getName() << " " << client->getBalance() << "/" << client->getLimite() << endl;
        } else if (dead.count(name)) {
            auto client = dead[name];
            cout << "@" << client->getName() << " " << client->getBalance() << "/" << client->getLimite() << endl;
        } else {
            cout << "fail: cliente nao existe\n";
        }
    }
    

    void give(string name, int value) {
        if (alive.find(name) == alive.end()) {
            cout << "fail: cliente nao existe" << endl;
            return;
        }
        
        auto client = alive[name];
        
        if (client->getBalance() + value > client->getLimite()) {
            cout << "fail: limite excedido" << endl;
            return;
        }
    
        auto op = make_shared<Operation>(nextOpId++, name, Label::GIVE, value);
        client->addOperation(op);
        operations.push_back(op);
    }

    void take(string name, int value) {
        if (!alive.count(name)) {
            cout << "fail: cliente nao existe\n";
            return;
        }
        auto op = make_shared<Operation>(nextOpId++, name, Label::TAKE, value);
        operations.push_back(op);
        alive[name]->addOperation(op);

        if (!alive[name]->isAlive()) {
            dead[name] = alive[name];
            alive.erase(name);
        }
    }

    void kill(string name) {
        if (!alive.count(name)) {
            cout << "fail: cliente nao existe\n";
            return;
        }
        dead[name] = alive[name];
        alive.erase(name);
    }
};

int main() {
    Agiota agiota;
    while(true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if(cmd == "end") {
            break;
        }
        else if(cmd == "addCli") {
             string name;
            int limite {};
            ss >> name >> limite;
            agiota.addClient(name, limite);
        }
        else if(cmd == "show") {
            agiota.show();
        }
        else if(cmd == "showCli") {
            string name;
            ss >> name;
            agiota.showClient(name);
        }
        else if(cmd == "kill") {
            string name;
            ss >> name;
            agiota.kill(name);
        }
        else if(cmd == "give") {
            string name;
            int value;
            ss >> name >> value;
            agiota.give(name, value);
        }
        else if(cmd == "take") {
            string name;
            int value;
            ss >> name >> value;
            agiota.take(name, value);
        }
        else if(cmd == "plus") {
        }
        else {
            cout << "fail: comando invalido\n";
        }
    }
}
