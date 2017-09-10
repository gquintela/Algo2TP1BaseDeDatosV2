//
// Created by gonzalo on 7/09/17.
//

#include "gtest/gtest.h"

#include "../src/restriccion.h"

TEST(restriccion_test, generadores) {
    Restriccion("LU", datoNat(123), true);
    Restriccion("LU", datoNat(123), false);
    Restriccion("Carrera", datoStr("Computacion"), true);
    Restriccion("Carrera", datoStr("Computacion"), false);
}

TEST(restriccion_test, campos) {
    EXPECT_EQ(Restriccion("LU", datoNat(123), true).campo(), "LU");
    EXPECT_EQ(Restriccion("LU", datoNat(123), false).campo(), "LU");
    EXPECT_EQ(Restriccion("Carrera", datoStr("Computacion"), true).campo(), "Carrera");
    EXPECT_EQ(Restriccion("Carrera", datoStr("Computacion"), false).campo(), "Carrera");
}

TEST(restriccion_test, valores) {
    EXPECT_EQ(Restriccion("LU", datoNat(123), true).valor(), datoNat(123));
    EXPECT_EQ(Restriccion("LU", datoNat(123), false).valor(), datoNat(123));
    EXPECT_EQ(Restriccion("Carrera", datoStr("Computacion"), true).valor(), datoStr("Computacion"));
    EXPECT_EQ(Restriccion("Carrera", datoStr("Computacion"), false).valor(), datoStr("Computacion"));
}

TEST(restriccion_test, coincidencias) {
    EXPECT_TRUE(Restriccion("LU", datoNat(123), true).coincidencia());
    EXPECT_FALSE(Restriccion("LU", datoNat(123), false).coincidencia());
    EXPECT_TRUE(Restriccion("Carrera", datoStr("Computacion"), true).coincidencia());
    EXPECT_FALSE(Restriccion("Carrera", datoStr("Computacion"), false).coincidencia());
}

TEST(restriccion_test, igualdad) {
    EXPECT_EQ(Restriccion("LU", datoNat(123), true), Restriccion("LU", datoNat(123), true));
    EXPECT_NE(Restriccion("LU", datoNat(123), true), Restriccion("LU", datoNat(123), false));
    EXPECT_NE(Restriccion("LU", datoNat(123), true), Restriccion("Año", datoNat(123), true));
    EXPECT_NE(Restriccion("LU", datoNat(123), true), Restriccion("LU", datoNat(124), true));
}