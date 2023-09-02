#include "EixoDinamico.h"

EixoDinamico::EixoDinamico(Serie* serie, string unidade, int numeroDeDivisoes, double escalaMinimaInicial, double escalaMaximaInicial) : Eixo(serie->getNome(), unidade, numeroDeDivisoes, escalaMinimaInicial,escalaMaximaInicial){
    serieDoEixo = serie;
    if (escalaMinima >= escalaMaxima) throw new runtime_error ("Escala Minima >= Escala Maxima");
    //ctor
}

EixoDinamico::~EixoDinamico(){
    //dtor
}

string EixoDinamico::getTitulo(){
    return titulo;
}

string EixoDinamico::getUnidade(){
    return unidade;
}

int EixoDinamico::getNumeroDeDivisoes(){
    return numeroDeDivisoes;
}

double EixoDinamico::getIncrementoDaDivisao(){
    return (getEscalaMaxima() - getEscalaMinima())/numeroDeDivisoes;
}

double EixoDinamico::getEscalaMinima(){
    if (serieDoEixo->getTamanho() >= 2) {
        escalaMinima = serieDoEixo->getMinimo();
    }
    return escalaMinima;
}

double EixoDinamico::getEscalaMaxima(){
    if (serieDoEixo->getTamanho() >= 2) {
        escalaMaxima = serieDoEixo->getMaximo();
    }
    return escalaMaxima;
}
