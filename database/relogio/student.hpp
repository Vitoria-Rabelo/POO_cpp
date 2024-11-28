/*Relatório:
Passou em todos os testes
Realizei sozinha a atividade, uso do chatgpt para o problema de sobrecarga do operador << e 
std::setw(2) e std::setfill('0') para garantir 2 dígitos
Aprendi: niveis de acesso (public e private),formatacao com sprintf, sobrecarga de operador e formato 2 digitos,
Tempo de Atividade: 2 horas
*/
#pragma once
#include "fn.hpp"

// Por padrão, todos os membros de uma class são privados diferente da struct//
class Time 
{   
private:

    int hour {0};
    int minute {0};
    int second {0};

public:

    Time(int hr, int min, int sec)
    {
        this->setHour(hr);    
        this->setMinute(min);
        this->setSecond(sec);
    }

    std::string str() const
    {
        char data[30];
        sprintf(data,"%02d:%02d:%02d", this->hour, this->minute, this->second);
        return {data};
    }

    friend std::ostream& operator<<(std::ostream& os, const Time& t)
    {
        // Usando std::setw(2) e std::setfill('0') para garantir 2 dígitos com preenchimento com zero à esquerda
        os << std::setw(2) << std::setfill('0') << t.hour << ":"
           << std::setw(2) << std::setfill('0') << t.minute << ":"
           << std::setw(2) << std::setfill('0') << t.second;
        return os;
    }


    //metodo de leitura//
    int getHour()
    {
        return this->hour;
    }

    int getMinute()
    {
        return this->minute;
    }

    int getSecond()
    {
        return this->second;
    }
    //metodo de escrita//
    void setHour(int value)
    {
        if(value < 0 || value > 23)
        {
            std::cout << "fail: hora invalida\n";
            return ;
        }
        this->hour = value;
    }

    void setMinute(int value)
    {
        if(value < 0 || value > 59)
        {
            std::cout << "fail: minuto invalido\n";
            return ;
        }
        this->minute = value;
    }

    void setSecond(int value)
    {
        if(value < 0 || value > 59)
        {
            std::cout << "fail: segundo invalido\n";
            return ;
        }
        this->second = value;
    }

    //metodo para incrementar
    void nextSecond()
    {
        second++;

        if(second > 59)
        {
            second = 0;
            minute++;

            if(minute > 59)
            {
                minute = 0;
                hour++;

                if(hour > 23)
                {
                    hour = 0;
                }
            }
        }
    }
};


class Student 
{
private:
    Time time;

public:
    Student(int hour = 0, int minute = 0, int second = 0): time(hour, minute, second) {}
    void init(int hour = 0, int minute = 0, int second = 0) {
        this->time = Time(hour, minute, second);
    }

    void setHour(int hour) {
        (void) hour;
        this->time.setHour(hour);
    }

    void setMinute(int minute) {
        this->time.setMinute(minute);
    }
    void setSecond(int second) {
        (void) second;
        this->time.setSecond(second);
    }

    void nextSecond() {
        this->time.nextSecond();
    }
    
    void show() {
        fn::write(time);
    }
};