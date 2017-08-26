//
// Created by gonzalo on 26/08/17.
//

#include "BaseDeDatos.h"
#include "utils.h"

BaseDeDatos::BaseDeDatos(vector<string> nombresTabla, vector<Tabla> tablas) :
        _nombresTabla(nombresTabla), _tablas(tablas) {}

void BaseDeDatos::agregarTabla(string nombre, Tabla t) {
    if (pertenece(nombre, _nombresTabla)) {
        // ver como implementar la restriccion
    } else {
        _nombresTabla.push_back(nombre);
        _tablas.push_back(t);
    }
}

void BaseDeDatos::agregarRegistroATabla(string nombreTabla, Registro r) {
    if (!sePuedeInsertarRegistro(nombreTabla, r)) {
        // ver como implementar la restriccion
    } else {
        for (int i = 0; i < _nombresTabla.size(); i++) {
            if (nombreTabla == _nombresTabla[i]) {
                _tablas[i].agregarRegistro(r);
            }
        }
    }
}

bool BaseDeDatos::sePuedeInsertarRegistro(string nombreTabla, Registro r) {
    // ver que nombreTabla este en _nombresTabla
    int i = 0;
    while (i < _nombresTabla.size() && !(nombreTabla == _nombresTabla[i])) {
        i++;
    }
    if (i == _nombresTabla.size() ){
        return false;
    }
    // ver que los campos de nombreTabla sean los mismos de r
    if (! seteq(_tablas[i].campos(),r.campos())) {
        return false;
    }
    //chequear que para cada campo, el tipo de dato sea el mismo
    for(int j = 0; j < _tablas[i].campos().size();j++){

        if (_tablas[i].tipoCampo(_tablas[i].campos()[j]).esNat() != r.dato(_tablas[i].campos()[j]).esNat()) {
            return false;
        }
    }

    // ver que de las claves de nombreTabla los valores de r no sean todos iguales a alguno de nombreTabla

    for(int j = 0; j < _tablas[i].registros().size();j++) {
        bool esDuplicado = true;
        for(int k = 0; k < _tablas[i].claves().size();k++) {
            if (_tablas[i].registros()[j].dato(_tablas[i].claves()[k]) != r.dato(_tablas[i].claves()[k])) {
                esDuplicado = false;
            }
        }
        if (esDuplicado){
            return false;
        }
    }

    return false;
}

bool operator==(const BaseDeDatos &, const BaseDeDatos &) {
    return false;
}

bool operator!=(const BaseDeDatos &, const BaseDeDatos &) {
    return false;
}
//comento para probar commiteo en Clion
