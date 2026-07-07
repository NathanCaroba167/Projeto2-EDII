//
// Created by natha on 22/06/2026.
//

#include <stdlib.h>

#include "../unity/unity.h"

#include "../include/arvoreGeradoraMinima.h"

void setUp(void){}
void tearDown(void) {}

void teste_executarArvoreGeradoraMinima_grafoVazio_deveRetonarZeroArestas(void){
    Grafo g = criarGrafo();

    ResultadoArvoreGeradoraMinima r = executarArvoreGeradoraMinima(g, 5.0);

    TEST_ASSERT_EQUAL_INT(0, getArestasArvoreGeradoraMinima(r));

    liberarResultadoArvoreGeradoraMinima(r);
    liberarGrafo(g);
}

void teste_executarArvoreGeradoraMinima_verticeIsolado_naoDeveCrashar(void) {
    Grafo g = criarGrafo();
    inserirVerticeGrafo(g, criarVertice("v1", 0.0, 0.0));
    inserirVerticeGrafo(g, criarVertice("v2", 5.0, 0.0));
    inserirVerticeGrafo(g, criarVertice("v3", 10.0, 0.0));
    inserirArestaGrafo(g, criarAresta("v1", "v2", "CEP469", "CEP118", 50.0, 40.0, "Rua Socrates"));

    ResultadoArvoreGeradoraMinima r = executarArvoreGeradoraMinima(g, 50.0);

    TEST_ASSERT_EQUAL_INT(1, getArestasArvoreGeradoraMinima(r));

    liberarResultadoArvoreGeradoraMinima(r);
    liberarGrafo(g);
}

void teste_executarArvoreGeradoraMinima_umaAresta_vmMenorQueVl_deveModificarVM(void) {
    Grafo g = criarGrafo();
    inserirVerticeGrafo(g, criarVertice("v1", 0.0, 0.0));
    inserirVerticeGrafo(g, criarVertice("v2", 5.0, 0.0));
    inserirArestaGrafo(g, criarAresta("v1", "v2", "CEP169", "CEP104", 50.0, 50.0, "Rua Aristoteles"));

    ResultadoArvoreGeradoraMinima r = executarArvoreGeradoraMinima(g, 60.0);

    TEST_ASSERT_EQUAL_INT(1, getNumArestasArvoreGeradoraMinima(r));

    Vertice v1 = getVerticesGrafo(g, "v1");
    Lista lAresta = getArestasVertice(v1);
    Nopont noLista = getPrimeiroNoLista(lAresta);
    Aresta a = (Aresta) getItemNoLista(noLista);

    TEST_ASSERT_EQUAL_DOUBLE(75.0, getVelocidadeAresta(a));

    liberarResultadoArvoreGeradoraMinima(r);
    liberarGrafo(g);
}

void teste_executarArvoreGeradoraMinima_umaAresta_vmMaiorOuIgualQueVl_naoDeveModificarVM(void) {
    Grafo g = criarGrafo();
    inserirVerticeGrafo(g, criarVertice("v1", 0.0, 0.0));
    inserirVerticeGrafo(g, criarVertice("v2", 5.0, 0.0));
    inserirArestaGrafo(g, criarAresta("v1", "v2", "CEP139", "CEP194", 50.0, 50.0, "Rua Kant"));

    ResultadoArvoreGeradoraMinima r = executarArvoreGeradoraMinima(g, 40.0);

    TEST_ASSERT_EQUAL_INT(0, getNumArestasArvoreGeradoraMinima(r));

    Vertice v1 = getVerticesGrafo(g, "v1");
    Lista lAresta = getArestasVertice(v1);
    Nopont noLista = getPrimeiroNoLista(lAresta);
    Aresta a = (Aresta) getItemNoLista(noLista);

    TEST_ASSERT_EQUAL_DOUBLE(50.0, getVelocidadeAresta(a));

    liberarResultadoArvoreGeradoraMinima(r);
    liberarGrafo(g);
}

void teste_executarArvoreGeradoraMinima_caminhoTriangulo_deveEscolherMenorCmp(void) {
    Grafo g = criarGrafo();
    inserirVerticeGrafo(g, criarVertice("v1", 0.0, 0.0));
    inserirVerticeGrafo(g, criarVertice("v2", 5.0, 0.0));
    inserirVerticeGrafo(g, criarVertice("v3", 10.0, 5.0));
    inserirArestaGrafo(g, criarAresta("v1", "v2", "CEP139", "CEP194", 10.0, 30.0, "Rua Kant"));
    inserirArestaGrafo(g, criarAresta("v2", "v3", "CEP149", "CEP194", 20.0, 30.0, "Rua Descartes"));
    inserirArestaGrafo(g, criarAresta("v1", "v3", "CEP194", "CEP129", 100.0, 30.0, "Rua Nietzsche"));

    ResultadoArvoreGeradoraMinima r = executarArvoreGeradoraMinima(g, 40.0);

    TEST_ASSERT_EQUAL_INT(2, getNumArestasArvoreGeradoraMinima(r));

    liberarResultadoArvoreGeradoraMinima(r);
    liberarGrafo(g);
}

void teste_executarArvoreGeradoraMinima_caminhoTriangulo_naoDeveModificarArestaForaArvore(void) {
    Grafo g = criarGrafo();
    inserirVerticeGrafo(g, criarVertice("v1", 0.0, 0.0));
    inserirVerticeGrafo(g, criarVertice("v2", 5.0, 0.0));
    inserirVerticeGrafo(g, criarVertice("v3", 10.0, 5.0));
    inserirArestaGrafo(g, criarAresta("v1", "v2", "CEP139", "CEP194", 10.0, 30.0, "Rua Locke"));
    inserirArestaGrafo(g, criarAresta("v2", "v3", "CEP149", "CEP194", 20.0, 30.0, "Rua Heraclito"));
    inserirArestaGrafo(g, criarAresta("v1", "v3", "CEP194", "CEP129", 100.0, 30.0, "Rua Gorgias"));

    ResultadoArvoreGeradoraMinima r = executarArvoreGeradoraMinima(g, 40.0);

    Vertice v1 = getVerticesGrafo(g, "v1");
    Lista lAresta = getArestasVertice(v1);
    Nopont noLista = getPrimeiroNoLista(lAresta);
    while (noLista != NULL) {
        Aresta a = (Aresta) getItemNoLista(noLista);
        if (getComprimentoAresta(a) == 100.0) {
            TEST_ASSERT_EQUAL_DOUBLE(30.0, getVelocidadeAresta(a));
        }
        noLista = getProximoNoLista(noLista);
    }

    liberarResultadoArvoreGeradoraMinima(r);
    liberarGrafo(g);
}

void teste_liberarResultadoArvoreGeradoraMinima_naoDeveCrashar(void) {
    Grafo g = criarGrafo();
    inserirVerticeGrafo(g,criarVertice("v1", 0.0, 0.0));
    inserirVerticeGrafo(g,criarVertice("v2", 5.0, 0.0));
    inserirArestaGrafo(g, criarAresta("v1", "v2", "CEP360", "CEP361", 10.0, 3.0, "Rua Platao"));

    ResultadoArvoreGeradoraMinima r = executarArvoreGeradoraMinima(g, 10.0);
    liberarResultadoArvoreGeradoraMinima(r);
    liberarGrafo(g);
    TEST_PASS();
}

int main() {
    UNITY_BEGIN();
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO ARVOREGERADORAMINIMA\n");
    printf("==========================================\n");

    RUN_TEST(teste_executarArvoreGeradoraMinima_grafoVazio_deveRetonarZeroArestas);
    RUN_TEST(teste_executarArvoreGeradoraMinima_verticeIsolado_naoDeveCrashar);
    RUN_TEST(teste_executarArvoreGeradoraMinima_umaAresta_vmMenorQueVl_deveModificarVM);
    RUN_TEST(teste_executarArvoreGeradoraMinima_umaAresta_vmMaiorOuIgualQueVl_naoDeveModificarVM);
    RUN_TEST(teste_executarArvoreGeradoraMinima_caminhoTriangulo_deveEscolherMenorCmp);
    RUN_TEST(teste_executarArvoreGeradoraMinima_caminhoTriangulo_naoDeveModificarArestaForaArvore);
    RUN_TEST(teste_liberarResultadoArvoreGeradoraMinima_naoDeveCrashar);

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return UNITY_END();
}
