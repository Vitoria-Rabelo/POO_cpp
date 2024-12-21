/*Reltorio de Atividade:
Realizei a atividade depois de ver o video da resolucao em sala*/
#include <iostream>
#include <list>
#include <sstream>
#include <memory>
using namespace std;

// Função auxiliar para mapear e juntar elementos de um container
template <typename CONTAINER, typename FUNC>
auto map_join(const CONTAINER& c, FUNC f, const string& sep = ", ") {
    stringstream ss;
    for (auto it = c.begin(); it != c.end(); ++it) {
        ss << (it != c.begin() ? sep : "");
        ss << f(*it);
    }
    return ss.str();
}

class Grafite{
    private:
        float calibre;
        int tamanho;
        std::string dureza;

    public:
        Grafite(float calibre = 0, int tamanho = 0, std::string dureza = ""): calibre(calibre), tamanho(tamanho), dureza(dureza){}

        float getCalibre() const{
            return this->calibre;
        }
        float getTamanho() const{
            return this->tamanho;
        }

        void usandoTamanho(int uso){
            this->tamanho -= uso;
        }

        int usandoFolha(){
            if(dureza == "HB"){
                return 1;
            }
            if(dureza == "2B"){
                return 2;
            }
            if(dureza == "4B"){
                return 4;
            }
            if(dureza == "6B"){
                return 6;
            }
            return 0;
        }


        std::string str() const{
            stringstream ss;
            ss << "[" << calibre << ":" << dureza << ":" << tamanho << "]";
            return ss.str();
        }
};

class Lapiseira{
    private:
        float calibre{0};
        std::shared_ptr<Grafite> bico{nullptr};
        list<std::shared_ptr<Grafite>> tambor;
    public:
        Lapiseira(float calibre = 0): calibre(calibre){}

        void insert(shared_ptr<Grafite>grafite){
            if(this->calibre != grafite->getCalibre()){
                std::cout << "fail: calibre incompatível\n";
                return;
            }
            tambor.push_back(grafite);
        }

        void puxar(){
            if(this->bico != nullptr){
                std::cout<< "fail: ja existe grafite no bico\n";
                return;
            }
            if(tambor.empty()){
                std::cout << "fail: tambor vazio\n";
                return;
            }
            this->bico = tambor.front();
            tambor.pop_front();
        }

        void remove(){
            if(this->bico == nullptr){
                std::cout << "fail: nao existe grafite\n";
            }
            this->bico = nullptr;
        }

        void write(){
            if (this->bico == nullptr) {
            std::cout << "fail: nao existe grafite no bico\n";
            return;
            }
            if (this->bico->getTamanho() < this->bico->usandoFolha() || this->bico->getTamanho() == 0) {
                std::cout << "fail: folha incompleta\n" ;
                this->bico->usandoTamanho(this->bico->getTamanho());
                return;
            }
            this->bico->usandoTamanho(this->bico->usandoFolha());
        }
        
        std::string str() const {
            stringstream ss;
            auto lstr = [](auto x) {return x->str();};
            ss << "calibre: " << this->calibre << ", bico: " << (bico != nullptr ? bico->str() : "[]")
            << ", tambor: <" << map_join(tambor, lstr, "") << ">";
            return ss.str();
        }

};

int main() {
    Lapiseira lapiseira(0.5);
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;  
        }
        else if (cmd == "show") { 
            std::cout << lapiseira.str() << std::endl;
        } 
        else if (cmd == "init") { 
            float calibre;
            ss >> calibre;
            lapiseira = Lapiseira(calibre);
        } 
        else if (cmd == "insert") { 
            float calibre;
             string dureza;
            int tamanho;
            ss >> calibre >> dureza >> tamanho;
            lapiseira.insert(std::make_shared<Grafite> (calibre, tamanho, dureza));
        } 
        else if (cmd == "remove") { 
            lapiseira.remove();
        } 
        else if (cmd == "pull") { 
            lapiseira.puxar();
        } 
        else if (cmd == "write") { 
            lapiseira.write();
        } 
        else {
            cout << "fail: comando invalido\n";
        }
    }
}
