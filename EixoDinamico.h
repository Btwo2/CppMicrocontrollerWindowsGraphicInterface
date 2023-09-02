#ifndef EIXODINAMICO_H_INCLUDED
#define EIXODINAMICO_H_INCLUDED

#include "Eixo.h"
#include "Serie.h"
#include "SerieDeCanal.h"
#include "Tempo.h"

using namespace std;

class EixoDinamico : public Eixo{
public:
    EixoDinamico(Serie* serie, string unidade, int numeroDeDivisoes, double escalaMinimaInicial, double escalaMaximaInicial);
    virtual ~EixoDinamico();
    string getTitulo();
    string getUnidade();
    int getNumeroDeDivisoes();
    double getIncrementoDaDivisao();
    double getEscalaMinima();
    double getEscalaMaxima();

private:
    Serie* serieDoEixo;
};

#endif // EIXODINAMICO_H_INCLUDED
