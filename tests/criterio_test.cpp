//
// Created by gonzalo on 7/09/17.
//

#include "gtest/gtest.h"

#include "../src/criterio.h"

class CriterioTests : public ::testing::Test {

protected:
    CriterioTests() : c1(
            {Restriccion("LU", datoNat(123), true), Restriccion("Carrera", datoStr("Computacion"), false)}),
                      c2({Restriccion("Carrera", datoStr("Computacion"), false),
                          Restriccion("LU", datoNat(123), true)}),
                      c3({Restriccion("LU", datoNat(123), false),
                          Restriccion("Carrera", datoStr("Computacion"), true)}),
                      c4({Restriccion("Carrera", datoStr("Computacion"), true),
                          Restriccion("LU", datoNat(123), false)}) {};

    Criterio c1;
    Criterio c2;
    Criterio c3;
    Criterio c4;

};

TEST(criterio_test, crear) {
    Criterio c1({Restriccion("LU", datoNat(123), true),
                 Restriccion("Carrera", datoStr("Computacion"), false)});
    Criterio c2({Restriccion("LU", datoNat(123), false),
                 Restriccion("Carrera", datoStr("Computacion"), true)});
    Criterio c3({Restriccion("LU", datoNat(123), false),
                 Restriccion("Carrera", datoStr("Computacion"), true)});
    Criterio c4({Restriccion("Carrera", datoStr("Computacion"), true),
                 Restriccion("LU", datoNat(123), false)});
};

TEST_F(CriterioTests, restricciones) {
    vector<Restriccion> v1 = {Restriccion("LU", datoNat(123), true),
                              Restriccion("Carrera", datoStr("Computacion"), false)};
    vector<Restriccion> v2 = {Restriccion("Carrera", datoStr("Computacion"), false),
                              Restriccion("LU", datoNat(123), true)};
    vector<Restriccion> v3 = {Restriccion("LU", datoNat(123), false),
                              Restriccion("Carrera", datoStr("Computacion"), true)};
    vector<Restriccion> v4 = {Restriccion("Carrera", datoStr("Computacion"), true),
                              Restriccion("LU", datoNat(123), false)};
    EXPECT_EQ(c1.restricciones(), v1);
    EXPECT_EQ(c2.restricciones(), v2);
    EXPECT_EQ(c3.restricciones(), v3);
    EXPECT_EQ(c4.restricciones(), v4);
};

TEST_F(CriterioTests, igualdad) {
    EXPECT_EQ(c1, c2);
    EXPECT_EQ(c3, c4);
    EXPECT_NE(c1, c3);
    EXPECT_NE(c1, c4);
    EXPECT_NE(c2, c3);
    EXPECT_NE(c2, c4);
};