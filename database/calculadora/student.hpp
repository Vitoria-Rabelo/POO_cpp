/*Relatório:
Passou em todos os testes
Realizei sozinha a atividade porem o monitor Henrique Pires me ajudou a otimizar criando um metodo useBattery 
Aprendi : quando deve "this->" para referenciar as variaveis corretamente, criar meus propios metodos para 
otimizar, utilizacao de ponto flutuante (float) em uma saida
Tempo de Atividade: cerca 2 horas e 30 min
*/
#pragma once
#include "fn.hpp"

struct Calculator
{
    int battery = 0;
    int batteryMax = 0;
    float display = 0;

    Calculator(int batteryMax)
    {
        this->battery = 0;
        this->batteryMax = batteryMax;
        this->display = 0;
    }

    void charge(int value)
    {
        this->battery += value;
        if(this->battery > this->batteryMax)
        {
            this->battery = this->batteryMax;
        }
    }

    bool useBattery()
    {
        if(this->battery <= 0)
        {
            std::cout << "fail: bateria insuficiente" << std::endl;
            return false;
        }

        this->battery -= 1;
        return true;
    }

    void sum(int a, int b)
    {   
        if(useBattery())
        {
            this->display = a + b;
        }
    }

    void division(int num, int den)
    {
        if(useBattery()){
            if (den == 0)
            {
                std::cout << "fail: divisao por zero" << std::endl;
            }
            else
            {
                this->display = (float) num / den;
            }
            
        }
    }

    std::string str()
    { 
        return fn::format("display = {%.2f}, battery = {}", display, battery);  
    } 
};

struct Student {
    Calculator c;
public:
    Student(int battery = 0) : c(battery) {}
    void show() {
        std::cout << c.str() << std::endl;
    }
    void init(int batteryMax) {
        c = Calculator(batteryMax);
    }
    void charge(int value) {
        c.charge(value);
    }
    void sum(int a, int b) {
        c.sum(a, b);
    }
    void div(int num, int den) {
        c.division(num, den);
    }
};
