#pragma once
#include "fn.hpp"
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <list>

class Pessoa{
    private:
        std::string cliente;
    public:
        Pessoa(std::string cliente = ""){
            this->cliente = cliente;
        }
};

class Mercantil{
    int qtd{0};
    std::vector<std::shared_ptr<Pessoa>> caixas; //insere e remove, começa nulo as posicoes.
    std::list<std::shared_ptr<Pessoa>> espera; //a fila anda: pessoa da posicao anterior fica na posicaoAnterior + 1; começa vazio.

    public:
        Mercantil(int qtd = 0):caixas(qtd, nullptr){}

    std::string str() const{
        std::stringstream ss;
        ss << "Caixas: [";
        int i = 0;
        for( auto elem : caixas){
            ss << (i++ != 0 ? ", " : "");
            ss << "-----";
        }
        ss << "]\nEspera: [";
        for(auto elem : espera){
            ss << " ";
        }
        ss << "]";
        return ss.str();
    }
};

class Adapter {
    Mercantil bank;
public:
    void init(int qtd_caixas) {
        bank = Mercantil(qtd_caixas);
    }
    void call(int indice) {
        (void) indice;
        // bank.chamarNoCaixa(indice);
    }
    void finish(int indice) {
        (void) indice;
        // bank.finalizar(indice);
    }
    void arrive(const std::string& nome) {
        // bank.chegar(std::make_shared<Pessoa>(nome));
        (void) nome;
    }

    void show() {
        // fn::write(bank.str());
    }
};
