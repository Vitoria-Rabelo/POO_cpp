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

class Battery { 
private:
    int capacity{0};
    int charge{0};

public:
    Battery(int capacity, int charge) : capacity(capacity), charge(charge) {}

    int getCapacity() const {
        return capacity;
    }

    int getCharge() const {
        return charge;
    }

    void useCharge(int percent) {
        if (charge >= percent) {
            charge -= percent;
        } else {
            charge = 0;
        }
    }

    bool isEmpty() const {
        return charge <= 0;
    }

    std::string str() const {
        std::stringstream ss;
        ss << "(" << charge << "/" << capacity << ")";
        return ss.str();
    }

    void show() const {
        std::cout << charge << "/" << capacity << std::endl;
    }
};

class Notebook {
private:
    bool powerOn = false;
    std::shared_ptr<Battery> battery;

public:
    Notebook() : powerOn{false}, battery(nullptr) {}

    bool opening() const {
        return powerOn;
    }

    void setBattery(std::shared_ptr<Battery> bat) {
        battery = bat;
    }

    void open() {
        if (powerOn) {
            std::cout << "Já está ligado\n";
        } else if (!battery || battery->isEmpty()) {
            std::cout << "Erro: sem bateria ou bateria descarregada.\n";
            return;
        } else {
            std::cout << "Notebook foi ligado\n";
            powerOn = true;
        }
    }

    void powerOff() {
        if (powerOn) {
            std::cout << "Desligando o computador\n";
            powerOn = false;
        } else {
            std::cout << "Já está desligado\n";
        }
    }

    void use(int time) {
        if (!powerOn) {
            std::cout << "Erro: ligue o notebook primeiro\n";
            return;
        }

        if (!battery || battery->isEmpty()) {
            std::cout << "Erro: bateria descarregada.\n";
            powerOff();
            return;
        }

        int actualUse = std::min(time, battery->getCharge());
        battery->useCharge(actualUse);
        std::cout << "Usando por " << actualUse << " minutos.\n";

        if (battery->isEmpty()) {
            std::cout << "Bateria descarregada. Notebook desligando.\n";
            powerOff();
        }
    }

    std::shared_ptr<Battery> rmBattery() {
        if (!battery) {
            std::cout << "Erro: não há bateria para remover.\n";
            return nullptr;
        }

        auto removedBattery = battery;
        battery = nullptr;
        if (powerOn) {
            std::cout << "Notebook desligado.\n";
            powerOff();
        }

        std::cout << "Bateria removida.\n";
        return removedBattery;
    }

    std::string str() const {
        std::stringstream ss;
        ss << "Notebook " << (opening() ? "Ligado" : "Desligado");
        return ss.str();
    }

    void show() const {
        std::cout << "Status: " << (powerOn ? "Ligado" : "Desligado") << std::endl;
        if (battery) {
            std::cout << ", Bateria: " << battery->str() << std::endl;
        } else {
            std::cout << ", Bateria: Sem bateria" << std::endl;
        }
    }
};

int main() {
    Notebook notebook;
    notebook.show();

    notebook.use(10);
    notebook.open();

    auto battery = std::make_shared<Battery>(50, 50); 
    battery->show();
    notebook.setBattery(battery);

    notebook.show();
    notebook.use(10);
    notebook.open();
    notebook.show();
    notebook.use(30);
    notebook.show();
    notebook.use(30);
    notebook.show();
    notebook.open();

    auto removedBattery = notebook.rmBattery();
    removedBattery->show(); 
}
