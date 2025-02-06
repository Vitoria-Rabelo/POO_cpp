#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

template<typename CONTAINER, typename FUNC>
string map_join(const CONTAINER& cont, FUNC func, string delim) {
    stringstream ss;
    for (auto it = cont.begin(); it != cont.end(); it++) {
        ss << (it == cont.begin() ? "" : delim);
        ss << func(*it);
    }
    return ss.str();
}

class Espiral{
    private:
        string nome;
        int qtd;
        double preco;
    
    public:
        Espiral(string nome, int qtd, double preco) : nome(nome), qtd(qtd), preco(preco){}

        string getNome(){
            return nome;
        }

        int getQtd(){
            return qtd;
        }

        double getPreco(){
            return preco;
        }

        void setNome(string novoNome){
            this->nome = novoNome;
        }

        void setQtd(int novoQtd){
            this->qtd = novoQtd;
        }

        void setPreco(double novoPreco){
            this->preco = novoPreco;
        }

        string str(){
            stringstream ss;
            ss << "[" << setw(8) << setfill(' ') << nome << " : " << qtd << " U : " <<fixed << setprecision(2) << preco << " RS]" ;

            return ss.str();
        }

};

class Maquina{
    private:
        vector<Espiral> qtdEspiral;
        double saldo;
        double lucro;

    public:
        Maquina(int numEspiral){
            qtdEspiral = vector<Espiral>(numEspiral,Espiral("empty", 0, 0));
            this->saldo = 0.00;
            this->lucro = 0.00;
           
        }

    int getEspiral(int index){
        if(index < 0 || index > (int) qtdEspiral.size()){
            std::cout << "fail: indice nao existe\n";
        }
        return index;
    }

    void setEspiral(int index, string nome, int qtd, double preco){
        if(index < 0 || index > (int) qtdEspiral.size()){
            std::cout << "fail: indice nao existe\n";
        }
       this->qtdEspiral[index] = Espiral(nome, qtd, preco);
    }

    void limpar(int index){
        if(index < 0 || index > (int) qtdEspiral.size()){
            std::cout << "fail: indice nao existe\n";
        }
        this->qtdEspiral[index] = Espiral("empty", 0, 0);
    }

    void inserirDinheiro(double dinheiro){
        this -> lucro += dinheiro;
        this->saldo += dinheiro;
    }

    void troco(){
        double saida;
        saida = this->saldo;
        this->saldo = 0;
        std::cout << "voce recebeu " <<fixed << setprecision(2) << saida <<  " RS" << endl;
    }

    void comprar(int indice){
        if(indice < 0 || indice >= (int) qtdEspiral.size()){
            std::cout << "fail: indice nao existe\n";
            return;
        }
        Espiral&  espiral = qtdEspiral[indice];
        if(espiral.getQtd() <= 0){
            std::cout << "fail: espiral sem produtos\n";
            return;
        }
        if (espiral.getPreco() > saldo){
            std::cout << "fail: saldo insuficiente\n";
            return;
        }

        espiral.setQtd(espiral.getQtd() - 1);
        saldo -= espiral.getPreco();
        std::cout << "voce comprou um " << espiral.getNome() << '\n';
    }

    string str(){
        stringstream ss;
        ss << "saldo: " << fixed << setprecision(2) << saldo << endl;
        for(size_t i = 0; i < qtdEspiral.size(); i++){
            ss << i << " " << qtdEspiral[i].str() << endl;
        }
        string saida = ss.str();
        saida.pop_back();
        return saida;
    }

};

int main() {
    Maquina maquina(3);
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        try {
            if (cmd == "show") {
               cout << maquina.str() << endl;
            } else if (cmd == "init") {
                int n_espirais {};
                ss >> n_espirais;
            } else if (cmd == "limpar") {
                int indice {};
                 ss >> indice;
                 maquina.limpar(indice);
            } else if (cmd == "dinheiro") {
                int value {};
                ss >> value;
                maquina.inserirDinheiro(value);
            } else if (cmd == "comprar") {
                 int index {};
                ss >> index;
                maquina.comprar(index);
            } else if (cmd == "set") {
                int index {};
                string name;
                int qtd {};
                double price {};
                ss >> index >> name >> qtd >> price;
                maquina.setEspiral(index, name, qtd, price);
            } else if (cmd == "troco") {
                maquina.troco();
            } else if (cmd == "end") {
                break;
            } else {
                cout << "comando invalido" << endl;
            }
        } catch (const char* e) {
            cout << e << endl;
        }
    }
}
