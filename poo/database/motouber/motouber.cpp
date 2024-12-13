#include <iostream>
#include "fn.hpp"

class Pessoa{
    private:
        std::string nome;
        int dinheiro{0};
    public:
        Pessoa(std::string nome, int dinheiro){
            this->nome = nome;
            this->dinheiro = dinheiro;
        }

        std::string getNome() const{
            return nome;
        }

        int getDinheiro() const{
            return dinheiro;
        }

        int setDinheiro(int novoValor){
            this->dinheiro = novoValor;
        } 

        std::string str(){
            return this->nome, ":", this->dinheiro;
        }

};


class Moto{
    private:
        int custo{0};
        std::shared_ptr<Pessoa>  passageiro{nullptr};
        std::shared_ptr<Pessoa> motorista{nullptr};

    public:
        Moto(std::shared_ptr<Pessoa> passageiro, std::shared_ptr<Pessoa> motorista){
            this->custo = 0;
            this->passageiro = nullptr;
            this->motorista = nullptr;
        }

        void setDriver(std::shared_ptr<Pessoa> motorista){
            this->motorista = motorista;
        }

        void setPass(std::shared_ptr<Pessoa> passageiro){
            this->passageiro = passageiro;
        }

        std::string str(){
            return fn::format("Const: {}, Driver: {}, Passenger: {}\n", this->custo, this->motorista, this->passageiro);
        }

        void dirigir(){
            if(this->motorista == nullptr){
                return;
            }
        }

        

};

class Adapter{
    Moto moto;
    public:
    
    void setDriver(){

    }

    void setPass(){

    }

    void drive(){

    }

    void leavePass(){

    }

    void show(){
        moto.str();
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