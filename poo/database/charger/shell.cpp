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
        Bateria(int capacidade = 0, int carga = 0) : capacidade(capacidade), carga(carga){}

        int getCapacidade() const{
            return this->capacidade;
        }

        int getCarga() const{
            return this->carga;
        }

        void setCarga(int newCarga){
            this->carga = newCarga;
        }

        std::string str() const{
            std::stringstream ss;
            ss << getCarga() << ":" << getCapacidade() << "\n";
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

        void setCarregador(std::shared_ptr<Carregador> newCarregador){
            this->carregador = newCarregador;
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
                this->bateria->setCarga(this->bateria->getCarga() - tempo);
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
            std::cout << "Notebook: desligado,Bateria: " << this->bateria << ", " << 
            this->carregador->str() << std::endl;
            }
            if(ligado == false && this->bateria != nullptr && this->carregador == nullptr){
            std::cout << "Notebook: desligado, Bateria:" << this->bateria->str() << std::endl;
            }
            if(ligado == false && this->bateria == nullptr && this->carregador != nullptr){
            std::cout << "Notebook: desligado, " << this->carregador->str() << std::endl;
            }
            if(ligado == true && this->bateria == nullptr && this->carregador == nullptr){
            std::cout << "Notebook: ligado";
            }
            if(ligado == true && this->bateria != nullptr && this->carregador != nullptr){
            std::cout << "Notebook: ligado por " << this->tempo << " min, Bateria: " << this->bateria << ", " << 
            this->carregador->str() << std::endl;
            }
            if(ligado == true && this->bateria != nullptr && this->carregador == nullptr){
            std::cout << "Notebook: ligado por " << this->tempo << " min, Bateria: " << this->bateria->str() << std::endl;
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
            // REMOVA O CARREGADOR DO NOTEBOOK E IMPRIMA SE ELE EXISTIR
        } else if (cmd == "set_battery") {
            // CRIE UM OBJETO Bateria E ATRIBUA AO NOTEBOOK
            // int capacity;
            // ss >> capacity;
        } else if (cmd == "rm_battery") {
            // REMOVA A BATERIA DO NOTEBOOK E IMPRIMA SE ELA EXISTIR
        } else if (cmd == "end") {
            break;
        } else {
            cout << "fail: comando inválido\n";
        }
    }    
}
