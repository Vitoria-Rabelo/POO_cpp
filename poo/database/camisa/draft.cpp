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

class Camisa{
    private:
    std::string tamanho;

    public:
    Camisa(std::string tamanho = "") : tamanho(tamanho){}

    std::string getTamanho() const{
        return tamanho;
    }

    void setTamanho(std::string valor){
        if(valor == "PP" || valor == "P" || valor == "M" || valor == "G" || valor == "GG" || valor == "XG"){
            tamanho = valor;
        }else{
            std::cout << "Tamanho informado é inválido.\n";
        }
    }

};
int main() {
    Camisa camisa;
     do {
        std::cout << "Digite o tamanho da camisa [PP, P, M, G, GG, XG]: ";
        std::string tamanho;
        std::cin >> tamanho;
        camisa.setTamanho(tamanho);
    } while (camisa.getTamanho().empty());

    std::cout << "O tamanho da camisa é " << camisa.getTamanho() << '\n';


    return 0;
}

