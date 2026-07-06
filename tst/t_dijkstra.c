//
// Created by natha on 22/06/2026.
//

#include <stdlib.h>

#include "../unity/unity.h"

#include "../include/lista.h"
#include "../include/aresta.h"
#include "../include/grafo.h"
#include "../include/dijkstra.h"

void setUp(void){}
void tearDown(void) {}

static Grafo montarGrafoLinear(void) {
    Grafo g = criarGrafo();

    inserirVerticeGrafo(g, criarVertice("v1", 0.0, 0.0));
    inserirVerticeGrafo(g, criarVertice("v2", 10.0, 0.0));
    inserirVerticeGrafo(g, criarVertice("v3", 30.0, 0.0));
    inserirArestaGrafo(g, criarAresta("v1", "v2", "CEP107", "CEP108",10.0, 40.0,"Rua Santos"));
    inserirArestaGrafo(g, criarAresta("v2", "v3", "CEP109", "CEP110",20.0, 50.0,"Rua Silva"));

    return g;
}

void teste_dijkstra_caminhoUnico_deveEncontrarUnicoCaminhoCorretamente(void) {
    Grafo g = montarGrafoLinear();

    ResultadoDijkstra r = executarDijkstra(g, "v1", "v3");

    TEST_ASSERT_TRUE(encontrouCaminhoDijkstra(r));

    liberarResultadoDijkstra(r);
    liberarGrafo(g);
}


void teste_dijkstra_caminhoUnico_deveListarArestasDoCaminhoCorretamente(void) {
    Grafo g = montarGrafoLinear();

    ResultadoDijkstra r = executarDijkstra(g, "v1", "v3");
    Lista caminho = getCaminhoDijkstra(r);

    TEST_ASSERT_EQUAL_INT(2, getTamanhoLista(caminho));

    Nopont no = getPrimeiroNoLista(caminho);
    Aresta a1 = getItemNoLista(no);
    no = getProximoNoLista(no);
    Aresta a2 = getItemNoLista(no);

    TEST_ASSERT_EQUAL_STRING("v2", getVerticeV2Aresta(a1));
    TEST_ASSERT_EQUAL_STRING("v3", getVerticeV2Aresta(a2));

    liberarResultadoDijkstra(r);
    liberarGrafo(g);
}

static Grafo montarGrafoInacessivel(void) {
    Grafo g = criarGrafo();

    inserirVerticeGrafo(g, criarVertice("v1", 0.0, 0.0));
    inserirVerticeGrafo(g, criarVertice("v2", 1.0, 0.0));
    inserirVerticeGrafo(g, criarVertice("v3", 5.0, 0.0));
    inserirArestaGrafo(g, criarAresta("v1", "v2", "CEP107", "CEP108",10.0, 60.0,"Rua Cuiaba"));

    return g;
}

void teste_dijkstra_destinoInacessivel_deveRetornarNaoEncontrou(void) {
    Grafo g = montarGrafoInacessivel();

    ResultadoDijkstra r = executarDijkstra(g, "v1", "v3");

    TEST_ASSERT_FALSE(encontrouCaminhoDijkstra(r));

    liberarResultadoDijkstra(r);
    liberarGrafo(g);
}

static Grafo montarGrafoMultiplosCaminhos(void) {
    Grafo g = criarGrafo();

    inserirVerticeGrafo(g, criarVertice("v1", 0.0, 0.0));
    inserirVerticeGrafo(g, criarVertice("v2", 0.0, 10.0));
    inserirVerticeGrafo(g, criarVertice("v3", 10.0, 10.0));
    inserirArestaGrafo(g, criarAresta("v1", "v2", "CEP110", "CEP111",5.0, 60.0,"Rua A"));
    inserirArestaGrafo(g, criarAresta("v2", "v3", "CEP110", "CEP112",5.0, 60.0,"Rua B"));
    inserirArestaGrafo(g, criarAresta("v1", "v3", "CEP113", "CEP110",15.0, 60.0,"Rua C"));

    return g;
}

void teste_dijkstra_multiplosCaminhos_deveEscolherMenorCaminho(void) {
    Grafo g = montarGrafoMultiplosCaminhos();

    ResultadoDijkstra r = executarDijkstra(g, "v1", "v3");

    TEST_ASSERT_TRUE(encontrouCaminhoDijkstra(r));

    Lista caminho = getCaminhoDijkstra(r);
    TEST_ASSERT_EQUAL_INT(2, getTamanhoLista(caminho));

    liberarResultadoDijkstra(r);
    liberarGrafo(g);
}

int main() {
    UNITY_BEGIN();
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO DIJKSTRA\n");
    printf("==========================================\n");

    RUN_TEST(teste_dijkstra_caminhoUnico_deveEncontrarUnicoCaminhoCorretamente);
    RUN_TEST(teste_dijkstra_caminhoUnico_deveListarArestasDoCaminhoCorretamente);
    RUN_TEST(teste_dijkstra_destinoInacessivel_deveRetornarNaoEncontrou);
    RUN_TEST(teste_dijkstra_multiplosCaminhos_deveEscolherMenorCaminho);

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return UNITY_END();
}