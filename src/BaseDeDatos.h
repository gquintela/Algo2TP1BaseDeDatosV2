//
// Created by gonzalo on 26/08/17.
//

#ifndef TP1_BASEDEDATOS_H
#define TP1_BASEDEDATOS_H

#include<vector>
//#include<iostream>
#include "Tabla.h"


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
    bool  sePuedeInsertarRegistro(string nombreTabla, Registro r );

    // @observador
//    Tabla busqueda(string campo) const;


private:

    vector<string> _nombresTabla;
    vector<Tabla> _tablas;
 /*   string _nombreTabla;
    Tabla _t;
    Registro _r;*/
};

bool operator==(const BaseDeDatos&, const BaseDeDatos&);
bool operator!=(const BaseDeDatos&, const BaseDeDatos&);


#endif //TP1_BASEDEDATOS_H
