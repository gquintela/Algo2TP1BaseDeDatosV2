//
// Created by gonzalo on 26/08/17.
//

#include "BaseDeDatos.h"


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
int BaseDeDatos::indiceDeNombreEnBase(const string &nombreTabla) const {
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

vector<string> BaseDeDatos::nombresTabla() const {
    return _nombresTabla;
}

vector<Tabla> BaseDeDatos::tablas() const {
    return _tablas;
}

bool BaseDeDatos::esCriterioValido(string &nombreTabla, Criterio &c) {

    int indiceTabla = indiceDeNombreEnBase(nombreTabla);

    for (int i = 0; i < c.restricciones().size(); i++) {
        for (int j = 0; j < _tablas[indiceTabla].campos().size(); j++) {
            bool perteneceCampo = false;
            if (c.restricciones()[i].campo() == _tablas[indiceTabla].campos()[j]) {
                perteneceCampo = true;
                if (c.restricciones()[i].valor().esNat() !=
                    _tablas[indiceTabla].tipoCampo(c.restricciones()[i].campo()).esNat()) {
                    return false;
                }
            }
            if (not perteneceCampo) {
                return false;
            }
        }
    }
    return true;
}


void BaseDeDatos::agregarACriteriosUsados(Criterio &c) {
    bool criterioYaUsado = false;
    for (int i = 0; i < _criteriosUsados.size(); i++) {
        if (c == _criteriosUsados[i].first) {
            _criteriosUsados[i].second++;
            criterioYaUsado = true;
        }
    }
    if (not criterioYaUsado) {
        pair<Criterio, int> elementoAagregar = make_pair(c, 1);
        _criteriosUsados.push_back(elementoAagregar);
    }
}

bool BaseDeDatos::registroPasaFiltroCriterio(Registro &r, Criterio &crit) {
    bool pasaFiltro = true;
    for (int i = 0; i < crit.restricciones().size(); i++) {
        for (int j = 0; j < r.campos().size(); j++) {
            if (r.campos()[j] == crit.restricciones()[i].campo()) {
                if (crit.restricciones()[i].coincidencia() and
                    crit.restricciones()[i].valor() != r.dato(r.campos()[j])) {
                    pasaFiltro = false;
                } else if (not crit.restricciones()[i].coincidencia() and
                           crit.restricciones()[i].valor() == r.dato(r.campos()[j])) {
                    pasaFiltro = false;
                }
            }
        }
    }
    return pasaFiltro;
}


Tabla BaseDeDatos::busqueda(string nombreTabla, Criterio c) {
    agregarACriteriosUsados(c);
    int indiceTabla = indiceDeNombreEnBase(nombreTabla);
    vector<Dato> tipoDeCampos;

    for (int i = 0; i < _tablas[indiceTabla].campos().size(); i++) {
        tipoDeCampos.push_back(_tablas[indiceTabla].tipoCampo(_tablas[indiceTabla].campos()[i]));
    }

    Tabla resultado(_tablas[indiceTabla].campos(), _tablas[indiceTabla].claves(), tipoDeCampos);

    for (int i = 0; i < _tablas[indiceTabla].registros().size(); i++) {
        if (registroPasaFiltroCriterio(_tablas[indiceTabla].registros()[i], c)) {
            resultado.agregarRegistro(_tablas[indiceTabla].registros()[i]);
        }
    }
    return resultado;
}

Criterio BaseDeDatos::criterioMasUsado() {
    Criterio resultado = {{}};
    int maxCantidadUsado = 0;
    for (int i = 0; i < _criteriosUsados.size(); i++) {
        if (_criteriosUsados[i].second > maxCantidadUsado) {
            maxCantidadUsado = _criteriosUsados[i].second;
            resultado = _criteriosUsados[i].first;
        }
    }

    return resultado;
}


bool operator==(const BaseDeDatos &b1, const BaseDeDatos &b2) {
    if (not seteq(b1.nombresTabla(), b2.nombresTabla())) {
        return false;
    }
    for (int i = 0; i < b1.nombresTabla().size(); i++) {
        if (b1.tablas()[i] != b2.tablas()[b2.indiceDeNombreEnBase(b1.nombresTabla()[i])]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const BaseDeDatos &b1, const BaseDeDatos &b2) {
    return not(b1 == b2);
}
//comento para probar commiteo en Clion
