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
    C10 = 1,
    C25 = 2, 
    C50 = 3, 
    R1 = 4

};

Moeda stringToMoeda(const string& label) {
    if (label == "10") return Moeda::C10;
    if (label == "25") return Moeda::C25;
    if (label == "50") return Moeda::C50;
    if (label == "100") return Moeda::R1;
    throw invalid_argument("fail: moeda inválida");
}

class Coin{
    Moeda moeda;
    int volume;
    string label;

    static float getMoeda(Moeda moeda){
        switch(moeda){
            case Moeda::C10: return 0.10;
            case Moeda::C25: return 0.25;
            case Moeda::C50: return 0.50;
            case Moeda::R1: return 1.00;
            default : 
                return 0.0;
        }
    }
    
public:
    Coin(Moeda moeda, int volume, string label = "") : moeda(moeda), volume(volume), label(label) {}

    double getValue() const{
       return getMoeda(moeda);
    }

    int getVolume() const{
        return this->volume;
    }

    static int getVolume(Moeda moeda) {
        switch(moeda) {
            case Moeda::C10: return 1;
            case Moeda::C25: return 2;
            case Moeda::C50: return 3;
            case Moeda::R1: return 4;
            default: return 0;
        }
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

    int getTotalVolume() const {
        int totalVolume = 0;
        for(const auto& coin : coins) {
            totalVolume += coin.getVolume();
        }
        for(const auto& item : items) {
            totalVolume += item.getVolume();
        }
        return totalVolume;
    }
    

    void addCoin(Coin coin){
        if(broken == true){
            cout << "fail: the pig is broken\n";
            return;
        }
        if(getTotalVolume() + coin.getVolume() > volumeMax){
            cout << "fail: the pig is full\n";
            return;
        }
        coins.push_back(coin);
    }

    void addItem(Item item){
        if(broken == true){
            cout << "fail: the pig is broken\n";
            return;
        }
        if(getTotalVolume() + item.getVolume() > volumeMax){
            cout << "fail: the pig is full\n";
            return;
        }
        items.push_back(item);
    }

    void breakPig(){
        broken = true;
    }

    void extractCoins(){
        if(broken == false){
            cout << "fail: you must break the pig first\n" << "[]\n";
            return;
        }
        cout << map_join(coins, [](const Coin& coin) {
            stringstream ss;
            ss << fixed << setprecision(2) << coin.getValue() << ":" << coin.getVolume();
            return ss.str();
        });
        cout << endl;
        coins.clear();
       
    }

    void extractItems(){
        if(broken == false){
            cout << "fail: you must break the pig first\n" << "[]\n";
            return;
        }
        cout << map_join(items, [](const Item& item){return item.toString();}) << endl ;
        items.clear();
    }

    void show() const{
        if(broken == true){
            cout << "state=broken ";
            cout << ": coins=" << map_join(coins, [](const Coin& coin) {
                stringstream ss;
                ss << fixed << setprecision(2) << coin.getValue() << ":" << coin.getVolume();
                return ss.str();
            });
            cout <<  " : items=" << map_join(items, [](const Item& item){return item.toString();}) ;
            cout << " : value=";
            double moedaTotal = 0.0;
                for (const auto& coin : coins) {
                moedaTotal += coin.getValue();
            }
            cout << fixed << setprecision(2) << moedaTotal << " : volume=";
            cout << "0/" << volumeMax << endl;
            return;
        } 
        cout << "state=intact ";
        cout << ": coins=" << map_join(coins, [](const Coin& coin) {
            stringstream ss;
            ss << fixed << setprecision(2) << coin.getValue() << ":" << coin.getVolume();
            return ss.str();
        });
        cout <<  " : items=" << map_join(items, [](const Item& item){return item.toString();}) ;
        cout << " : value=";
        double moedaTotal = 0.0;
            for (const auto& coin : coins) {
            moedaTotal += coin.getValue();
        }
        cout << fixed << setprecision(2) << moedaTotal << " : volume=";
        int totalVolume = 0;
            for (const auto& coin : coins) {
                totalVolume += coin.getVolume();
            }
            for (const auto& item : items) {
                totalVolume += item.getVolume();
            }
        cout << totalVolume << "/" << volumeMax << endl;
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
            pig.breakPig();
        } else if (cmd == "addCoin") {
            string label;
            ss >> label;
        try {
            Moeda moeda = stringToMoeda(label);
            int volume = Coin::getVolume(moeda); 
            pig.addCoin(Coin(moeda, volume, label)); 
        } catch (const exception& e) {
            cout << e.what() << endl;
        }
        } else if (cmd == "addItem") {
            string label;
            int volume;
            ss >> label >> volume;
            pig.addItem(Item(label, volume));
        } else if (cmd == "extractItems") {
            pig.extractItems();
        } else if (cmd == "extractCoins") {
            pig.extractCoins();
        } else {
            cout << "fail: invalid command\n";
        }
    }
}
