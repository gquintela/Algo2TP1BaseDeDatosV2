//
// Created by gonzalo on 26/08/17.
//

#ifndef TP1_BASEDEDATOS_H
#define TP1_BASEDEDATOS_H

#include<vector>
//#include<iostream>
#include "Tabla.h"
#include "utils.h"
#include "criterio.h"
#include <utility>


using namespace std;

class BaseDeDatos {

public:

    // @generador
    BaseDeDatos(vector <string> nombresTabla, vector<Tabla> tablas );

    // @generador
    void agregarTabla(string nombreTabla,Tabla t);

    // @generador
    void agregarRegistroATabla(string nombreTabla, Registro r);

    // @observador
    vector<string> nombresTabla() const;

    // @observador
    vector<Tabla> tablas() const;

    // @observador
    bool sePuedeInsertarRegistro(const string &nombreTabla, const Registro &r);

    // @otras operaciones
    int indiceDeNombreEnBase(const string &nombreTabla) const;


    bool esCriterioValido(string &nombreTabla, Criterio &c);


//    vector<Dato>

    // @observador
    Tabla busqueda(string &nombreTabla, Criterio &c);

    void agregarACriteriosUsados(Criterio &c);

    Criterio criterioMasUsado();

private:

    vector<string> _nombresTabla;
    vector<Tabla> _tablas;
    vector<pair<Criterio, int> > _criteriosUsados;

 /*   string _nombreTabla;
    Tabla _t;
    Registro _r;*/



    bool mismosCampos(const int &indiceTabla, const Registro &r);

    bool mismosTiposEnCampos(const int &indiceTabla, const Registro &r);

    bool noHayDuplicadosEnClaves(const int &indiceTabla, const Registro &r);

    bool registroPasaFiltroCriterio(Registro &r, Criterio &c);
};

bool operator==(const BaseDeDatos &b1, const BaseDeDatos &b2);

bool operator!=(const BaseDeDatos &b1, const BaseDeDatos &b2);


#endif //TP1_BASEDEDATOS_H
