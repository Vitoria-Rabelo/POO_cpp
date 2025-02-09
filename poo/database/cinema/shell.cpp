#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
using namespace std;

template<class CONTAINER, class FUNC>
string map_join(const CONTAINER& c, FUNC f, string sep) {
    stringstream ss;
    for (auto it = c.begin(); it != c.end(); it++) {
        ss << (it == c.begin() ? "" : sep);
        ss << f(*it);
    }
    return ss.str();
}

class Client{
    private:
        string id;
        int phone;
    
    public:
        Client(string id = "-", int phone = 0) : id(id), phone(phone){}

        string getId(){
            return id;
        }

        int getPhone(){
            return phone;
        }

        void setId(string newId){
            this->id = newId;
        }

        void setPhone(int newPhone){
            this->phone = newPhone;
        }

        string str() const{
            stringstream ss;
            ss << this->id << ":" << this->phone ;
            return ss.str();
        }
};

class Theater{
    private:
        vector<shared_ptr<Client>> seats;

    public:
        Theater(int index) {
            seats = vector<shared_ptr<Client>>(index, nullptr);
        };

        

        void reserve(string id, int phone, int index){
            if(index < 0 || index >= (int)seats.size()){
                cout << "fail: cadeira nao existe\n";
                return;
            }
            if(seats[index] != nullptr){
                cout << "fail: cadeira ja esta ocupada\n";
                return;
            }
            for (auto& seat : seats) {
                if (seat && seat->getId() == id) {
                    cout << "fail: cliente ja esta no cinema\n";
                    return;
                }
            }
            seats[index] = make_shared<Client>(id, phone);
        }

        void cancel(string id){
            for (auto& seat : seats) {
                if (seat && seat->getId() == id) {
                    seat = nullptr;
                    return;
                }
            }
            cout << "fail: cliente nao esta no cinema\n";
        }

        void show(){
            if (seats.empty()) {
                cout << "[]" << endl;
                return;
            }
            cout << "[" << map_join(seats, [](shared_ptr<Client> c) {
                return c ? c->str() : "-";
            }, " ") << "]" << endl;
        }

        
};

int main() {
    Theater theater(0);
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;    
        } else if (cmd == "show") {
            theater.show();
        } else if (cmd == "init") {
            int qtd;
            ss >> qtd;
            theater = Theater(qtd);
        } else if (cmd == "reserve") {
            string id;
            int phone = 0;
            int index = 0;
            ss >> id >> phone >> index;
            theater.reserve(id, phone, index);
        } else if (cmd == "cancel") {
            string id;
            ss >> id;
            theater.cancel(id);
        } else {
            cout << "fail: comando invalido" << endl;
        }
    }
}
