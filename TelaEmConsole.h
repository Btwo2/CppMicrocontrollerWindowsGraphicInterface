#ifndef TELACONSOLE_H
#define TELACONSOLE_H

#include "Tela.h"

/**
 * Tela implementada em console.
 *
 * @Version EP3
 */
class TelaEmConsole : public Tela {
public:
  TelaEmConsole();
  virtual ~TelaEmConsole();

  void apagar();
  void adicionarPontoEm (int x, int y);
  void adicionarForaDoLimiteDasOrdenadasEm(int x, Limite y);
  void adicionarForaDoLimiteDasAbscissasEm(int y, Limite x);
  void adicionarForaDoLimiteEm(Limite x, Limite y);
  void setEixoDasAbscissas(Eixo* abscissas);
  void setEixoDasOrdenadas(Eixo* ordenadas);
  void desenhar();
  int getDivisaoAbscissa();
  int getDivisaoOrdenada();
  int getLarguraUtil();
  int getAlturaUtil();
private:
  // Por problemas no compilador do CodeBlocks
  template<typename T> static std::string to_string(const T &n);
  void incluirEixoDasAbscissas();
  void incluirEixoDasOrdenadas();
  int getColunaEixo();
  int getLinhaEixo();
  void limpar();
  void escrever(string texto, int x, int y, int largura);
  void escrever(double valor, int x, int y, int largura);
  char** buffer;
  Eixo *abscissas = nullptr;
  Eixo *ordenadas = nullptr;
};

#endif // TELACONSOLE_H
