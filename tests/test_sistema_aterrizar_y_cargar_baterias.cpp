#include <sistema.h>
#include "gtest/gtest.h"
#include "factories.h"
#include "auxiliares.h"

TEST(test_sistema_aterrizar_y_cargar_baterias, aterrizan_y_cargan_solo_los_que_corresponden) {
    Posicion posG{0, 2};
    Campo campo_3x5(posG, {2, 0}, {3, 5});
    Sistema s1(campo_3x5, {});

    Drone uno_en_el_granero(1, algunos_productos());
    Drone uno_volando_con_bateria_80(2, algunos_productos());
    Drone uno_volando_con_bateria_60(3, algunos_productos());
    Drone uno_volando_con_bateria_30(4, algunos_productos());
    uno_en_el_granero.cambiarPosicionActual(posG);
    uno_volando_con_bateria_80.cambiarPosicionActual(posG);
    uno_volando_con_bateria_60.cambiarPosicionActual(posG);
    uno_volando_con_bateria_30.cambiarPosicionActual(posG);

    uno_volando_con_bateria_80.moverA({0, 1});
    uno_volando_con_bateria_80.moverA({0, 0});
    uno_volando_con_bateria_80.setBateria(80);

    uno_volando_con_bateria_60.moverA({1, 2});
    uno_volando_con_bateria_60.moverA({2, 2});
    uno_volando_con_bateria_60.setBateria(60);

    uno_volando_con_bateria_30.moverA({0, 3});
    uno_volando_con_bateria_30.moverA({0, 4});
    uno_volando_con_bateria_30.setBateria(30);

    s1._enjambre.push_back(uno_en_el_granero);
    s1._enjambre.push_back(uno_volando_con_bateria_80);
    s1._enjambre.push_back(uno_volando_con_bateria_60);
    s1._enjambre.push_back(uno_volando_con_bateria_30);

    s1.aterrizarYCargarBaterias(60);

    Drone el_del_granero_en_s1 = test::buscarDroneEnSistema(uno_en_el_granero, s1);
    EXPECT_EQ(1, el_del_granero_en_s1.id());
    EXPECT_EQ(100, el_del_granero_en_s1.bateria());
    EXPECT_TRUE(!el_del_granero_en_s1.enVuelo());
    EXPECT_TRUE(el_del_granero_en_s1.vueloRealizado().empty());
    EXPECT_TRUE(test::mismos(algunos_productos(), el_del_granero_en_s1.productosDisponibles()));

    Drone el_que_esta_volando_con_bateria_80_en_s1 = test::buscarDroneEnSistema(uno_volando_con_bateria_80, s1);
    EXPECT_EQ(2, el_que_esta_volando_con_bateria_80_en_s1.id());
    EXPECT_EQ(80, el_que_esta_volando_con_bateria_80_en_s1.bateria());
    EXPECT_TRUE(el_que_esta_volando_con_bateria_80_en_s1.enVuelo());
    EXPECT_TRUE(!el_que_esta_volando_con_bateria_80_en_s1.vueloRealizado().empty());
    EXPECT_TRUE(test::mismos(algunos_productos(), el_que_esta_volando_con_bateria_80_en_s1.productosDisponibles()));

    Drone el_que_esta_volando_con_bateria_60_en_s1 = test::buscarDroneEnSistema(uno_volando_con_bateria_60, s1);
    EXPECT_EQ(3, el_que_esta_volando_con_bateria_60_en_s1.id());
    EXPECT_EQ(60, el_que_esta_volando_con_bateria_60_en_s1.bateria());
    EXPECT_TRUE(el_que_esta_volando_con_bateria_60_en_s1.enVuelo());
    EXPECT_TRUE(!el_que_esta_volando_con_bateria_60_en_s1.vueloRealizado().empty());
    EXPECT_TRUE(test::mismos(algunos_productos(), el_que_esta_volando_con_bateria_60_en_s1.productosDisponibles()));

    Drone el_que_estaba_volando_con_bateria_30_en_s1 = test::buscarDroneEnSistema(uno_volando_con_bateria_30, s1);
    EXPECT_EQ(4, el_que_estaba_volando_con_bateria_30_en_s1.id());
    EXPECT_EQ(100, el_que_estaba_volando_con_bateria_30_en_s1.bateria());
    EXPECT_TRUE(!el_que_estaba_volando_con_bateria_30_en_s1.enVuelo());
    EXPECT_TRUE(el_que_estaba_volando_con_bateria_30_en_s1.vueloRealizado().empty());
    EXPECT_TRUE(test::mismos(algunos_productos(), el_que_estaba_volando_con_bateria_30_en_s1.productosDisponibles()));
}
