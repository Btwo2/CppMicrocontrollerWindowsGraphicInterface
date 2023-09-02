#include "SerieDeCanal.h"

SerieDeCanal::SerieDeCanal (string nome, int quantidadeMaxima) : Serie (nome) {
    this->quantidadeMaxima = quantidadeMaxima;
    serie_numerica = new double[quantidadeMaxima];
    vazia = true;
}

SerieDeCanal::~SerieDeCanal() {
  //dtor
}

bool SerieDeCanal::estaVazia() {
    return vazia;
}

int SerieDeCanal::getTamanho() {
    return tamanho;
}

double SerieDeCanal::getValor(int posicao) {
    if(posicao < quantidadeMaxima && posicao >= 0) return serie_numerica[posicao];
    else throw new out_of_range ("Posicao Invalida");
}

double SerieDeCanal::getMinimo() {
    if (vazia) throw new runtime_error ("Serie vazia");
    else {
        double minimo = serie_numerica[0];

        for(int i = 1; i < tamanho; i++){
            if(minimo > serie_numerica[i]) minimo = serie_numerica[i];
        }
        return minimo;
    }
}

double SerieDeCanal::getMaximo() {
    if (vazia) throw new runtime_error ("Serie vazia");
    else {
            double maximo = serie_numerica[0];

            for (int i = 1; i< tamanho; i++){
                if (maximo < serie_numerica[i]) maximo = serie_numerica[i];
            }
            return maximo;
    }
}

void SerieDeCanal::adicionar (double valor) {
    if(vazia){
        serie_numerica[0] = valor;
        vazia = false;
        tamanho++;
        fim++;
    } else {
            if(tamanho == quantidadeMaxima) {
                Enqueue(serie_numerica,valor);
            } else {
                Enqueue(serie_numerica, valor);
                tamanho++;
            }
    }
}

void SerieDeCanal::Enqueue(double *serie_numerica, double valor) {
    serie_numerica[fim] = valor;
    fim = fim + 1;

    if (fim == inicio) inicio = 1;
    if (fim == quantidadeMaxima) {
            fim = 0;
            inicio = 1;
    }
}
