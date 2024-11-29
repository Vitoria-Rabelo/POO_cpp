/*Relatório:
Passou em todos os testes
Assisti a video-aula do professor e  realizei a atividade.
Aprendizado  sobre limpeza de memoria com destructor,lista de inicialização , usar parametro default,
ponteiros inteligentes, auto backup,
Tempo de Atividade: 2 horas
*/
#pragma once
#include "fn.hpp"

class Person
{   
private:

    std::string name;
    int age;

public:

    Person(std::string name, int age): name(name), age(age){}

    std::string getName()
    {
        return this->name;
    }

    int getAge()
    {
        return this->age;
    }

    std::string str() const
    {
        return fn::format("{}:{}", name, age);
    }
};

std::ostream& operator<<(std::ostream &os, const Person& person)
    {
        return os << person.str();
    }

class Motorcycle
{

private:
    int power{1};
    int time{0};
    std::shared_ptr<Person> person {nullptr};
    std::string name{"empty"}; 

public:
    Motorcycle(int power = 1): power(power) {}

    void insert(std::shared_ptr<Person> person) 
    {
        if (this->person != nullptr)
        {
            fn::write("fail: busy motorcycle");
            return;
        }
        this->person = person;
        this->name = person->getName();
    }

    void buyTime(int time)
    {
        this->time += time;
    }

    void drive(int time){
        if(this->time == 0)
        {
            fn::write("fail: buy time first");
            return;
        }
        if(this->person == nullptr)
        {
            fn::write("fail: empty motorcycle");
            return;
        }
        if(this->person->getAge() > 10)
        {
            fn::write("fail: too old to drive");
            return;
        }
        if(this->time < time)
        {
            //usa print para substituir a variavel
            fn::print("fail: time finished after {} minutes\n", this->time);
            this->time = 0;
            return;
        }
        this->time -= time;
    }

    std::string honk() const
    {
        std::string  out = "P";
        for(int i = 0; i < (int) this->power; i++)
        {
            out += 'e';
        }
        return out + "m";
        //ou: auto x = "P" + std::string(this->potencia, 'e') + "m";
    }

    std::shared_ptr<Person> remove()
    {
        if(this->person == nullptr)
        {
            fn::write("fail: empty motorcycle");
            return nullptr;
        }
        auto backup = this->person;
        this->person = nullptr;
        return backup;
    }
    
    std::string str() const
     {
        std::string name("empty");
        if(this->person != nullptr) 
        {
            name = this->person->str();
        }
        return fn::format("power:{}, time:{}, person:({})", this->power, this->time, name);
    }

};


std::ostream& operator<<(std::ostream &os, const Motorcycle& motorcycle)
    {
        return os << motorcycle.str();
    }

class Student {
    Motorcycle motorcycle;
public:

    Student(int power = 1): motorcycle(power) {}

    void init(int power = 1) {
        this->motorcycle = Motorcycle(power);
         motorcycle = Motorcycle(power);
    }

    void enter(std::string name, int age) {
        auto person = std::make_shared<Person>(name, age);
        motorcycle.insert(person);
    }

    void leave() {
        auto person = motorcycle.remove();
        fn::write(person == nullptr ? "---" : person->str());
    }

    void honk() const {
        fn::write(motorcycle.honk());
    }

    void buy(int time) {
        motorcycle.buyTime(time);
    }

    void drive(int time) {
        motorcycle.drive(time);
    }

    void show() const {
         fn::write(motorcycle.str());
    }
};