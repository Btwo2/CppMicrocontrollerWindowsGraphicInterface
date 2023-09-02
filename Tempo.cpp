#include "Tempo.h"

Tempo::Tempo(int tamanhoDaFaixa) : Serie("Tempo") {
    this->tamanhoDaFaixa = tamanhoDaFaixa;
    tempo = new int[tamanhoDaFaixa];
    vazia = true;
    //ctor
}

Tempo::~Tempo() {
    //dtor
}

void Tempo::incrementar() {
    if(vazia){
        tempo[0] = 1;
        vazia = false;
        tamanho++;
    } else {
            if(tamanho == tamanhoDaFaixa) Enqueue(tempo, tempo[inicio] + tamanhoDaFaixa);
            if (tamanho < tamanhoDaFaixa) {
                tamanho++;
                Enqueue(tempo, tamanho);
            }
    }
}

bool Tempo::estaVazia() {
    return vazia;
}

int Tempo::getTamanho() {
    return tamanho;
}

double Tempo::getValor(int posicao) {
    if (posicao < tamanhoDaFaixa && posicao >= 0) return tempo[posicao];
    else throw new out_of_range ("Posicao Invalida");
}

double Tempo::getMaximo() {
    if (vazia) throw new runtime_error ("Serie vazia");
    else {
            int maximo = tempo[0];

            for(int i = 1; i < tamanho; i++) {
                if(maximo < tempo[i]) maximo = tempo[i];
            }
            return maximo;
    }
}

double Tempo::getMinimo() {
    if (vazia) throw new runtime_error ("Serie vazia");
    else {
            int minimo = tempo[0];

            for(int i = 1; i < tamanho; i++) {
                if(minimo > tempo[i]) minimo = tempo[i];
            }
            return minimo;
    }
}

void Tempo::Enqueue(int *tempo, int valor) {
    if (fim == tamanhoDaFaixa - 1){
        fim = 0;
        inicio = 1;
    } else fim++;

    tempo[fim] = valor;

    if (inicio == tamanhoDaFaixa - 1) inicio = 0;
    if (fim == inicio) inicio++;
}
