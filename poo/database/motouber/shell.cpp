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

        void passageiroPagando(int distanciaPercorrida){
            if(dinheiro < distanciaPercorrida){
                dinheiro = 0;
            }else{
                dinheiro -= distanciaPercorrida;
            }
        }

        void motoristaRecebendo(int distanciaPercorrida){
            dinheiro += distanciaPercorrida;
        }

        std::string str() const{
            return fn::format("{}:{}", this->nome, this->dinheiro);
        }

};

class Moto{
    private:
        int custo{0};
        std::shared_ptr<Pessoa> motorista{nullptr};
        std::shared_ptr<Pessoa> passageiro{nullptr};

    public:
        Moto(): custo(0) , motorista(nullptr), passageiro(nullptr){}

        int getCusto() const {
            return custo;
        }

        std::string setDriver(std::shared_ptr<Pessoa> motoqueiro){
            if(this->motorista != nullptr){
                return "Falha: já existe motorista\n";
            }
            motorista = motoqueiro;
            return "Motorista está na moto\n";
        }

        std::string setPass(std::shared_ptr<Pessoa> passageiro){
            if(this->motorista == nullptr){
                return "Falha, não há motorista\n";
            }
            this->passageiro = passageiro;
            return "passageiro subiu na moto\n";
        }

        std::string dirigir(int distancia){
            if(motorista == nullptr){
                return "Falha, não há motorista\n";
            }
            if(passageiro == nullptr){
                return "Falha, não há passageiro\n";
            }
            
            custo += distancia;
            return "A moto está andando\n";
        }

        std::string leavePass(){
            if(passageiro == nullptr){
                return "Falha, não há passageiro\n";
            }
            if (passageiro->getDinheiro() < custo) {
                std::cout << "fail: Passenger does not have enough money\n";
            }
            motorista->motoristaRecebendo(custo);
            passageiro->passageiroPagando(custo);
            std::string mensagem = fn::format("{}:{} leave\n", passageiro->getNome(), passageiro->getDinheiro());
            custo = 0;
            passageiro = nullptr;
            return mensagem;
        }

        std::string str() const {
            std::string motoristaStr = motorista ? motorista->str() : "None";
            std::string passageiroStr = passageiro ? passageiro->str() : "None";
            return fn::format("Cost: {}, Driver: {}, Passenger: {}", custo, motoristaStr, passageiroStr);
        }
};


class Adapter {
    Moto moto;
public:
    void setDriver(std::string nome, int dinheiro) {
        moto.setDriver(std::make_shared<Pessoa>(nome, dinheiro));
    }
    void setPass(std::string nome, int dinheiro) {
        moto.setPass(std::make_shared<Pessoa>(nome, dinheiro));
    }
    void drive(int distance) {
       moto.dirigir(distance);
    }
    void leavePass() {
    std::cout << moto.leavePass();
    }
    void show() {
        std::cout << moto.str() << std::endl;

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