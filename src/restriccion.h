//
// Created by gonzalo on 3/09/17.
//

#ifndef TP1_RESTRICCION_H
#define TP1_RESTRICCION_H

#include <string>
#include "Dato.h"

using namespace std;

class Restriccion {

public:

    // @generador
    Restriccion(string campo, Dato valor, bool coincidencia);

    // @observador
    string campo() const;

    // @observador
    Dato valor() const;

    // @observador
    bool coincidencia() const;

private:

    string _campo;
    Dato _valor;
    bool _coincidencia;

};

bool operator==(const Restriccion &res1, const Restriccion &res2);
bool operator!=(const Restriccion &res1, const Restriccion &res2);

#endif //TP1_RESTRICCION_H
