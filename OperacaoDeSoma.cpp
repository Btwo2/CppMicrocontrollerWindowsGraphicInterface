#include "OperacaoDeSoma.h"

OperacaoDeSoma::OperacaoDeSoma(double valor) {
    this->value = valor;
}

OperacaoDeSoma::~OperacaoDeSoma() {
    //dtot
}

double OperacaoDeSoma::executar(double valor) {
    return value + valor;
}
