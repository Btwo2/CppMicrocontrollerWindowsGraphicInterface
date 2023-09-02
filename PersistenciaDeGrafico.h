#ifndef PERSISTENCIADEGRAFICO_H
#define PERSISTENCIADEGRAFICO_H

#include <vector>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <algorithm>

#include "Grafico.h"

/**
 * Cuida da persistencia de um grafico, salvando e obtendo graficos.
 *
 * Assuma que nao pode haver espacos nos campos string.
 *
 * Formato do arquivo:
 * NOME_DO_GRAFICO1
 * NUMERO_DE_VALORES
 * TITULO_X
 * UNIDADE_X
 * VALOR1
 * VALOR2
 * VALOR3
 * ...
 * TITULO_Y
 * UNIDADE_Y
 * VALOR1
 * VALOR2
 * VALOR3
 * ...
 * NOME_DO_GRAFICO2
 * ...
 * @Version EP3
 */

using namespace std;

class PersistenciaDeGrafico {
public:
    /**
    * Cria um objeto que persiste (insere e le) no 'arquivo'
    * @throw runtime_error Caso o arquivo nao siga o formato
    */
    /* ----REVISAO-FORMATO--INCERTO-------
       ---INT------DOUBLE------STRING-----
       ----CLASSES--TEMPO--INCREMENTAR??--
       --ERROS--EM--CLASSE--OU--DIRETOS--- */
    PersistenciaDeGrafico (Tela* tela, string arquivo);
    virtual ~PersistenciaDeGrafico();
    Grafico* obter (string nome);
    vector<string>* getNomes();
    void inserir (string nome, Grafico* g);

private:
    string arquivo;
    Tela* screen;
    vector<string> *nomes;
    vector<Grafico*> *graficos;
};

#endif // PERSISTENCIADOGRAFICO_H
