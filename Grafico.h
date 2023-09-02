#ifndef GRAFICO_H_INCLUDED
#define GRAFICO_H_INCLUDED
#include "TelaEmConsole.h"
#include "Serie.h"
#include "SerieDeCanal.h"
#include "Tempo.h"
#include "EixoDinamico.h"

using namespace std;

class Grafico {
public:
    Grafico(Tela* tela, Serie* x, Serie *y, Eixo* abscissas, Eixo* ordenadas);
    virtual ~Grafico();
    virtual void desenhar();
    virtual void reset();
    virtual Serie* getSerieNasAbscissas();
    virtual Serie* getSerieNasOrdenadas();
    virtual Eixo* getEixoDasAbscissas();
    virtual Eixo* getEixoDasOrdenadas();

private:
    Serie* serieNasAbscissas;
    Serie* serieNasOrdenadas;
    Eixo* eixoDasAbscissas;
    Eixo* eixoDasOrdenadas;
    Tela* screen;
};
#endif // GRAFICO_H_INCLUDED
