//
// Created by gonzalo on 3/09/17.
//

#include <vector>
#include "restriccion.h"

Restriccion::Restriccion(string campo, Dato valor, bool coincidencia) :
        _campo(campo), _valor(valor), _coincidencia(coincidencia) {};


string Restriccion::campo() const {
    return _campo;
}

Dato Restriccion::valor() const {
    return _valor;
}

bool Restriccion::coincidencia() const {
    return _coincidencia;
}

bool operator==(const Restriccion &res1, const Restriccion &res2) {
    return (res1.campo() == res2.campo() and res1.valor() == res2.valor() and
            res1.coincidencia() == res2.coincidencia());
}

bool operator!=(const Restriccion &res1, const Restriccion &res2) {
    return not(res1 == res2);
}



