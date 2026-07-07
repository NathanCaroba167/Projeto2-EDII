//
// Created by natha on 06/04/2026.
//
#include <string.h>
#include <stdio.h>

#include "../unity/unity.h"
#include "../include/quadra.h"

void setUp(void) {}
void tearDown(void) {}

void teste_criarQuadra_deveRegistrarAtributosCorretamente(void) {
    Quadra q = criarQuadra("cep01", 10.0, 20.0, 100.0, 50.0);

    TEST_ASSERT_NOT_NULL(q);
    TEST_ASSERT_EQUAL_STRING("cep01", getCEPQuadra(q));
    TEST_ASSERT_EQUAL_DOUBLE(10.0, getXQuadra(q));
    TEST_ASSERT_EQUAL_DOUBLE(20.0, getYQuadra(q));
    TEST_ASSERT_EQUAL_DOUBLE(100.0, getWQuadra(q));
    TEST_ASSERT_EQUAL_DOUBLE(50.0, getHQuadra(q));

    liberarQuadra(q);
}

void teste_criarQuadra_valoresIniciaisDefinidosParaCoresESW(void) {
    Quadra q = criarQuadra("cep02", 15.0, 25.0, 120.0, 60.0);

    TEST_ASSERT_EQUAL_STRING("", getCorBQuadra(q));
    TEST_ASSERT_EQUAL_STRING("", getCorPQuadra(q));
    TEST_ASSERT_EQUAL_DOUBLE(1.0, getSWQuadra(q));

    liberarQuadra(q);
}

void teste_setters_deveAtualizarValoresCorretamente(void) {
    Quadra q = criarQuadra("cep03", 22.0, 40.0, 90.0, 40.0);

    setCEPQuadra(q, "cep4070");
    setXQuadra(q, 26.0);
    setYQuadra(q, 45.0);
    setWQuadra(q, 110.0);
    setHQuadra(q, 55.0);
    setCorBQuadra(q, "blue");
    setCorPQuadra(q, "black");
    setSWQuadra(q, 5.0);

    TEST_ASSERT_EQUAL_STRING("cep4070", getCEPQuadra(q));
    TEST_ASSERT_EQUAL_DOUBLE(26.0, getXQuadra(q));
    TEST_ASSERT_EQUAL_DOUBLE(45.0, getYQuadra(q));
    TEST_ASSERT_EQUAL_DOUBLE(110.0, getWQuadra(q));
    TEST_ASSERT_EQUAL_DOUBLE(55.0, getHQuadra(q));
    TEST_ASSERT_EQUAL_STRING("blue", getCorBQuadra(q));
    TEST_ASSERT_EQUAL_STRING("black", getCorPQuadra(q));
    TEST_ASSERT_EQUAL_DOUBLE(5.0, getSWQuadra(q));

    liberarQuadra(q);
}

void teste_liberarQuadra_naoDeveCrashar(void) {
    Quadra q = criarQuadra("cep10", 20.0, 20.0, 100.0, 50.0);

    liberarQuadra(q);
    TEST_PASS();
}

int main() {
    UNITY_BEGIN();
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO QUADRA\n");
    printf("==========================================\n");

    RUN_TEST(teste_criarQuadra_deveRegistrarAtributosCorretamente);
    RUN_TEST(teste_setters_deveAtualizarValoresCorretamente);
    RUN_TEST(teste_liberarQuadra_naoDeveCrashar);

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return UNITY_END();
}