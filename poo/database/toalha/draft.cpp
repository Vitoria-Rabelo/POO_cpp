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

class Toalha{

    private:
    std::string cor;
    std::string tamanho;
    int umidade{0}; 

    public:
    //inicializando atributos : parametros(cor e tamanho) e umidade //
    Toalha(const std::string& cor = "", const std::string& tamanho = "") : cor(cor), tamanho(tamanho), umidade(0){}

    int getUmidadeMaxima() const{
        if(tamanho == "P"){
            return  10;
        }
       if(tamanho == "M"){
            return 20;
        }
        if(tamanho == "G"){
            return 30;
        }
        return 0;
    }

    void enxugar(int umidadeRecebida){
        if(umidade + umidadeRecebida > getUmidadeMaxima()){
            umidade = getUmidadeMaxima();
            std::cout << "toalha enxarcada\n";
        }else{
            umidade += umidadeRecebida;
        }
    }

    void torcer(){
        umidade = 0;
    }

    bool estaSeca() const{
       if (umidade == 0) {
            std::cout << "True\n"; 
            return true;
        } else {
            std::cout << "False\n";
            return false;
        }
    }

    std::string toString() const {
        return cor + " " + tamanho + " " + std::to_string(umidade);
    }

    void mostrar(){
        std::cout << toString() << "\n";
    }
};
int main() {
    Toalha toalha("Azul", "P");
    toalha.mostrar();
    toalha.enxugar(5);
    toalha.mostrar() ;
    toalha.estaSeca();
    toalha.enxugar(5);
    toalha.mostrar();
    toalha.enxugar(5);
    toalha.mostrar();
    toalha.torcer(); 
    toalha = Toalha("Verde", "G");
    toalha.estaSeca();
    toalha.enxugar(30);
    toalha.mostrar();
    toalha.estaSeca();
    toalha.enxugar(1);
    toalha.enxugar(30);
}

