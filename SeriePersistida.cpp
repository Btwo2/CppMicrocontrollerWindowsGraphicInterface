#include "SeriePersistida.h"

SeriePersistida::SeriePersistida(string nome, vector <double>* valores) : Serie (nome) {
    this->nome = nome;
    this->valores = valores;
    this->tamanho = valores->size();
    this->vazia = valores->empty();
}

SeriePersistida::~SeriePersistida() {
    //dtor
}

bool SeriePersistida::estaVazia() {
    return vazia;
}

int SeriePersistida::getTamanho() {
    return tamanho;
}

double SeriePersistida::getValor(int posicao) {
    if(posicao < tamanho && posicao >= 0) {
        return valores->at (posicao);
    } else {
        throw new runtime_error("Posicao invalida");
    }
}

double SeriePersistida::getMinimo() {
    if (vazia) throw new runtime_error ("Serie vazia");
    else {
            double minimo = valores->at (0);

            for(int i = 1; i < tamanho; i++){
                if(minimo > valores->at (i)) minimo = valores->at (i);
            }
            return minimo;
    }
}

double SeriePersistida::getMaximo() {
    if (vazia) throw new runtime_error ("Serie vazia");
    else {
            double maximo = valores->at (0);

            for(int i = 1; i< tamanho; i++){
                if(maximo < valores->at (i)) maximo = valores->at (i);
            }
            return maximo;
    }
}
