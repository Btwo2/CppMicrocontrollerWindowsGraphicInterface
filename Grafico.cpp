#include "Grafico.h"

Grafico::Grafico(Tela* tela, Serie* x, Serie* y, Eixo* abscissas, Eixo* ordenadas){
    screen = tela;
    serieNasAbscissas = x;
    serieNasOrdenadas = y;
    eixoDasAbscissas = abscissas;
    eixoDasOrdenadas = ordenadas;
    //ctor
}

Grafico::~Grafico(){
    //dtor
}

void Grafico::desenhar(){

    reset();

    double escalamaxY = eixoDasOrdenadas->getEscalaMaxima();
    double escalaminY = eixoDasOrdenadas->getEscalaMinima();
    double escalamaxX = eixoDasAbscissas->getEscalaMaxima();
    double escalaminX = eixoDasAbscissas->getEscalaMinima();
    double x;
    double y;
    int tamanho = serieNasAbscissas->getTamanho();

    screen->setEixoDasAbscissas(eixoDasAbscissas);
    screen->setEixoDasOrdenadas(eixoDasOrdenadas);



for (int i = 0; i < tamanho; i++){

        x = (screen->getLarguraUtil() - 1)*(serieNasAbscissas->getValor(i) - escalaminX)/(escalamaxX - escalaminX);
        y = (screen->getAlturaUtil() - 1)*(serieNasOrdenadas->getValor(i) - escalaminY)/(escalamaxY - escalaminY);

        int ponto_x = x + 0.5; //arredonda o valor de x
        int ponto_y = y + 0.5; //arredonda o valor de y

        if (ponto_x > screen->getLarguraUtil() - 1 && ponto_y > screen->getAlturaUtil() - 1) screen->adicionarForaDoLimiteEm(Limite::SUPERIOR, Limite::SUPERIOR);
        if (ponto_x > screen->getLarguraUtil() - 1 && ponto_y < 0) screen->adicionarForaDoLimiteEm(Limite::SUPERIOR, Limite::INFERIOR);
        if (ponto_x < 0 && ponto_y > screen->getAlturaUtil() - 1) screen->adicionarForaDoLimiteEm(Limite::INFERIOR, Limite::SUPERIOR);
        if (ponto_x < 0 && ponto_y < 0) screen->adicionarForaDoLimiteEm(Limite::INFERIOR, Limite::INFERIOR);
        if (ponto_x > screen->getLarguraUtil() - 1 && ponto_y <= screen->getAlturaUtil() - 1 && ponto_y >= 0) screen->adicionarForaDoLimiteDasAbscissasEm(ponto_y, Limite::SUPERIOR);
        if (ponto_x < 0 && ponto_y <= screen->getAlturaUtil() - 1 && ponto_y >= 0) screen->adicionarForaDoLimiteDasAbscissasEm(ponto_y , Limite::INFERIOR);
        if (ponto_y > screen->getAlturaUtil() - 1 && ponto_x <= screen->getLarguraUtil() - 1 && ponto_x >= 0)screen->adicionarForaDoLimiteDasOrdenadasEm(ponto_x, Limite::SUPERIOR);
        if (ponto_y <  0 && ponto_x <= screen->getLarguraUtil() - 1 && ponto_x >= 0) screen->adicionarForaDoLimiteDasOrdenadasEm(ponto_x, Limite::INFERIOR);
        if (ponto_y >=  0 && ponto_y <= screen->getAlturaUtil() - 1 && ponto_x <= screen->getLarguraUtil() - 1 && ponto_x >= 0) screen->adicionarPontoEm(ponto_x, ponto_y);
    }

    screen->desenhar();
}

void Grafico::reset(){
    screen->apagar();
}

Serie* Grafico::getSerieNasAbscissas(){
    return serieNasAbscissas;
}

Serie* Grafico::getSerieNasOrdenadas(){
    return serieNasOrdenadas;
}

Eixo* Grafico::getEixoDasAbscissas(){
    return eixoDasAbscissas;
}

Eixo* Grafico::getEixoDasOrdenadas(){
    return eixoDasOrdenadas;
}
