#include "TelaEmConsole.h"

#include <iostream>
#include <cmath>
#include <stdexcept>
#include <sstream>
#include <string>

#include "Eixo.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define SETA_CIMA '^'
#define SETA_DIREITA '>'
#define LINHA_EIXO_ABSCISSAS '-'
#define MARCADOR_EIXO_ABSCISSAS '|'
#define LINHA_EIXO_ORDENADAS '|'
#define MARCADOR_EIXO_ORDENADAS '-'
#define PONTO 'X'
#define ERRO 'O'

#define LARGURA_DA_TELA 74
#define ALTURA_DA_TELA 20

// Constantes da tela
#define LARGURA_UTIL 61
#define ALTURA_UTIL 16

#define DIVISAO_ABSCISSA 10
#define DIVISAO_ORDENADA 5

#define LARGURA_TEXTO 6
#define LARGURA_NUMERO 5

using namespace std;

TelaEmConsole::TelaEmConsole() {
	buffer = new char*[ALTURA_DA_TELA];

	for (int i = 0; i < ALTURA_DA_TELA; i++) {
    buffer[i] = new char[LARGURA_DA_TELA];
	}
	apagar();
}

TelaEmConsole::~TelaEmConsole() {
	for (int i = 0; i < ALTURA_DA_TELA; i++) {
    delete[] buffer[i];
	}

	delete[] buffer;
}

void TelaEmConsole::apagar() {
  limpar();
	for (int h = 0; h < ALTURA_DA_TELA; h++) {
		for (int l = 0; l < LARGURA_DA_TELA; l++) {
			buffer[h][l] = ' ';
		}
	}
}

// http://www.cplusplus.com/articles/4z18T05o/
void TelaEmConsole::limpar() {

#ifdef _WIN32
  HANDLE                     hStdOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD                      count;
  DWORD                      cellCount;
  COORD                      homeCoords = { 0, 0 };

  hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
  if (hStdOut == INVALID_HANDLE_VALUE) return;

  /* Get the number of cells in the current buffer */
  if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
  cellCount = csbi.dwSize.X *csbi.dwSize.Y;

  /* Fill the entire buffer with spaces */
  if (!FillConsoleOutputCharacter(
    hStdOut,
    (TCHAR) ' ',
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Fill the entire buffer with the current colors and attributes */
  if (!FillConsoleOutputAttribute(
    hStdOut,
    csbi.wAttributes,
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Move the cursor home */
  SetConsoleCursorPosition(hStdOut, homeCoords);
#else
  write(1,"\E[H\E[2J",7);
  //cout << "\f";
#endif
}

int TelaEmConsole::getColunaEixo() {
	return LARGURA_DA_TELA - LARGURA_UTIL - 1;
}

int TelaEmConsole::getLinhaEixo() {
	return ALTURA_UTIL;
}

void TelaEmConsole::incluirEixoDasAbscissas() {
  if (abscissas == nullptr) {
    throw new logic_error("Eixo das abscissas nao definido.");
  }

	buffer[getLinhaEixo()][LARGURA_DA_TELA - 1] = SETA_DIREITA;

	// Linha
	for (int i = getColunaEixo(); i < LARGURA_DA_TELA - 1; i++) {
		if (buffer[getLinhaEixo()][i] == ' ')
      buffer[getLinhaEixo()][i] = LINHA_EIXO_ABSCISSAS;
	}

	// Divisoes
	int divisao = 0;
  for (int i = getColunaEixo(); i < LARGURA_DA_TELA - 1; i += DIVISAO_ABSCISSA) {
    if (buffer[getLinhaEixo() + 1][i] == ' ')
		buffer[getLinhaEixo() + 1][i] = MARCADOR_EIXO_ABSCISSAS;
		// Imprimindo o valor
		string texto = to_string(abscissas->getEscalaMinima() + abscissas->getIncrementoDaDivisao() * divisao);
		// Arrumando a posicao do valor no centro e evitando estouro na ultima posicao
		int posicao = i;
		if (i + ((texto.length() < LARGURA_NUMERO)?texto.length():LARGURA_NUMERO) > LARGURA_DA_TELA) {
      // Eh a ultima posicao e vai estourar
      posicao -= (i + LARGURA_NUMERO) - LARGURA_DA_TELA;
		} else {
		  // centralizando
		  posicao -= ((texto.length() < LARGURA_NUMERO)?(texto.length() / 2):(LARGURA_NUMERO / 2));
		}
    escrever(abscissas->getEscalaMinima() + abscissas->getIncrementoDaDivisao() * divisao, posicao, getLinhaEixo() + 2, LARGURA_NUMERO);
    divisao++;
  }

    // Titulo
  escrever(abscissas->getTitulo(), LARGURA_DA_TELA - 2 * LARGURA_TEXTO - 2, getLinhaEixo() + 3, LARGURA_TEXTO);
  buffer[getLinhaEixo() + 3][LARGURA_DA_TELA - LARGURA_TEXTO - 1] = '(';
  escrever(abscissas->getUnidade(), LARGURA_DA_TELA - LARGURA_TEXTO, getLinhaEixo() + 3, LARGURA_TEXTO - 2);
  int posicaoFechaParenteses = LARGURA_DA_TELA - 1;
  while (posicaoFechaParenteses > LARGURA_DA_TELA - LARGURA_TEXTO - 1 && buffer[getLinhaEixo() + 3][posicaoFechaParenteses] == ' ') {
    posicaoFechaParenteses--;
  }
  buffer[getLinhaEixo() + 3][posicaoFechaParenteses + 1] = ')';
}

void TelaEmConsole::incluirEixoDasOrdenadas() {
  if (ordenadas == nullptr) {
    throw new logic_error("Eixo das ordenadas nao definido.");
  }

  buffer[0][getColunaEixo()] = SETA_CIMA;

  // Linha
	for (int i = 1; i < getLinhaEixo(); i++) {
    if (buffer[i][getColunaEixo()] == ' ')
      buffer[i][getColunaEixo()] = LINHA_EIXO_ORDENADAS;
	}

	// Divisoes
	int divisao = 0;
  for (int i = getLinhaEixo(); i > 0; i -= DIVISAO_ORDENADA) {
    if (buffer[i][getColunaEixo() - 1] == ' ')
		buffer[i][getColunaEixo() - 1] = MARCADOR_EIXO_ORDENADAS;
    escrever(ordenadas->getEscalaMinima() + ordenadas->getIncrementoDaDivisao() * divisao, getColunaEixo() - 1 - LARGURA_NUMERO, i, LARGURA_NUMERO);
    divisao++;
  }

  // Titulo
  escrever(ordenadas->getTitulo(), 0, 1, LARGURA_TEXTO);
  buffer[2][0] = '(';
  escrever(ordenadas->getUnidade(), 1, 2, LARGURA_TEXTO - 2);
  int posicaoFechaParenteses = LARGURA_TEXTO - 1;
  while (posicaoFechaParenteses > 0 && buffer[2][posicaoFechaParenteses] == ' ') {
    posicaoFechaParenteses--;
  }
  buffer[2][posicaoFechaParenteses + 1] = ')';
}

void TelaEmConsole::escrever(string texto, int x, int y, int largura) {
  // Escreve no maximo largura caracteres
  for (int i = 0; i < largura && i < (int) texto.length() && x + i < LARGURA_DA_TELA; i++) {
    buffer[y][x + i] = texto[i];
  }
}

void TelaEmConsole::escrever(double valor, int x, int y, int largura) {
  // Escreve no maximo largura caracteres
  string texto = to_string(valor);

  if (valor > pow(10, largura)) {
    throw new runtime_error("Valor maior que o possivel de representar: " + to_string(texto));
  }
  escrever(texto, x, y, largura);
}

void TelaEmConsole::adicionarPontoEm (int x, int y) {
  if (x < 0 || x >= LARGURA_UTIL) {
    throw new out_of_range("x fora dos limites: " + to_string(x));
  }

  if (y < 0 || y >= ALTURA_UTIL) {
    throw new out_of_range("y fora dos limites: " + to_string(y));
  }

  buffer[getLinhaEixo() - y][getColunaEixo() + x] = PONTO;
}

void TelaEmConsole::adicionarForaDoLimiteDasOrdenadasEm(int x, Limite y) {
  if (x >= 0 && x < LARGURA_UTIL) {
    if (y == Limite::SUPERIOR)
      buffer[0][getColunaEixo() + x] = ERRO;
    else buffer[getLinhaEixo() + 1][getColunaEixo() + x] = ERRO;
  } else throw new out_of_range("x fora dos limites: " + to_string(x));
}

void TelaEmConsole::adicionarForaDoLimiteDasAbscissasEm(int y, Limite x) {
  if (y >= 0 && y < ALTURA_UTIL) {
    if (x == Limite::SUPERIOR)
      buffer[getLinhaEixo() - y][LARGURA_DA_TELA - 1] = ERRO;
    else buffer[getLinhaEixo() - y][getColunaEixo() - 1] = ERRO;
  } else throw new out_of_range("y fora dos limites: " + to_string(y));
}

void TelaEmConsole::adicionarForaDoLimiteEm(Limite x, Limite y) {
  int posicaoX, posicaoY;

  if (x == Limite::SUPERIOR)
    posicaoX = LARGURA_DA_TELA - 1;
  else posicaoX = getColunaEixo() - 1;

  if (y == Limite::SUPERIOR)
    posicaoY = 0;
  else posicaoY = getLinhaEixo() + 1;

  buffer[posicaoY][posicaoX] = ERRO;
}

void TelaEmConsole::setEixoDasAbscissas (Eixo* abscissas) {
	this->abscissas = abscissas;
}

void TelaEmConsole::setEixoDasOrdenadas (Eixo* ordenadas) {
	this->ordenadas = ordenadas;
}

void TelaEmConsole::desenhar() {
  incluirEixoDasAbscissas();
  incluirEixoDasOrdenadas();

	for (int h = 0; h < ALTURA_DA_TELA; h++) {
      for (int l = 0; l < LARGURA_DA_TELA; l++) {
        cout << buffer[h][l];
      }
      cout << endl;
	}
}

int TelaEmConsole::getDivisaoAbscissa() {
  return DIVISAO_ABSCISSA;
}

int TelaEmConsole::getDivisaoOrdenada() {
  return DIVISAO_ORDENADA;
}

int TelaEmConsole::getLarguraUtil() {
  return LARGURA_UTIL;
}

int TelaEmConsole::getAlturaUtil() {
  return ALTURA_UTIL;
}

template<typename T> string TelaEmConsole::to_string(const T &n) {
  std::ostringstream stm;
  stm << n;
  return stm.str();
}