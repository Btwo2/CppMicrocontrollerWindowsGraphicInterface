#include "Serie.h"

Serie::Serie(string nome){
    this->nome = nome;
    //ctor
}

Serie::~Serie(){
    //dtor
}

string Serie::getNome(){
    return nome;
}
