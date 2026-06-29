//
// Created by natha on 21/06/2026.
//

#include <stdlib.h>

#include "../unity/unity.h"

#include "../include/aresta.h"

void setUp(void){}
void tearDown(void) {}

void teste_criarAresta_deveCriarArestaCorretamenteComAtributosIndicados(void) {
    Vertice v1 = criarVertice("1", 2,2);
    Vertice v2 = criarVertice("2", 4,4);
    Aresta a = criarAresta(v1, v2, "CEP01", "CEP02", 30.6, 80.7, "Getulio Vargas");
    TEST_ASSERT_NOT_NULL(a);
    TEST_ASSERT_EQUAL_PTR(v1, getVerticeV1Aresta(a));
    TEST_ASSERT_EQUAL_PTR(v2, getVerticeV2Aresta(a));
    TEST_ASSERT_EQUAL_STRING("CEP01", getQuadraLadoDireitoAresta(a));
    TEST_ASSERT_EQUAL_STRING("CEP02", getQuadraLadoEsquerdoAresta(a));
    TEST_ASSERT_EQUAL_DOUBLE(30.6, getComprimentoAresta(a));
    TEST_ASSERT_EQUAL_DOUBLE(80.7, getVelocidadeAresta(a));
    TEST_ASSERT_EQUAL_STRING("Getulio Vargas", getNomeAresta(a));

    liberarAresta(a);
}

void teste_criarAresta_devePermitirQuadraDireitaNula(void) {
    Aresta a = criarAresta("v3", "v4", NULL, "CEP301", 80.5, 60.0, "Avenida Paulista");

    TEST_ASSERT_NULL(getQuadraLadoDireitoAresta(a));
    TEST_ASSERT_EQUAL_STRING("CEP301", getQuadraLadoEsquerdoAresta(a));

    liberarAresta(a);
}

void teste_criarAresta_devePermitirQuadraEsquerdaNula(void) {
    Aresta a = criarAresta("v3", "v4", "CEP300", NULL, 80.5, 60.0, "Avenida Paulista");

    TEST_ASSERT_EQUAL_STRING("CEP300", getQuadraLadoDireitoAresta(a));
    TEST_ASSERT_NULL(getQuadraLadoEsquerdoAresta(a));

    liberarAresta(a);
}

void teste_criarAresta_devePermitirAmbasQuadrasNulas(void) {
    Aresta a = criarAresta("v3", "v4", NULL, NULL, 80.5, 60.0, "Avenida Paulista");

    TEST_ASSERT_NULL(getQuadraLadoDireitoAresta(a));
    TEST_ASSERT_NULL(getQuadraLadoEsquerdoAresta(a));

    liberarAresta(a);
}

void teste_setVmAresta_deveAtualizarVelocidadeMediaAresta(void) {
    Vertice v1 = criarVertice("1", 2,2);
    Vertice v2 = criarVertice("2", 4,4);
    Aresta a = criarAresta(v1, v2, "CEP01", "CEP02", 30.6, 80.7, "Getulio Vargas");

    setVelocidadeAresta(a, 15.5);

    TEST_ASSERT_EQUAL_DOUBLE(15.5, getVelocidadeAresta(a));

    liberarAresta(a);
}


int main() {
    UNITY_BEGIN();
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO ARESTA\n");
    printf("==========================================\n");

    RUN_TEST(teste_criarAresta_deveCriarArestaCorretamenteComAtributosIndicados);
    RUN_TEST(teste_criarAresta_devePermitirQuadraDireitaNula);
    RUN_TEST(teste_criarAresta_devePermitirQuadraEsquerdaNula);
    RUN_TEST(teste_criarAresta_devePermitirAmbasQuadrasNulas);
    RUN_TEST(teste_setVmAresta_deveAtualizarVelocidadeMediaAresta);
    RUN_TEST(teste_gettesAresta_devePegarValoresCorretamente);
    RUN_TEST(teste_settersAresta_deveDefinirValoresCorretamente);
    RUN_TEST(teste_liberarAresta_deveLiberarArestaCorretamente);


    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return UNITY_END();
}