#include <sstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <cmath>
#include <algorithm>
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
    GIVE, TAKE, PLUS
};

string labelToString(Label label) {
    switch (label) {
        case Label::GIVE: return "give";
        case Label::TAKE: return "take";
        case Label::PLUS: return "plus";
        default: return "unknown";
    }
}

class Operation {
    int id;
    string name;
    Label label;
    int value;

public:
    Operation(int id, string name, Label label, int value) : id(id), name(name), label(label), value(value) {}

    int getId() const { return id; }
    string getName() const { return name; }
    int getValue() const { return value; }
    Label getLabel() const { return label; }

    string str() const {
        stringstream ss;
        ss << "id:" << id << " " << labelToString(label) << ":" << name << " " << value;
        return ss.str();
    }
};

class Client {
    string name;
    int limite;
    list<shared_ptr<Operation>> operations;

public:
    Client(string name, int limite) : name(name), limite(limite) {}

    string getName() const { return name; }
    int getLimite() const { return limite; }

    void addOperation(shared_ptr<Operation> op) {
        operations.push_back(op);
    }

    int getBalance() const {
        int balance = 0;
        for (const auto& op : operations) {
            if (op->getLabel() == Label::GIVE || op->getLabel() == Label::PLUS)
                balance += op->getValue();
            else if (op->getLabel() == Label::TAKE)
                balance -= op->getValue();
        }
        return balance;
    }

    bool isAlive() const { return getBalance() >= -limite; }

    string str() const {
        stringstream ss;
        ss << name << " " << getBalance() << "/" << limite;
        return ss.str();
    }

    list<shared_ptr<Operation>> getOperations() const {
        return operations;
    }
};

class Agiota {
    map<string, shared_ptr<Client>> alive;
    map<string, shared_ptr<Client>> dead;
    list<shared_ptr<Operation>> operations;
    list<shared_ptr<Operation>> deadOperations;
    int nextOpId = 0;

public:
    void addClient(string name, int limite) {
        if (alive.count(name) || dead.count(name)) {
            cout << "fail: cliente ja existe\n";
            return;
        }
        alive[name] = make_shared<Client>(name, limite);
    }

    void show() const {
        stringstream ss;

        // Ordena e exibe clientes vivos
        vector<shared_ptr<Client>> clientesOrdenados;
        for (const auto& [_, client] : alive)
            clientesOrdenados.push_back(client);
        sort(clientesOrdenados.begin(), clientesOrdenados.end(),
             [](const shared_ptr<Client>& a, const shared_ptr<Client>& b) {
                 return a->getName() < b->getName();
             });
        for (const auto& cliente : clientesOrdenados)
            ss << ":) " << cliente->str() << endl;

        // Exibe operações na ordem global
        for (const auto& op : operations)
            ss << "+ " << op->str() << endl;

        // Ordena e exibe clientes mortos
        vector<shared_ptr<Client>> clientesOrdenadosMortos;
        for (const auto& [_, client] : dead)
            clientesOrdenadosMortos.push_back(client);
        sort(clientesOrdenadosMortos.begin(), clientesOrdenadosMortos.end(),
             [](const shared_ptr<Client>& a, const shared_ptr<Client>& b) {
                 return a->getName() < b->getName();
             });
        for (const auto& cliente : clientesOrdenadosMortos)
            ss << ":( " << cliente->str() << endl;

        // Exibe operações dos clientes mortos
        for (const auto& op : deadOperations)
            ss << "- " << op->str() << endl;

        cout << ss.str();
    }

    void showClient(string name) const {
        if (alive.count(name)) {
            auto client = alive.at(name);
            cout << client->str() << endl;
            for (const auto& op : client->getOperations())
                cout << op->str() << endl;
        } else if (dead.count(name)) {
            auto client = dead.at(name);
            cout << "@" << client->str() << endl;
            for (const auto& op : client->getOperations())
                cout << op->str() << endl;
        } else {
            cout << "fail: cliente nao existe\n";
        }
    }

    void give(string name, int value) {
        if (!alive.count(name)) {
            cout << "fail: cliente nao existe\n";
            return;
        }

        auto client = alive[name];
        if (client->getBalance() + value > client->getLimite()) {
            cout << "fail: limite excedido\n";
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

            operations.remove_if([&](const shared_ptr<Operation>& op) {
                if (op->getName() == name) {
                    deadOperations.push_back(op);
                    return true;
                }
                return false;
            });
        }
    }

    void kill(string name) {
        if (!alive.count(name)) {
            cout << "fail: cliente nao existe\n";
            return;
        }

        auto client = alive[name];
        dead[name] = client;
        alive.erase(name);

        operations.remove_if([&](const shared_ptr<Operation>& op) {
            if (op->getName() == name) {
                deadOperations.push_back(op);
                return true;
            }
            return false;
        });
    }

    void plus() {
        list<string> clientes;
        for (const auto& [name, _] : alive)
            clientes.push_back(name);

        for (const auto& name : clientes) {
            auto client = alive[name];
            int juros = ceil(client->getBalance() * 0.1);
            auto op = make_shared<Operation>(nextOpId++, name, Label::PLUS, juros);
            client->addOperation(op);
            operations.push_back(op);

            if (!client->isAlive()) {
                dead[name] = client;
                alive.erase(name);

                operations.remove_if([&](const shared_ptr<Operation>& op) {
                    if (op->getName() == name) {
                        deadOperations.push_back(op);
                        return true;
                    }
                    return false;
                });
            }
        }
    }
};


int main() {
    Agiota agiota;
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        } else if (cmd == "addCli") {
            string name;
            int limite;
            ss >> name >> limite;
            agiota.addClient(name, limite);
        } else if (cmd == "show") {
            agiota.show();
        } else if (cmd == "showCli") {
            string name;
            ss >> name;
            agiota.showClient(name);
        } else if (cmd == "kill") {
            string name;
            ss >> name;
            agiota.kill(name);
        } else if (cmd == "give") {
            string name;
            int value;
            ss >> name >> value;
            agiota.give(name, value);
        } else if (cmd == "take") {
            string name;
            int value;
            ss >> name >> value;
            agiota.take(name, value);
        } else if (cmd == "plus") {
            agiota.plus();
        } else {
            cout << "fail: comando invalido\n";
        }
    }
}