#include "SerieProcessada.h"

#include <iostream>

SerieProcessada::SerieProcessada(string nome, Serie* original, Operacao* operacao) : Serie (nome) {
    this->nome = nome;
    this->original = original;
    this->operacao = operacao;
    this->vazia = false;
    this->tamanho = original->getTamanho();

}

SerieProcessada::~SerieProcessada() {
    //dtor
}


bool SerieProcessada::estaVazia() {
    return vazia;
}

int SerieProcessada::getTamanho() {
    return tamanho;
}

double SerieProcessada::getValor(int posicao) {
    if(posicao < tamanho && posicao >= 0) return operacao->executar(original->getValor(posicao));
    else throw new runtime_error("Posicao invalida");
}

double SerieProcessada::getMaximo() {
    if (vazia) throw new runtime_error ("Serie vazia");
    else {
            double maximo = original->getValor(0);

            for(int i = 1; i < tamanho; i++){
                if(maximo > operacao->executar(original->getValor(i))) maximo = operacao->executar(original->getValor(i));
            }
            return maximo;
    }
}

double SerieProcessada::getMinimo() {
    if (vazia) throw new runtime_error ("Serie vazia");
    else {
            double minimo = original->getValor(0);

            for(int i = 1; i < tamanho; i++){
                if(minimo > operacao->executar(original->getValor(i))) minimo = operacao->executar(original->getValor(i));
            }
            return minimo;
    }
}
