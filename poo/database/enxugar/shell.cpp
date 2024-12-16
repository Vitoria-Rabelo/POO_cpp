/* Fiz a atividade sozinha, aprendi coo fazer as mensagens de teste*/
#include <iostream>
#include <sstream>
using namespace std;

class Towel{
    private:
        std::string color;
        std::string size;
        int wetness{0};
    public:
        Towel(std::string color = "", std::string size = "" ){
            this->color = color;
            this->size = size;
            this->wetness = 0;
        }
        
        std::string getColor() const{
            return this->color;
        }

        std::string getSize() const{
            return this->size;
        }

        int getWetness() const{
            return wetness;
        }

        void setColor(std::string newColor){
            this->color = newColor;
        }

        void setSize(std::string newSize){
            this->size = newSize;
        }

        void setWetness(int newWetness){
            this->wetness = newWetness;
        }

        void dry(int amout){
            setWetness(this->wetness += amout);
        }

        void wringOut(){
            setWetness(this->wetness = 0);
        }

        int getMaxWetness(){
            if(getSize() == "P"){
                return 10;
            }
            if(getSize() == "M"){
                return 20;
            }
            if(getSize() == "G"){
                return 30;
            }
            return 0;
        }

        bool isDry(){
            if(getWetness() == 0){
                return true;
            }
            return false;
        }

        void enxugando(int enxugar){
            setWetness(this->wetness += enxugar);
            if(getWetness() >= getMaxWetness()){
                setWetness(getMaxWetness());
                std::cout << "toalha encharcada\n" ;
            }
        }

        std::string str() const {
            std::ostringstream oss;
            oss << "Cor: " << this->getColor()
            << ", Tamanho: " << this->getSize()
            << ", Umidade: " << this->getWetness();
            return oss.str();
        }

        void creatingNewTowel(){
            std::cout << "$criar " << this->getColor() << " " << this->getSize() << std::endl;
        }
        void show(){
            std::cout << "$mostrar\n" << str() << std::endl;
        }

        void end() {
            std::cout << "$end\n";
        }

        void seca() {
            std::cout << "$seca\n";
        }

        void enxugar(int value){
            std::cout << "$enxugar" << " " << value << std::endl;
        }

        void torcer(){
            std::cout << "$torcer" << std::endl;
        }
};

int main() {
    Towel towel;
    while (true) {
        string line, cmd;
        getline(cin, line);

        stringstream par(line);
        par >> cmd;

        if (cmd == "mostrar") { towel.show();
        } else if (cmd == "criar") { // ATUALIZE A TOALHA UTILIZAND O CONSTRUTOR
            std::string color, size;
            par >> color >> size;
            towel.setColor(color);
            towel.setSize(size);
            towel.creatingNewTowel();
        } else if (cmd == "enxugar") { // USE O METODO ENXUGAR
            int umidade {};
            par >> umidade;
            towel.enxugar(umidade);
            towel.enxugando(umidade);
        } else if (cmd == "torcer") { // USE O METODO TORCER 
        towel.torcer();
        towel.wringOut();
        } else if (cmd == "seca") { towel.seca();
                                    if(towel.isDry() == true){ std::cout << "sim\n";}
                                    if(towel.isDry() == false){ std::cout << "nao\n";}
        } else if (cmd == "end") {
            towel.end();
            break;
        } else {
            cout << "fail: comando invalido" << endl;
        }
    }
}