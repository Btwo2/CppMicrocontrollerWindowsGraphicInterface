#include "Eixo.h"

Eixo::Eixo(string titulo, string unidade, int numeroDeDivisoes, double escalaMinima, double escalaMaxima){
    this->titulo = titulo;
    this->unidade = unidade;
    this->numeroDeDivisoes = numeroDeDivisoes;
    if (escalaMinima >= escalaMaxima) throw new runtime_error ("Escala Minima >= Escala Maxima");
    this->escalaMinima = escalaMinima;
    this->escalaMaxima = escalaMaxima;
    incrementoDaDivisao = (escalaMaxima - escalaMinima)/numeroDeDivisoes;

    //ctor
}

Eixo::~Eixo(){
    //dtor
}

string Eixo::getTitulo(){
    return titulo;
}

string Eixo::getUnidade(){
    return unidade;
}

int Eixo::getNumeroDeDivisoes(){
    return numeroDeDivisoes;
}

double Eixo::getIncrementoDaDivisao(){
    return (escalaMaxima - escalaMinima)/numeroDeDivisoes;
}

double Eixo::getEscalaMinima(){
    return escalaMinima;
}

double Eixo::getEscalaMaxima(){
    return escalaMaxima;
}

