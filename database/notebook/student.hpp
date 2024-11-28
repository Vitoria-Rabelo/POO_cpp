#include <iostream>
#include <sstream>
#include <iomanip>
#include <array>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <memory>

class Batery{
    private:
    int capacity{0};
    int charge{0};
    public:

    Batery(int capacity, int charge): capacity(capacity),charge(charge){}

    int getCapacity() const{
        return capacity;
    }
    int getCharge() const{
        return charge;
    }
};

class Notebook{

private:
    bool powerOn = false;
    std::shared_ptr<Batery> batery;
public: 
    Notebook() : powerOn{false} {}

    bool opening(){
        return this->powerOn;
    }

    void setBatery(std::shared_ptr<Batery> bat){
        this->batery = bat;
    }

    void open(){
        if(this->powerOn){
            std::cout << "Ja esta ligado\n";
        }else{
            std::cout << "Ligando\n";
            this->powerOn = true;
        }
    }
    void powerOff(){
        if(this->powerOn){
            std::cout << "Desligando  o computador\n";
            this->powerOn = false;
        }else{
            std::cout << "Ja esta desligado\n";
        }
    }
    

    void use(int time){

    }

    std::string str() {
        std::stringstream ss;
        ss << "Notebook" << (opening? "Ligado");
        sreturn ss.str();
    }
};


int main(){
    Notebook notebook;
    auto batery = std::make_shared<Batery>(50);
    notebook.setBatery(batery);
}