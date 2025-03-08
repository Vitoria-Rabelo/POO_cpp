#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>
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
            ss << "______" << this->tipo << " : " << setfill('-') << setw(8) << this->id << " : " << this->horaEntrada;
            return ss.str();
         }

};

class Bike : public Veiculo{
    public:
       Bike(string id = " ", int horaEntrada = 0) : Veiculo(id, "Bike", horaEntrada){};
       double calcularValor(){
           return 3.00;
       }
};

class Moto : public Veiculo{
    public:
       Moto(string id = " ", int horaEntrada = 0) : Veiculo(id, "Moto", horaEntrada){};
       double calcularValor(int horaSair){
              return (horaSair - getHoraEntrada()) / 20.0;
       }
};

class Carro : public Veiculo{
    public:
       Carro(string id = " ", int horaEntrada = 0) : Veiculo(id, "Carro", horaEntrada){};
         double calcularValor(int horaSair){
                    double valorPagar = (horaSair - getHoraEntrada()) / 10.0;
                    if(valorPagar < 5.0){
                        return 5.0;
                    }
                    return valorPagar;
         }
};

int main() {
    
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        } else if (cmd == "show") {
        } else if (cmd == "estacionar") {
            // string tipo, id;
            // ss >> tipo >> id;
        } else if (cmd == "tempo") {
            // int tempo {};
            // ss >> tempo;
        } else if (cmd == "pagar") {
            // string id;
            // ss >> id;
        } else {
            cout << "fail: comando invalido" << endl;
        }
    }
}
