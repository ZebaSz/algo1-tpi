#include <sistema.h>
#include "gtest/gtest.h"
#include "auxiliares.h"

TEST(test_sistema_fertilizar_por_filas, todos_fertilizan_hasta_donde_pueden) {
    Posicion posG{2, 2};
    Campo campo_5x5(posG, {0, 3}, {5, 5});
    Sistema s1(campo_5x5, {});

    std::vector<Producto> fertilizante_suficiente = {Fertilizante, Fertilizante, Fertilizante, Fertilizante,
                                                     Fertilizante, Fertilizante, PlaguicidaBajoConsumo, Herbicida};

    std::vector<Producto> solo_3_fertilizantes = {Fertilizante, Fertilizante, Fertilizante, PlaguicidaBajoConsumo,
                                                  Herbicida};

    /* -> Estado inicial de posicion de drones (numerados del 0 al 4) y lo que tiene que pasar
     * |---C0|
     * |----1|
     * |--G-2|
     * |---M3|
     * |----4|
     */

    Drone en_fila_0_por_chocarse_con_la_casa(1, fertilizante_suficiente);
    Drone en_fila_1_por_quedarse_sin_bateria(2, fertilizante_suficiente);
    Drone en_fila_2_por_chocarse_con_granero(3, fertilizante_suficiente);
    Drone en_fila_3_por_quedarse_sin_fertiliante(4, solo_3_fertilizantes);
    Drone en_fila_4_que_va_a_llegar_hasta_el_final(5, fertilizante_suficiente);
    Drone uno_en_el_granero(6, fertilizante_suficiente);

    en_fila_0_por_chocarse_con_la_casa.moverA({0, 4});
    en_fila_1_por_quedarse_sin_bateria.moverA({1, 4});
    en_fila_2_por_chocarse_con_granero.moverA({2, 4});
    en_fila_3_por_quedarse_sin_fertiliante.moverA({3, 4});
    en_fila_4_que_va_a_llegar_hasta_el_final.moverA({4, 4});
    uno_en_el_granero.cambiarPosicionActual(posG);

    en_fila_1_por_quedarse_sin_bateria.setBateria(1);

    for (unsigned int i = 0; i < s1._campo.dimensiones().ancho; i++) {
        for (unsigned int j = 0; j < s1._campo.dimensiones().largo; j++) {
            s1._estado.parcelas[i][j] = RecienSembrado;
        }
    }

    s1._estado.parcelas[3][3] = ConMaleza;

    s1._enjambre.push_back(en_fila_0_por_chocarse_con_la_casa);
    s1._enjambre.push_back(en_fila_1_por_quedarse_sin_bateria);
    s1._enjambre.push_back(en_fila_2_por_chocarse_con_granero);
    s1._enjambre.push_back(en_fila_3_por_quedarse_sin_fertiliante);
    s1._enjambre.push_back(en_fila_4_que_va_a_llegar_hasta_el_final);
    s1._enjambre.push_back(uno_en_el_granero);

    s1.fertilizarPorFilas();

    /* -> Estado final de posición de drones esperado (numerados del 0 al 4)
     * |---C0| <- No avanza pq se choca con la casa inmediatamente
     * |---1-| <- Va a avanzar 1 pos pq se queda sin bateria
     * |--G2-| <- Va a avanzar 1 pos pq se choca con el granero
     * |-3---| <- Va a avanzar 3 pos pq tiene 3 fertilizantes pero 1 parcela (M) tiene maleza (no cosechable).
     * |4----| <- Va a avanzar 4 pos (hasta el final del campo)
     */

    en_fila_0_por_chocarse_con_la_casa = test::buscarDroneEnSistema(en_fila_0_por_chocarse_con_la_casa, s1);
    EXPECT_EQ(1, en_fila_0_por_chocarse_con_la_casa.id());
    EXPECT_EQ(100, en_fila_0_por_chocarse_con_la_casa.bateria());
    EXPECT_TRUE(en_fila_0_por_chocarse_con_la_casa.enVuelo());
    EXPECT_TRUE(!en_fila_0_por_chocarse_con_la_casa.vueloRealizado().empty());
    EXPECT_EQ((Posicion{0, 4}), en_fila_0_por_chocarse_con_la_casa.posicionActual());
    EXPECT_TRUE(test::mismos(
            {Fertilizante, Fertilizante, Fertilizante, Fertilizante, Fertilizante, PlaguicidaBajoConsumo, Herbicida},
            en_fila_0_por_chocarse_con_la_casa.productosDisponibles()));

    en_fila_1_por_quedarse_sin_bateria = test::buscarDroneEnSistema(en_fila_1_por_quedarse_sin_bateria, s1);
    EXPECT_EQ(2, en_fila_1_por_quedarse_sin_bateria.id());
    EXPECT_EQ(0, en_fila_1_por_quedarse_sin_bateria.bateria());
    EXPECT_TRUE(en_fila_1_por_quedarse_sin_bateria.enVuelo());
    EXPECT_TRUE(!en_fila_1_por_quedarse_sin_bateria.vueloRealizado().empty());
    EXPECT_EQ((Posicion{1, 3}), en_fila_1_por_quedarse_sin_bateria.posicionActual());
    EXPECT_TRUE(test::mismos({Fertilizante, Fertilizante, Fertilizante, Fertilizante, PlaguicidaBajoConsumo, Herbicida},
                             en_fila_1_por_quedarse_sin_bateria.productosDisponibles()));

    en_fila_2_por_chocarse_con_granero = test::buscarDroneEnSistema(en_fila_2_por_chocarse_con_granero, s1);
    EXPECT_EQ(3, en_fila_2_por_chocarse_con_granero.id());
    EXPECT_EQ(99, en_fila_2_por_chocarse_con_granero.bateria());
    EXPECT_TRUE(en_fila_2_por_chocarse_con_granero.enVuelo());
    EXPECT_TRUE(!en_fila_2_por_chocarse_con_granero.vueloRealizado().empty());
    EXPECT_EQ((Posicion{2, 3}), en_fila_2_por_chocarse_con_granero.posicionActual());
    EXPECT_TRUE(test::mismos({Fertilizante, Fertilizante, Fertilizante, Fertilizante, PlaguicidaBajoConsumo, Herbicida},
                             en_fila_2_por_chocarse_con_granero.productosDisponibles()));

    en_fila_3_por_quedarse_sin_fertiliante = test::buscarDroneEnSistema(en_fila_3_por_quedarse_sin_fertiliante, s1);
    EXPECT_EQ(4, en_fila_3_por_quedarse_sin_fertiliante.id());
    EXPECT_EQ(97, en_fila_3_por_quedarse_sin_fertiliante.bateria());
    EXPECT_TRUE(en_fila_3_por_quedarse_sin_fertiliante.enVuelo());
    EXPECT_TRUE(!en_fila_3_por_quedarse_sin_fertiliante.vueloRealizado().empty());
    EXPECT_EQ((Posicion{3, 1}), en_fila_3_por_quedarse_sin_fertiliante.posicionActual());
    EXPECT_TRUE(test::mismos({PlaguicidaBajoConsumo, Herbicida},
                             en_fila_3_por_quedarse_sin_fertiliante.productosDisponibles()));

    en_fila_4_que_va_a_llegar_hasta_el_final = test::buscarDroneEnSistema(en_fila_4_que_va_a_llegar_hasta_el_final, s1);
    EXPECT_EQ(5, en_fila_4_que_va_a_llegar_hasta_el_final.id());
    EXPECT_EQ(96, en_fila_4_que_va_a_llegar_hasta_el_final.bateria());
    EXPECT_TRUE(en_fila_4_que_va_a_llegar_hasta_el_final.enVuelo());
    EXPECT_TRUE(!en_fila_4_que_va_a_llegar_hasta_el_final.vueloRealizado().empty());
    EXPECT_EQ((Posicion{4, 0}), en_fila_4_que_va_a_llegar_hasta_el_final.posicionActual());
    EXPECT_TRUE(test::mismos({Fertilizante, PlaguicidaBajoConsumo, Herbicida},
                             en_fila_4_que_va_a_llegar_hasta_el_final.productosDisponibles()));

    uno_en_el_granero = test::buscarDroneEnSistema(uno_en_el_granero, s1);
    EXPECT_EQ(6, uno_en_el_granero.id());
    EXPECT_EQ(100, uno_en_el_granero.bateria());
    EXPECT_TRUE(!uno_en_el_granero.enVuelo());
    EXPECT_TRUE(uno_en_el_granero.vueloRealizado().empty());
    EXPECT_EQ(posG, uno_en_el_granero.posicionActual());
    EXPECT_TRUE(test::mismos(fertilizante_suficiente, uno_en_el_granero.productosDisponibles()));

    /* -> Estado final del campo (C = Casa, G = Granero, L = Listo Para Cosechar, M = Con Maleza)
     * |---CL|
     * |---LL|
     * |--GLL|
     * |-LLML|
     * |LLLLL|
     */

    EXPECT_EQ(RecienSembrado, s1.estadoDelCultivo({0, 0}));
    EXPECT_EQ(RecienSembrado, s1.estadoDelCultivo({0, 1}));
    EXPECT_EQ(RecienSembrado, s1.estadoDelCultivo({0, 2}));
    //EXPECT_EQ(CASA, s1.estadoDelCultivo({0, 3}));
    EXPECT_EQ(ListoParaCosechar, s1.estadoDelCultivo({0, 4}));

    EXPECT_EQ(RecienSembrado, s1.estadoDelCultivo({1, 0}));
    EXPECT_EQ(RecienSembrado, s1.estadoDelCultivo({1, 1}));
    EXPECT_EQ(RecienSembrado, s1.estadoDelCultivo({1, 2}));
    EXPECT_EQ(ListoParaCosechar, s1.estadoDelCultivo({1, 3}));
    EXPECT_EQ(ListoParaCosechar, s1.estadoDelCultivo({1, 4}));

    EXPECT_EQ(RecienSembrado, s1.estadoDelCultivo({2, 0}));
    EXPECT_EQ(RecienSembrado, s1.estadoDelCultivo({2, 1}));
    //EXPECT_EQ(GRANERO, s1.estadoDelCultivo({2, 2}));
    EXPECT_EQ(ListoParaCosechar, s1.estadoDelCultivo({2, 3}));
    EXPECT_EQ(ListoParaCosechar, s1.estadoDelCultivo({2, 4}));

    EXPECT_EQ(RecienSembrado, s1.estadoDelCultivo({3, 0}));
    EXPECT_EQ(ListoParaCosechar, s1.estadoDelCultivo({3, 1}));
    EXPECT_EQ(ListoParaCosechar, s1.estadoDelCultivo({3, 2}));
    EXPECT_EQ(ConMaleza, s1.estadoDelCultivo({3, 3}));
    EXPECT_EQ(ListoParaCosechar, s1.estadoDelCultivo({3, 4}));

    EXPECT_EQ(ListoParaCosechar, s1.estadoDelCultivo({4, 0}));
    EXPECT_EQ(ListoParaCosechar, s1.estadoDelCultivo({4, 1}));
    EXPECT_EQ(ListoParaCosechar, s1.estadoDelCultivo({4, 2}));
    EXPECT_EQ(ListoParaCosechar, s1.estadoDelCultivo({4, 3}));
    EXPECT_EQ(ListoParaCosechar, s1.estadoDelCultivo({4, 4}));
}
