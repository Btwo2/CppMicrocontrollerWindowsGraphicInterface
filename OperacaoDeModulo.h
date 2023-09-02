#ifndef OPERACAODEMODULO_H_INCLUDED
#define OPERACAODEMODULO_H_INCLUDED

#include "Operacao.h"

class OperacaoDeModulo : public Operacao {
public:
    OperacaoDeModulo();
    virtual ~OperacaoDeModulo();
    virtual double executar(double valor);

};

#endif // OPERACAODEMODULO_H_INCLUDED
