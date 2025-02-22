
#include <iostream>
#include <vector>
#include <algorithm> // Para sort e shuffle
#include <random>    // Para gerar números aleatórios

class Foo {
public:
    int x;
    Foo(int x) : x(x) {}
    std::string str() const { return "Foo(" + std::to_string(x) + ")"; }
};

void printVector(const std::vector<int>& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << vec[i];
        if (i < vec.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
}

void printVector(const std::vector<Foo>& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << vec[i].str();
        if (i < vec.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
}

int main() {
    std::vector<int> lista_vazia;
    std::vector<int> lista_preenchida = {1, 2, 3, 4, 5};
    std::vector<Foo> lista_preenchida_objetos = {Foo(1), Foo(2), Foo(3), Foo(4), Foo(5)};
    
    // Adicionar elementos
    lista_vazia.push_back(1);
    lista_preenchida.push_back(6);
    lista_preenchida_objetos.push_back(Foo(6));
    
    // Impressão formatada
    printVector(lista_vazia);
    printVector(lista_preenchida);
    printVector(lista_preenchida_objetos);
    
    // Criar array com sequência 0 a n
    int n = 10;
    std::vector<int> sequencia(n);
    for (int i = 0; i < n; i++) {
        sequencia[i] = i;
    }
    printVector(sequencia);
    
    // Criar array com valores aleatórios
    std::vector<int> aleatorios(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    for (int& num : aleatorios) {
        num = dis(gen);
    }
    printVector(aleatorios);
    
    // Acessar elementos
    std::cout << "Primeiro elemento: " << lista_preenchida[0] << "\n";
    
    // Percorrer elementos com range-based for
    for (int num : lista_preenchida) {
        std::cout << num << " ";
    }
    std::cout << "\n";
    
    // Percorrer com índice
    for (size_t i = 0; i < lista_preenchida.size(); i++) {
        std::cout << lista_preenchida[i] << " ";
    }
    std::cout << "\n";
    
    // Procurar elemento X
    int x = 3;
    auto it = std::find(lista_preenchida.begin(), lista_preenchida.end(), x);
    if (it != lista_preenchida.end()) {
        std::cout << "Elemento " << x << " encontrado\n";
    } else {
        std::cout << "Elemento " << x << " nao encontrado\n";
    }
    
    // Criar array filtrado (pares)
    std::vector<int> pares;
    for (int num : lista_preenchida) {
        if (num % 2 == 0) pares.push_back(num);
    }
    printVector(pares);
    
    // Criar array transformado (ao quadrado)
    std::vector<int> quadrados;
    for (int num : lista_preenchida) {
        quadrados.push_back(num * num);
    }
    printVector(quadrados);
    
    // Remover elemento X
    lista_preenchida.erase(std::remove(lista_preenchida.begin(), lista_preenchida.end(), x), lista_preenchida.end());
    printVector(lista_preenchida);
    
    // Remover todos os elementos X (exemplo com 6)
    lista_preenchida.erase(std::remove(lista_preenchida.begin(), lista_preenchida.end(), 6), lista_preenchida.end());
    printVector(lista_preenchida);
    
    // Funções nativas
    std::sort(lista_preenchida.begin(), lista_preenchida.end()); // Ordenação
    std::shuffle(lista_preenchida.begin(), lista_preenchida.end(), gen); // Embaralhamento
    printVector(lista_preenchida);
    
    return 0;
}
