//
// Created by gonzalo on 26/08/17.
//

#include "gtest/gtest.h"
#include "../src/BaseDeDatos.h"
#include "../src/utils.h"

using namespace std;

class BaseDeDatosTests : public ::testing::Test {

protected:
    BaseDeDatosTests() :
            r({"LU", "Año", "Nombre", "Carrera"},
              {datoNat(182), datoNat(18), datoStr("March"), datoStr("Computacion")}),

            t1({"LU", "Año", "Nombre", "Carrera"},
               {"LU", "Año"},
               {datoNat(0), datoNat(0), datoStr(""), datoStr("")}),
            t2({"Cod", "Carrera"},
               {"Cod"},
               {datoNat(0), datoStr("")}),
            b0({}, {}),
            b1({"tabla01"}, {t1}),
            b2({"tabla02"}, {t2}),
            b3({"tabla01", "tabla02"}, {t1, t2}) {};


    Registro r;
    Tabla t1;
    Tabla t2;
    BaseDeDatos b0;
    BaseDeDatos b1;
    BaseDeDatos b2;
    BaseDeDatos b3;
};

TEST_F(BaseDeDatosTests, agregarTabla) {
    b0.agregarTabla("tabla01", t1);
    EXPECT_EQ(b0, b1);
    b0.agregarTabla("tabla02", t2);
    EXPECT_EQ(b0, b3);

}

TEST_F(BaseDeDatosTests, agregarRegistroATabla) {
    b3.agregarRegistroATabla("tabla01", r);
    EXPECT_EQ(b3.tablas()[0].registros().size(), 1);

}

TEST_F(BaseDeDatosTests, sePuedeInsertarRegistro) {
    Registro r0({"Año", "Nombre", "Carrera"},
                {datoNat(18), datoStr("March"), datoStr("Computacion")});
    Registro r1({"LU", "Año", "Nombre", "Carrera"},
                {datoNat(182), datoStr("dieciocho"), datoStr("March"), datoStr("Computacion")});
    Registro r2({"LU", "Año", "Nombre", "Carrera"},
                {datoNat(182), datoNat(18), datoStr("Ivan"), datoStr("Abogacia")});

    EXPECT_FALSE(b3.sePuedeInsertarRegistro("tabla01", r0));
    EXPECT_FALSE(b3.sePuedeInsertarRegistro("tabla01", r1));
    EXPECT_TRUE(b3.sePuedeInsertarRegistro("tabla01", r));
    b3.agregarRegistroATabla("tabla01", r);
    EXPECT_EQ(b3.tablas()[0].registros().size(), 1);
    EXPECT_FALSE(b3.sePuedeInsertarRegistro("tabla01", r2));
    b3.agregarRegistroATabla("tabla01", r); //inserto registro con mismos valores en campos clave
    EXPECT_EQ(b3.tablas()[0].registros().size(), 1);
}

TEST_F(BaseDeDatosTests, nombresTablas) {
    vector<string> v = {"tabla01", "tabla02"};
    EXPECT_EQ(b3.nombresTabla(), v);
}

TEST_F(BaseDeDatosTests, tablas) {
    vector<Tabla> v = {t1, t2};
    EXPECT_EQ(b3.tablas(), v);
}

TEST_F(BaseDeDatosTests, busqueda) {
    Registro r0({"LU", "Año", "Nombre", "Carrera"},
                {datoNat(182), datoNat(18), datoStr("March"), datoStr("Computacion")});
    b3.agregarRegistroATabla("tabla01", r0);
    Criterio c({Restriccion("LU", datoNat(182), true)});
    Criterio c2({Restriccion("LU", datoNat(182), false)});
    Tabla t3 = b3.busqueda("tabla01", c2);
    EXPECT_EQ(t3, t1);
    Tabla t4 = b3.busqueda("tabla01", c);
    t1.agregarRegistro(r0);
    EXPECT_EQ(t4, t1);

}
