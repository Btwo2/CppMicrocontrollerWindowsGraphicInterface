//Bruno Cesar Martins - nusp 9836923
//Lucca Scholler Ferreira Bonetti - nusp 9853280

#include <iostream>
#include <string.h>
#include "Tempo.h"
#include "SerieDeCanal.h"
#include "SeriePersistida.h"
#include "SerieProcessada.h"
#include "EixoDinamico.h"
#include "Grafico.h"
#include "TelaEmConsole.h"
#include "IHC.h"
#include "InterfaceSerial.h"
#include "Cursor.h"
#include "PersistenciaDeGrafico.h"
#include "OperacaoDeModulo.h"
#include "OperacaoDeSoma.h"
#include "AreaDoGrafico.h"

using namespace std;

int main(void){
    InterfaceSerial *is = new InterfaceSerial();
    Serie *serieX, *serieY;
    Grafico *g;
    Tela* tela = new TelaEmConsole();               //pre-definido
    PersistenciaDeGrafico* p = new PersistenciaDeGrafico(tela, "dados.txt");
    Operacao *operacaoX, *operacaoY;
    string correcaoX, correcaoY;
    string carregar;

    is->inicializar("i");
    cout << "Carregar um grafico (s/n): ";
    cin >> carregar;

    while (carregar != "s" && carregar != "n"){       // condicao para tipos invalidados
        cout << endl << "ERRO: INVALIDO" << endl << endl;
        cout << "Carregar um grafico (s/n): " << endl << endl;
        cin >> carregar;
    }

    if (carregar == "s") {
        int numeroDoGrafico;

        cout << endl << "Graficos disponiveis: " << endl;

        for (int i = 0; i < p->getNomes()->size(); i++) {
            cout << i+1 << ") " <<  p->getNomes()->at(i) << endl;
        }

        cout << endl << "Digite o numero do grafico para carregar: ";
        cin >> numeroDoGrafico;

        while (cin.fail() || numeroDoGrafico <= 0 || numeroDoGrafico > p->getNomes()->size()){    // condicao para series invalidadas
            cout << endl << "ERRO: GRAFICO INVALIDO" << endl << endl;
            cout << "Escolha um grafico valido: " << endl << endl;
            cout << "Graficos disponiveis" << endl;

            for (int i = 0; i < p->getNomes()->size(); i++){
                cout << i+1 << ") " << p->getNomes()->at(i) << endl;
            }

            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cin >> numeroDoGrafico;
        }

        numeroDoGrafico = numeroDoGrafico-1;
        g = p->obter(p->getNomes()->at (numeroDoGrafico));
        serieX = g->getSerieNasAbscissas();
        serieY = g->getSerieNasOrdenadas();

        for (int i = 0; i <= p->getNomes()->size(); i++) {
            if (numeroDoGrafico == i) {
                is->registrar(serieX->getNome(), serieX);
                is->registrar(serieY->getNome(), serieY);
            }
        }
        delete p;
    }

    if (carregar == "n") {
        int numeroDaSerieX;
        int quantidadeMaximaDeValoresX;
        int numeroDaSerieY;
        int quantidadeMaximaDeValoresY;
        int escalaMinimaInicialY;
        int escalaMaximaInicialY;
        double escalaMinimaInicialX;
        double escalaMaximaInicialX;
        string correcaoX;
        string tipoDeEixoX;
        string unidadeEixoX;
        string correcaoY;
        string tipoDeEixoY;
        string unidadeEixoY;
        Eixo *eixoX, *eixoY;

        cout << endl << "Escolha uma serie para o eixo X:" << endl;
        cout << "0) Tempo" << endl;
        /*for(int i = 0; i < is->getQuantidadeDeCanais(); i++){
          cout << i+1 << ") " << is->getNomeDosCanais()[i] << endl;
        }*/
        cin >> numeroDaSerieX;

        while (cin.fail() || numeroDaSerieX != 0) {//< 0 || numeroDaSerieX > is->getQuantidadeDeCanais()){    // condicao para series invalidadas
            cout << endl << "ERRO: SERIE INVALIDA" << endl << endl;
            cout << "Escolha uma serie valida para o eixo X: " << endl;
            cout << "0) Tempo" << endl;
            /*for(int i = 0; i < is->getQuantidadeDeCanais(); i++){
                    cout << i+1 << ") " << is->getNomeDosCanais()[i] << endl;
            }*/
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cin >> numeroDaSerieX;
        }

        cout << endl << "Informe a quantidade maxima de valores: ";
        cin >> quantidadeMaximaDeValoresX;

        while (quantidadeMaximaDeValoresX <= 0 || cin.fail()) {    // condicao para valores invalidadas
            cout << endl << "ERRO: QUANTIDADE INVALIDA" << endl << endl;
            cout << "Informe uma quantidade maxima de valores valida para o eixo X: ";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cin >> quantidadeMaximaDeValoresX;
        }

        cout <<endl << "Aplicar correcao (s)oma, (m)odulo ou (n)enhum: ";
        cin >> correcaoX;

        while (correcaoX != "s" && correcaoX != "m" && correcaoX != "n") {       // condicao para tipos invalidados
            cout << endl << "TIPO INVALIDO" << endl << endl;
            cout << "Tipos Validos:" << endl;
            cout << "S) Soma " << endl;
            cout << "M) Modulo" << endl;
            cout << "N) Nenhum" << endl;
            cin >> correcaoX;
        }

        if (correcaoX == "s") {
            int valor_correcao;

            cout << endl << "Valor da correcao: ";
            cin >> valor_correcao;

            while (cin.fail()) {                            // condicao para escalas invalidadas
                cout << endl << "ERRO: VALOR INVALIDO" << endl << endl;
                cout << "Informe um valor valido: ";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cin >> valor_correcao;
            }
         operacaoX = new OperacaoDeSoma(valor_correcao);
        }

        if (correcaoX == "m") {
            operacaoX = new OperacaoDeModulo();
        }

        cout << endl << "O eixo deve ser (e)statico ou (d)inamico: ";
        cin >> tipoDeEixoX;

        while (tipoDeEixoX != "e" && tipoDeEixoX != "d"){       // condicao para tipos invalidados
            cout << endl << "ERRO: TIPO INVALIDO" << endl << endl;
            cout << "Tipos Validos:" << endl;
            cout << "D) Dinamico " << endl;
            cout << "E) Estatico " << endl;
            cin >> tipoDeEixoX;
        }

        cout << endl <<"Informe a unidade do eixo: ";
        cin >> unidadeEixoX;
        cout << endl <<"Informe a escala minima inicial: ";
        cin >> escalaMinimaInicialX;

        while (cin.fail()) {                            // condicao para escalas invalidadas
            cout << endl << "ERRO: ESCALA INVALIDA" << endl << endl;
            cout << "Informe uma escala minima inicial valida para o eixo X: ";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cin >> escalaMinimaInicialX;
        }

        cout << endl << "Informe a escala maxima inicial: ";
        cin >> escalaMaximaInicialX;

        while (cin.fail()) {                            // condicao para escalas invalidadas
            cout << endl << "ERRO: ESCALA INVALIDA" << endl << endl;
            cout << "Informe uma escala maxima inicial valida para o eixo X: ";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cin >> escalaMaximaInicialX;
        }

        while (escalaMaximaInicialX <= escalaMinimaInicialX){        // condicao para escalas inversas
            cout << endl << "ESCALA MAXIMA MENOR/IGUAL A ESCALA MINIMA" << endl << endl;
            cout << "Informe a escala minima inicial: ";
            cin >> escalaMinimaInicialX;

            while (cin.fail()) {                            // condicao para escalas invalidadas
                cout << endl << "ERRO: ESCALA INVALIDA" << endl << endl;
                cout << "Informe uma escala minima inicial valida para o eixo X: ";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cin >> escalaMinimaInicialX;
            }

            cout << endl << "Informe a escala maxima inicial: ";
            cin >> escalaMaximaInicialX;

            while (cin.fail()) {                            // condicao para escalas invalidadas
                cout << endl << "ERRO: ESCALA INVALIDA" << endl << endl;
                cout << "Informe uma escala maxima inicial valida para o eixo X: ";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cin >> escalaMaximaInicialX;
            }
        }

        cout << endl;
        cout << "Escolha uma serie para o eixo Y: " << endl;
        /*for(int i = 0; i < is->getQuantidadeDeCanais(); i++) {
            cout << i+1 << ") " << is->getNomeDosCanais()[i] << endl;
        }*/

        cin >> numeroDaSerieY;

        while (cin.fail() || numeroDaSerieY != 0) {//< 0 || numeroDaSerieY > is->getQuantidadeDeCanais()){    // condicao para series invalidadas
            cout << endl << "ERRO: SERIE INVALIDA" << endl << endl;
            cout << "Escolha uma serie valida para o eixo Y: " << endl << endl;
            //for(int i = 0; i < is->getQuantidadeDeCanais(); i++)
            //  cout << i+1 << ") " << is->getNomeDosCanais()[i] << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cin >> numeroDaSerieY;
        }

        cout << endl << "Informe a quantidade maxima de valores: ";
        cin >> quantidadeMaximaDeValoresY;

        while (quantidadeMaximaDeValoresY < 0 || cin.fail()) {    // condicao para valores invalidadas
            cout << endl << "ERRO: QUANTIDADE INVALIDA" << endl << endl;
            cout << "Informe uma quantidade maxima de valores valida para o eixo Y: ";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cin >> quantidadeMaximaDeValoresY;
        }

        cout <<endl << "Aplicar correcao (s)oma, (m)odulo ou (n)enhum: ";
        cin >> correcaoY;

        while (correcaoY != "s" && correcaoY != "m" && correcaoY != "n"){       // condicao para tipos invalidados
            cout << endl << "TIPO INVALIDO" << endl << endl;
            cout << "Aplicar correcao (s)oma, (m)odulo ou (n)enhum: " << endl;
            cin >> correcaoY;
        }

        if (correcaoY == "s") {
            int valor_correcao;

            cout << endl << "Valor da correcao: ";
            cin >> valor_correcao;

            while (cin.fail()) {                            // condicao para escalas invalidadas
                cout << endl << "ERRO: VALOR INVALIDO" << endl << endl;
                cout << "Informe um valor valido: ";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cin >> valor_correcao;
            }
            operacaoY = new OperacaoDeSoma(valor_correcao);
        }

        if (correcaoY == "m") {
            operacaoY = new OperacaoDeModulo();
        }

        cout << endl << "O eixo deve ser (e)statico ou (d)inamico: ";
        cin >> tipoDeEixoY;

        while (tipoDeEixoY != "e" && tipoDeEixoY != "d"){       // condicao para tipos invalidados
            cout << endl << "TIPO INVALIDO" << endl << endl;
            cout << "O eixo deve ser (e)statico ou (d)inamico: " << endl;
            cin >> tipoDeEixoY;
        }

        cout << endl << "Informe a unidade do eixo: ";
        cin >> unidadeEixoY;
        cout << endl <<"Informe a escala minima inicial: ";
        cin >> escalaMinimaInicialY;

        while (cin.fail()) {                            // condicao para escalas invalidadas
            cout << endl << "ERRO: ESCALA INVALIDA" << endl << endl;
            cout << "Informe uma escala minima inicial valida para o eixo Y: ";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cin >> escalaMinimaInicialY;
        }

        cout << endl << "Informe a escala maxima inicial: ";
        cin >> escalaMaximaInicialY;

        while (cin.fail()) {                            // condicao para escalas invalidadas
            cout << endl << "ERRO: ESCALA INVALIDA" << endl << endl;
            cout << "Informe uma escala maxima inicial valida para o eixo Y: ";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cin >> escalaMaximaInicialY;
        }

        while (escalaMaximaInicialY <= escalaMinimaInicialY){        // condicao para escalas inversas
            cout << endl << "ESCALA MAXIMA MENOR/IGUAL A ESCALA MINIMA" << endl << endl;
            cout << "Informe a escala minima inicial: ";
            cin >> escalaMinimaInicialY;

            while (cin.fail()) {                            // condicao para escalas invalidadas
                cout << endl << "ERRO: ESCALA INVALIDA" << endl << endl;
                cout << "Informe uma escala minima inicial valida para o eixo Y: ";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cin >> escalaMinimaInicialY;
            }

            cout << endl << "Informe a escala maxima inicial: ";
            cin >> escalaMaximaInicialY;

            while (cin.fail()) {                            // condicao para escalas invalidadas
                cout << endl << "ERRO: ESCALA INVALIDA" << endl << endl;
                cout << "Informe uma escala maxima inicial valida para o eixo Y: ";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cin >> escalaMaximaInicialY;
            }
        }

        if (numeroDaSerieX == 0) {
                serieX = new Tempo(quantidadeMaximaDeValoresX);
        } else {
            serieX = new SerieDeCanal("Serie X", quantidadeMaximaDeValoresX);
        }

        if ( numeroDaSerieY == 0) {
                serieY = new Tempo(quantidadeMaximaDeValoresY);
        } else {
            serieY = new SerieDeCanal("Serie Y", quantidadeMaximaDeValoresY);
        }

        if(tipoDeEixoX == "d"){
            eixoX = new EixoDinamico(serieX, unidadeEixoX, tela->getLarguraUtil()/tela->getDivisaoAbscissa(), escalaMinimaInicialX, escalaMaximaInicialX);
        } else{
            eixoX = new Eixo(serieX->getNome(), unidadeEixoX, tela->getLarguraUtil()/tela->getDivisaoAbscissa(), escalaMinimaInicialX, escalaMaximaInicialX);
        }

        if(tipoDeEixoY == "d"){
            eixoY = new EixoDinamico(serieY, unidadeEixoY, tela->getAlturaUtil()/tela->getDivisaoOrdenada(), escalaMinimaInicialY, escalaMaximaInicialY);
        } else {
            eixoY = new Eixo(serieY->getNome(), unidadeEixoY, tela->getAlturaUtil()/tela->getDivisaoOrdenada(), escalaMinimaInicialY, escalaMaximaInicialY);
        }

        g = new Grafico (tela, serieX, serieY, eixoX, eixoY);

    is->registrar (/*is->getNomeDosCanais()[numeroDaSerieX]*/"x", g->getSerieNasAbscissas());
    is->registrar (/*is->getNomeDosCanais()[ numeroDaSerieY]*/"y", g->getSerieNasOrdenadas());

    }

    while (!IHC::escFoiPressionado()){
        if (Tempo* tempo = dynamic_cast<Tempo*>(serieX)){     // Se o eixo x for o tempo
          tempo->incrementar();
        }
        if (Tempo* tempo = dynamic_cast<Tempo*>(serieY)){     // Se o eixo y for o tempo
           tempo->incrementar();
        }
        if (carregar == "n") {
                is->atualizar();
        }

        g->desenhar();
        IHC::sleep();
    }

    if (carregar == "n") {
        string analisar;
        string salvar;

        cout << endl << "Analisar uma area do  grafico (s/n): ";
        cin >> analisar;

        while (analisar != "s" && analisar != "n"){       // condicao para tipos invalidados
            cout << endl << "TIPO INVALIDO" << endl << endl;
            cout << "Analisar uma area do  grafico (s/n): " << endl;
            cin >> analisar;
        }

        if (analisar == "s") {
            double cursor1_x;
            double cursor1_y;
            double cursor2_x;
            double cursor2_y;

            cout << endl << "Cordenada X do Cursor 1: ";
            cin >> cursor1_x;

            while (cin.fail()) {                            // condicao para valores invalidadas
                cout << endl << "ERRO: COORDENADA INVALIDA" << endl << endl;
                cout << "Insira um valor para a coordenada X do Cursor 1: ";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cin >> cursor1_x;
            }

            cout << endl << "Cordenada Y do Cursor 1: ";
            cin >> cursor1_y;

            while (cin.fail()) {                            // condicao para valores invalidadas
                cout << endl << "ERRO: COORDENADA INVALIDA" << endl << endl;
                cout << "Insira um valor para a coordenada Y do Cursor 1: ";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cin >> cursor1_y;
            }

            cout << endl << "Cordenada X do Cursor 2: ";
            cin >> cursor2_x;

            while (cin.fail()) {                            // condicao para valores invalidadas
                cout << endl << "ERRO: COORDENADA INVALIDA" << endl << endl;
                cout << "Insira um valor para a coordenada X do Cursor 1: ";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cin >> cursor2_x;
            }

            cout << endl << "Cordenada Y do Cursor 2: ";
            cin >> cursor2_y;

            while (cin.fail()) {                            // condicao para valores invalidadas
                cout << endl << "ERRO: COORDENADA INVALIDA" << endl << endl;
                cout << "Insira um valor para a coordenada Y do Cursor 1: ";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cin >> cursor2_y;
            }

            while (cursor1_x >= cursor2_x || cursor1_y >= cursor2_y) {
                cout << endl << "ERRO: CURSORES INVALIDOS OU IGUAIS" << endl << endl;
                cout << "Cordenada X do Cursor 1: ";
                cin >> cursor1_x;

                while (cin.fail()) {                            // condicao para valores invalidadas
                    cout << endl << "ERRO: COORDENADA INVALIDA" << endl << endl;
                    cout << "Insira um valor para a coordenada X do Cursor 1: ";
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cin >> cursor1_x;
                }

                cout << endl << "Cordenada Y do Cursor 1: ";
                cin >> cursor1_y;

                while (cin.fail()) {                            // condicao para valores invalidadas
                    cout << endl << "ERRO: COORDENADA INVALIDA" << endl << endl;
                    cout << "Insira um valor para a coordenada Y do Cursor 1: ";
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cin >> cursor1_y;
                }

                cout << endl << "Cordenada X do Cursor 2: ";
                cin >> cursor2_x;

                while (cin.fail()) {                            // condicao para valores invalidadas
                    cout << endl << "ERRO: COORDENADA INVALIDA" << endl << endl;
                    cout << "Insira um valor para a coordenada X do Cursor 1: ";
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cin >> cursor2_x;
                }

                cout << endl << "Cordenada Y do Cursor 2: ";
                cin >> cursor2_y;

                while (cin.fail()) {                            // condicao para valores invalidadas
                    cout << endl << "ERRO: COORDENADA INVALIDA" << endl << endl;
                    cout << "Insira um valor para a coordenada Y do Cursor 1: ";
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cin >> cursor2_y;
                }
            }

            Cursor* cursor1 = new Cursor(cursor1_x, cursor1_y);
            Cursor* cursor2 = new Cursor(cursor2_x, cursor2_y);
            Serie *corrigidax, *corrigiday;

            if (correcaoX == "m" || correcaoX == "s") { corrigidax = new SerieProcessada(serieX->getNome(), serieX, operacaoX);
            } else {
                corrigidax = serieX;
            }

            if (correcaoY == "m" || correcaoY == "s") {
                    corrigiday = new SerieProcessada(serieY->getNome(), serieY, operacaoY);
            } else {
                corrigiday = serieY;
            }

            AreaDoGrafico *area = new AreaDoGrafico(corrigidax, corrigiday, cursor1, cursor2);

            cout << endl << endl << "Valor minimo da abscissa | ordenada: " << area->getMinimoDaAbscissa() << " | " << area->getMinimoDaOrdenada() << endl;
            cout << endl << "Valor maximo da abscissa | ordenada: " << area->getMaximoDaAbscissa() << " | " << area->getMaximoDaOrdenada() << endl;
            cout << endl << "Valor da media da abscissa | ordenada: " << area->getMediaDaAbscissa() << " | " << area->getMediaDaOrdenada() << endl;
            cout << endl << "Desvio padrao da abscissa | ordenada: " << area->getDesvioPadraoDaAbscissa() << " | " << area->getDesvioPadraoDaOrdenada();
        }

        cout << endl << endl <<"Salvar o grafico (s/n): ";
        cin >> salvar;

        while (salvar != "s" && salvar != "n"){       // condicao para tipos invalidados
            cout << endl << "TIPO INVALIDO" << endl << endl;
            cout << "Salvar o grafico (s/n): " << endl;
            cin >> salvar;
        }

        if (salvar == "s") {
            string nomedografico;

            cout << endl << "Nome do grafico: ";
            cin >> nomedografico;
            p->inserir(nomedografico, g);
            cout << endl << "Grafico salvo" << endl;
        }
    }

    delete tela;
    delete g;
    delete is;
    delete serieX;
    delete serieY;
}
