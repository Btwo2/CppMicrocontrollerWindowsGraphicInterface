#ifndef SERIEPROCESSADA_H_INCLUDED
#define SERIEPROCESSADA_H_INCLUDED

#include "Serie.h"
#include "Operacao.h"

#include <stdexcept>

class SerieProcessada : public Serie {
public:
    SerieProcessada(string nome, Serie* original, Operacao* operacao);
    ~SerieProcessada();

    bool estaVazia();
    int getTamanho();
    double getValor(int posicao);
    double getMaximo();
    double getMinimo();

private:
    Serie* original;
    Operacao* operacao;

};

#endif // SERIEPROCESSADA_H_INCLUDED
