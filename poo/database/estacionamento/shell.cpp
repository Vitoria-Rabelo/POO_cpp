#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

class Veiculo{
    string id;
    string tipo;
    int horaEntrada;

    public:
        Veiculo(string id = " ", string tipo = " ", int horaEntrada = 0): id(id), tipo(tipo), horaEntrada(horaEntrada){};
        virtual ~Veiculo() {};

         string getId(){
            return id;
         }

         string getTipo(){
            return tipo;
         }

         int getHoraEntrada(){
            return horaEntrada;
         }

         void setHoraEntrada(int newHora){
            this->horaEntrada = newHora;
         }

         virtual double calcularValor(int horaSair) = 0;


         virtual string str() const{
            stringstream ss;
            if(tipo != "Carro"){
            ss << "______" << this->tipo << " : " << setfill('_') << setw(10) << this->id << " : " << this->horaEntrada;
            }else{
                ss << "_____" << this->tipo << " : " << setfill('_') << setw(10) << this->id << " : " << this->horaEntrada;
            }
            return ss.str();
         }

};

class Bike : public Veiculo{
    public:
       Bike(string id = " ", int horaEntrada = 0) : Veiculo(id, "Bike", horaEntrada){};
       double calcularValor(int) override{
           return 3.00;
       }
};

class Moto : public Veiculo{
    public:
       Moto(string id = " ", int horaEntrada = 0) : Veiculo(id, "Moto", horaEntrada){};
       double calcularValor(int horaSair) override{
              return (horaSair - getHoraEntrada()) / 20.0;
       }
};

class Carro : public Veiculo{
    public:
       Carro(string id = " ", int horaEntrada = 0) : Veiculo(id, "Carro", horaEntrada){};
         double calcularValor(int horaSair) override{
                    double valorPagar = (horaSair - getHoraEntrada()) / 10.0;
                    if(valorPagar < 5.0){
                        return 5.0;
                    }
                    return valorPagar;
         }
};

class Estacionamento{
    vector<Veiculo*> veiculos;
    int horaAtual;

    public:
        Estacionamento(int horaAtual = 0) : horaAtual(horaAtual){};

        void procurarVeiculo(string id){
            for(auto& v: veiculos){
                if(v->getId() == id){
                    cout << v->str() << endl;
                    return;
                }
            }
        }

        void estacionar(Veiculo* veiculo){
            veiculo->setHoraEntrada(horaAtual);
            veiculos.push_back(veiculo);
        }

        void passarTempo(int tempo){
            horaAtual += tempo;
        }

        void pagar(string id){
            for(auto it = veiculos.begin(); it != veiculos.end(); it++){
                if((*it)->getId() == id){
                    cout << (*it)->getTipo() << " chegou " << (*it)->getHoraEntrada() << " saiu " << horaAtual << "." <<  " Pagar R$ "
                     <<  fixed << setprecision(2) << (*it)->calcularValor(horaAtual) << endl;
                    veiculos.erase(it);
                    return;
                }
            }
        }
        void show(){
            for(auto& v: veiculos){
                cout << v->str() << endl;
            }
            cout << "Hora atual: " << horaAtual << endl;
        }
};

int main() {
    Estacionamento estacionamento;
    vector<Veiculo*> veiculos;
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        std::stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        } else if (cmd == "show") {         
            estacionamento.show();

        } else if (cmd == "estacionar") {
            string tipo, id;
            ss >> tipo >> id;

            if(tipo == "bike"){
                estacionamento.estacionar(new Bike(id, 0));
            }
            else if(tipo == "moto"){
                estacionamento.estacionar(new Moto(id, 0));
            }
            else{
                estacionamento.estacionar(new Carro(id, 0));
            }
        } else if (cmd == "tempo") {
            int tempo {};
            ss >> tempo;
            estacionamento.passarTempo(tempo);
        } else if (cmd == "pagar") {
            string id;
            ss >> id;
            estacionamento.pagar(id);
        } else {
            cout << "fail: comando invalido" << endl;
        }
    }
}
