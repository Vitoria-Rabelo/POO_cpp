#include <iostream>
#include "fn.hpp"

class Pessoa{
    private:
        std::string nome;
        int dinheiro{0};

    public:
        Pessoa(std::string nome = "", int dinheiro = 0): nome(nome) , dinheiro(dinheiro){}

        std::string getNome() const{
            return nome;
        }

        int getDinheiro() const{
            return dinheiro;
        }

        std::string str() const{
            return fn::format("{}:{}", this->nome, this->dinheiro);
        }

        void show{
            std::cout << pessoa.str();
        }

};

class Moto{
    private:
        int custo{0};
        std::shared_ptr<Pessoa> pessoa{nullptr};

    public:
        Moto(int custo = 0,  std::shared_ptr<Pessoa> pessoa): custo(custo) , pessoa(pessoa){}

        int getCusto() const {
            return custo;
        }

        std::string setDriver(std::shared_ptr<Pessoa> pessoa, std::string motoqueiro){
            
        }

        std::string setPass(std::shared_ptr<Pessoa> pessoa, std::string passageiro){
            if(setDriver == nullptr){
                std::cout << "Falha, não há motoqueiro" << std::endl;
            }else{

            }
            return passageiro = pessoa;
        }

        std::string str() const{
           return fn::format("Cost: {}, Driver: None, Passenger: None", this->custo);
        }

        void show(){
            std::cout << moto.str();
        }
};

class Adapter {
    Moto moto;
public:
    void setDriver(std::string nome, int dinheiro) {
        moto.setDriver();
    }
    void setPass(std::string nome, int dinheiro) {
        (void) nome;
        (void) dinheiro;
    }
    void drive(int distance) {
        (void) distance;
    }
    void leavePass() {
    }
    void show() {
        std::cout << moto.str();
    }
};

int main() {
    Adapter adp;
    while (true) {
        fn::write("$", "");
        auto line = fn::input();
        auto args = fn::split(line, ' ');
        fn::write(line);

        if      (args[0] == "end")       { break;                                  }
        else if (args[0] == "setDriver") { adp.setDriver(args[1], +args[2]);       }
        else if (args[0] == "setPass")   { adp.setPass(args[1], +args[2]);         }
        else if (args[0] == "drive")     { adp.drive(+args[1]);                    }
        else if (args[0] == "leavePass") { adp.leavePass();                        }
        else if (args[0] == "show")      { adp.show();                             }
        else                             { fn::write("fail: command not found\n"); }
    }
}