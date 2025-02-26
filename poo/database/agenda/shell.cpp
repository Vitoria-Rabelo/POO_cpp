#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

template <typename CONTAINER, typename FUNC>
string map_join(const CONTAINER& cont, FUNC func, string sep = " ") {
    stringstream ss;
    for (auto it = cont.begin(); it != cont.end(); it++) {
        ss << (it == cont.begin() ? "" : sep);
        ss << func(*it);
    }
    return ss.str();
}

pair<string, string> decodeFone(string fone) {
    stringstream ss(fone);
    string id, number;
    getline(ss, id, ':');
    getline(ss, number);
    return {id, number};
}

class Fone {
    string id;
    string number;
public:
    Fone(string id = "", string number = "") : id(id), number(number) {}

    string getId() { return id; }
    string getNumber() { return number; }

    bool isValid() {
        string validos = "0123456789().-";
        for (char c : number) {
            if (validos.find(c) == string::npos) {
                cout << "fail: invalid number" << endl;
                return false;
            }
        }
        return true;
    }

    string toString() { return id + ":" + number; }
};

class Contact {
    string name;
    bool favorited;
    vector<Fone> fones;
public:
    Contact(string name = "") : name(name), favorited(false) {}

    string getName() { return name; }
    void setName(string name) { this->name = name; }
    bool isFavorited() { return favorited; }
    void toggleFavorited() { favorited = !favorited; }
    vector<Fone> getFones() { return fones; }

    void addFone(string id, string number) {
        Fone fone(id, number);
        if (fone.isValid()) {
            fones.push_back(fone);
        }
    }

    void rmFone(int index) {
        if (index >= 0 && index < (int)fones.size()) {
            fones.erase(fones.begin() + index);
        }
    }

    string toString() {
        stringstream ss;
        ss << (favorited ? "@ " : "- ") << name << " [" 
           << map_join(fones, [](Fone f) { return f.toString(); }, ", ") << "]";
        return ss.str();
    }
};

class Agenda {
    vector<Contact> contacts;

    int findPosByName(string name) {
        for (size_t i = 0; i < contacts.size(); i++) {
            if (contacts[i].getName() == name)
                return i;
        }
        return -1;
    }

public:
    void addContact(string name, vector<Fone> fones) {
        int pos = findPosByName(name);
        if (pos != -1) {
            for (auto& f : fones) {
                contacts[pos].addFone(f.getId(), f.getNumber());
            }
        } else {
            Contact contact(name);
            for (auto& f : fones) {
                contact.addFone(f.getId(), f.getNumber());
            }
            contacts.push_back(contact);
            sort(contacts.begin(), contacts.end(), [](Contact a, Contact b) {
                return a.getName() < b.getName();
            });
        }
    }

    Contact* getContact(string name) {
        int pos = findPosByName(name);
        if (pos != -1) return &contacts[pos];
        return nullptr;
    }

    void rmContact(string name) {
        int pos = findPosByName(name);
        if (pos != -1) {
            contacts.erase(contacts.begin() + pos);
        }
    }

    vector<Contact> search(string pattern) {
        vector<Contact> result;
        for (auto& c : contacts) {
            if (c.toString().find(pattern) != string::npos) {
                result.push_back(c);
            }
        }
        return result;
    }

    vector<Contact> getFavorited() {
        vector<Contact> result;
        for (auto& c : contacts) {
            if (c.isFavorited()) {
                result.push_back(c);
            }
        }
        return result;
    }

    vector<Contact> getContacts() { return contacts; }

    string toString() {
        return map_join(contacts, [](Contact c) { return c.toString(); }, "\n");
    }
};

int main() {
    Agenda agenda;
    string line, cmd;
    while (true) {
        getline(cin, line);
        cout << "$" << line << endl;
        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        } else if (cmd == "add") {
            string name, token;
            ss >> name;
            vector<Fone> fones;
            while (ss >> token) {
                auto [id, number] = decodeFone(token);
                fones.push_back(Fone(id, number));
            }
            agenda.addContact(name, fones);
        } else if (cmd == "show") {
            cout << agenda.toString() << endl;
        } else if (cmd == "rmFone") {
            string name;
            int index;
            ss >> name >> index;
            Contact* contact = agenda.getContact(name);
            if (contact) {
                contact->rmFone(index);
            }
        }else if ( cmd == "rm"){
            string name;
            ss >> name;
            agenda.rmContact(name);
        } else if (cmd == "search") {
            string pattern;
            ss >> pattern;
            cout << map_join(agenda.search(pattern), [](Contact c) { return c.toString(); }, "\n") << endl;
        } else if (cmd == "tfav") {
            string name;
            ss >> name;
            Contact* contact = agenda.getContact(name);
            if (contact) {
                contact->toggleFavorited();
            }
        } else if (cmd == "showFav") {
            cout << map_join(agenda.getFavorited(), [](Contact c) { return c.toString(); }, "\n") << endl;

        }else if (cmd == "favs") {
            vector<Contact> favs = agenda.getFavorited();
            cout << map_join(favs, [](Contact c) { return c.toString(); }, "\n") << endl;
        }
        else {
            cout << "fail: comando invalido" << endl;
        }
    }
}
