#ifndef OPERACAO_H_INCLUDED
#define OPERACAO_H_INCLUDED

/**
 * Classe abstrata que representa a operacao a ser aplicada.*
 *
 * @Version EP3
 */
class Operacao {
public:
    /**
    * Executa a operacao no 'valor' de uma serie.
    */
    virtual double executar(double valor) = 0;
    virtual ~Operacao();

};

#endif // OPERACAO_H_INCLUDED
