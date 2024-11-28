/*Relatório:
Passou em todos os testes
Realizei sozinha a atividade, uso de chatgpt para testAlive;
Aprendi: encapsulamento, setter para modificar os atributos privados.
Tempo de Atividade: 4 horas
*/
#include "fn.hpp"

class Pet {
private:
    int energyMax{0};
    int hungryMax{0};
    int cleanMax{0};
    int energy{0};
    int hungry{0};
    int clean{0};
    int diamonds{0};
    int age{0};
    bool alive{true};

public:
    Pet(int energy, int hungry, int clean)
        : energyMax(energy), hungryMax(hungry), cleanMax(clean),
          energy(energy), hungry(hungry), clean(clean) {}

    bool isAlive() const {
        return alive;
    }

    void setAlive(bool state) {
        alive = state;
    }

    int getEnergy() const {
        return energy;
    }

    void setEnergy(int x) {
        energy = std::max(0, std::min(energyMax, x));
    }

    int getHungry() const {
        return hungry;
    }

    void setHungry(int x) {
        hungry = std::max(0, std::min(hungryMax, x));
    }

    int getClean() const {
        return clean;
    }

    void setClean(int x) {
        clean = std::max(0, std::min(cleanMax, x));
    }

    int getEnergyMax() const {
        return energyMax;
    }

    int getHungryMax() const {
        return hungryMax;
    }

    int getCleanMax() const {
        return cleanMax;
    }

    int getDiamonds() const {
        return diamonds;
    }

    void setDiamonds(int x) {
        diamonds = x;
    }

    int getAge() const {
        return age;
    }

    void setAge(int x) {
        age = x;
    }

    std::string str() const {
        std::ostringstream oss;
        oss << "E:" << energy << "/" << energyMax
            << ", S:" << hungry << "/" << hungryMax
            << ", L:" << clean << "/" << cleanMax
            << ", D:" << diamonds
            << ", I:" << age;
        return oss.str();
    }
};

class Game {
private:
    std::shared_ptr<Pet> pet{nullptr};

    bool testAlive() {
        if (!pet->isAlive()) {
            std::cout << "fail: pet esta morto\n";
            return false;
        }

        if (pet->getEnergy() <= 0) {
            pet->setAlive(false);
            std::cout << "fail: pet morreu de fraqueza\n";
            return false;
        }

        if (pet->getHungry() <= 0) {
            pet->setAlive(false);
            std::cout << "fail: pet morreu de fome\n";
            return false;
        }

        if (pet->getClean() <= 0) {
            pet->setAlive(false);
            std::cout << "fail: pet morreu de sujeira\n";
            return false;
        }

        return true;
    }

public:
    Game(std::shared_ptr<Pet> pet) : pet(pet) {}

    void init(int energy, int hungry, int clean) {
        pet = std::make_shared<Pet>(energy, hungry, clean);
    }

    std::string str() const {
        return pet->str();
    }

    void play() {
        if (!testAlive()) return;

        pet->setEnergy(pet->getEnergy() - 2);
        pet->setHungry(pet->getHungry() - 1);
        pet->setClean(pet->getClean() - 3);
        pet->setDiamonds(pet->getDiamonds() + 1);
        pet->setAge(pet->getAge() + 1);

        testAlive();
    }

    void eat() {
        if (!testAlive()) return;

        pet->setEnergy(pet->getEnergy() - 1);
        pet->setHungry(pet->getHungry() + 4);
        pet->setClean(pet->getClean() - 2);
        pet->setAge(pet->getAge() + 1);

        testAlive();
    }

    void sleep() {
        if (!testAlive()) return;

        int energyNeeded = pet->getEnergyMax() - pet->getEnergy();
        if (energyNeeded < 5) {
            std::cout << "fail: nao esta com sono\n";
            return;
        }

        pet->setEnergy(pet->getEnergyMax());
        pet->setAge(pet->getAge() + energyNeeded);
        pet->setHungry(pet->getHungry() - 1);

        testAlive();
    }

    void shower() {
        if (!testAlive()) return;

        pet->setEnergy(pet->getEnergy() - 3);
        pet->setHungry(pet->getHungry() - 1);
        pet->setClean(pet->getCleanMax());
        pet->setAge(pet->getAge() + 2);

        testAlive();
    }
};

class Student {
private:
    Game game;

public:
    Student(int energy, int hungry, int clean)
        : game(Game(std::make_shared<Pet>(energy, hungry, clean))) {}

    void show() {
        std::cout << this->game.str() << std::endl;
    }

    void play() {
        this->game.play();
    }

    void shower() {
        this->game.shower();
    }

    void eat() {
        this->game.eat();
    }

    void sleep() {
        this->game.sleep();
    }
};
