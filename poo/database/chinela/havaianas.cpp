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


class Havaianas {

    private:

    int tamanho{0};

    public:

    Havaianas(int tamanho = 0)
    {
        this->tamanho = tamanho;
    }

    int getTamanho() const
    {
        return this->tamanho;
    }

    void setTamanho(int value)
    {
        if(value % 2 == 0)
        {
            if(value >= 20 && value <=50)
            {
                this->tamanho = value;
                return ;
            }
        }
        std::cout << "falha ao informar tamanho\n";
    }

};

int main()
{

    Havaianas havaianas;
    
    do{
        std::cout << "Digite o tamanho entre [20 a 50]: ";
        int tamanho;
        std::cin >> tamanho;
        havaianas.setTamanho(tamanho);
        std::cout << "O tamanho da chinela é " << havaianas.getTamanho() << '\n';
    }while(havaianas.getTamanho() == 0);
    return 0;
   
};
