#ifndef OPERACAODESOMA_H_INCLUDED
#define OPERACAODESOMA_H_INCLUDED

#include "Operacao.h"

using namespace std;

class OperacaoDeSoma : public Operacao {
public:
    OperacaoDeSoma(double valor);
    virtual ~OperacaoDeSoma();
    virtual double executar(double valor);

private:
    double value;

};

#endif // OPERACAODESOMA_H_INCLUDED
