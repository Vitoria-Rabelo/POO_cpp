/*Relatório:
Passou em todos os testes
Realizei sozinha a atividade com base na atividade anterior (animal)
Aprendi: como usar incremento e decremento em c++, mensagens de erro para casos específicos, diferença
entre return e std::cout. A lógica do método drive foi a mais complexa, testei varias vezes de formas diferentes
Tempo de Atividade: cerca 3 horas (com algumas pausas)
*/
#include "fn.hpp"

struct Car
{
    int pass = 0;
    int passMax = 2;
    int gas = 0;
    int gasMax = 100;
    int km = 0;

    // metodo especial constructor inicializando atributos//
    Car()
    {
        this->pass = 0;
        this->passMax = 2;
        this->gas = 0;
        this->gasMax = 100;
        this->km = 0;
    }

    void enter()
    {
        pass++;
        if (pass > passMax)
        {
            pass = 2;
            std::cout << "fail: limite de pessoas atingido" << std::endl;
        }
    }

    std::string str()
    {
        return "pass: " + std::to_string(pass) + ", gas: " + std::to_string(gas) + ", km: " + std::to_string(km);
    }

    void leave()
    {
        pass--;
        if (pass < 0)
        {
            pass = 0;
            std::cout << "fail: nao ha ninguem no carro" << std::endl;
        }
    }

    void fuel(int abasteceu)
    {
        gas += abasteceu;
        if (gas > gasMax)
        {
            gas = gasMax;
        }
    }

    void drive(int dist)
    {
        if (pass == 0)
        {
            std::cout << "fail: nao ha ninguem no carro" << std::endl;
            return;
        }

        if (gas == 0)
        {
            std::cout << "fail: tanque vazio" << std::endl;
            return;
        }

        if (dist > gas)
        {
            km += gas;
            std::cout << "fail: tanque vazio apos andar " << gas << " km" << std::endl;
            gas = 0;
            return;
        }

        gas -= dist;
        km += dist;
    }
};

struct Student
{
    Car car;
    Student() : car()
    {
        car = Car();
    }

    void enter()
    {
        car.enter();
    }
    void leave()
    {
        car.leave();
    }
    void fuel(int q)
    {
        car.fuel(q);
        (void)q;
    }
    void drive(int q)
    {
        car.drive(q);
        (void)q;
    }
    void show()
    {
        std::cout << car.str() << std::endl;
    }
};

struct Debug
{
    // Se a variável debug for true, os testes não serão executados
    // Apenas o conteúdo do método run() será executado
    // Você pode usar isso para testar seu código manualmente
    static const bool debug = false;
    static void run()
    {
        std::cout << "Debug ativado" << std::endl;
    }
};
