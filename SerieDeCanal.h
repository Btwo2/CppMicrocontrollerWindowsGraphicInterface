#ifndef SERIEDECANAL_H_INCLUDED
#define SERIEDECANAL_H_INCLUDED

#include "Serie.h"
#include <stdexcept>

class SerieDeCanal : public Serie {
public:
    SerieDeCanal (string nome, int quantidadeMaxima);
    ~SerieDeCanal();

    bool estaVazia();
    int getTamanho();
    double getValor(int posicao);
    double getMaximo();
    double getMinimo();

    virtual void adicionar (double valor);

protected:
    double *serie_numerica;
    int inicio = 0;
    int fim = 0;
    int quantidadeMaxima; //definida pelo usuario

private:
    void Enqueue (double *serieDeCanal, double valor);  //fila circular
    void Dequeue (double *serieDeCanal);

};

#endif // SERIEDECANAL_H_INCLUDED
