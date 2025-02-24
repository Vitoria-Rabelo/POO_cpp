#include <iostream>
#include <memory>
#include <sstream>
#include <list>
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

class Kid{
    int age;
    string name;

public:
    Kid(string name, int age) : name(name), age(age){}

    string getName() const {
        return name;
    }
    int getAge(){
        return age;
    }
    string str()  {
        stringstream ss;
        ss << name << ":" << age;
        return ss.str();
    }

};

class Trampoline{
    list<Kid> playing;
    list<Kid>  waiting;

public:
    Trampoline() {};

    void arrive(Kid kid){       
        waiting.push_back(kid);
    }

    void enter(){
        if(waiting.size() > 0){
            playing.push_back(waiting.front());
            waiting.pop_front();
        }
    }

};

int main() {

    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        } else if (cmd == "show") {
        } else if (cmd == "arrive") {
            // string name;
            // int age;
            // ss >> name >> age;
        } else if (cmd == "enter") {
        } else if (cmd == "leave") {
        } else if (cmd == "remove") {
            // string name;
            // ss >> name;
        } else {
            cout << "fail: comando invalido" << endl;
        }
    }
}
