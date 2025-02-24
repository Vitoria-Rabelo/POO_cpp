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

class Kid {
    string name;
    int age;

public:
    Kid(string name, int age) : name(name), age(age) {}

    string getName() const {
        return name;
    }
    
    int getAge() const {
        return age;
    }

    string str() const {
        stringstream ss;
        ss << name << ":" << age;
        return ss.str();
    }
};

class Trampoline {
    list<Kid> playing;
    list<Kid> waiting;

public:
    Trampoline() {}

    void arrive(Kid kid) {       
        waiting.push_front(kid);
    }

    void enter() {
        if (!waiting.empty()) {
            playing.push_back(waiting.back());
            waiting.pop_back();
        }
    }
    

    void leave() {
        if (!playing.empty()) {
            playing.pop_front();
        }
    }

    void show() {
        cout << "["
             << map_join(waiting, [](const Kid& kid) { return kid.str(); }, ", ")
             << "] => ["
             << map_join(playing, [](const Kid& kid) { return kid.str(); }, ", ")
             << "]"
             << endl;
    }
};

int main() {
    Trampoline trampoline;

    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        } else if (cmd == "show") {
            trampoline.show();
        } else if (cmd == "arrive") {
            string name;
            int age;
            ss >> name >> age;
            trampoline.arrive(Kid(name, age));
        } else if (cmd == "enter") {
            trampoline.enter();
        } else if (cmd == "leave") {
            trampoline.leave();
        } else {
            cout << "fail: comando invalido" << endl;
        }
    }
}
