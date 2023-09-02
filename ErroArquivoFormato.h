#ifndef ERROARQUIVOFORMATO_H_INCLUDED
#define ERROARQUIVOFORMATO_H_INCLUDED

#include <stdexcept>
#include <string>

using namespace std;

class ErroArquivoFormato : public runtime_error {
public:
    ErroArquivoFormato (const string &alerta);

};

#endif // ERROARQUIVOFORMATO_H_INCLUDED
