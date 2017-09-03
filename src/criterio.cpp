//
// Created by gonzalo on 3/09/17.
//

#include "criterio.h"
#include "utils.h"


Criterio::Criterio(vector<Restriccion> restricciones) :
        _restricciones(restricciones) {};

vector<Restriccion> Criterio::restricciones() const {
    return _restricciones;
}


bool operator==(const Criterio &c1, const Criterio &c2) {
    return seteq(c1.restricciones(), c2.restricciones());
}

bool operator!=(const Criterio &c1, const Criterio &c2) {
    return not(c1 == c2);
}
