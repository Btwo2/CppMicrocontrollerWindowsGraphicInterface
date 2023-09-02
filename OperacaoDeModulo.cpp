#include "OperacaoDeModulo.h"

OperacaoDeModulo::OperacaoDeModulo() {
    //ctor
}

OperacaoDeModulo::~OperacaoDeModulo() {
    //dtor
}

double OperacaoDeModulo::executar(double valor) {
    if (valor < 0) return -valor;
    else return valor;
}
