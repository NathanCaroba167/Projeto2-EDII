//
// Created by natha on 08/07/2026.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../unity/unity.h"
#include "../include/quadra.h"
#include "../include/grafo.h"
#include "../include/lista.h"
#include "../include/vertice.h"
#include "../include/aresta.h"
#include "../include/geo.h"

void setUp(void) {}
void tearDown(void) {}

static void criarArquivoGeoDeTeste(const char* caminho, const char* conteudo) {
    FILE* f = fopen(caminho, "w");
    if (f != NULL) {
        fprintf(f, "%s", conteudo);
        fclose(f);
    }
}

void teste_lerGeo_deveLerQuadrasComSucesso(void) {
    char* caminho = "/tmp/t_geo_1.geo";
    char* conteudo = "q CEP01 10.0 20.0 100.0 50.0\n"
                     "q CEP02 150.0 200.0 80.0 90.0\n";

    criarArquivoGeoDeTeste(caminho, conteudo);

    Lista resultado = lerGeo(caminho);
    TEST_ASSERT_NOT_NULL(resultado);

    Nopont no = getPrimeiroNoLista(resultado);
    TEST_ASSERT_NOT_NULL(no);

    Quadra q1 = (Quadra) getItemNoLista(no);
    TEST_ASSERT_NOT_NULL(q1);

    TEST_ASSERT_EQUAL_STRING("orange", getCorPQuadra(q1));
    TEST_ASSERT_EQUAL_STRING("black", getCorBQuadra(q1));
    TEST_ASSERT_EQUAL_FLOAT(1.0, getSWQuadra(q1));

    remove(caminho);
}

void teste_lerGeo_deveMudarEstiloComComandoCQ(void) {
    char* caminho = "/tmp/t_geo_2.geo";
    char* conteudo = "cq 2.5 red blue\n"
                     "q CEP03 30.0 40.0 120.0 60.0\n";

    criarArquivoGeoDeTeste(caminho, conteudo);

    Lista resultado = lerGeo(caminho);
    TEST_ASSERT_NOT_NULL(resultado);

    Nopont no = getPrimeiroNoLista(resultado);
    TEST_ASSERT_NOT_NULL(no);

    Quadra q = (Quadra) getItemNoLista(no);
    TEST_ASSERT_NOT_NULL(q);

    TEST_ASSERT_EQUAL_FLOAT(2.5, getSWQuadra(q));
    TEST_ASSERT_EQUAL_STRING("red", getCorPQuadra(q));
    TEST_ASSERT_EQUAL_STRING("blue", getCorBQuadra(q));

    remove(caminho);
}

void teste_lerGeo_deveIgnorarLinhasVaziasEComandosDesconhecidos(void) {
    char* caminho = "/tmp/t_geo_3.geo";
    char* conteudo = "\n"
                     "   \n"
                     "xyz 1 2 3\n"
                     "q CEP04 0.0 0.0 10.0 10.0\n";

    criarArquivoGeoDeTeste(caminho, conteudo);

    Lista resultado = lerGeo(caminho);
    TEST_ASSERT_NOT_NULL(resultado);

    Nopont no = getPrimeiroNoLista(resultado);
    TEST_ASSERT_NOT_NULL(no);
    Quadra q = (Quadra) getItemNoLista(no);
    TEST_ASSERT_NOT_NULL(q);

    remove(caminho);
}

int main() {
    UNITY_BEGIN();
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO GEO\n");
    printf("==========================================\n");

    RUN_TEST(teste_lerGeo_deveLerQuadrasComSucesso);
    RUN_TEST(teste_lerGeo_deveMudarEstiloComComandoCQ);
    RUN_TEST(teste_lerGeo_deveIgnorarLinhasVaziasEComandosDesconhecidos);

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return UNITY_END();
}