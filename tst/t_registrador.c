//
// Created by natha on 04/07/2026.
//

#include <stdlib.h>

#include "../unity/unity.h"

#include "../include/registrador.h"

void setUp(void){}
void tearDown(void) {}

void teste_criarRegistradores_devemComecarVazios(void) {
    Registradores estoque = criarRegistradores();

    TEST_ASSERT_NOT_NULL(estoque);
    for (int i = 0; i <= 10; i++) {
        char nome[4];
        sprintf(nome, "R%d", i);
        TEST_ASSERT_FALSE(registradorOcupado(estoque, nome));
    }

    liberarRegistradores(estoque);
}

void teste_setRegistrador_deveOcuparORegistrador(void) {
    Registradores estoque = criarRegistradores();

    TEST_ASSERT_FALSE(registradorOcupado(estoque, "R0"));
    setRegistrador(estoque, "R0", 10.0, 20.0);
    TEST_ASSERT_TRUE(registradorOcupado(estoque, "R0"));

    liberarRegistradores(estoque);
}

void teste_setRegistrador_deveArmazenarPosicaoCorretamente(void) {
    Registradores estoque = criarRegistradores();

    setRegistrador(estoque, "R3", 67.7, 77.6);

    TEST_ASSERT_EQUAL_DOUBLE(67.7, getXRegistrador(estoque, "R3"));
    TEST_ASSERT_EQUAL_DOUBLE(77.6, getYRegistrador(estoque, "R3"));

    liberarRegistradores(estoque);
}

void teste_setRegistrador_sobrescritaDeveAtualizarPosicaoRegistrador(void) {
    Registradores estoque = criarRegistradores();

    setRegistrador(estoque, "R4", 20.0, 30.0);
    setRegistrador(estoque, "R4", 30.0, 40.0);

    TEST_ASSERT_EQUAL_DOUBLE(30.0, getXRegistrador(estoque, "R4"));
    TEST_ASSERT_EQUAL_DOUBLE(40.0, getYRegistrador(estoque, "R4"));

    liberarRegistradores(estoque);
}

void teste_liberarRegistradores_naoDeveCrashar(void) {
    Registradores estoque = criarRegistradores();
    liberarRegistradores(estoque);
    TEST_PASS();
}

int main() {
    UNITY_BEGIN();
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO REGISTRADOR\n");
    printf("==========================================\n");

    RUN_TEST(teste_criarRegistradores_devemComecarVazios);
    RUN_TEST(teste_setRegistrador_deveOcuparORegistrador);
    RUN_TEST(teste_setRegistrador_deveArmazenarPosicaoCorretamente);
    RUN_TEST(teste_setRegistrador_sobrescritaDeveAtualizarPosicaoRegistrador);
    RUN_TEST(teste_liberarRegistradores_naoDeveCrashar);

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return UNITY_END();
}
