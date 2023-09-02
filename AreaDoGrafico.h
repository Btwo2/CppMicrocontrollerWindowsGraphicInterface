#ifndef AREADOGRAFICO_H
#define AREADOGRAFICO_H

#include "Serie.h"
#include "Cursor.h"
#include "SeriePersistida.h"

#include <stdexcept>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

/**
 * Representa uma area do grafico que se deseja fazer medidas.
 *
 * A area e delimitada por dois cursores: c1 e c2. Os valores dos
 * cursores sao baseados nos valores das series.
 *
 * Evite duplicacao de codigo!
 *
 * @Version EP3
 */
class AreaDoGrafico {
public:
   /**
    * Cria uma area do grafico considerando a area entre dois cursores.
    * @throw out_of_range Caso os cursores nao delimitem uma area valida
    * (o c1 sempre deve ficar a esquerda e abaixo do c2).
    */
    AreaDoGrafico(Serie* x, Serie* y, Cursor* c1, Cursor* c2);
    virtual ~AreaDoGrafico();

    double getMaximoDaAbscissa();
    double getMinimoDaAbscissa();
    double getMediaDaAbscissa();
    double getDesvioPadraoDaAbscissa();

    double getMaximoDaOrdenada();
    double getMinimoDaOrdenada();
    double getMediaDaOrdenada();
    double getDesvioPadraoDaOrdenada();

private:
    SeriePersistida* xc; //serie com os valores da serie x delimitados pelos cursores
    SeriePersistida* yc; //serie com os valores da serie y delimitados pelos cursores

};

#endif // AREADOGRAFICO_H
