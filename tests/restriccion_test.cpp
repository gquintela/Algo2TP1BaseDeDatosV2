//
// Created by gonzalo on 7/09/17.
//

#include "gtest/gtest.h"

#include "../src/restriccion.h"

TEST(restriccion_test, generadores) {
    Restriccion("LU", Dato(123, "", true), true);
    Restriccion("LU", Dato(123, "", true), false);
    Restriccion("Carrera", Dato(0, "Computacion", false), true);
    Restriccion("Carrera", Dato(0, "Computacion", false), false);
}

TEST(restriccion_test, campos) {
    EXPECT_EQ(Restriccion("LU", Dato(123, "", true), true).campo(), "LU");
    EXPECT_EQ(Restriccion("LU", Dato(123, "", true), false).campo(), "LU");
    EXPECT_EQ(Restriccion("Carrera", Dato(0, "Computacion", false), true).campo(), "Carrera");
    EXPECT_EQ(Restriccion("Carrera", Dato(0, "Computacion", false), false).campo(), "Carrera");
}

TEST(restriccion_test, valores) {
    EXPECT_EQ(Restriccion("LU", Dato(123, "", true), true).valor(), Dato(123, "", true));
    EXPECT_EQ(Restriccion("LU", Dato(123, "", true), false).valor(), Dato(123, "", true));
    EXPECT_EQ(Restriccion("Carrera", Dato(0, "Computacion", false), true).valor(), Dato(0, "Computacion", false));
    EXPECT_EQ(Restriccion("Carrera", Dato(0, "Computacion", false), false).valor(), Dato(0, "Computacion", false));
}

TEST(restriccion_test, coincidencias) {
    EXPECT_TRUE(Restriccion("LU", Dato(123, "", true), true).coincidencia());
    EXPECT_FALSE(Restriccion("LU", Dato(123, "", true), false).coincidencia());
    EXPECT_TRUE(Restriccion("Carrera", Dato(0, "Computacion", false), true).coincidencia());
    EXPECT_FALSE(Restriccion("Carrera", Dato(0, "Computacion", false), false).coincidencia());
}

TEST(restriccion_test, igualdad) {
    EXPECT_EQ(Restriccion("LU", Dato(123, "", true), true), Restriccion("LU", Dato(123, "", true), true));
    EXPECT_NE(Restriccion("LU", Dato(123, "", true), true), Restriccion("LU", Dato(123, "", true), false));
    EXPECT_NE(Restriccion("LU", Dato(123, "", true), true), Restriccion("Año", Dato(123, "", true), true));
    EXPECT_NE(Restriccion("LU", Dato(123, "", true), true), Restriccion("LU", Dato(124, "", true), true));
}