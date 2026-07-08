//
// Created by natha on 03/12/2025.
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
#include "../include/svg.h"

void setUp(void) {}
void tearDown(void) {}

static char* lerArquivo(const char* caminho) {
    FILE* f = fopen(caminho, "r");
    if (f == NULL) {
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    long tamanho = ftell(f);
    rewind(f);

    char* buffer = (char*) malloc(tamanho + 1);
    if (buffer == NULL) {
        fclose(f);
        return NULL;
    }
    fread(buffer, 1, tamanho, f);
    buffer[tamanho] = '\0';
    fclose(f);
    return buffer;
}

void teste_abrirSVG_deveCriarArquivo(void) {
    char* caminho = "/tmp/t_svg_1.svg";

    Arquivo svg = abrirSVG(caminho);
    TEST_ASSERT_NOT_NULL(svg);
    fecharSVG(svg);

    FILE* f = fopen(caminho, "r");
    TEST_ASSERT_NOT_NULL(f);
    fclose(f);
}

void teste_inicializarSVG_deveEscreverCabecalhoSVG(void) {
    char* caminho = "/tmp/t_svg_2.svg";

    Arquivo svg = abrirSVG(caminho);
    inicializarSVG(svg);
    fecharSVG(svg);

    char* conteudo = lerArquivo(caminho);
    TEST_ASSERT_NOT_NULL(conteudo);
    TEST_ASSERT_NOT_NULL(strstr(conteudo, "<?xml"));
    TEST_ASSERT_NOT_NULL(strstr(conteudo, "<svg"));
    free(conteudo);
}

void teste_fecharSVG_deveEscreverTagFechamentoSVG(void) {
    char* caminho = "/tmp/t_svg_3.svg";

    Arquivo svg = abrirSVG(caminho);
    inicializarSVG(svg);
    fecharSVG(svg);

    char* conteudo = lerArquivo(caminho);
    TEST_ASSERT_NOT_NULL(conteudo);
    TEST_ASSERT_NOT_NULL(strstr(conteudo, "</svg>"));
    free(conteudo);
}

void teste_desenharQuadraSVG_deveDesenharQuadraCorretamente(void) {
    char* caminho = "/tmp/t_svg_4.svg";

    Arquivo svg = abrirSVG(caminho);
    inicializarSVG(svg);

    Quadra q = criarQuadra("cep1", 10.0, 20.0, 100.0, 50.0);
    setCorBQuadra(q, "black");
    setCorPQuadra(q, "blue");
    desenharQuadraSVG(svg, q);

    fecharSVG(svg);
    liberarQuadra(q);

    char* conteudo = lerArquivo(caminho);
    TEST_ASSERT_NOT_NULL(conteudo);
    TEST_ASSERT_NOT_NULL(strstr(conteudo, "<rect"));
    TEST_ASSERT_NOT_NULL(strstr(conteudo, "cep1"));
    free(conteudo);
}

void teste_desenharArestaSVG_deveDesenharArestaCorretamente(void) {
    char* caminho = "/tmp/t_svg_5.svg";

    Arquivo svg = abrirSVG(caminho);
    inicializarSVG(svg);

    Aresta a = criarAresta("v1", "v2", "CEP106", "CEP103", 10.0, 50.0, "Rua Faria");
    desenharArestaSVG(svg,a);

    fecharSVG(svg);
    liberarAresta(a);

    char* conteudo = lerArquivo(caminho);
    TEST_ASSERT_NOT_NULL(conteudo);
    TEST_ASSERT_NOT_NULL(strstr(conteudo, "<line"));
    free(conteudo);
}

void teste_desenharBoundingBoxComponenteSVG_deveDesenharBoxCorretamente(void) {
    char* caminho = "/tmp/t_svg_6.svg";
    Arquivo svg = abrirSVG(caminho);
    inicializarSVG(svg);

    desenharBoundingBoxComponenteSVG(svg, 10.0, 10.0, 200.0, 150.0, "blue");

    fecharSVG(svg);

    char* conteudo = lerArquivo(caminho);
    TEST_ASSERT_NOT_NULL(conteudo);
    TEST_ASSERT_NOT_NULL(strstr(conteudo, "<rect"));
    TEST_ASSERT_NOT_NULL(strstr(conteudo, "0.5"));
    TEST_ASSERT_NOT_NULL(strstr(conteudo, "blue"));
    free(conteudo);
}

void teste_desenharArestaArvoreGeradoraMinimaSVG_deveDesenharArestaCorretamente(void) {
    char* caminho = "/tmp/t_svg_7.svg";

    Arquivo svg = abrirSVG(caminho);
    inicializarSVG(svg);

    Aresta a = criarAresta("v1", "v2", "CEP106", "CEP103", 10.0, 50.0, "Rua Faria");
    desenharArestaArvoreGeradoraMinimaSVG(svg,a);

    fecharSVG(svg);
    liberarAresta(a);

    char* conteudo = lerArquivo(caminho);
    TEST_ASSERT_NOT_NULL(conteudo);
    TEST_ASSERT_NOT_NULL(strstr(conteudo, "<line"));
    TEST_ASSERT_NOT_NULL(strstr(conteudo, "red"));
    free(conteudo);
}

void teste_desenharPercursoSVG_deveDesenharPercursoCorretamenteSVG(void) {
    char* caminho = "/tmp/t_svg_8.svg";

    Arquivo svg = abrirSVG(caminho);
    inicializarSVG(svg);

    Grafo g = criarGrafo();
    inserirVerticeGrafo(g, criarVertice("v1", 0.0, 0.0));
    inserirVerticeGrafo(g, criarVertice("v2", 50.0, 50.0));
    inserirArestaGrafo(g,  criarAresta("v1", "v2", "CEP146", "CEP163", 40.0, 60.0, "Rua Augusta"));

    Vertice v1 = getVerticesGrafo(g, "v1");
    Lista lAresta = getArestasVertice(v1);
    Nopont noLista = getPrimeiroNoLista(lAresta);
    Aresta a = (Aresta) getItemNoLista(noLista);

    Lista percurso = iniciarLista();
    inserirListaFim(percurso, a);

    desenharPercursoSVG(svg, g, 0.0, 0.0, percurso, "blue", 0);

    fecharSVG(svg);
    liberarLista(percurso);
    liberarGrafo(g);

    char* conteudo = lerArquivo(caminho);
    TEST_ASSERT_NOT_NULL(conteudo);
    TEST_ASSERT_NOT_NULL(strstr(conteudo, "<path"));
    TEST_ASSERT_NOT_NULL(strstr(conteudo, "animateMotion"));
    free(conteudo);
}

void teste_desenharMarcadorSVG_deveDesenharMarcadorI(void) {
    char* caminho = "/tmp/t_svg_9.svg";

    Arquivo svg = abrirSVG(caminho);
    inicializarSVG(svg);

    desenharMarcadorSVG(svg, 10.0, 10.0, 'I', "green");

    fecharSVG(svg);

    char* conteudo = lerArquivo(caminho);
    TEST_ASSERT_NOT_NULL(conteudo);
    TEST_ASSERT_NOT_NULL(strstr(conteudo, "I"));
    TEST_ASSERT_NOT_NULL(strstr(conteudo, "green"));
    free(conteudo);
}

void teste_desenharMarcadorSVG_deveDesenharMarcadorF(void) {
    char* caminho = "/tmp/t_svg_10.svg";

    Arquivo svg = abrirSVG(caminho);
    inicializarSVG(svg);

    desenharMarcadorSVG(svg, 100.0, 100.0, 'F', "red");

    fecharSVG(svg);

    char* conteudo = lerArquivo(caminho);
    TEST_ASSERT_NOT_NULL(conteudo);
    TEST_ASSERT_NOT_NULL(strstr(conteudo, "F"));
    TEST_ASSERT_NOT_NULL(strstr(conteudo, "red"));
    free(conteudo);
}

int main() {
    UNITY_BEGIN();
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO SVG\n");
    printf("==========================================\n");

    RUN_TEST(teste_abrirSVG_deveCriarArquivo);
    RUN_TEST(teste_inicializarSVG_deveEscreverCabecalhoSVG);
    RUN_TEST(teste_fecharSVG_deveEscreverTagFechamentoSVG);
    RUN_TEST(teste_desenharQuadraSVG_deveDesenharQuadraCorretamente);
    RUN_TEST(teste_desenharArestaSVG_deveDesenharArestaCorretamente);
    RUN_TEST(teste_desenharBoundingBoxComponenteSVG_deveDesenharBoxCorretamente);
    RUN_TEST(teste_desenharArestaArvoreGeradoraMinimaSVG_deveDesenharArestaCorretamente);
    RUN_TEST(teste_desenharPercursoSVG_deveDesenharPercursoCorretamenteSVG);
    RUN_TEST(teste_desenharMarcadorSVG_deveDesenharMarcadorI);
    RUN_TEST(teste_desenharMarcadorSVG_deveDesenharMarcadorF);

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return UNITY_END();
}