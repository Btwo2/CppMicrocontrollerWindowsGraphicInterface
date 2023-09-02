#ifndef TEMPO_H_INCLUDED
#define TEMPO_H_INCLUDED

#include "Serie.h"
#include "SerieDeCanal.h"
#include "Tempo.h"

#include <stdexcept>

class Tempo : public Serie{
public:
    Tempo(int tamanhoDaFaixa);
    virtual ~Tempo();
    virtual void incrementar(); //adicionar unidade de tempo

    bool estaVazia();
    int getTamanho();
    double getValor(int posicao);
    double getMaximo();
    double getMinimo();

protected:
    int *tempo;
    int inicio = 0;
    int fim = 0;
    int tamanhoDaFaixa;

private:
    void Enqueue (int *serieDeTempo, int valor);

};

#endif // TEMPO_H_INCLUDED
