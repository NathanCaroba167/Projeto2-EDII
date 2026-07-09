//
// Created by natha on 21/06/2026.
//

#include <stdlib.h>
#include <string.h>

#include "../unity/unity.h"

#include "../include/vertice.h"
#include "../include/aresta.h"

void setUp(void) {}
void tearDown(void) {}

void teste_criaAresta_deveArmazenarTodosAtributosCorretamente(void) {
    Aresta a = criarAresta("v2", "12345-000", "12345-001", 120.5, 13.8,"Rua das Flores");

    TEST_ASSERT_NOT_NULL(a);
    TEST_ASSERT_EQUAL_STRING("v2", getIDVerticeDestinoAresta(a));
    TEST_ASSERT_EQUAL_STRING("Rua das Flores", getNomeAresta(a));
    TEST_ASSERT_EQUAL_STRING("12345-000", getQuadraLadoDireitoAresta(a));
    TEST_ASSERT_EQUAL_STRING("12345-001", getQuadraLadoEsquerdoAresta(a));
    TEST_ASSERT_EQUAL_DOUBLE(120.5, getComprimentoAresta(a));
    TEST_ASSERT_EQUAL_DOUBLE(13.8, getVelocidadeAresta(a));

    liberarAresta(a);
}

void teste_criaAresta_devePermitirLdirNulo(void) {
    Aresta a = criarAresta("v3", NULL, "98765-000", 80.0, 10.0, "Avenida Central");

    TEST_ASSERT_NULL(getQuadraLadoDireitoAresta(a));
    TEST_ASSERT_EQUAL_STRING("98765-000", getQuadraLadoEsquerdoAresta(a));

    liberarAresta(a);
}

void teste_criaAresta_devePermitirLesqNulo(void) {
    Aresta a = criarAresta("v4", "11111-000", NULL, 50.0, 8.0, "Rua Sem Saida");

    TEST_ASSERT_EQUAL_STRING("11111-000", getQuadraLadoDireitoAresta(a));
    TEST_ASSERT_NULL(getQuadraLadoEsquerdoAresta(a));

    liberarAresta(a);
}

void teste_criaAresta_devePermitirAmbosLadosNulos(void) {
    Aresta a = criarAresta("v5", NULL, NULL, 30.0, 5.0, "Travessa Nova");

    TEST_ASSERT_NULL(getQuadraLadoDireitoAresta(a));
    TEST_ASSERT_NULL(getQuadraLadoEsquerdoAresta(a));

    liberarAresta(a);
}

void teste_criaAresta_deveCopiarStringsInternamente(void) {
    char idDestino[20];
    strcpy(idDestino, "v6");
    char nome[40];
    strcpy(nome, "Rua Original");

    Aresta a = criarAresta(idDestino, NULL, NULL, 10.0, 1.0, nome);

    strcpy(idDestino, "ALTERADO");
    strcpy(nome, "ALTERADO");

    TEST_ASSERT_EQUAL_STRING("v6", getIDVerticeDestinoAresta(a));
    TEST_ASSERT_EQUAL_STRING("Rua Original", getNomeAresta(a));

    liberarAresta(a);
}

void teste_setVelocidadeAresta_deveAtualizarVelocidadeMedia(void) {
    Aresta a = criarAresta("v7", NULL, NULL, 100.0, 10.0, "Rua Teste");

    setVelocidadeAresta(a, 15.5);

    TEST_ASSERT_EQUAL_DOUBLE(15.5, getVelocidadeAresta(a));

    liberarAresta(a);
}

void teste_setVelocidadeAresta_naoDeveAlterarOutrosAtributos(void) {
    Aresta a = criarAresta("v8", "11111-000", "22222-000", 200.0, 10.0, "Rua Teste 2");

    setVelocidadeAresta(a, 20.0);

    TEST_ASSERT_EQUAL_STRING("v8", getIDVerticeDestinoAresta(a));
    TEST_ASSERT_EQUAL_STRING("Rua Teste 2", getNomeAresta(a));
    TEST_ASSERT_EQUAL_STRING("11111-000", getQuadraLadoDireitoAresta(a));
    TEST_ASSERT_EQUAL_STRING("22222-000", getQuadraLadoEsquerdoAresta(a));
    TEST_ASSERT_EQUAL_DOUBLE(200.0, getCcomprimentoAresta(a));
    TEST_ASSERT_EQUAL_DOUBLE(20.0, getVelocidadeAresta(a));

    liberarAresta(a);
}

int main() {
    UNITY_BEGIN();
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO ARESTA\n");
    printf("==========================================\n");

    RUN_TEST(teste_criaAresta_devePermitirAmbosLadosNulos);
    RUN_TEST(teste_criaAresta_deveArmazenarTodosAtributosCorretamente);
    RUN_TEST(teste_criaAresta_devePermitirLdirNulo);
    RUN_TEST(teste_criaAresta_devePermitirLesqNulo);
    RUN_TEST(teste_criaAresta_deveCopiarStringsInternamente);
    RUN_TEST(teste_setVelocidadeAresta_deveAtualizarVelocidadeMedia);
    RUN_TEST(teste_setVelocidadeAresta_naoDeveAlterarOutrosAtributos);

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return UNITY_END();
}