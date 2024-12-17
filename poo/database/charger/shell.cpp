#include <iostream>
#include <sstream>
#include <memory>
#include <utility>
using namespace std;

class Carregador{
    private:
        int potencia{0};
    public:
        Carregador(int potencia = 0) : potencia(potencia){}

        int getPotencia() const{
            return this->potencia;
        }

        std::string str() const{
            std::stringstream ss;
            ss << "Carregador " << this->getPotencia() << "W";
            return ss.str();
        }
};

class Bateria{
    private:
        int capacidade{0};
        int carga{0};
    public: 
        Bateria(int capacidade = 0, int carga = 0) : capacidade(capacidade){
            if (carga == 0) {
                carga = capacidade;
            }
            this->carga = carga;}

        int getCapacidade() const{
            return this->capacidade;
        }

        int getCarga() const{
            return this->carga;
        }

        void setCarga(int newCarga){
            this->carga = newCarga;
            if(this->carga > this->capacidade){
                this->carga = this->capacidade;
            }
        }


        std::string str() const{
            std::stringstream ss;
            ss << this->carga << "/" << this->capacidade;
            return ss.str();
        }
};

class Notebook{
    private:
        bool ligado;
        std::shared_ptr<Bateria> bateria;
        std::shared_ptr<Carregador> carregador;
        int tempo{0};
    public:
        Notebook(){
            this->bateria = nullptr;
            this-> carregador  = nullptr;
            this->ligado = false;
            this->tempo = 0;
        }

        void setCarregador(std::shared_ptr<Carregador> novoCarregador){
            if(this->carregador == nullptr){
                this->carregador = novoCarregador;
                }else{
                    std::cout << "fail: carregador já conectado\n";
                }
        }

        void removeCarregador(){
            if(this->carregador != nullptr){
                std::cout << "Removido " << this->carregador->getPotencia() << "W" <<std::endl;
                this->carregador = nullptr;
                this->ligado = false;
            }else{
                std::cout << "fail: Sem carregador\n";
            }
        }

        void setBateria(std::shared_ptr<Bateria> novaBateria){
            if(this->bateria == nullptr){
            this->bateria = novaBateria;
            }else{
                std::cout << "fail: já existe bateria\n";
            }
        }

        void removeBateria(){
            if(this->bateria != nullptr){
                std::cout << "Removido " << this->bateria->getCarga() << "/" << this->bateria->getCapacidade() <<
                std::endl;
                this->bateria = nullptr;
                this->ligado = false;
            }else{
                std::cout << "fail: Sem bateria\n";
            }
        }

        void ligar(){
            if(this->bateria != nullptr || this->carregador != nullptr){
                this->ligado = true;
            }else{
            this->ligado = false;
            std::cout << "fail: não foi possível ligar\n";
            }
        }

        void desligar(){
            this->ligado = false;
        }

        void usar(int tempo){
            this->tempo += tempo;
            if(this->ligado == false){
                std::cout << "fail: desligado\n";
            }
            if(this->bateria != nullptr && this->carregador == nullptr){
                if(this->bateria->getCarga() <= tempo){
                    std::cout << "fail: descarregou\n";
                    this->bateria->setCarga(0);
                    this->ligado = false;
                }else{
                    this->bateria->setCarga(this->bateria->getCarga() - tempo);
                    if(this->bateria->getCarga() < 0){
                        this->bateria->setCarga(0);
                    }
                }  
            }
            if(this->bateria != nullptr && this->carregador != nullptr){
                this->bateria->setCarga(this->bateria->getCarga() + tempo);
                
            }
        }

        void show(){
            if(ligado == false && this->bateria == nullptr && this->carregador == nullptr){
            std::cout << "Notebook: desligado\n";
            }
            if(ligado == false && this->bateria != nullptr && this->carregador != nullptr){
            std::cout << "Notebook: desligado,Bateria " << this->bateria << ", " << 
            this->carregador->str() << std::endl;
            }
            if(ligado == false && this->bateria != nullptr && this->carregador == nullptr){
            std::cout << "Notebook: desligado, Bateria " << this->bateria->str() << std::endl;
            }
            if(ligado == false && this->bateria == nullptr && this->carregador != nullptr){
            std::cout << "Notebook: desligado, " << this->carregador->str() << std::endl;
            }
            if(ligado == true && this->bateria == nullptr && this->carregador == nullptr){
            std::cout << "Notebook: ligado\n";
            }
            if(ligado == true && this->bateria != nullptr && this->carregador != nullptr){
            std::cout << "Notebook: ligado por " << this->tempo << " min, Carregador "<< this->carregador->getPotencia() 
            << "W, Bateria " << this->bateria->str() <<std::endl;
            }
            if(ligado == true && this->bateria != nullptr && this->carregador == nullptr){
            std::cout << "Notebook: ligado por " << this->tempo << " min, Bateria " << this->bateria->str() << std::endl;
            }
            if(ligado == true && this->bateria == nullptr && this->carregador != nullptr){
            std::cout << "Notebook: ligado por " << this->tempo << " min, " << this->carregador->str() << std::endl;
            }
        }

};

int main() {
    Notebook note;
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "show") { note.show();
        } else if (cmd == "turn_on") { note.ligar();
        } else if (cmd == "turn_off") { note.desligar();
        } else if (cmd == "use") { 
            int tempo;
            ss >> tempo;
            note.usar(tempo) ;
        } else if (cmd == "set_charger") {
            int potencia;
            ss >> potencia;
            auto carregador = std::make_shared<Carregador>(potencia);
            note.setCarregador(carregador);
        } else if (cmd == "rm_charger") {
            note.removeCarregador();
        } else if (cmd == "set_battery") {
            int capacidade;
            ss >> capacidade;
            auto bateria = std::make_shared<Bateria>(capacidade);
            note.setBateria(bateria);
        } else if (cmd == "rm_battery") {
            note.removeBateria();
        } else if (cmd == "end") {
            break;
        } else {
            cout << "fail: comando inválido\n";
        }
    }    
}
