#ifndef TELA_H
#define TELA_H

#include "Eixo.h"

using namespace std;

/**
 * Eh um tipo que define apenas dois valores: SUPERIOR e INFERIOR.
 * Para usar eh so fazer: Limite::SUPERIOR ou Limite::INFERIOR.
 */
enum Limite{SUPERIOR, INFERIOR};

/**
 * Representa a tela onde o grafico sera plotado.
 * @Version EP3
 */
class Tela {
public:
  Tela();
  virtual ~Tela();

  /**
   * Apaga a tela.
   */
  virtual void apagar() = 0;

  /**
   * Adiciona um ponto na tela, nas coordenadas x e y da Tela.
   *
   * A tela tem tamanho LARGURA_UTIL x ALTURA_UTIL.
   * @throw out_of_range Caso x < 0 ou x >= LARGURA_UTIL
   * ou y < 0 ou y >= ALTURA_UTIL.
   */
  virtual void adicionarPontoEm (int x, int y) = 0;

  /**
   * Adiciona um ponto fora do limite do eixo das ordenadas.
   *
   * Por exemplo, se deseja-se desenhar o ponto (0, 11) no Grafico,
   * mas o Eixo y tem maximo 10, o ponto deve ser colocado no limite
   * superior das ordenadas e no ponto equivalente a x = 0.
   * @throw out_of_range Caso x < 0 ou x >= LARGURA_UTIL
   */
  virtual void adicionarForaDoLimiteDasOrdenadasEm(int x, Limite y) = 0;

  /**
   * Adiciona um ponto fora do limite do eixo das abscissas.
   *
   * Por exemplo, se deseja-se desenhar o ponto (0, 11), mas o Eixo x tem
   * minimo 5, o ponto deve ser colocado no limite inferior das
   * abscissas e no ponto equivalente a y = 11.
   * @throw out_of_range Caso y < 0 ou y >= ALTURA_UTIL.
   */
  virtual void adicionarForaDoLimiteDasAbscissasEm(int y, Limite x) = 0;

  /**
   * Adiciona um ponto fora do limite de ambos os eixos.
   *
   * Por exemplo, se deseja-se desenhar o ponto (0, 11), mas o Eixo x tem
   * minimo 5 e o Eixo y tem maximo 10 e esse ponto estaria fora da escala,
   * o ponto deve ser colocado no limite inferior das abscissas e no superior
   * das ordenadas.
   */
  virtual void adicionarForaDoLimiteEm(Limite x, Limite y) = 0;

  /**
   * Define o eixo das abscissas.
   */
  virtual void setEixoDasAbscissas(Eixo* abscissas) = 0;

  /**
   * Define o eixo das ordenadas.
   */
  virtual void setEixoDasOrdenadas(Eixo* ordenadas) = 0;

  /**
   * Desenha a tela, colocando os eixos definidos e os pontos adicionados.
   * @throw logic_error Caso os eixos nao tenham sido adicionados
   * @throw runtime_error Caso nao seja possivel desenhar
   */
  virtual void desenhar() = 0;

  /**
   * Obtem o numero de divisoes existentes na absissa
   */
  virtual int getDivisaoAbscissa() = 0;

  /**
   * Obtem o numero de divisoes existentes na ordenada
   */
  virtual int getDivisaoOrdenada() = 0;

  /**
   * Obtem a largura util da tela em pontos. Ou seja, eh possivel plotar de
   * 0 a getLarguraUtil().
   */
  virtual int getLarguraUtil() = 0;

  /**
   * Obtem a altura util da tela em pontos. Ou seja, eh possivel plotar de
   * 0 a getAlturaUtil().
   */
  virtual int getAlturaUtil() = 0;
};

#endif // TELA_H
