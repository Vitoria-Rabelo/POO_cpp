#include "fn.hpp"

class Towel{
    private:
        std::string size;
    public:
        Towel(){
            this->size = "";
        }

        std::string getSize() const{
            return this->size;
        }

        void setSize(std::string newSize){
            if(newSize == "PP" || newSize == "P" || newSize == "M" || newSize == "GG" ||
                newSize == "XG"){
                    this->size = newSize;
            }else{
                std::cout << "fail: Valor inválido, tente PP, P, M, G, GG ou XG\n";
            }

        }
};

class Adapter {
    std::shared_ptr<Towel> towel;
public:
    Adapter() {
        this->towel = std::make_shared<Towel>();
    }
    void size(const std::string& size) {
        this->towel->setSize(size);
    }
    void show() {
        std::cout << "size: (" << this->towel->getSize() << ")\n";
    }
};

int main() {
    Adapter adapter;
    while (true) {
        fn::write("$", "");
        auto line = fn::input();
        auto args = fn::split(line, ' ');
        fn::write(line);

        if      (args[0] == "end")  { break;                         }
        else if (args[0] == "size") { adapter.size(args[1]);         }
        else if (args[0] == "show") { adapter.show();                }
        else                        { fn::write("Comando inválido"); }
    }
}