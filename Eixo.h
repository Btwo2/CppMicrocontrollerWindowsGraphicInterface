#ifndef EIXO_H
#define EIXO_H

#include <string>
#include <stdexcept>

using namespace std;

/**
 * Representa um Eixo do grafico.
 *
 * @Version EP3
 */
class Eixo {
public:

  /**
   * @throw runtime_error caso escalaMinima >= escalaMaxima
   */
  Eixo(string titulo, string unidade, int numeroDeDivisoes,
       double escalaMinima, double escalaMaxima);
  virtual ~Eixo();

  virtual string getTitulo();
  virtual string getUnidade();
  virtual int getNumeroDeDivisoes();

  /**
   * Calcule o incremento da divisao a partir do maximo, minimo
   * e numero de divisoes, seguindo exatamente o enunciado.
   *
   * Deve-se assumir que os valores necessarios ja foram
   * definidos antes de chamar este metodo.
   */
  virtual double getIncrementoDaDivisao();
  virtual double getEscalaMinima();
  virtual double getEscalaMaxima();

protected:
    string titulo;
    string unidade;
    int numeroDeDivisoes;
    double escalaMinima;
    double escalaMaxima;
    double incrementoDaDivisao;
};

#endif // EIXO_H
