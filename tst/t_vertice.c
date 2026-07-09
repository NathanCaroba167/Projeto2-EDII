//
// Created by natha on 21/06/2026.
//

#include <stdlib.h>

#include "../unity/unity.h"

#include "../include/aresta.h"

#include "../include/lista.h"

#include "../include/vertice.h"

void setUp(void){}
void tearDown(void) {}

void teste_criarVertice_deveCriarVerticeCorretamenteComAtributosIndicados(void) {
    Vertice v1 = criarVertice("v1", 2.6, 3.7, 0);

    TEST_ASSERT_NOT_NULL(v1);
    TEST_ASSERT_EQUAL_STRING("v1", getIDVertice(v1));
    TEST_ASSERT_EQUAL_INT(2.6, getXVertice(v1));
    TEST_ASSERT_EQUAL_INT(3.7, getYVertice(v1));

    liberarVertice(v1);
}

void teste_setArestaVertice_deveGuardarArestaNaListaCorretamente(void) {
    Vertice v2 = criarVertice("v2", 2.6, 3.7, 0);
    Aresta a = criarAresta("v3", "CEP303", "CEP304", 75.0, 45.0, "Getulio Vargas");

    setArestaVertice(v2, a);

    Lista arestas = getArestasVertice(v2);
    Nopont n = getPrimeiroNoLista(arestas);
    TEST_ASSERT_NOT_NULL(n);

    Aresta arestaGuardada = (Aresta) getItemNoLista(n);
    TEST_ASSERT_EQUAL_STRING("v7", getIDVerticeDestinoAresta(arestaGuardada));
    TEST_ASSERT_EQUAL_STRING("v3", getIDVerticeDestinoAresta(arestaGuardada));
    TEST_ASSERT_EQUAL_DOUBLE(75.0, getComprimentoAresta(arestaGuardada));
    TEST_ASSERT_EQUAL_DOUBLE(45.0, getVelocidadeAresta(arestaGuardada));

    liberarVertice(v2);
}

void teste_liberarVertice_naoDeveCrashar(void) {
    Vertice v = criarVertice("v9", 6.7, 6.7, 0);
    setArestaVertice(v, criarAresta("v3", "CEP303", "CEP304", 75.0, 45.0, "Getulio Vargas"));
    setArestaVertice(v, criarAresta("v7", "CEP304", "CEP303", 55.0, 80.0, "Alfredo Gois"));

    liberarVertice(v);
    TEST_PASS();
}

int main() {
    UNITY_BEGIN();
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO VERTICE\n");
    printf("==========================================\n");

    RUN_TEST(teste_criarVertice_deveCriarVerticeCorretamenteComAtributosIndicados);
    RUN_TEST(teste_setArestaVertice_deveGuardarArestaNaListaCorretamente);
    RUN_TEST(teste_liberarVertice_naoDeveCrashar);

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return UNITY_END();
}