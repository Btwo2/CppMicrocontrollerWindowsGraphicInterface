#ifndef SERIEPERSISTIDA_H
#define SERIEPERSISTIDA_H

#include "Serie.h"

#include <vector>
#include <stdexcept>

using namespace std;

/**
 * Representa uma serie que foi persistida e, portanto, carregada.
 *
 * Note que nao ha uma forma de adicionar valores, fora do construtor.
 *
 * @Version EP3
 */
class SeriePersistida : public Serie {
public:
    SeriePersistida (string nome, vector<double>* valores);
    virtual ~SeriePersistida();

    bool estaVazia();
    int getTamanho();
    double getValor(int posicao);
    double getMaximo();
    double getMinimo();

private:
    vector <double>* valores;

};

#endif // SERIEPERSISTIDA_H
