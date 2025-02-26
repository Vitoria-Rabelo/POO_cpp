#include <iostream>
#include <vector>
#include <sstream>
#include <utility>
#include <iomanip>
#include <memory>
#include <list>
using namespace std;

template <typename CONTAINER, typename FN>
string map_join(const CONTAINER& container, FN fn, string sep = ", ", string prefix = "[", string suffix = "]") {
    stringstream ss;
    for (auto it = container.begin(); it != container.end(); ++it) {
        ss << (it != container.begin() ? sep : "") << fn(*it);
    }
    return prefix + ss.str() + suffix;
}

enum class Moeda{
    C5, C10, C25, C50, R1
};

Moeda stringToMoeda(const string& label) {
    if (label == "C5") return Moeda::C5;
    if (label == "C10") return Moeda::C10;
    if (label == "C25") return Moeda::C25;
    if (label == "C50") return Moeda::C50;
    if (label == "R1") return Moeda::R1;
    throw invalid_argument("fail: moeda inválida");
}

class Coin{
    Moeda moeda;
    int volume;
    string label;

    static float getMoeda(Moeda moeda){
        switch(moeda){
            case Moeda::C5: return 0.05;
            case Moeda::C10: return 0.10;
            case Moeda::C25: return 0.25;
            case Moeda::C50: return 0.50;
            case Moeda::R1: return 1.00;
            default : 
                return 0.0;
        }
    }
    
public:
    Coin(Moeda moeda, int volume = 0, string label = "") : moeda(moeda), volume(volume), label(label) {}

    double getValue() const{
       return getMoeda(moeda);
    }

    int getVolume(){
        return this->volume;
    }

    string getLabel() const{
        return this->label;
    }
};

class Item {
    string label;
    int volume;
public:
    Item(string label = "", int volume = 0) : label(label), volume(volume) {}

    string getLabel() const{ 
        return label;
     }
    int getVolume() const{ 
        return volume; 
    }

    void setLabel(string label){
        this->label = label;
    }

    void setVolume(int volume){
        this->volume = volume;
    }

    string toString() const{
        stringstream ss;
        ss << label << ":" << volume;
        return ss.str();
    }
};
class Pig{
    bool broken;
    list<Coin> coins;
    list<Item> items;
    int volumeMax;

public:
    Pig(int volumeMax = 0) : broken(false), volumeMax(volumeMax){};

    void addCoin(Coin coin){
        coins.push_back(coin);
    }

    void addItem(Item item){
        items.push_back(item);
    }

    void breakPig(){
        broken = true;
    }

    void show() const{
        if(broken == true){
            cout << "state=broken ";
        } 
        cout << "state=intact ";
        cout << ": coins=" << map_join(coins, [](const Coin& coin){return coin.getLabel();});
        cout <<  " : items=" << map_join(items, [](const Item& item){return item.toString();}) ;
        cout << " : value=";
        cout << volumeMax << endl;
    }
};
int main() {
    Pig pig;
    Coin c(Moeda::C50, 1, "50 centavos");;
    Item item;
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        } else if (cmd == "init") {
         int volumeMax;
         ss >> volumeMax;
         pig = Pig(volumeMax);
        } else if (cmd == "show") {
            pig.show();
        } else if (cmd == "break") {
        } else if (cmd == "addCoin") {
            string label;
             ss >> label;
             try {
                Moeda moeda = stringToMoeda(label);
                pig.addCoin(Coin(moeda, 0, label));
            } catch (const exception& e) {
                cout << e.what() << endl;
            }
        } else if (cmd == "addItem") {
            // string label;
            // int volume;
            // ss >> label >> volume;
        } else if (cmd == "extractItems") {
            // Obtenha os itens com o método extractItems
            // e imprima os itens obtidos
        } else if (cmd == "extractCoins") {
            // Obtenha as moedas com o método extractCoins
            // e imprima as moedas obtidas
        } else {
            cout << "fail: invalid command\n";
        }
    }
}
