/*Parte feita em sala acompanhando o professor e continuei sozinha em casa
Conceitos aprendidos: vetores, listas, uso de ponteiro e passagens por referencia*/
#define __LIST
#define __MEMORY
#pragma once
#include "fn.hpp"
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <list>

class Pessoa{
    private:
        std::string nome;
    public:
        Pessoa(std::string nome = ""){
            this->nome = nome;
        }

        std::string getNome() const{
            return nome;
        }

        std::string str() const{
            return this->nome;
        }
};

class Mercantil{
    std::vector<std::shared_ptr<Pessoa>> caixas; //insere e remove, começa nulo as posicoes.
    std::list<std::shared_ptr<Pessoa>> fila; //a fila anda: pessoa da posicao anterior fica na posicaoAnterior + 1; começa vazio.

    public:
        Mercantil(int n_caixas = 0 ){
            //inicia as posicoes do vetor com nullptr
            for(int i = 0; i < n_caixas; i++){
                caixas.push_back(nullptr);
            }
        }


    void chamarNoCaixa(int indice){
        if(caixas[indice] != nullptr){
            std::cout << "fail: caixa ocupado\n";
            return;
        }
        if(fila.size() == 0){
            std::cout << "fail: sem clientes\n";
            return;
        }
        //a primeira pessoa da fila vai ocupar a posicao (indice) do vetor
        caixas[indice] = fila.front();
        //removendo a pessoa da fila de espera
        fila.pop_front();
    }

    void chegar(std::shared_ptr<Pessoa> pessoa){
        fila.push_back(pessoa);
    }

    void finalizar(size_t indice){
        if(indice >= caixas.size()){
            std::cout << "fail: caixa inexistente\n";
            return;
        }
        if(caixas[indice] == nullptr){
            std::cout << "fail: caixa vazio\n";
            return;
        }
        caixas[indice] = nullptr;
    }

    std::string str() const {
        std::stringstream ss;
        ss << "Caixas: [";
        int i = 0;
        for (auto elem : caixas) {
            ss << (i++ != 0 ? ", " : "");
            ss << (elem ? elem->str() : "-----");
        }
        ss << "]\nEspera: [";
        bool first = true;
        for (auto elem : fila) {
            ss << (!first ? ", " : "") << (elem ? elem->str() : "");
            first = false;
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
        bank.chamarNoCaixa(indice);
    }
    void finish(int indice) {
        bank.finalizar(indice);
    }
    void arrive(const std::string& nome) {
        bank.chegar(std::make_shared<Pessoa>(nome));
    }

    void show() {
        fn::write(bank.str());
    }
};
