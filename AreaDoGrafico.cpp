#include "AreaDoGrafico.h"

AreaDoGrafico::AreaDoGrafico(Serie* x, Serie* y, Cursor* c1, Cursor* c2) {
    if(c1->getX() >= c2->getX() || c1->getY() >= c2->getY()) {
            throw new out_of_range ("Cursores invalidos ou iguais");
    }

    vector<double>* vx = new vector<double>;
    vector<double>* vy = new vector<double>;

    for (int i = 0; i < x->getTamanho(); i++) {
        if (x->getValor(i) <= c2->getX() && x->getValor(i) >= c1->getX()) vx->push_back(x->getValor(i));
        if (y->getValor(i) <= c2->getY() && y->getValor(i) >= c1->getY()) vy->push_back(y->getValor(i));
    }

    xc = new SeriePersistida(x->getNome(), vx);
    yc = new SeriePersistida(y->getNome(), vy);
}

AreaDoGrafico::~AreaDoGrafico() {
    //dtor
}

double AreaDoGrafico::getMaximoDaAbscissa() {
    if (xc->estaVazia()) {
            return 0;
    } else {
        return xc->getMaximo();
    }
}

double AreaDoGrafico::getMinimoDaAbscissa() {
    if (xc->estaVazia()) {
            return 0;
    } else {
        return xc->getMinimo();
    }
}

double AreaDoGrafico::getMediaDaAbscissa() {
    if (xc->estaVazia()) {
            return 0;
    } else {
        double media = 0.0;

        for (int i = 0; i < xc->getTamanho(); i++) {
            media+= xc->getValor(i);
        }
        media /= xc->getTamanho();
        return media;
    }
}

double AreaDoGrafico::getDesvioPadraoDaAbscissa() {
    if (xc->estaVazia()) {
            return 0;
    } else {
        double var = 0.0;

        for (int i = 0; i < xc->getTamanho(); i++) {
            var += pow(xc->getValor(i) - getMediaDaAbscissa(),2);
        }
    var /= xc->getTamanho();
    return sqrt(var);
    }
}

double AreaDoGrafico::getMaximoDaOrdenada() {
    if (yc->estaVazia()) {
            return 0;
    } else {
        return yc->getMaximo();
    }
}

double AreaDoGrafico::getMinimoDaOrdenada() {
    if (yc->estaVazia()) {
        return 0;
    } else {
        return yc->getMinimo();
    }
}

double AreaDoGrafico::getMediaDaOrdenada() {
    if (yc->estaVazia()) {
        return 0;
    } else {
        double media = 0.0;

        for (int i = 0; i < yc->getTamanho(); i++) {
            media+= yc->getValor(i);
        }
    media /= yc->getTamanho();
    return media;
    }
}

double AreaDoGrafico::getDesvioPadraoDaOrdenada() {
    if (yc->estaVazia()) {
        return 0;
    } else {
        double var = 0.0;

        for (int i = 0; i < yc->getTamanho(); i++) {
            var += pow(yc->getValor(i) - getMediaDaOrdenada(),2);
        }
    var /= yc->getTamanho();
    return sqrt(var);
    }
}
