#include "PersistenciaDeGrafico.h"

PersistenciaDeGrafico::PersistenciaDeGrafico(Tela* tela, string arquivo) {
    nomes = new vector <string>;
    graficos = new vector <Grafico*>;
    screen = tela;
    ifstream entrada;
    entrada.open (arquivo);

    if (entrada.fail()) {
        cout << "Arquivo nao encontrado";
        entrada.close();
    }
    string s;
    int i;
    double d;
    int cont = 0;
    Serie* sx;
    Serie* sy;

    while (entrada.good()) {
        entrada >> s;           //nome do grafico
        if (entrada.eof()) {
            if (cont == 0) throw new runtime_error ("Formato de arquivo invalido");
            else break;
        }
        nomes->push_back(s);

        entrada >> i;           //numero de valoers
        if (entrada.eof()) throw new runtime_error ("Formato de arquivo invalido");
        if (entrada.fail()) throw new runtime_error ("Formato de arquivo invalido");
        int numero_de_valores = i;

        entrada >> s;           //titulo x

        if (entrada.eof()) throw new runtime_error ("Formato de arquivo invalido");

        sx = new SerieDeCanal (s, numero_de_valores);
        entrada >> s;           //unidade x

        if (entrada.eof()) throw new runtime_error ("Formato de arquivo invalido");

        if(sx->getNome() == "Tempo") {
            for (int j = 0 ; j < numero_de_valores; j++) {
                entrada >> i;   //valores x

                if (entrada.eof()) throw new runtime_error ("Formato de arquivo invalido");
                if (entrada.fail()) throw new runtime_error ("Formato de arquivo invalido");
                if (SerieDeCanal* x = dynamic_cast<SerieDeCanal*>(sx))
                    x->adicionar(i);
            }
        } else {
            for (int j = 0 ; j < numero_de_valores; j++) {

                entrada >> d;   //valores x

                if (entrada.eof()) throw new runtime_error ("Formato de arquivo invalido");
                if (entrada.fail()) throw new runtime_error ("Formato de arquivo invalido");
                if (SerieDeCanal* x = dynamic_cast<SerieDeCanal*>(sx))
                    x->adicionar(d);

            }
        }
        Eixo* ex = new Eixo(sx->getNome(), s, screen->getLarguraUtil()/screen->getDivisaoAbscissa(), sx->getMinimo(), sx->getMaximo());

        entrada >> s;           //titulo y

        if (entrada.eof()) throw new runtime_error ("Formato de arquivo invalido");

        sy = new SerieDeCanal(s, numero_de_valores);
        entrada >> s;           //unidade y

        if (entrada.eof()) throw new runtime_error ("Formato de arquivo invalido");

        if(sy->getNome() == "Tempo") {
            for (int j = 0 ; j < numero_de_valores; j++) {

                entrada >> i;

                if (entrada.eof()) throw new runtime_error ("Formato de arquivo invalido");
                if (entrada.fail()) throw new runtime_error ("Formato de arquivo invalido");
                if (SerieDeCanal* y = dynamic_cast<SerieDeCanal*>(sy))
                    y->adicionar(i);
            }
        } else {
            for (int j = 0 ; j < numero_de_valores; j++) {

                entrada >> d;

                if (entrada.eof()) throw new runtime_error ("Formato de arquivo invalido");
                if (entrada.fail()) throw new runtime_error ("Formato de arquivo invalido");
                if (SerieDeCanal* y = dynamic_cast<SerieDeCanal*>(sy))
                    y->adicionar(d);
            }
        }
        Eixo* ey = new Eixo(sy->getNome(), s, screen->getAlturaUtil()/screen->getDivisaoOrdenada(), sy->getMinimo(), sy->getMaximo());
        Grafico* g = new Grafico(screen, sx, sy, ex, ey);
        graficos->push_back(g);
        cont++;
    }
    entrada.close();
    this->arquivo = arquivo;
}

PersistenciaDeGrafico::~PersistenciaDeGrafico() {
    //dtor
}

Grafico* PersistenciaDeGrafico::obter(string nome) {
    if (nomes->empty()) return NULL;
    vector <string>::iterator i;
    i = find (nomes->begin(), nomes->end(), nome);

    if (i != nomes->end()) {
        for (int j = 0; j < nomes->size(); j++)
            if (nomes->at (j) == *i) return graficos->at (j);
    } else return NULL;
}

vector <string>* PersistenciaDeGrafico::getNomes() {
    return nomes;
}

void PersistenciaDeGrafico::inserir(string nome, Grafico* g) {
    vector <string>::iterator i;
    i = find (nomes->begin(), nomes->end(), nome);

    if (i != nomes-> end()) {
        throw new runtime_error ("Ja existe um grafico com o mesmo nome");
    }
    if (g->getSerieNasAbscissas()->estaVazia()) throw new runtime_error ("Serie do eixo das abscissas vazia");
    if (g->getSerieNasOrdenadas()->estaVazia()) throw new runtime_error ("Serie do eixo das ordenadas vazia");

    ofstream saida;
    saida.open (arquivo, ios_base::app);

    if (saida.fail()) throw new runtime_error ("Impossivel escrever no arquivo");

    saida << nome << endl;
    saida << g->getSerieNasAbscissas()->getTamanho() << endl;
    saida << g->getSerieNasAbscissas()->getNome() << endl;
    saida << g->getEixoDasAbscissas()->getUnidade() << endl;

    for (int i = 0; i < g->getSerieNasAbscissas()->getTamanho(); i++)
        saida << g->getSerieNasAbscissas()->getValor(i) << endl;

    saida << g->getSerieNasOrdenadas()->getNome() << endl;
    saida << g->getEixoDasOrdenadas()->getUnidade() << endl;

    for (int i = 0; i < g->getSerieNasOrdenadas()->getTamanho(); i++)
        saida << g->getSerieNasOrdenadas()->getValor(i) << endl;

    nomes->push_back(nome);
    graficos->push_back(g);
}
