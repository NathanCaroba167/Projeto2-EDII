//
// Created by natha on 22/06/2026.
//

#include <stdlib.h>

#include "../unity/unity.h"

#include "../include/grafo.h"

void setUp(void){}
void tearDown(void) {}

void teste_criarGrafo_deveComecarVazio(void) {
    Grafo g = criarGrafo(0);

    TEST_ASSERT_NOT_NULL(g);
    TEST_ASSERT_EQUAL_INT(0, getNumVerticesGrafo(g));
    TEST_ASSERT_EQUAL_INT(0, getNumArestasGrafo(g));

    liberarGrafo(g);
}

void teste_buscarVertice_deveEncontrarVerticeExistente(void) {
    Grafo g = criarGrafo(1);
    inserirVerticeGrafo(g,criarVertice("v1", 5.7, 8.0, 0));

    Vertice v = buscaVertice(g,"v1");

    TEST_ASSERT_NOT_NULL(v);
    TEST_ASSERT_EQUAL_STRING("v1", getIDVertice(v));
    TEST_ASSERT_EQUAL_DOUBLE(5.7, getXVertice(v));
    TEST_ASSERT_EQUAL_DOUBLE(8.0, getYVertice(v));

    liberarGrafo(g);
}

void teste_buscarVertice_deveRetornarNULLParaIDInexistente(void) {
    Grafo g = criarGrafo(1);
    inserirVerticeGrafo(g,criarVertice("v1", 7.7, 8.9, 0));

    Vertice v = buscaVertice(g,"erro total");

    TEST_ASSERT_NULL(v);

    liberarGrafo(g);
}

void teste_inserirArestaGrafo_deveVerificarDirigibilidadeGrafo(void) {
    Grafo g = criarGrafo(2);
    inserirVerticeGrafo(g,criarVertice("v1", 16.7, 20.0, 0));
    inserirVerticeGrafo(g,criarVertice("v2", 12.7, 10.0, 1));

    inserirArestaGrafo(g, "v1", "v2", "CEP103", "CEP301", 35.6, 65.0, "Rua Santa Angela");

    Vertice origem = buscaVertice(g, "v1");
    Vertice destino = buscaVertice(g, "v2");

    TEST_ASSERT_EQUAL_INT(1, getTamanhoLista(getArestasVertice(origem)));
    TEST_ASSERT_EQUAL_INT(0, getTamanhoLista(getArestasVertice(destino)));

    liberarGrafo(g);
}

void teste_inserirArestaGrafo_deveInserirDuasArestasFormamRuaMaoDupla(void) {
    Grafo g = criarGrafo(2);
    inserirVerticeGrafo(g,criarVertice("v1", 14.7, 22.0, 0));
    inserirVerticeGrafo(g,criarVertice("v2", 10.7, 16.0, 1));

    inserirArestaGrafo(g, "v1", "v2", "CEP203", "CEP321", 30.6, 70.0, "Rua Santa Maria");
    inserirArestaGrafo(g, "v2", "v1", "CEP412", "CEP405", 30.6, 50.0, "Rua Santa Maria");

    Vertice v1 = buscaVertice(g, "v1");
    Vertice v2 = buscaVertice(g, "v2");

    TEST_ASSERT_EQUAL_INT(1, getTamanhoLista(getArestasVertice(v1)));
    TEST_ASSERT_EQUAL_INT(1, getTamanhoLista(getArestasVertice(v2)));
    TEST_ASSERT_EQUAL_INT(2, getNumArestasGrafo(g));

    liberarGrafo(g);
}

void teste_getNumArestasGrafo_deveContarNumeroArestasCorretamente(void) {
    Grafo g = criarGrafo(4);
    inserirVerticeGrafo(g,criarVertice("v1", 11.7, 26.0, 0));
    inserirVerticeGrafo(g,criarVertice("v2", 18.7, 16.0, 1));
    inserirVerticeGrafo(g,criarVertice("v3", 21.7, 26.0, 2));
    inserirVerticeGrafo(g,criarVertice("v4", 26.7, 17.0, 3));


    inserirArestaGrafo(g, "v1", "v2", "CEP412", "CEP405", 40.6, 70.0, "Rua Santa Monica");
    inserirArestaGrafo(g, "v1", "v3", "CEP405", "CEP413", 50.6, 80.0, "Rua Esperanca");
    inserirArestaGrafo(g, "v2", "v4", "CEP414", "CEP405", 45.6, 50.0, "Rua Natal");
    inserirArestaGrafo(g, "v4", "v3", "CEP415", "CEP405", 39.6, 60.0, "Rua Coritiba");

    TEST_ASSERT_EQUAL_INT(3, getNumArestasGrafo(g));

    liberarGrafo(g);

}

void teste_getVerticesGrafo_deveRetornarListaComTodosVerticesInseridos(void) {
    Grafo g = criarGrafo(3);
    inserirVerticeGrafo(g,criarVertice("v1", 31.7, 16.0, 0));
    inserirVerticeGrafo(g,criarVertice("v2", 25.5, 14.7, 1));
    inserirVerticeGrafo(g,criarVertice("v3", 43.5, 24.7, 2));

    Lista vertices = getVerticesGrafo(g);
    TEST_ASSERT_EQUAL_INT(3,getTamanhoLista(vertices));

    liberarGrafo(g);
}

void teste_liberarGrafo_naoDeveCrasharComGrafoVazio(void) {
    Grafo g = criarGrafo(0);
    liberarGrafo(g);
    TEST_PASS();
}

void teste_liberarGrafo_naoDeveCrasharComVerticesEArestas(void) {
    Grafo g = criarGrafo(2);
    inserirVerticeGrafo(g,criarVertice("v1", 12.0, 14.0, 0));
    inserirVerticeGrafo(g,criarVertice("v2", 21.5, 34.7, 1));
    inserirArestaGrafo(g, "v1", "v2", "CEP405", "CEP412", 40.6, 70.0, "Rua Santa Monica");
    liberarGrafo(g);
    TEST_PASS();
}


int main() {
    UNITY_BEGIN();
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO GRAFO\n");
    printf("==========================================\n");

    RUN_TEST(teste_criarGrafo_deveComecarVazio);
    RUN_TEST(teste_buscarVertice_deveEncontrarVerticeExistente);
    RUN_TEST(teste_buscarVertice_deveRetornarNULLParaIDInexistente);
    RUN_TEST(teste_inserirArestaGrafo_deveVerificarDirigibilidadeGrafo);
    RUN_TEST(teste_inserirArestaGrafo_deveInserirDuasArestasFormamRuaMaoDupla);
    RUN_TEST(teste_getNumArestasGrafo_deveContarNumeroArestasCorretamente);
    RUN_TEST(teste_getVerticesGrafo_deveRetornarListaComTodosVerticesInseridos);
    RUN_TEST(teste_liberarGrafo_naoDeveCrasharComGrafoVazio);
    RUN_TEST(teste_liberarGrafo_naoDeveCrasharComVerticesEArestas);

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return UNITY_END();
}