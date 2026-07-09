//
// Created by natha on 22/06/2026.
//

#include <stdlib.h>
#include <string.h>

#include "../unity/unity.h"

#include "../include/grafo.h"
#include "../include/vertice.h"
#include "../include/lista.h"
#include "../include/componentes.h"

void setUp(void){}
void tearDown(void) {}

static int totalVerticesEmComponentes(ResultadoComponentes r) {
    int total = 0;
    for (int i = 0; i < getNumComponentes(r); i++) {
        total += getTamanhoLista(getVerticesComponentes(r, i));
    }
    return total;
}

static int componenteDoVertice(ResultadoComponentes r, const char* id) {
    for (int i = 0; i < getNumComponentes(r); i++) {
        Lista comp = getVerticesComponentes(r, i);
        Nopont noLista = getPrimeiroNoLista(comp);
        while (noLista != NULL) {
            Vertice v = (Vertice) getItemNoLista(noLista);
            if (strcmp(getIDVertice(v), id) == 0) return i;
            noLista = getProximoNoLista(noLista);
        }
    }
    return -1;
}

void teste_executarComponentes_grafoVazio_deveRetornarZeroComponentes(void) {
    Grafo g = criarGrafo(0);

    ResultadoComponentes r = executarComponentes(g, 0.0);

    TEST_ASSERT_EQUAL_INT(0, getNumComponentes(r));

    liberarResultadoComponentes(r);
    liberarGrafo(g);
}

void teste_executarComponentes_umVerticeApenas_deveRetornarUmComponente(void) {
    Grafo g = criarGrafo(1);
    inserirVerticeGrafo(g, criarVertice("v1", 0.0, 0.0, 0));

    ResultadoComponentes r = executarComponentes(g, 0.0);

    TEST_ASSERT_EQUAL_INT(1, getNumComponentes(r));
    TEST_ASSERT_EQUAL_INT(1, getTamanhoLista(getVerticesComponentes(r,0)));

    liberarResultadoComponentes(r);
    liberarGrafo(g);
}

void teste_executarComponentes_grafoConexo_deveRetornarUmComponente(void) {
    Grafo g = criarGrafo(3);
    inserirVerticeGrafo(g, criarVertice("v1", 0.0, 0.0, 0));
    inserirVerticeGrafo(g, criarVertice("v2", 5.0, 0.0, 1));
    inserirVerticeGrafo(g, criarVertice("v3", 10.0, 0.0, 2));
    inserirArestaGrafo(g, "v1", "v2", "CEP405", "CEP412", 40.0, 10.0, "Rua Santa Monica");
    inserirArestaGrafo(g, "v2", "v3", "CEP444", "CEP417", 40.0, 10.0, "Rua Santa Angela");

    ResultadoComponentes r = executarComponentes(g, 5.0);

    TEST_ASSERT_EQUAL_INT(1, getNumComponentes(r));
    TEST_ASSERT_EQUAL_INT(3, totalVerticesEmComponentes(r));

    liberarResultadoComponentes(r);
    liberarGrafo(g);
}

void teste_executarComponentes_verticeIsolado_deveGerarDoisComponentes(void) {
    Grafo g = criarGrafo(3);
    inserirVerticeGrafo(g, criarVertice("v1", 0.0, 0.0, 0));
    inserirVerticeGrafo(g, criarVertice("v2", 5.0, 0.0, 1));
    inserirVerticeGrafo(g, criarVertice("v3", 10.0, 0.0, 2));
    inserirArestaGrafo(g, "v1", "v2", "CEP409", "CEP418", 50.0, 10.0, "Rua Julia");

    ResultadoComponentes r = executarComponentes(g, 5.0);

    TEST_ASSERT_EQUAL_INT(2, getNumComponentes(r));
    TEST_ASSERT_EQUAL_INT(3, totalVerticesEmComponentes(r));

    int comp1 = componenteDoVertice(r, "v1");
    int comp2 = componenteDoVertice(r, "v2");
    int comp3 = componenteDoVertice(r, "v3");

    TEST_ASSERT_NOT_EQUAL(-1, comp1);
    TEST_ASSERT_EQUAL_INT(comp1, comp2);
    TEST_ASSERT_NOT_EQUAL(comp1, comp3);

    liberarResultadoComponentes(r);
    liberarGrafo(g);
}

void teste_executarComponentes_verificaVL_deveSepararQuandoVMInsuficiente(void) {
    Grafo g = criarGrafo(2);
    inserirVerticeGrafo(g, criarVertice("v1", 0.0, 0.0, 0));
    inserirVerticeGrafo(g, criarVertice("v2", 5.0, 0.0, 1));
    inserirArestaGrafo(g, "v1", "v2", "CEP286", "CEP589", 60.0, 5.0, "Rua Rebeca");

    ResultadoComponentes r1 = executarComponentes(g, 5.0);
    ResultadoComponentes r2 = executarComponentes(g, 6.0);

    TEST_ASSERT_EQUAL_INT(1, getNumComponentes(r1));
    TEST_ASSERT_EQUAL_INT(2, getNumComponentes(r2));

    liberarResultadoComponentes(r1);
    liberarResultadoComponentes(r2);
    liberarGrafo(g);
}

void teste_executarComponentes_grafoMaoUnica_deveSerFracamenteConexo(void) {
    Grafo g = criarGrafo(2);
    inserirVerticeGrafo(g, criarVertice("v1", 0.0, 0.0, 0));
    inserirVerticeGrafo(g, criarVertice("v2", 5.0, 0.0, 1));
    inserirArestaGrafo(g, "v1", "v2", "CEP742", "CEP157", 80.0, 10.0, "Rua Giovanna");

    ResultadoComponentes r = executarComponentes(g, 5.0);

    TEST_ASSERT_EQUAL_INT(1, getNumComponentes(r));

    int comp1 = componenteDoVertice(r, "v1");
    int comp2 = componenteDoVertice(r, "v2");
    TEST_ASSERT_EQUAL_INT(comp1, comp2);

    liberarResultadoComponentes(r);
    liberarGrafo(g);
}

void teste_executarComponentes_tresGruposSeparados_deveGerarTresComponentes(void) {
    Grafo g = criarGrafo(5);
    inserirVerticeGrafo(g, criarVertice("v1", 0.0, 0.0, 0));
    inserirVerticeGrafo(g, criarVertice("v2", 5.0, 0.0, 1));
    inserirVerticeGrafo(g, criarVertice("v3", 10.0, 0.0, 2));
    inserirVerticeGrafo(g, criarVertice("v4", 15.0, 0.0, 3));
    inserirVerticeGrafo(g, criarVertice("v5", 20.0, 0.0, 4));
    inserirArestaGrafo(g,"v1", "v2", "CEP390", "CEP391", 30.0, 10.0, "Rua Isabelle");
    inserirArestaGrafo(g, "v3", "v4", "CEP419", "CEP420", 30.0, 10.0, "Rua Ana");

    ResultadoComponentes r = executarComponentes(g, 5.0);

    TEST_ASSERT_EQUAL_INT(3, getNumComponentes(r));
    TEST_ASSERT_EQUAL_INT(5, totalVerticesEmComponentes(r));

    int comp1 = componenteDoVertice(r, "v1");
    int comp2 = componenteDoVertice(r, "v2");
    int comp3 = componenteDoVertice(r, "v3");
    int comp4 = componenteDoVertice(r, "v4");
    int comp5 = componenteDoVertice(r, "v5");

    TEST_ASSERT_EQUAL_INT(comp1, comp2);
    TEST_ASSERT_EQUAL_INT(comp3, comp4);
    TEST_ASSERT_NOT_EQUAL(comp1, comp3);
    TEST_ASSERT_NOT_EQUAL(comp1, comp5);
    TEST_ASSERT_NOT_EQUAL(comp3, comp5);

    liberarResultadoComponentes(r);
    liberarGrafo(g);
}

void teste_liberarResultadoComponentes_naoDeveCrashar(void) {
    Grafo g = criarGrafo(1);
    inserirVerticeGrafo(g,criarVertice("v1", 0.0, 0.0, 0));
    ResultadoComponentes r = executarComponentes(g, 0.0);
    liberarResultadoComponentes(r);
    liberarGrafo(g);
    TEST_PASS();
}

int main() {
    UNITY_BEGIN();
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO COMPONENTES\n");
    printf("==========================================\n");

    RUN_TEST(teste_executarComponentes_grafoVazio_deveRetornarZeroComponentes);
    RUN_TEST(teste_executarComponentes_umVerticeApenas_deveRetornarUmComponente);
    RUN_TEST(teste_executarComponentes_grafoConexo_deveRetornarUmComponente);
    RUN_TEST(teste_executarComponentes_verticeIsolado_deveGerarDoisComponentes);
    RUN_TEST(teste_executarComponentes_verificaVL_deveSepararQuandoVMInsuficiente);
    RUN_TEST(teste_executarComponentes_grafoMaoUnica_deveSerFracamenteConexo);
    RUN_TEST(teste_executarComponentes_tresGruposSeparados_deveGerarTresComponentes);
    RUN_TEST(teste_liberarResultadoComponentes_naoDeveCrashar);

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return UNITY_END();
}