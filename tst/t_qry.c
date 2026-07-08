//
// Created by natha on 08/07/2026.
//

#include <stdlib.h>
#include <string.h>

#include "../unity/unity.h"
#include "../include/quadra.h"
#include "../include/grafo.h"
#include "../include/lista.h"
#include "../include/vertice.h"
#include "../include/aresta.h"
#include "../include/qry.h"

void setUp(void){}
void tearDown(void) {}

static void criarArquivoQryDeTeste(const char* caminho, const char* conteudo) {
    FILE* f = fopen(caminho, "w");
    if (f != NULL) {
        fprintf(f, "%s", conteudo);
        fclose(f);
    }
}

static char* lerArquivoTexto(const char* caminho) {
    FILE* f = fopen(caminho, "r");
    if (f == NULL) return NULL;

    fseek(f, 0, SEEK_END);
    long tamanho = ftell(f);
    rewind(f);

    char* buffer = (char*) malloc(tamanho + 1);
    fread(buffer, 1, tamanho, f);
    buffer[tamanho] = '\0';
    fclose(f);
    return buffer;
}

void teste_lerComandosExecutar_deveEcoarComandoNoTxt(void) {
    char* caminhoQry = "/tmp/t_qry_1.qry";
    char* caminhoTxt = "/tmp/t_qry_1.txt";
    char* caminhoSvg = "/tmp/t_qry_1.svg";

    char* conteudoQry = "mvm 60.0 10.0 10.0 50.0 50.0\n"
                        "regs 25.5\n"
                        "exp 12.0\n";

    criarArquivoQryDeTeste(caminhoQry, conteudoQry);

    FILE* txt = fopen(caminhoTxt, "w");
    FILE* svg = fopen(caminhoSvg, "w");

    Grafo g = criarGrafo();
    Lista quadras = iniciarLista();

    lerComandosExecutar(svg, txt, caminhoQry, g, quadras);

    fclose(txt);
    fclose(svg);

    char* resultadoTxt = lerArquivoTexto(caminhoTxt);
    TEST_ASSERT_NOT_NULL(resultadoTxt);

    TEST_ASSERT_NOT_NULL(strstr(resultadoTxt, "[*] mvm 60.0 10.0 10.0 50.0 50.0"));
    TEST_ASSERT_NOT_NULL(strstr(resultadoTxt, "[*] regs 25.5"));
    TEST_ASSERT_NOT_NULL(strstr(resultadoTxt, "[*] exp 12.0"));

    free(resultadoTxt);
    remove(caminhoQry);
    remove(caminhoTxt);
    remove(caminhoSvg);
}

void teste_lerComandosExecutar_deveIgnorarLinhasVazias(void) {
    char* caminhoQry = "/tmp/t_qry_2.qry";
    char* caminhoTxt = "/tmp/t_qry_2.txt";
    char* caminhoSvg = "/tmp/t_qry_2.svg";

    char* conteudoQry = "\n\n   \n\n";
    criarArquivoQryDeTeste(caminhoQry, conteudoQry);

    FILE* txt = fopen(caminhoTxt, "w");
    FILE* svg = fopen(caminhoSvg, "w");
    Grafo g = criarGrafo();
    Lista quadras = iniciarLista();

    lerComandosExecutar(svg, txt, caminhoQry, g, quadras);

    fclose(txt);
    fclose(svg);

    char* resultadoTxt = lerArquivoTexto(caminhoTxt);
    TEST_ASSERT_NOT_NULL(resultadoTxt);

    TEST_ASSERT_NULL(strstr(resultadoTxt, "[*]"));

    free(resultadoTxt);
    remove(caminhoQry);
    remove(caminhoTxt);
    remove(caminhoSvg);
}

int main() {
    UNITY_BEGIN();
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO QRY (PARSER)\n");
    printf("==========================================\n");

    RUN_TEST(teste_lerComandosExecutar_deveEcoarComandoNoTxt);
    RUN_TEST(teste_lerComandosExecutar_deveIgnorarLinhasVazias);

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return UNITY_END();
}