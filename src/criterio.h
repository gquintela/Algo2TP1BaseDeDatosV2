//
// Created by gonzalo on 3/09/17.
//

#ifndef TP1_CRITERIO_H
#define TP1_CRITERIO_H

#include <string>
#include "Dato.h"
#include "restriccion.h"
#include <vector>

using namespace std;

class Criterio {

public:


    Criterio(vector<Restriccion> restricciones);

    // @observador
    vector<Restriccion> restricciones() const;


private:

    vector<Restriccion> _restricciones;


};

//Dato datoNat(int valorNat);
//
//Dato datoStr(string valorStr);
//
//bool operator==(const Dato&, const Dato&);
//
//bool operator!=(const Dato&, const Dato&);

bool operator==(const Criterio &c1, const Criterio &c2);

bool operator!=(const Criterio &c1, const Criterio &c2);



#endif //TP1_CRITERIO_H
