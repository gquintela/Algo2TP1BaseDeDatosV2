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

// buscar indice de tabla en base, si no esta devuelve el total de tablas
int BaseDeDatos::indiceDeNombreEnBase(const string &nombreTabla) {
    int i = 0;
    while (i < _nombresTabla.size() && !(nombreTabla == _nombresTabla[i])) {
        i++;
    }
    return i;
}

// ver que los campos de nombreTabla sean los mismos de r
bool BaseDeDatos::mismosCampos(const int &indiceTabla, const Registro &r) {
    return seteq(_tablas[indiceTabla].campos(), r.campos());
}

//chequear que para cada campo, el tipo de dato sea el mismo
bool BaseDeDatos::mismosTiposEnCampos(const int &indiceTabla, const Registro &r) {

    for (int j = 0; j < _tablas[indiceTabla].campos().size(); j++) {

        if (_tablas[indiceTabla].tipoCampo(_tablas[indiceTabla].campos()[j]).esNat() !=
            r.dato(_tablas[indiceTabla].campos()[j]).esNat()) {
            return false;
        }
    }
    return true;
}

// ver que de las claves de nombreTabla los valores de r no sean todos iguales a alguno de nombreTabla
bool BaseDeDatos::noHayDuplicadosEnClaves(const int &indiceTabla, const Registro &r) {
    for (int j = 0; j < _tablas[indiceTabla].registros().size(); j++) {
        bool esDuplicado = true;
        for (int k = 0; k < _tablas[indiceTabla].claves().size(); k++) {
            if (_tablas[indiceTabla].registros()[j].dato(_tablas[indiceTabla].claves()[k]) !=
                r.dato(_tablas[indiceTabla].claves()[k])) {
                esDuplicado = false;
            }
        }
        if (esDuplicado) {
            return false;
        }
    }
    return true;
}


bool BaseDeDatos::sePuedeInsertarRegistro(const string &nombreTabla, const Registro &r) {


    int indiceTabla = indiceDeNombreEnBase(nombreTabla);

    if (indiceTabla == _nombresTabla.size()) {
        return false;
    }

    return (mismosCampos(indiceTabla, r)) and mismosTiposEnCampos(indiceTabla, r) and
           noHayDuplicadosEnClaves(indiceTabla, r);
}


bool operator==(const BaseDeDatos &, const BaseDeDatos &) {
    return false;
}

bool operator!=(const BaseDeDatos &, const BaseDeDatos &) {
    return false;
}
//comento para probar commiteo en Clion
