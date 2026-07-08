//
// Created by natha on 22/06/2026.
//

#include <stdlib.h>

#include "../unity/unity.h"
#include "../include/quadra.h"
#include "../include/grafo.h"
#include "../include/lista.h"
#include "../include/vertice.h"
#include "../include/aresta.h"
#include "../include/via.h"

void setUp(void){}
void tearDown(void) {}

static void criarArquivoViaDeTeste(const char* caminho, const char* conteudo) {
    FILE* f = fopen(caminho, "w");
    if (f != NULL) {
        fprintf(f, "%s", conteudo);
        fclose(f);
    }
}

void teste_lerVia_deveInserirVerticesComSucesso(void) {
    char* caminho = "/tmp/t_via_1.via";
    char* conteudo = "v V10 10.5 20.5\n"
                     "v V20 100.0 200.0\n";

    criarArquivoViaDeTeste(caminho, conteudo);

    Grafo g = lerVia(caminho);
    TEST_ASSERT_NOT_NULL(g);

    Vertice v1 = getVerticesGrafo(g, "V10");
    Vertice v2 = getVerticesGrafo(g, "V20");

    TEST_ASSERT_NOT_NULL(v1);
    TEST_ASSERT_NOT_NULL(v2);

    remove(caminho);
}

void teste_lerVia_deveInserirArestasETratarHifens(void) {
    char* caminho = "/tmp/t_via_2.via";
    char* conteudo = "v v1 0.0 0.0\n"
                     "v v2 10.0 10.0\n"
                     "e v1 v2 CEP_DIR - 50.0 60.0 RuaAugusta\n";

    criarArquivoViaDeTeste(caminho, conteudo);

    Grafo g = lerVia(caminho);
    TEST_ASSERT_NOT_NULL(g);

    Vertice v1 = getVerticesGrafo(g, "v1");
    TEST_ASSERT_NOT_NULL(v1);

    Lista lArestas = getArestasVertice(v1);
    TEST_ASSERT_NOT_NULL(lArestas);

    Nopont no = getPrimeiroNoLista(lArestas);
    TEST_ASSERT_NOT_NULL(no);

    Aresta a = (Aresta) getItemNoLista(no);
    TEST_ASSERT_NOT_NULL(a);

    remove(caminho);
}

void teste_lerVia_deveIgnorarLinhasVaziasEComandosDesconhecidos(void) {
    char* caminho = "/tmp/t_via_3.via";
    char* conteudo = "\n"
                     "\r\n"
                     "   \n"
                     "e_invalido v1 v2\n"
                     "v V30 5.0 5.0\n";

    criarArquivoViaDeTeste(caminho, conteudo);

    Grafo g = lerVia(caminho);
    TEST_ASSERT_NOT_NULL(g);

    Vertice v3 = getVerticesGrafo(g, "V30");
    TEST_ASSERT_NOT_NULL(v3);

    remove(caminho);
}

int main() {
    UNITY_BEGIN();
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO VIA (GRAFO)\n");
    printf("==========================================\n");

    RUN_TEST(teste_lerVia_deveInserirVerticesComSucesso);
    RUN_TEST(teste_lerVia_deveInserirArestasETratarHifens);
    RUN_TEST(teste_lerVia_deveIgnorarLinhasVaziasEComandosDesconhecidos);

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return UNITY_END();
}