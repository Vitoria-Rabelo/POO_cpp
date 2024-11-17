#pragma once
#include "fn.hpp"

struct Animal
{
    std::string especie;
    std::string barulho;
    int idade;

    Animal(std::string especie = "", std::string barulho = "")
    {
        this->especie = especie;
        this->barulho = barulho;
        this->idade = 0;
    }
    std::string fazerBarulho() const
    {
        if (this->idade == 0)
        {
            return "---";
        }
        if (this->idade == 4)
        {
            return "RIP";
        }
        return barulho;
    }
    void envelhecer(int nivel)
    {
        idade += nivel;
        if (idade >= 4)
        {
            this->idade = 4;
            std::cout << "warning: " << especie << " morreu" << std::endl;
        }
    }

    std::string str() const
    {
        return especie + ":" + std::to_string(idade) + ":" + barulho;
    }

};


struct Student {
    Animal animal;
    void init(std::string especie = "", std::string barulho = "") {
        animal = Animal(especie, barulho);
    }

    void grow(int nivel) {
        animal.envelhecer(nivel);
    }

    void noise() {
        std::cout << animal.fazerBarulho() << std::endl;
    }

    void show() {
        std::cout << animal.str() << std::endl;
    }
};
