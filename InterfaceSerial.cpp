#include "InterfaceSerial.h"

void InterfaceSerial::inicializar (string porta) {
}

void InterfaceSerial::registrar (string canal, Serie* serie) {
    if (t == NULL) {
        t = serie;
    } else if (s == NULL) {
        s = serie;
    }
}

bool InterfaceSerial::atualizar() {
    if(SerieDeCanal* x = dynamic_cast<SerieDeCanal*>(s)) {
        x->adicionar(numeroDeChamadas + 5);
    } if(SerieDeCanal* x = dynamic_cast<SerieDeCanal*>(t)){
        x->adicionar(numeroDeChamadas*8);
    }
    numeroDeChamadas++;
    return true;
}
